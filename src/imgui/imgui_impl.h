#pragma once
#include "../Common.hpp"

struct GLFWwindow;

enum GlfwClientApi
{
    GlfwClientApi_Unknown,
    GlfwClientApi_OpenGL,
    GlfwClientApi_Vulkan
};

IMGUI_API bool        ImGui_impl_init(GLFWwindow* window, bool install_callbacks, GlfwClientApi client_api);
IMGUI_API void        ImGui_impl_shutdown();
IMGUI_API void        ImGui_impl_new_frame();

// Use if you want to reset your rendering device without losing ImGui state.
//IMGUI_API void        ImGui_impl_invalidate_device_objects();
//IMGUI_API bool        ImGui_impl_create_device_objects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
IMGUI_API void        ImGui_impl_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
IMGUI_API void        ImGui_impl_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
IMGUI_API void        ImGui_impl_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
IMGUI_API void        ImGui_impl_char_callback(GLFWwindow* window, unsigned int c);

extern int    g_WindowAttribute;
extern double g_mouse_x; 
extern double g_mouse_y;