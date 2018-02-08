#include "Common.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Game.hpp"
#include "general/Settings.hpp"

Settings settings;
unique_ptr<Game> game;