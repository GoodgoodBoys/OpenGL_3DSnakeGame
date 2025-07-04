#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction { UP, LEFT, DOWN, RIGHT };

class Snake {
public:
	Snake(int initalLength, int initalPositionX, int initalPositionY, float unitSize, Direction initialDirection);
	~Snake();
	void update();
	void draw();
	void targetUpdate(bool prolong);
	std::vector<std::pair<int, int>> getBody();
	void changeDir(Direction dir);
	void movingUpdate(float processCount, bool prolong);
	void arriveNewPosition();
	bool isSnakeEaten(std::pair<int, int> foodPosition);

private:
	bool _alive;

	int _bodyLength;
	float _unitSize;
	Direction _movingDirection;

	unsigned int _EBO;

	std::vector<std::pair<int, int>> _body;
	std::vector<std::pair<int, int>> _bodyNew;
	std::vector<std::pair<unsigned int, unsigned int>> _VAO;
	std::pair<unsigned int, unsigned int> _VAOHeadMoving;
	

};