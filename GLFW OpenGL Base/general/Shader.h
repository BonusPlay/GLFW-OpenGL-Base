#pragma once
#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct
{
	unsigned int ID;
	unsigned int v_shader;
	unsigned int f_shader;
} Shader;

Shader* Shader_Ctor(const char* v_shader_path, const char* f_shader_path);
void Shader_DCtor(Shader* shader);

void Shader_Use(Shader* shader);
void Shader_SetBool(Shader* shader, const char* name, bool value);
void Shader_SetInt(Shader* shader, const char* name, int value);
void Shader_SetFloat(Shader* shader, const char* name, float value);
void Shader_SetVec2(Shader* shader, const char* name, const vec2 value);
void Shader_SetVec2(Shader* shader, const char* name, float x, float y);
void Shader_SetVec3(Shader* shader, const char* name, const vec3 value);
void Shader_SetVec3(Shader* shader, const char* name, float x, float y, float z);
void Shader_SetVec4(Shader* shader, const char* name, const vec4 value);
void Shader_SetVec4(Shader* shader, const char* name, float x, float y, float z, float w);
void Shader_SetMat2(Shader* shader, const char* name, const mat2 value);
void Shader_SetMat3(Shader* shader, const char* name, const mat3 value);
void Shader_SetMat4(Shader* shader, const char* name, const mat4 value);