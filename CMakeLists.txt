cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB CPP_FILES
	"src/*.cpp"
	"src/game_objects/*.cpp"
	"src/imgui/*.cpp"
	"src/states/*.cpp"
)

file(GLOB C_FILES
	"src/utils/glad.c"
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