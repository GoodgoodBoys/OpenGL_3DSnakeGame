#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Map 
{
public:
	Map(int width, std::vector<int> map);
	~Map();
	void update();
	void draw();
	std::vector<int> getMap();

private:
	int _width;
	int _size;
	std::vector<int> _map;

	unsigned int _EBO;
	std::vector<std::pair<unsigned int, unsigned int>> _VAO;
	std::pair<unsigned int, unsigned int> floorVAO;
};

