#pragma once
#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct
{
	unsigned int ID;
	unsigned int v_shader;
	unsigned int f_shader;
} Shader;

Shader* Shader_Ctor(const char* v_shader_name, const char* f_shader_name);
void Shader_DCtor(Shader* s);

void Shader_Use(Shader* s);
void Shader_SetBool(Shader* s, const char* name, bool value);
void Shader_SetInt(Shader* s, const char* name, int value);
void Shader_SetFloat(Shader* s, const char* name, float value);
void Shader_SetVec2(Shader* s, const char* name, const vec2 value);
void Shader_SetVec2f(Shader* s, const char* name, float x, float y);
void Shader_SetVec3(Shader* s, const char* name, const vec3 value);
void Shader_SetVec3f(Shader* s, const char* name, float x, float y, float z);
void Shader_SetVec4(Shader* s, const char* name, const vec4 value);
void Shader_SetVec4f(Shader* s, const char* name, float x, float y, float z, float w);
void Shader_SetMat3(Shader* s, const char* name, const mat3 value);
void Shader_SetMat4(Shader* s, const char* name, const mat4 value);