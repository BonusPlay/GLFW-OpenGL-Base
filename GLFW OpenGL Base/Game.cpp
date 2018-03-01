#include "Game.hpp"
#include "imgui/imgui_impl.h"
#include "imgui/fonts.hpp"
#include "general/Settings.hpp"
#include "general/SharedData.hpp"

float last_x = settings.screen_width / 2.0f;
float last_y = settings.screen_height / 2.0f;

Game::Game()
{
	init_opengl();
	init_ui();
	init_audio();
	glfwMakeContextCurrent(nullptr); // Only 1 thread at a time can have OpenGL context and we want it on rendering thread
}

Game::~Game()
{
	BASS_Free();
	ImGui_impl_shutdown();
}

GLFWwindow* Game::get_window() const
{
	return window;
}

void Game::set_volume(float volume)
{
	BASS_SetVolume(volume);
}

void Game::init_opengl()
{
	glfwSetErrorCallback(log_error);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(settings.screen_width, settings.screen_height, "Beat Hunter", nullptr, nullptr);
	if (window == nullptr)
		throw runtime_error("Failed to create GLFW window");

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw runtime_error("Failed to initialize GLAD");

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_CULL_FACE);

	glfwSwapInterval(1); // 1 - VSync ON, 0 - VSync OFF
}

void Game::init_ui() const
{
	// ImGui_impl handles creating and destroying context
	ImGui_impl_init(window, false);
	ImGui::StyleColorsDark();

	Fonts::init();
}

void Game::init_audio() const
{
	if (HIWORD(BASS_GetVersion()) != BASSVERSION)
		throw runtime_error("An incorrect version of BASS.DLL was loaded");

	if (!BASS_Init(-1, 44100, 0, NULL, NULL))
		throw runtime_error("Can't initialize BASS device");

	BASS_SetVolume(1);

	if (BASS_ErrorGetCode() != BASS_OK)
		throw runtime_error(std::to_string(BASS_ErrorGetCode()));
}

void Game::framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	settings.screen_width = width;
	settings.screen_height = height;
}

void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	const float x_offset = xpos - last_x;
	const float y_offset = last_y - ypos; // reversed since y-coordinates go from bottom to top

	last_x = xpos;
	last_y = ypos;

	if (!settings.ui_open)
		shared.game_state->update(x_offset, y_offset);
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	shared.game_state->update(key, scancode, action, mods);
}

void Game::log_error(int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}