#ifndef _MY_GL_HPP
#define _MY_GL_HPP

namespace my
{
	namespace GL
	{
		void start_glfw()
		{
			if (!glfwInit())
			{
				std::cerr << "Failed to initialize GLFW. Exiting program with exit code 1" << std::endl;
				std::exit(1);
			}
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		void start_glad()
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
		        std::cerr << "Failed to initialize GLAD. Exiting program with exit code 1" << std::endl;
		        std::exit(1);
		    }
		}
		
		void framebuffer_size_callback(GLFWwindow *window, int width, int height)
		{
		    glViewport(0, 0, width, height);
		}

		bool* window_selected = new bool(true);

		void processInput(GLFWwindow *window)
		{
    		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        		glfwSetWindowShouldClose(window, true);
		}

		void glfw_window_selected_callback(GLFWwindow* window, int focused)
		{
    		if (focused)
    		{
    		    // The window is now selected (focused)
				*window_selected = true;
    		    printf("Window is now focused\n");
    		}
    		else
    		{
    		    // The window is no longer selected (focused)
				*window_selected = false;
    		    printf("Window is no longer focused\n");
    		}
		}

		bool glfw_window_selected(GLFWwindow* window)
		{
			glfwSetWindowFocusCallback(window, glfw_window_selected_callback);
			return *window_selected;
		}
		
		typedef std::pair<float, float> coords;

		class shader
		{
			unsigned int ID;
		public:
        	shader(const char* vertex_path, const char* fragment_path)
        	{
				std::ifstream vertexShaderFile(vertex_path);
				std::string vertexShaderSrc((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
				vertexShaderFile.close();
				int vertexShader = glCreateShader(GL_VERTEX_SHADER);
				char* c_str = (char*)(vertexShaderSrc.c_str());
    			glShaderSource(vertexShader, 1, &c_str, NULL);
    			glCompileShader(vertexShader);

				int success;
    			char* infoLog = new char[512];
    			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    			if (!success)
    			{
        			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED:\n" << infoLog << std::endl;
					std::exit(1);
    			}

				std::ifstream fragmentShaderFile(fragment_path);
				std::string fragmentShaderSrc((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
				fragmentShaderFile.close();
				int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				c_str = (char*)(fragmentShaderSrc.c_str());
    			glShaderSource(fragmentShader, 1, &c_str, nullptr);
				glCompileShader(fragmentShader);

    			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    			if (!success)
    			{
        			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:\n" << infoLog << std::endl;
					std::exit(1);
    			}

				ID = glCreateProgram();
				glAttachShader(ID, vertexShader);
				glAttachShader(ID, fragmentShader);
				glLinkProgram(ID);

				glGetProgramiv(ID, GL_LINK_STATUS, &success);
    			if (!success)
				{
    	    		glGetProgramInfoLog(ID, 512, NULL, infoLog);
    	    		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
					std::exit(1);
    			}

				delete infoLog;
        	}
			void use()
			{
				glUseProgram(ID);
			}
		};

		class window
		{
			GLFWwindow* glfw_window;
		public:
			void glfw_window_errors(void)
			{
				if (!glfw_window)
				{
					std::cerr << "Could not open GLFW window. Exiting with exit code 1" << std::endl;
					std::exit(1);
				}
			}
			void glfw_window_errors(int error_code)
			{
				if (!glfw_window)
				{
					std::cerr << "Could not open GLFW window. Exiting with exit code " << error_code << std::endl;
				}
			}
			window()
			{
				glfw_window = glfwCreateWindow(800, 600, "my::GL::window::window", nullptr, nullptr);
				glfw_window_errors();
				glfwMakeContextCurrent(glfw_window);
				glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
			}
			window(const char* name)
			{
				glfw_window = glfwCreateWindow(800, 600, name, nullptr, nullptr);
				glfw_window_errors();
				glfwMakeContextCurrent(glfw_window);
				glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
			}
			window(std::string name)
			{
				glfw_window = glfwCreateWindow(800, 600, name.c_str(), nullptr, nullptr);
				glfw_window_errors();
				glfwMakeContextCurrent(glfw_window);
				glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
			}
			window(int len, int height)
			{
				glfw_window = glfwCreateWindow(len, height, "my::GL::window::window", nullptr, nullptr);
				glfw_window_errors();
				glfwMakeContextCurrent(glfw_window);
				glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
			}
			window(int len, int height, const char* name)
			{
				glfw_window = glfwCreateWindow(len, height, name, nullptr, nullptr);
				glfw_window_errors();
				glfwMakeContextCurrent(glfw_window);
				glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
			}
			window(int len, int height, std::string name)
			{
				glfw_window = glfwCreateWindow(len, height, name.c_str(), nullptr, nullptr);
				glfw_window_errors();
				glfwMakeContextCurrent(glfw_window);
				glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
			}

			bool getKey(int key_ID)
			{
				if (glfwGetKey(glfw_window, key_ID) == GLFW_PRESS)
					return true;
				return false;
			}

			std::pair<float, float> cursor()
			{
				double xPos;
				double yPos;
				glfwGetCursorPos(glfw_window, &xPos, &yPos);
				int width, height;
				glfwGetWindowSize(glfw_window, &width, &height);

				/* because of 16:9 aspect ratio, we make x-axis from -8<=x<=8 */
				float x_normalized = 16.0f * (float)xPos / (float)width - 8.0f;
				float y_normalized = -9.0f * (float)yPos / (float)height + 4.5f;

				return std::pair<float, float>(x_normalized, y_normalized);
			}

			bool shouldClose()
			{
				return glfwWindowShouldClose(this->glfw_window);
			}
			bool selected()
			{
				return glfw_window_selected(this->glfw_window);
			}

			void swap_buffers()
			{
				glfwSwapBuffers(glfw_window);
			}

			void process_input()
			{
				processInput(glfw_window);
			}
		};

		class vertices;
	}
}

#include <my/GL/vertexClass.hpp>

#endif