#pragma once
#include "Shader.h"
#include "../utils/Typedefs.h"

typedef struct
{
	struct
	{
		/**
		 * @brief Object deconstructor
		 * @param go GameObject to deconstruct
		 */
		void(*GameObject_DCtor)(struct GameObject* go);

		/**
		 * @brief Draws object with shader
		 * @param go GameObject to draw
		 * @param shader Shader to draw with
		 */
		void(*GameObject_Draw)(struct GameObject* go, Shader* shader);
	} vftable;

	vec3 position;
	quat rotation;
	vec3 scale;
} GameObject;

/**
 * @brief GameObject constructor
 * 
 * calls #GameObject_Ctor2 with identity vectors/matrices
 * 
 * @returns GameObject
 */
GameObject* GameObject_Ctor0();

/**
 * @brief GameObject constructor
 * @param position position
 * 
 * calls #GameObject_Ctor2 with identity matrices
 * 
 * @returns GameObject
 */
GameObject* GameObject_Ctor1(vec3 position);

/**
 * @brief GameObject constructor
 * @param position position
 * @param rotation rotation
 * @param scale scale
 * @returns GameObject
 */
GameObject* GameObject_Ctor2(vec3 position, quat rotation, vec3 scale);