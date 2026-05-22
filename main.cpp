#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] =
{
	-0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,     0.70f, 0.60f, 0.35f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,     0.70f, 0.60f, 0.35f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,     0.70f, 0.60f, 0.35f,	1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,     0.70f, 0.60f, 0.35f,	0.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,     0.75f, 0.62f, 0.40f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,     0.75f, 0.62f, 0.40f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,     0.75f, 0.62f, 0.40f,	1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,     0.75f, 0.62f, 0.40f,	0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,     0.90f, 0.78f, 0.55f,	0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,     0.90f, 0.78f, 0.55f,	1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,     0.90f, 0.78f, 0.55f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,     0.90f, 0.78f, 0.55f,	0.0f, 1.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,

	4, 6, 5,
	4, 7, 6,

	8, 9, 10,
	8, 10, 11,

	12, 14, 13,
	12, 15, 14,

	16, 17, 18,
	16, 18, 19,

	20, 22, 21,
	20, 23, 22
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Cube OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniID, 0.5f);
		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
