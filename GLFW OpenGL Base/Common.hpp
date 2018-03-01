#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <tuple>
#include <thread>
#include <map>
#include <fstream>
#include <atomic>
#include <mutex>
#include <condition_variable>

// GLAD + GLFW
#include <glad.h>
#include <GLFW/glfw3.h>

// GLM
#define GLM_ENABLE_EXPERIMENTAL // required for quaternions
#include <GLM/glm.hpp>
#include <GLM/gtx/quaternion.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

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

// Some of the stuff from STL that you'll use a lot
using std::string;
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

#define GET_VARIABLE_NAME(Variable) (#Variable)

#ifdef _WIN32
//const char PATH_SEP = '\\'; TODO: fully implement windows path
const char PATH_SEP = '/';
#else
const char PATH_SEP = '/';
#endif