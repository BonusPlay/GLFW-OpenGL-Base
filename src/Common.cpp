#include "Common.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Game.hpp"
unique_ptr<Game> g_Game;

#include "game_objects/Settings.hpp"
Settings g_Settings;

#include "game_objects/SharedData.hpp"
SharedData g_Shared;