#pragma once
#include "GameObject.h"
#include "../utils/Vector.h"

typedef struct
{
	GameObject base;

	struct
	{
		/**
		 * @brief Backup for overloaded #GameObject_DCtor
		 * @param go GameObject to deconstruct
		 */
		void (*GameObject_DCtor)(GameObject* go);

		/**
		 * @brief Backup for overloaded #GameObject_Draw
		 * @param go GameObject to draw
		 * @param shader Shader to draw with
		 */
		void (*GameObject_Draw)(GameObject* go, Shader* shader);
	} vftable;

	Vector* textures_loaded;
	Vector* meshes;

	// directory model is in (file path)
	char* directory;
} Model;

/**
 * @brief Model constructor
 * @param file model name (has to have a corresponding resource files)
 * @returns Model
 */
Model* Model_Ctor(const char* file);