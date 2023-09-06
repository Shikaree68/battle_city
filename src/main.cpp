#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include "Renderer/shader_program.h"
#include "Renderer/sprite.h"
#include "Renderer/animated_sprite.h"
#include "Renderer/texture_2D.h"
#include "Resources/resource_manager.h"

using namespace std::literals;

namespace INFO{
int GLFW_VER_MAJOR = 4;
int GLFW_VER_MINOR = 6;
}  // namespace INFO

GLfloat points[]{
	0.0f,  50.f, 0.0f,
	50.f, -50.f, 0.0f,
	-50.f, -50.f, 0.0f
};

GLfloat colors[]{
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f
};

GLfloat tex_coords[]{
	0.5f, 1.f,
	1.f, 0.f,
	0.f, 0.f,
};

glm::ivec2 WINDOW_SIZE(640, 480);
bool is_eagle = false;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height){
	WINDOW_SIZE.x = width;
	WINDOW_SIZE.y = height;
	glViewport(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y);
}

void glfwKeyCallback(GLFWwindow* p_window, int key, int scancode, int action,
					 int mode){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(p_window, GL_TRUE);
	}
	if(key == GLFW_KEY_ENTER && action == GLFW_PRESS){
		is_eagle = !is_eagle;
	}
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
		return -1;
	}
	std::cout << "Renderer: "sv << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: "sv << glGetString(GL_VERSION) << std::endl;

	glClearColor(1, 1, 0, 1);
	{
		ResourceManager resource_manager(argv[0]);
		auto default_shader_program = resource_manager.LoadShaders("DefaultShader",
																   "res/shaders/vertex.vert",
																   "res/shaders/fragment.frag");
		if(!default_shader_program){
			std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
			return -1;
		}

		auto sprite_shader_program = resource_manager.LoadShaders("SpriteShader",
																  "res/shaders/sprite_v.vert",
																  "res/shaders/sprite_f.frag");
		if(!default_shader_program){
			std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
			return -1;
		}

		auto tex = resource_manager.LoadTexture("DefaultTexture", "res/textures/map_16x16.png");

		std::vector<std::string> sub_textures_names{
			"block",				"top_block",
			"bottom_block",			"left_block",
			"right_block",			"top_left_block",
			"top_right_block",		"bottom_left_block",
			"bottom_right_block",

			"beton",				"top_beton",
			"bottom_beton",			"left_beton",
			"right_beton",			"top_left_beton",
			"top_right_beton",		"bottom_left_beton",
			"bottom_right_beton",

			"water1",	"water2",	"water3",
			"trees",	"ice",		"wall",
			"eagle",	"dead_eagle",
			"nothing",	"respawn1", "respawn2",
			"respawn3",	"respawn4",


		};
		auto texture_atlas = resource_manager.LoadTextureAtlas("DefaultTextureAtlas",
															   "res/textures/map_16x16.png",
															   sub_textures_names,
															   16, 16);
		auto sprite = resource_manager.LoadSprite("NewSprite",
												  "DefaultTextureAtlas",
												  "SpriteShader",
												  100, 100,
												  "block");
		sprite->SetPosition(glm::vec2(300, 100));

		auto animated_sprite = resource_manager.LoadAnimatedSprite("NewAnimatedSprite",
																   "DefaultTextureAtlas",
																   "SpriteShader",
																   100, 100,
																   "block");
		animated_sprite->SetPosition(glm::vec2(300, 300));

		std::vector<std::pair<std::string, uint64_t>> water_state;
		water_state.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1'000'000'000));
		water_state.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1'000'000'000));
		water_state.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1'000'000'000));

		std::vector<std::pair<std::string, uint64_t>> eagle_state;
		eagle_state.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1'000'000'000));
		eagle_state.emplace_back(std::make_pair<std::string, uint64_t>("dead_eagle", 1'000'000'000));

		animated_sprite->InsertState("water_state", water_state);
		animated_sprite->InsertState("eagle_state", eagle_state);

		animated_sprite->SetState("water_state");

		GLuint points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint texture_coordinates_vbo = 0;
		glGenBuffers(1, &texture_coordinates_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, texture_coordinates_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, texture_coordinates_vbo);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		default_shader_program->Use();
		default_shader_program->SetInt("tex", 0);

		glm::mat4 model_matrix_1 = glm::mat4(1.f);
		model_matrix_1 = glm::translate(model_matrix_1, glm::vec3(50.f, 50.f, 0.f));

		glm::mat4 model_matrix_2 = glm::mat4(1.f);
		model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(590.f, 50.f, 0.f));

		glm::mat4 pojection_matrix = glm::ortho(0.f, static_cast<float>(WINDOW_SIZE.x),
												0.f, static_cast<float>(WINDOW_SIZE.y),
												-100.f, 100.f);

		default_shader_program->SetMatrix4("projection_matrix", pojection_matrix);

		sprite_shader_program->Use();
		sprite_shader_program->SetInt("tex", 0);
		sprite_shader_program->SetMatrix4("projection_matrix", pojection_matrix);

		auto last_time = std::chrono::high_resolution_clock::now();

		/* Loop until the user closes the window */
		while(!glfwWindowShouldClose(p_window)){
			if(is_eagle){
				animated_sprite->SetState("eagle_state");
			} else{
				animated_sprite->SetState("water_state");
			}
			auto current_time = std::chrono::high_resolution_clock::now();
			uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - last_time).count();
			last_time = current_time;
			animated_sprite->Update(duration);

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			default_shader_program->Use();
			glBindVertexArray(vao);
			tex->Bind();

			default_shader_program->SetMatrix4("model_matrix", model_matrix_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			default_shader_program->SetMatrix4("model_matrix", model_matrix_2);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			sprite->Render();
			animated_sprite->Render();

			/* Swap front and back buffers */
			glfwSwapBuffers(p_window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}