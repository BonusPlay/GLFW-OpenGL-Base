#pragma once
#include <cglm/cglm.h>

/**
 * \brief Structure holding vertex data for .obj models.
 */
typedef struct
{
	vec3 position;
	vec3 normal;
	vec2 tex_coords;
	vec3 tangent;
	vec3 bitangent;
} Vertex;
