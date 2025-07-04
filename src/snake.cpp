#include "snake.hpp"

Snake::Snake(int initalLength, int initalPositionX, int initalPositionY, float unitSize, Direction initialDirection) 
{
	_alive = true;
	_bodyLength = 0;
	_unitSize = unitSize;
	_movingDirection = initialDirection;

	_body.push_back(std::make_pair(initalPositionX, initalPositionY));
	++_bodyLength;
	while (_body.size() < initalLength) {
		auto [x, y] = _body.back();
		if (_movingDirection == UP) 
			_body.push_back({ x, y - 1 });
		else if (_movingDirection == LEFT)
			_body.push_back({ x + 1, y });
		else if (_movingDirection == DOWN)
			_body.push_back({ x, y + 1 });
		else 
			_body.push_back({ x - 1, y });
		++_bodyLength;
	}

	_bodyNew = _body;

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

Snake::~Snake() {}

void Snake::update() {
	_VAO.resize(_bodyLength);

	for (int i = 0; i < _bodyLength; ++i) {
		float vertices[] = {
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 0.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_bodyNew.at(i).first + 1.0f, _bodyNew.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		};

		if (!glIsVertexArray(_VAO.at(i).first) || (0 == _VAO.at(i).first)) {
			std::cout << "new" << std::endl;
			glGenVertexArrays(1, &(_VAO.at(i).first));
		
		}
			

		if(glIsBuffer(_VAO.at(i).second) || (0 == _VAO.at(i).second))
			glGenBuffers(1, &(_VAO.at(i).second));

		glBindVertexArray(_VAO.at(i).first);

		glBindBuffer(GL_ARRAY_BUFFER, _VAO.at(i).second);
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

void Snake::draw()
{
	glBindVertexArray(_VAOHeadMoving.first);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i < _bodyLength; ++i) {
		glBindVertexArray(_VAO.at(i).first);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void Snake::targetUpdate(bool prolong) {

	if (prolong) {
		_body.push_back(std::make_pair(_bodyNew.at(_bodyLength - 1).first, _bodyNew.at(_bodyLength - 1).second));
		_bodyLength++;
	}
	_bodyNew = _body;

	for (int i = static_cast<int>(_bodyNew.size() - 1); i > 0; i--) {
		_bodyNew.at(i) = _bodyNew.at(i - 1);
	}
	switch (_movingDirection) {
	case Direction::UP:
		_bodyNew.at(0).second++;
		break;
	case Direction::LEFT:
		_bodyNew.at(0).first--;
		break;
	case Direction::DOWN:
		_bodyNew.at(0).second--;
		break;
	case Direction::RIGHT:
		_bodyNew.at(0).first++;
		break;
	}
}

void Snake::arriveNewPosition()
{
	_body = _bodyNew;
	_bodyLength = _body.size();
}

std::vector<std::pair<int, int>> Snake::getBody() 
{
	return _body;
}

void Snake::changeDir(Direction dir) {
	_movingDirection = dir;
}

void Snake::movingUpdate(float processCount, bool prolong) 
{
	float offsetHead[2] = {0};
	if (_movingDirection == UP)
		offsetHead[1] = processCount;
	else if (_movingDirection == DOWN)
		offsetHead[1] = -processCount;
	else if (_movingDirection == LEFT)
		offsetHead[0] = -processCount;
	else if (_movingDirection == RIGHT)
		offsetHead[0] = processCount;

	float verticesHead[] = {
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,

		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 0.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 0.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(0).first + 1.0f + offsetHead[0], _body.at(0).second + 1.0f + offsetHead[1], 1.0f, 1.0f, 0.0f, 0.0f,
	};

	if (!glIsVertexArray(_VAOHeadMoving.first) || (0 == _VAOHeadMoving.first))
		glGenVertexArrays(1, &(_VAOHeadMoving.first));

	if (glIsBuffer(_VAOHeadMoving.second) || (0 == _VAOHeadMoving.second))
		glGenBuffers(1, &(_VAOHeadMoving.second));

	glBindVertexArray(_VAOHeadMoving.first);

	glBindBuffer(GL_ARRAY_BUFFER, _VAOHeadMoving.second);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHead), verticesHead, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	float offsetTail[2] = { (_body.at(_bodyLength - 2).first - _body.at(_bodyLength - 1).first) * processCount,
		(_body.at(_bodyLength - 2).second - _body.at(_bodyLength - 1).second) * processCount };

	float verticesTail[] = {
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,

		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 0.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 0.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(_bodyLength - 1).first + 1.0f + offsetTail[0], _body.at(_bodyLength - 1).second + 1.0f + offsetTail[1], 1.0f, 1.0f, 0.0f, 0.0f,
	};

	if (!glIsVertexArray(_VAO.at(_bodyLength - 1).first) || (0 == _VAO.at(_bodyLength - 1).first))
		glGenVertexArrays(1, &(_VAO.at(_bodyLength - 1).first));

	if (glIsBuffer(_VAO.at(_bodyLength - 1).second) || (0 == _VAO.at(_bodyLength - 1).second))
		glGenBuffers(1, &(_VAO.at(_bodyLength - 1).second));

	glBindVertexArray(_VAO.at(_bodyLength - 1).first);

	glBindBuffer(GL_ARRAY_BUFFER, _VAO.at(_bodyLength - 1).second);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTail), verticesTail, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	for (int i = 0; i < _bodyLength - 1; ++i) {
		float vertices[] = {
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 0.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		_body.at(i).first + 1.0f, _body.at(i).second + 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		};

		if (!glIsVertexArray(_VAO.at(i).first) || (0 == _VAO.at(i).first))
			glGenVertexArrays(1, &(_VAO.at(i).first));

		if (glIsBuffer(_VAO.at(i).second) || (0 == _VAO.at(i).second))
			glGenBuffers(1, &(_VAO.at(i).second));

		glBindVertexArray(_VAO.at(i).first);

		glBindBuffer(GL_ARRAY_BUFFER, _VAO.at(i).second);
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

bool Snake::isSnakeEaten(std::pair<int, int> foodPosition)
{
	if (_body.at(0) == foodPosition)
		return true;
	return false;
}
