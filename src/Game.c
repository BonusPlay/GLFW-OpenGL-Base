#include "Game.h"
#include "general/Settings.h"
#include "states/State1.h"
#include "utils/SwissArmyKnife.h"

static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 720;

static float last_x;
static float last_y;

GameState* state;

void init_opengl();
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
	g_Settings = (Settings*)malloc(sizeof(Settings));
	if(!g_Settings)
		panic("malloc failed in Game_init");

	g_Settings->screen_width = 1280;
	g_Settings->screen_height = 720;
	g_Settings->music_volume = 1.0f;
	last_x = SCREEN_WIDTH / 2.0f;
	last_y = SCREEN_HEIGHT / 2.0f;

	init_opengl();
	init_audio();
}

void deinit()
{
	State1_DCtor((State1*)state); // HACK: idk which state dctr to call, this should be resolved by vftables
	BASS_Free();
}

void update()
{
	glfwPollEvents ();
	BASS_SetVolume(g_Settings->music_volume);
	State1_Update((State1*)state); // HACK: vftable
}

void render()
{
	glClearColor (1.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	State1_Render((State1*)state);

	glfwSwapBuffers (g_Window);
}

void set_state(GameState* next)
{
	state = next;
}


/**********************************************
****************    private    ****************
**********************************************/

void init_opengl()
{
	glfwSetErrorCallback(log_error);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	g_Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Beat Hunter", NULL, NULL);
	if (g_Window == NULL)
	{
		panic("GLFW window create failed");
		glfwTerminate();
	}

	glfwMakeContextCurrent(g_Window);
	glfwSetFramebufferSizeCallback(g_Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(g_Window, mouse_callback);
	glfwSetKeyCallback(g_Window, key_callback);
	glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		panic("GLAD initialization failed");

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_CULL_FACE);

	glfwSwapInterval(1);
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

	GameState_UpdateM(state, x_offset, y_offset);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	State1_UpdateK((State1*)state, key, scancode, action, mods); // HACK: vftable
}

static void log_error(int error, const char* description)
{
	LogD("[ERROR](%i) %s\n", error, description);
}