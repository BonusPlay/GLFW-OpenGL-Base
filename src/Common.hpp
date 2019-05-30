#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <tuple>
#include <thread>
#include <map>
#include <any>
#include <array>
#include <fstream>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string_view>

// GLAD + GLFW
#define GLFW_INCLUDE_NONE // we include GLAD so we don't want glfw to load it's own
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#define GLM_ENABLE_EXPERIMENTAL // required for quaternions
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// STB
#include <stb_image.h>

// IMGUI
#include "imgui/imconfig.h"
#include <imgui.h>

// BASS
#include <bass.h>

// SpdLog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Some of the stuff from STL that you'll use a lot
using std::string;
using std::string_view;
using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;
using std::make_shared;
using std::exception;
using std::get;
using std::tuple;
using std::make_tuple;
using std::vector;
using std::thread;
using std::map;
using std::pair;
using std::make_pair;
using std::runtime_error;
using std::error_code;
using std::mutex;
using std::condition_variable;
using std::atomic;
using std::unique_lock;
using std::scoped_lock;
using std::array;

#define GET_VARIABLE_NAME(Variable) (#Variable)

#ifdef _WIN32
//const char PATH_SEP = '\\'; TODO: fully implement windows path
const char PATH_SEP = '/';
#else
const char PATH_SEP = '/';
#endif