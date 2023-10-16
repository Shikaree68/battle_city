#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "Game/game.h"
#include "Resources/resource_manager.h"
#include "Renderer/renderer.h"

using namespace std::literals;

namespace INFO{
int GLFW_VER_MAJOR = 4;
int GLFW_VER_MINOR = 6;
}  // namespace INFO

glm::ivec2 WINDOW_SIZE(13 * 16, 14 * 16);
std::unique_ptr<Game> game(std::make_unique<Game>(WINDOW_SIZE));


void glfwWindowSizeCallback(GLFWwindow* window, int width, int height){
	WINDOW_SIZE.x = width;
	WINDOW_SIZE.y = height;

	const float map_aspect_ratio = 13.f / 14.f;
	uint32_t view_port_width = WINDOW_SIZE.x;
	uint32_t view_port_height = WINDOW_SIZE.y;
	uint32_t view_port_left_offset = 0;
	uint32_t view_port_bottom_offset = 0;

	if(WINDOW_SIZE.x * 1.f/ WINDOW_SIZE.y > map_aspect_ratio){
		view_port_width = static_cast<uint32_t>(WINDOW_SIZE.y * map_aspect_ratio);
		view_port_left_offset = (WINDOW_SIZE.x - view_port_width) / 2;
	} else{
		view_port_height = static_cast<uint32_t>(WINDOW_SIZE.x / map_aspect_ratio);
		view_port_bottom_offset = (WINDOW_SIZE.y - view_port_height) / 2;
	}

	RenderEngine::Renderer::SetViewport(view_port_width, view_port_height, view_port_left_offset, view_port_bottom_offset);
}

void glfwKeyCallback(GLFWwindow* p_window, int key, int scancode, int action,
					 int mode){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(p_window, GL_TRUE);
	}
	game->SetKey(key, action);
}

int main(int argc, char** argv){
	/* Initialize the library */
	if(!glfwInit()){
		std::cout << "glfwInit failed!"sv << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, INFO::GLFW_VER_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, INFO::GLFW_VER_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* p_window = glfwCreateWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, "Battle City", nullptr, nullptr);
	if(!p_window){
		std::cout << "glfwCreateWindow failed!"sv << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(p_window, glfwWindowSizeCallback);
	glfwSetKeyCallback(p_window, glfwKeyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(p_window);

	if(!gladLoadGL()){
		std::cout << "Can't load GLAD"sv << std::endl;
	}
	std::cout << "Renderer: "sv << RenderEngine::Renderer::GetRenderType() << std::endl;
	std::cout << "OpenGL version: "sv << RenderEngine::Renderer::GetRenderVersion() << std::endl;

	RenderEngine::Renderer::SetClearColor(0, 0, 0, 1);
	{
		ResourceManager::SetExecutablePath(argv[0]);		
		game->Initialize();
		auto last_time = std::chrono::high_resolution_clock::now();

		/* Loop until the user closes the window */
		while(!glfwWindowShouldClose(p_window)){
			/* Poll for and process events */
			glfwPollEvents();

			auto current_time = std::chrono::high_resolution_clock::now();
			uint32_t duration = static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - last_time).count());
			last_time = current_time;
			game->Update(duration);

			/* Render here */
			RenderEngine::Renderer::Clear();

			game->Render();

			/* Swap front and back buffers */
			glfwSwapBuffers(p_window);
		}
		game.reset();
		ResourceManager::UnloadAllResources();
	}
	glfwTerminate();
	return 0;
}