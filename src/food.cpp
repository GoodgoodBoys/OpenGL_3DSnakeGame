#include "food.hpp"

#include <iostream>
#include <random>

Food::Food(float unit = 1.0f) : _unitSize(unit) {
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
}

Food::~Food() {};

std::pair<int, int> Food::newPosition(std::vector<std::pair<int, int>> snakeBody, std::vector<int> map)
{
	std::pair<int, int> targetPosition;

	for (int i = 0; i < snakeBody.size() - 1; i++) {
		map.at(snakeBody.at(i).first + snakeBody.at(i).second * 10) = 1;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 9);

	do
	{
		targetPosition.first = distrib(gen);
		targetPosition.second = distrib(gen);
	} while (1 == map.at(targetPosition.first + targetPosition.second * 10));

	std::cout << "targetPosition = " << targetPosition.first << targetPosition.second << std::endl;
	_position = targetPosition;
	return targetPosition;
}

std::pair<int, int> Food::getPosition() { return _position; }

void Food::update(std::vector<std::pair<int, int>> snakeBody, std::vector<int> map)
{
	newPosition(snakeBody, map);

	float floorVertices[] = {
	_position.first, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,

	_position.first, _position.second, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, 1.0f, 0.0f, 0.0f, 1.0f,

	_position.first, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,

	_position.first + _unitSize, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,

	_position.first, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second, _unitSize, 0.0f, 0.0f, 1.0f,

	_position.first, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,
	_position.first, _position.second + _unitSize, 1.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, 0.0f, 0.0f, 0.0f, 1.0f,
	_position.first + _unitSize, _position.second + _unitSize, _unitSize, 0.0f, 0.0f, 1.0f,
	};

	if (!glIsVertexArray(_VAO.first) || (0 == _VAO.first))
		glGenVertexArrays(1, &(_VAO.first));

	if (glIsBuffer(_VAO.second) || (0 == _VAO.second))
		glGenBuffers(1, &(_VAO.second));

	glBindVertexArray(_VAO.first);

	glBindBuffer(GL_ARRAY_BUFFER, _VAO.second);
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

void Food::draw() 
{
	glBindVertexArray(_VAO.first);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

