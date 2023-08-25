#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std::literals;

namespace INFO 
{
    int GLFW_VER_MAJOR{ 4 };
    int GLFW_VER_MINOR{ 6 };
}
namespace SCREEN
{
    int WIDTH{ 640 };
    int HEIGHT{ 480 };
}

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) 
{
    SCREEN::WIDTH = width;
    SCREEN::HEIGHT = height;
    glViewport(0, 0, SCREEN::WIDTH, SCREEN::HEIGHT);
}

void glfwKeyCallback(GLFWwindow* p_window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(p_window, GL_TRUE);
    }
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed!"sv << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, INFO::GLFW_VER_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, INFO::GLFW_VER_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* p_window = glfwCreateWindow(SCREEN::WIDTH, SCREEN::HEIGHT, "Battle City", nullptr, nullptr);
    if (!p_window)
    {
        std::cout << "glfwCreateWindow failed!"sv << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(p_window, glfwWindowSizeCallback);
    glfwSetKeyCallback(p_window, glfwKeyCallback);
    /* Make the window's context current */
    glfwMakeContextCurrent(p_window);

	if(!gladLoadGL())
	{
		std::cout << "Can't load GLAD"sv << std::endl;
		return -1;
	}
    std::cout << "Renderer: "sv << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: "sv << glGetString(GL_VERSION) << std::endl;
	
	glClearColor(1, 1, 0, 1);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(p_window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(p_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}