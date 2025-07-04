#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Food {
public:
	Food(float unit);
	~Food();
	std::pair<int, int> newPosition(std::vector<std::pair<int, int>> snakeBody, std::vector<int> map);
	std::pair<int, int> getPosition();
	void update(std::vector<std::pair<int, int>> snakeBody, std::vector<int> map);
	void draw();

private:
	std::pair<int, int> _position;
	float _unitSize;

	std::pair<unsigned int, unsigned int> _VAO;
	unsigned int _EBO;
};

