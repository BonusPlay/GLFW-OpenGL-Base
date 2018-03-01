#include "Game.hpp"
#include "imgui/imgui_impl.h"
#include "general/Settings.hpp"
#include "imgui/fonts.hpp"

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

float last_x = SCREEN_WIDTH / 2.0f;
float last_y = SCREEN_HEIGHT / 2.0f;

Game::Game ()
{
	init_opengl ();
	init_ui ();
	init_audio ();
}

Game::~Game ()
{
	BASS_Free ();

	ImGui_impl_shutdown ();
	glfwTerminate ();
}

void Game::update ()
{
	glfwPollEvents ();
	ImGui_impl_new_frame ();

	set_volume (settings.music_volume);

	game_state->update ();
}

void Game::render () const
{
	glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	game_state->render ();

	ImGui::Render ();

	glfwSwapBuffers (window);
}

GLFWwindow* Game::get_window () const
{
	return window;
}

void Game::set_volume (float volume)
{
	BASS_SetVolume (volume);
}

shared_ptr<GameState> Game::get_game_state() const
{
	return game_state;
}

void Game::init_opengl ()
{
	glfwSetErrorCallback (log_error);

	glfwInit ();
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Beat Hunter", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate ();
		throw;
	}
	glfwMakeContextCurrent (window);
	glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);
	glfwSetCursorPosCallback (window, mouse_callback);
	glfwSetKeyCallback (window, key_callback);
	glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader (reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw;
	}

	glEnable (GL_DEPTH_TEST);

	glDepthFunc (GL_LESS);
	glEnable (GL_STENCIL_TEST);
	glStencilFunc (GL_NOTEQUAL, 1, 0xFF);
	glStencilOp (GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable (GL_CULL_FACE);

	glfwSwapInterval (1);
}

void Game::init_ui () const
{
	// ImGui_impl handles creating and destroying context
	ImGui_impl_init (window, false);
	ImGui::StyleColorsDark ();

	Fonts::init();
}

void Game::init_audio () const
{
	if (HIWORD (BASS_GetVersion ()) != BASSVERSION)
		throw runtime_error ("An incorrect version of BASS.DLL was loaded");

	if (!BASS_Init (-1, 44100, 0, NULL, NULL))
		throw runtime_error ("Can't initialize BASS device");

	BASS_SetVolume (1);

	if (BASS_ErrorGetCode () != BASS_OK)
		throw runtime_error (std::to_string (BASS_ErrorGetCode ()));
}

void Game::log_error (int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}

void Game::framebuffer_size_callback (GLFWwindow* window, const int width, const int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport (0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void Game::mouse_callback (GLFWwindow* window, double xpos, double ypos)
{
	const float x_offset = xpos - last_x;
	const float y_offset = last_y - ypos; // reversed since y-coordinates go from bottom to top

	last_x = xpos;
	last_y = ypos;

	if (!settings.ui_open)
		game->get_game_state ()->update (x_offset, y_offset);
}

void Game::key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	game->get_game_state ()->update (key, scancode, action, mods);
}