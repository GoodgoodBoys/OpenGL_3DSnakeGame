#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <learnopengl/shader_s.h>

#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include "snake.hpp"
#include "map.hpp"
#include "food.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int leight);
void processInput(GLFWwindow* window, Direction& direction);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 15.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int mapWidth = 10;
std::vector<int> mapDesign = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("D:/VSCode/VSCodeProject/OpenGL/practice/snakeGame/src/shader/4.1.texture.vs", "D:/VSCode/VSCodeProject/OpenGL/practice/snakeGame/src/shader/4.1.texture.fs");


	//unsigned int texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//int width, height, nrChannels;
	//unsigned char* data = stbi_load("D:/VSCode/VSCodeProject/OpenGL/test/Project2/resource/textures/wolien.jpg", &width, &height, &nrChannels, 0);
	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//stbi_image_free(data);


	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	
	Snake snake(4, 2, 4, 1, Direction::UP);
	snake.targetUpdate(false);
	Map map(mapWidth, mapDesign);
	Food food(1.0f);
	food.update(snake.getBody(), map.getMap());

	float offset = 0.0f;
	Direction direction = UP;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window, direction);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, /*(float)glfwGetTime() * */glm::radians(0.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		unsigned int transformModel = glGetUniformLocation(ourShader.ID, "model");
		glUniformMatrix4fv(transformModel, 1, GL_FALSE, glm::value_ptr(model));
		unsigned int transformView = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(transformView, 1, GL_FALSE, glm::value_ptr(view));
		unsigned int transformProj = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(transformProj, 1, GL_FALSE, glm::value_ptr(projection));

		ourShader.use();

		if (offset < 1.0f) 
		{
			offset += 0.001f;
			snake.movingUpdate(offset, false);
		
		}
		else
		{
			snake.arriveNewPosition();
			snake.changeDir(direction);
			if (snake.isSnakeEaten(food.getPosition())) {
				snake.targetUpdate(true);
				std::cout << "update" << std::endl;
				snake.update();
				std::cout << "food" << std::endl;
				food.update(snake.getBody(), map.getMap());
			}
			else
			{
				snake.targetUpdate(false);
			}
			offset = 0.0f;
			snake.movingUpdate(offset, false);
			

		}

		// Draw 
		snake.draw();
		map.draw();
		food.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window, Direction& direction)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 1.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		direction = UP;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		direction = DOWN;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		direction = LEFT;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		direction = RIGHT;


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
