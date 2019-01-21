#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>
#include "../utils/SwissArmyKnife.h"
#include <glad.h>
#include "../utils/Typedefs.h"
#include <errno.h>
#include <string.h>

#define CHUNK 1024 // read 1024 bytes at a time

char* shader_load(const char* path);
void v_shader_compile(Shader* s, const char* code); // joining these 2 functions make resulting function very ugly
void f_shader_compile(Shader* s, const char* code);
void create_shader_program(Shader* s);


/*********************************************
****************    public    ****************
*********************************************/

Shader* Shader_Ctor(const char* v_shader_name, const char* f_shader_name)
{
	assert(v_shader_name);
	assert(f_shader_name);

	LogD("Shader_Ctor\n");
	Shader* s = (Shader*)malloc(sizeof(Shader));
	if (!s)
		panic("malloc failed in Shader_Ctor");

	char* v_path = concat3("res/shaders/", v_shader_name, ".vert");
	char* f_path = concat3("res/shaders/", f_shader_name, ".frag");

	char* v_shader_code = shader_load(v_path);
	char* f_shader_code = shader_load(f_path);

	free(v_path);
	free(f_path);

	v_shader_compile(s, v_shader_code);
	f_shader_compile(s, f_shader_code);

	free(v_shader_code);
	free(f_shader_code);

	create_shader_program(s);

	return s;
}

void Shader_DCtor(Shader* s)
{
	assert(s);
	glDeleteShader(s->ID);
	free(s);
}

void Shader_Use(Shader* shader)
{
	assert(shader);
	glUseProgram(shader->ID);
}

void Shader_SetBool(Shader* shader, const char* name, bool value)
{
	assert(shader);
	assert(name);
	glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

void Shader_SetInt(Shader* shader, const char* name, int value)
{
	assert(shader);
	assert(name);
	glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void Shader_SetFloat(Shader* shader, const char* name, float value)
{
	assert(shader);
	assert(name);
	glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void Shader_SetVec2(Shader* shader, const char* name, const vec2 value)
{
	assert(shader);
	assert(name);
	glUniform2fv(glGetUniformLocation(shader->ID, name), 1, value);
}

void Shader_SetVec2f(Shader* shader, const char* name, float x, float y)
{
	assert(shader);
	assert(name);
	glUniform2f(glGetUniformLocation(shader->ID, name), x, y);
}

void Shader_SetVec3(Shader* shader, const char* name, const vec3 value)
{
	assert(shader);
	assert(name);
	glUniform3fv(glGetUniformLocation(shader->ID, name), 1, value);
}

void Shader_SetVec3f(Shader* shader, const char* name, float x, float y, float z)
{
	assert(shader);
	assert(name);
	glUniform3f(glGetUniformLocation(shader->ID, name), x, y, z);
}

void Shader_SetVec4(Shader* shader, const char* name, const vec4 value)
{
	assert(shader);
	assert(name);
	glUniform4fv(glGetUniformLocation(shader->ID, name), 1, value);
}

void Shader_SetVec4f(Shader* shader, const char* name, float x, float y, float z, float w)
{
	assert(shader);
	assert(name);
	glUniform4f(glGetUniformLocation(shader->ID, name), x, y, z, w);
}

void Shader_SetMat3(Shader* s, const char* name, const mat3 value)
{
	assert(s);
	assert(name);
	glUniformMatrix3fv(glGetUniformLocation(s->ID, name), 1, GL_FALSE, value);
}

void Shader_SetMat4(Shader* s, const char* name, const mat4 value)
{
	assert(s);
	assert(name);
	glUniformMatrix4fv(glGetUniformLocation(s->ID, name), 1, GL_FALSE, value);
}

/**********************************************
****************    private    ****************
**********************************************/

char* shader_load(const char* path)
{
	assert(path);
	// source: https://stackoverflow.com/a/2029227

	char* source = NULL;
	FILE* fp;
	errno_t error = fopen_s(&fp, path, "r");
	if (error != 0)
	{
		fprintf(stderr, "cannot open file '%s': '%d", path, error);
		assert(false);
	}

	if (fp != NULL)
	{
		// Go to the end of the file
		if (fseek(fp, 0L, SEEK_END) == 0)
		{
			// Get the size of the file
			long bufsize = ftell(fp);
			if (bufsize == -1)
			{
				assert(false);
				// TODO: error handling
			}

			source = malloc(sizeof(char) * (bufsize + 1));
			assert(source);

			// Go back to the start of the file
			if (fseek(fp, 0L, SEEK_SET) != 0)
			{
				assert(false);
				// TODO: error handling
			}

			/* Read the entire file into memory. */
			size_t newLen = fread(source, sizeof(char), bufsize, fp);
			if (ferror(fp) != 0)
			{
				assert(false);
				// TODO: error handling
			}
			else
				source[newLen++] = '\0';
		}
		fclose(fp);
	}

	return source;
}

void v_shader_compile(Shader* s, const char* code)
{
	assert(s);
	assert(code);

	s->v_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(s->v_shader, 1, &code, NULL);
	glCompileShader(s->v_shader);
	// check for shader compile errors

	int success;
	char info_log[512];
	glGetShaderiv(s->v_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(s->v_shader, 512, NULL, info_log);
		LogD("[ERROR] %s\n", info_log);
		// log_error ("Shader::f_shader_compile", info_log);
		//throw runtime_error("Failed to compile fragment shader");
		// TODO: error handling
	}
}

void f_shader_compile(Shader* s, const char* code)
{
	assert(s);
	assert(code);

	s->f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(s->f_shader, 1, &code, NULL);
	glCompileShader(s->f_shader);
	// check for shader compile errors

	int success;
	char info_log[512];
	glGetShaderiv(s->f_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(s->f_shader, 512, NULL, info_log);
		LogD("[ERROR] %s\n", info_log);
		// log_error ("Shader::f_shader_compile", info_log);
		//throw runtime_error("Failed to compile fragment shader");
		// TODO: error handling
	}
}

void create_shader_program(Shader* s)
{
	assert(s);

	s->ID = glCreateProgram();
	glAttachShader(s->ID, s->v_shader);
	glAttachShader(s->ID, s->f_shader);
	glLinkProgram(s->ID);

	int success;
	char info_log[512];
	glGetProgramiv(s->ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(s->ID, 512, NULL, info_log);
		LogD("[ERROR] %s\n", info_log);
		// log_error ("Shader::create_shader_program", info_log);
		//throw runtime_error("Failed to compile shader program");
		// TODO: error handling
	}

	glDeleteShader(s->v_shader);
	glDeleteShader(s->f_shader);
}