#include "Game.hpp"
#include "imgui/imgui_impl.hpp"
#include "imgui/fonts.hpp"
#include "game_objects/Settings.hpp"
#include "game_objects/SharedData.hpp"

float last_x = g_Settings.screen_width / 2.0f;
float last_y = g_Settings.screen_height / 2.0f;

void GLAPIENTRY msg_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

// needs to be available to static functions
vector<unique_ptr<GameState>> game_states;

Game::Game()
{
	init_opengl();
	init_ui();
	init_audio();
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

void Game::set_game_state(unique_ptr<GameState> game_state)
{
	game_states.push_back(std::move(game_state));
}

void Game::update()
{
	glfwPollEvents();
	ImGui_impl_new_frame();

	set_volume(g_Settings.music_volume);

	game_states.back()->update();
}

void Game::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	game_states.back()->render();

	ImGui::Render();

	glfwSwapBuffers(window);
}

void Game::init_opengl()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(g_Settings.screen_width, g_Settings.screen_height, "Beat Hunter", nullptr, nullptr);
	if (window == nullptr)
		throw runtime_error("Failed to create GLFW window");

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw runtime_error("Failed to initialize GLAD");

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(msg_callback, 0);
	glfwSetErrorCallback(log_error);

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
	IMGUI_CHECKVERSION();
	ImGui_impl_init(window, false, GlfwClientApi_OpenGL);
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

void Game::framebuffer_size_callback(GLFWwindow * window, const int width, const int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	g_Settings.screen_width = width;
	g_Settings.screen_height = height;
}

void Game::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	const float x_offset = xpos - last_x;
	const float y_offset = last_y - ypos; // reversed since y-coordinates go from bottom to top

	last_x = xpos;
	last_y = ypos;

	if (!g_Settings.ui_open)
		game_states.back()->update(x_offset, y_offset);
}

void Game::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	game_states.back()->update(key, scancode, action, mods);
}

void Game::log_error(int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}

void GLAPIENTRY msg_callback(GLenum msg_source, GLenum msg_type, GLuint id, GLenum msg_severity, GLsizei length, const GLchar* message, const void* userParam)
{
	string source;
	string type;
	string severity;
	spdlog::level::level_enum level;

	switch(msg_source)
	{
	case GL_DEBUG_SOURCE_API:
		source = "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		source = "Window";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		source = "Shader";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		source = "ThirdParty";
		break;
	default: // also handles DEBUG_SOURCE_OTHER
		source = "Other";
		break;
	}

	switch (msg_severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severity = "medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		severity = "low";
		break;
	default: // also handles DEBUG_SEVERITY_NOTIFICATION
		severity = "notification";
		break;
	}

	switch (msg_type)
	{
	case GL_DEBUG_TYPE_ERROR:
		type = "ERROR";
		level = spdlog::level::err;
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type = "DEPRECATED";
		level = spdlog::level::warn;
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type = "UB";
		level = spdlog::level::err;
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		type = "Portability";
		level = spdlog::level::warn;
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		type += "Performance";
		level = spdlog::level::warn;
		break;
	case GL_DEBUG_TYPE_MARKER:
		type += "Marker";
		level = spdlog::level::info;
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		type += "Push Group";
		level = spdlog::level::info;
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		type += "Pop Group";
		level = spdlog::level::info;
		break;
	default: // also handles DEBUG_TYPE_OTHER
		type += "Other";
		level = spdlog::level::info;
		break;
	}

	spdlog::log(level, "[{}] [{}] [{}]\n[{}]", source, severity, type, message);
}