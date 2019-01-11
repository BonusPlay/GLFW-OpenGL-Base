#include "Game.h"
#include <stdbool.h>
#include <stdio.h>
#include "general/Settings.h"

GLFWwindow* window;
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

float last_x = SCREEN_WIDTH / 2.0f;
float last_y = SCREEN_HEIGHT / 2.0f;

void init_opengl();
void init_ui();
void init_audio();
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void log_error(int error, const char* description);

/*********************************************
****************    public    ****************
*********************************************/

void init()
{
	init_opengl();
	init_ui();
	init_audio();
}

void deinit();
void update();
void render();

/**********************************************
****************    private    ****************
**********************************************/

void init_opengl()
{
	glfwSetErrorCallback(log_error);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Beat Hunter", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		// TODO: error handling

	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// TODO: error handling
	}

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_CULL_FACE);

	glfwSwapInterval(1);
}

void init_ui()
{
	// ImGui_impl handles creating and destroying context
	ImGui_impl_init(window, false);
	ImGui::StyleColorsDark();

	Fonts::init();
}

void init_audio()
{
	if (HIWORD(BASS_GetVersion()) != BASSVERSION);
		//throw runtime_error("An incorrect version of BASS.DLL was loaded");
		// TODO: error handling

	if (!BASS_Init(-1, 44100, 0, NULL, NULL));
		//throw runtime_error("Can't initialize BASS device");
		// TODO: error handling

	BASS_SetVolume(1);

	if (BASS_ErrorGetCode() != BASS_OK);
		//throw runtime_error(std::to_string(BASS_ErrorGetCode()));
		// TODO: error handling
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	const float x_offset = xpos - last_x;
	const float y_offset = last_y - ypos; // reversed since y-coordinates go from bottom to top

	last_x = xpos;
	last_y = ypos;

	if (!g_Settings->ui_open)
		update(x_offset, y_offset);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	update(key, scancode, action, mods);
}

static void log_error(int error, const char* description)
{
	// TODO: error handling
}