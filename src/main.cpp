/* C Standard Library */
#include <cstdlib>

/* C++ Standard Library */
#include <fstream>
#include <iostream>
#include <vector>

/* OpenGL */
#include <glad/glad.h> /* Modern OpenGL */
#include <GLFW/glfw3.h> /* Legacy OpenGL */

/* From this project */
#include <my/GL.hpp>

namespace tests
{
	template <typename T>
	void print(std::vector<T> vec)
	{
		std::cout << "std::vector :  " << std::endl;
		for (int i = 0; i < vec.size(); i++)
		{
			std::cout << "\t" << i << " => " << vec.at(i) << std::endl;
		}
	}
}

int main1(int, char**);
int glMain(int, char**);
void vertexTest(void);
int main(int argc, char** argv)
{
	// int exit_code = main1(argc, argv);
	// my::GL::vertices* Vertices = new my::GL::vertices;
	// Vertices->draw_quad(std::pair<float, float>(0, 0), std::pair<float, float>(0, 0), std::pair<float, float>(0, 0), std::pair<float, float>(0, 0));
	// std::vector<float> floatVec = Vertices->float_vec();
	// for (int i = 0; i < floatVec.size(); i++)
	// {
	// 	std::cout << floatVec.at(i) << std::endl;
	// }
	// delete Vertices;
	
	int exit_code = 0;
	// vertexTest();
	exit_code = glMain(argc, argv);
	// main1(argc, argv);
	return exit_code;
	// return exit_code;
}

void vertexTest()
{
	my::GL::vertices::objectClass C = my::GL::vertices::objectClass::quad(std::pair<float, float>(1.0f, 1.0f), std::pair<float, float>(1.0f, 0.0f), std::pair<float, float>(0.0f, 1.0f), std::pair<float, float>(-1.0f, -1.0f));
	C.translate(0.1f, 0.0f);
	
	my::GL::vertices vertices;
	vertices.objects.push_back(my::GL::vertices::objectClass());
	vertices.objects.at(0) = my::GL::vertices::objectClass::quad(std::pair<float, float>(1.0f, 1.0f), std::pair<float, float>(1.0f, 0.0f), std::pair<float, float>(0.0f, 1.0f), std::pair<float, float>(-1.0f, -1.0f));
	vertices.objects.at(0).translate(-0.1f, 0.0f);
	vertices.objects.at(0).translate(-0.1f, 0.0f);

	return;
}

void updateVertexObjects(unsigned int& VAO, unsigned int& VBO, my::GL::vertices& vertices)
{
	// glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);

	// glBindVertexArray(VAO);
	std::cout << "updateVertexObjects: my::GL::vertices obj size is " << vertices.float_vec().size() << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.float_vec().size() * sizeof(float), vertices.float_vec().data(), GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);

	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int glMain(int argc, char** argv)
{
	my::GL::start_glfw();
	my::GL::window* window = new my::GL::window("foo");
	my::GL::start_glad();
	glViewport(0, 0, 800, 600);

	my::GL::shader* Shader = new my::GL::shader("shaders/vert.glsl", "shaders/frag.glsl");

	my::GL::vertices* vertices = new my::GL::vertices();
#define coords	std::pair<float, float>
	vertices->draw_quad(coords(-1.0f, -1.0f), coords(0.0f, -1.0f), coords(0.0f, 0.0f), coords(-1.0f, 0.0f));


	/*
		set up VAO & VBO 
	---------------------------------------------------------------------------------------------------------------------------------
	*/
	std::cout << "float vec size: " << vertices->float_vec().size() << std::endl;
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices->float_vec().size() * sizeof(float), vertices->float_vec().data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*
	--------------------------------------------------------------------------------------------------------------------------------
	*/

	while (!window->shouldClose())
	{
		if (!window->selected())
		{
			while (!window->selected() && !window->shouldClose())
			{
				glfwPollEvents();
			}
		}
		window->process_input();

		if (window->getKey(GLFW_KEY_ESCAPE))
		{
			std::cout << "escape key pressed" << std::endl;
			break;
		}
		if (window->getKey(GLFW_KEY_W))
		{
			std::cout << "moving object up" << std::endl;
			vertices->objects.at(0).translate(0.00f, 0.01f);
			tests::print(vertices->float_vec());
			std::cout << "float vec size: " << vertices->float_vec().size() << std::endl;
			updateVertexObjects(VAO, VBO, *vertices);
			// translate(0.1f, 0.1f);
		}
		else if (window->getKey(GLFW_KEY_S))
		{
			std::cout << "moving object down" << std::endl;
			vertices->objects.at(0).translate(0.00f, -0.01f);
		}

	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);

	    Shader->use();
	    glBindVertexArray(VAO);
	    glDrawArrays(GL_TRIANGLES, 0, 6);

		// glfwSwapBuffers(window);
		window->swap_buffers();
		glfwPollEvents();
	}

	delete window;

#undef coords
	return 0;
}