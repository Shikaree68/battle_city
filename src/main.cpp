#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "Game/game.h"
#include "Resources/resource_manager.h"
#include "Renderer/renderer.h"
#include "Physics/physics_engine.h"

using namespace std::literals;

namespace INFO{
int GLFW_VER_MAJOR = 4;
int GLFW_VER_MINOR = 6;
}  // namespace INFO

static constexpr std::uint16_t scale = 3;
static constexpr std::uint16_t block_size = 16;
glm::uvec2 window_size(scale * 16 * block_size, scale * 15 * block_size);
std::unique_ptr<Game> game(std::make_unique<Game>(window_size));


void glfwWindowSizeCallback(GLFWwindow* window, int width, int height){
	window_size.x = width;
	window_size.y = height;
	game->SetWindowSize(window_size);
}

void glfwKeyCallback(GLFWwindow* p_window, int key, int scancode, int action,
					 int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(p_window, GL_TRUE);
	}
	game->SetKey(key, action);
}

int main(int argc, char** argv) {
	/* Initialize the library */
	if(!glfwInit()){
		std::cout << "glfwInit failed!"sv << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, INFO::GLFW_VER_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, INFO::GLFW_VER_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* p_window = glfwCreateWindow(window_size.x, window_size.y, "Battle City", nullptr, nullptr);
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
	RenderEngine::Renderer::SetDepthTest(true);

	{
		ResourceManager::SetExecutablePath(argv[0]);	
		Physics::PhysicsEngine::Initialize();
		game->Initialize();
		//glfwSetWindowSize(p_window, static_cast<int>(3 * game->GetCurrentWidth()), static_cast<int>(3 * game->GetCurrentHeight()));
		auto last_time = std::chrono::high_resolution_clock::now();

		/* Loop until the user closes the window */
		while(!glfwWindowShouldClose(p_window)){
			/* Poll for and process events */
			glfwPollEvents();

			auto current_time = std::chrono::high_resolution_clock::now();
			double duration = std::chrono::duration<double, std::milli>(current_time - last_time).count();
			last_time = current_time;
			game->Update(duration);
			
			Physics::PhysicsEngine::Update(duration);
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