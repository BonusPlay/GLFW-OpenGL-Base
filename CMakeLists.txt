cmake_minimum_required(VERSION 3.10)
<<<<<<< HEAD

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

=======
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MY_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

>>>>>>> a4a49d8... fafa
file(GLOB CPP_FILES
	"src/*.cpp"
	"src/game_objects/*.cpp"
	"src/imgui/*.cpp"
	"src/states/*.cpp"
)

file(GLOB C_FILES
<<<<<<< HEAD
	"src/utils/glad.c"
=======
	"src/glad.c"
>>>>>>> a4a49d8... fafa
)

file (GLOB HPP_FILES
	"src/*.cpp"
	"src/game_objects/*.cpp"
	"src/imgui/*.cpp"
	"src/states/*.cpp"
)

file(GLOB H_FILES
	"src/imgui/imconfig.h"
)

add_executable (main ${CPP_FILES} ${C_FILES} ${HPP_FILES} ${H_FILES})

<<<<<<< HEAD
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
#find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(main PRIVATE glad::glad)
target_link_libraries(main PRIVATE glm)
target_link_libraries(main PRIVATE glfw)
#target_link_libraries(main PRIVATE imgui::imgui)
target_link_libraries(main PRIVATE spdlog::spdlog)

# ImGUI
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)

# BASS lib
if (WIN32)
message("Windows")
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/bass/c/bass.h)
target_link_libraries(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/bass/c/x64/bass.lib)
endif (WIN32)

if (UNIX AND NOT APPLE)
message("Linux")
#target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/bass/bass.h)
#target_link_libraries(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/bass/x64/libbass.so)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/bass)
endif (UNIX AND NOT APPLE)

if (APPLE)
message("Apple")
message(""${CMAKE_CURRENT_SOURCE_DIR})
endif (APPLE)
=======
find_package(OpenGL)
target_link_libraries(main PRIVATE ${OPENGL_gl_LIBRARY} ${CMAKE_DL_LIBS})

target_include_directories (main PRIVATE ${MY_LIB_DIR}/assimp/include)
target_include_directories (main PRIVATE ${MY_LIB_DIR}/assimp/build/include)
target_link_libraries (main PRIVATE ${MY_LIB_DIR}/assimp/build/code/libassimp.so)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/bass)
target_link_libraries (main PRIVATE ${MY_LIB_DIR}/bass/x64/libbass.so)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/glad/include)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/glfw/include)
target_link_libraries (main PRIVATE ${MY_LIB_DIR}/glfw/build/src/libglfw.so)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/glm)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/imgui)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/spdlog/include)

target_include_directories (main PRIVATE ${MY_LIB_DIR}/stb)
>>>>>>> a4a49d8... fafa
