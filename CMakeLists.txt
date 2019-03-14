cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MY_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

file(GLOB CPP_FILES
	"src/*.cpp"
	"src/game_objects/*.cpp"
	"src/imgui/*.cpp"
	"src/states/*.cpp"
)

file(GLOB C_FILES
	"src/glad.c"
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