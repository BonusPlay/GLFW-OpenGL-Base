cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

set(PROJECT_NAME GLFWOpenGLBase)
# Output Variables
set(OUTPUT_DEBUG $(SolutionDir)Build/$(Configuration) $(PlatformTarget)/)
set(OUTPUT_REL $(SolutionDir)Build/$(Configuration) $(PlatformTarget)/)
# Folders files
set(CPP_DIR_1 ./)
set(CPP_DIR_2 ./)
set(CPP_DIR_3 general)
set(CPP_DIR_4 imgui)
set(CPP_DIR_5 ./)
set(CPP_DIR_6 states)
set(CPP_DIR_7 threads)
set(CPP_DIR_8 utils)
set(HEADER_DIR_1 )
set(HEADER_DIR_2 general)
set(HEADER_DIR_3 imgui)
set(HEADER_DIR_4 states)
set(HEADER_DIR_5 threads)

############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME} CXX)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

############## Artefacts Output #################
# Defines outputs , depending Debug or Release. #
#################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
endif()

################# Flags ################
# Defines Flags for Windows and Linux. #
########################################

if(MSVC)
   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /EHsc")
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /EHsc")
endif(MSVC)
if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

################ Files ################
#   --   Add files to project.   --   #
#######################################

file(GLOB SRC_FILES
    ${CPP_DIR_1}/*.cpp
    ${CPP_DIR_1}/*.c
    ${CPP_DIR_2}/*.cpp
    ${CPP_DIR_2}/*.c
    ${CPP_DIR_3}/*.cpp
    ${CPP_DIR_3}/*.c
    ${CPP_DIR_4}/*.cpp
    ${CPP_DIR_4}/*.c
    ${CPP_DIR_5}/*.cpp
    ${CPP_DIR_5}/*.c
    ${CPP_DIR_6}/*.cpp
    ${CPP_DIR_6}/*.c
    ${CPP_DIR_7}/*.cpp
    ${CPP_DIR_7}/*.c
    ${CPP_DIR_8}/*.cpp
    ${CPP_DIR_8}/*.c
    ${HEADER_DIR_1}/*.h
    ${HEADER_DIR_2}/*.h
    ${HEADER_DIR_3}/*.h
    ${HEADER_DIR_4}/*.h
    ${HEADER_DIR_5}/*.h
)

# Add executable to build.
add_executable(${PROJECT_NAME} 
   ${SRC_FILES}
)

if(MSVC)
   target_link_libraries(${PROJECT_NAME} glfw3.lib opengl32.lib assimp-vc140-mt.lib bass.lib )
endif(MSVC)
