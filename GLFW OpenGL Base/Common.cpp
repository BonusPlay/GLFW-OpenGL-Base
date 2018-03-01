#include "Common.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Game.hpp"
unique_ptr<Game> game;

#include "general/Settings.hpp"
Settings settings;

#include "general/SharedData.hpp"
SharedData shared;