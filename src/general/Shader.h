#pragma once
#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct
{
	unsigned int ID;
	unsigned int v_shader;
	unsigned int f_shader;
} Shader;

/**
 * @brief Shader constructor
 * @param v_shader_name vertex shader name (has to have corresponding file in resources)
 * @param f_shader_name fragment shader name (has to have corresponding file in resources)
 * @returns Shader
 */
Shader* Shader_Ctor(const char* v_shader_name, const char* f_shader_name);

/**
 * @brief Shader deconstructor
 * @param s Shader to deconstruct
 */
void Shader_DCtor(Shader* s);

/**
 * @brief Sets shader as currently used
 * @param s Shader to use
 */
void Shader_Use(Shader* s);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetBool(Shader* s, const char* name, bool value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetInt(Shader* s, const char* name, int value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetFloat(Shader* s, const char* name, float value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetVec2(Shader* s, const char* name, const vec2 value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param x Shader parameter X value
 * @param y Shader parameter Y value
 */
void Shader_SetVec2f(Shader* s, const char* name, float x, float y);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetVec3(Shader* s, const char* name, const vec3 value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param x Shader parameter X value
 * @param y Shader parameter Y value
 * @param z Shader parameter Z value
 */
void Shader_SetVec3f(Shader* s, const char* name, float x, float y, float z);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetVec4(Shader* s, const char* name, const vec4 value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param x Shader parameter X value
 * @param y Shader parameter Y value
 * @param z Shader parameter Z value
 * @param w Shader parameter W value
 */
void Shader_SetVec4f(Shader* s, const char* name, float x, float y, float z, float w);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetMat3(Shader* s, const char* name, const mat3 value);

/**
 * @brief Sets shader parameter value
 * @param name Shader parameter name
 * @param value Shader parameter value
 */
void Shader_SetMat4(Shader* s, const char* name, const mat4 value);