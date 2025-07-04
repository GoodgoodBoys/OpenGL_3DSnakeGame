#include "map.hpp"

#include <string>

Map::Map(int width, std::vector<int> map)
{
	if (map.size() != width * width) {
		std::string errInfo = "[Map] Width: " + std::to_string(width) + " don't fit map size.";
		throw std::invalid_argument(errInfo);
	}
	_width = width;
	_map = map;
	_size = map.size();

	unsigned int indices[] = {
	0, 1, 2,
	3, 4, 5,

	6, 7, 8,
	9, 10, 11,

	12, 13, 14,
	15, 16, 17,

	18, 19, 20,
	21, 22, 23,

	24, 25, 26,
	27, 28, 29,

	30, 31, 32,
	33, 34, 35,
	};

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	update();
}

Map::~Map() {}

void Map::update()
{
	_VAO.resize(_size);
	
	for (int i = 0; i < _width; ++i) {
		for (int j = 0; j < _width; ++j) {
			if (_map.at(i * _width + j) != 1)
				continue;

			float vertices[] = {
			i + 0.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

			i + 0.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

			i + 0.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

			i + 1.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

			i + 0.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

			i + 0.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			i + 0.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			i + 1.0f, j + 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			};

			if (!glIsVertexArray(_VAO.at(i * _width + j).first) || (0 == _VAO.at(i * _width + j).first))
				glGenVertexArrays(1, &(_VAO.at(i * _width + j).first));

			if (glIsBuffer(_VAO.at(i * _width + j).second) || (0 == _VAO.at(i * _width + j).second))
				glGenBuffers(1, &(_VAO.at(i * _width + j).second));

			glBindVertexArray(_VAO.at(i * _width + j).first);

			glBindBuffer(GL_ARRAY_BUFFER, _VAO.at(i * _width + j).second);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

			// Position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// Color
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);
		}
	}

	float floorVertices[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
		static_cast<float>(_width), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
		static_cast<float>(_width), static_cast<float>(_width), 0.0f, 0.0f, 0.0f, 0.0f,
		static_cast<float>(_width), static_cast<float>(_width), 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, static_cast<float>(_width), 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	};

	if (!glIsVertexArray(floorVAO.first) || (0 == floorVAO.first))
		glGenVertexArrays(1, &(floorVAO.first));

	if (glIsBuffer(floorVAO.second) || (0 == floorVAO.second))
		glGenBuffers(1, &(floorVAO.second));

	glBindVertexArray(floorVAO.first);

	glBindBuffer(GL_ARRAY_BUFFER, floorVAO.second);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
}

void Map::draw() 
{
	for (std::pair VAO : _VAO)
	{
		glBindVertexArray(VAO.first);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	glBindVertexArray(floorVAO.first);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

std::vector<int> Map::getMap()
{
	return _map;
}
