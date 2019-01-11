#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>

#define CHUNK 1024 // read 1024 bytes at a time

char* shader_load(const char* path);
void v_shader_compile(Shader* shader, const char* code); // joining these 2 functions make resulting function very ugly
void f_shader_compile(Shader* shader, const char* code);
void create_shader_program(Shader* shader);


/*********************************************
****************    public    ****************
*********************************************/

Shader* Shader_Ctor(const char* v_shader_path, const char* f_shader_path)
{
	Shader* shader = (Shader*)malloc(sizeof(Shader));

	const char* v_shader_code = shader_load("res/shaders/" + v_shader_path + ".vert");
	const char* f_shader_code = shader_load("res/shaders/" + f_shader_path + ".frag");

	v_shader_compile(shader, v_shader_code);
	f_shader_compile(shader, f_shader_code);

	create_shader_program(shader);

	return shader;
}

void Shader_DCtor(Shader* shader)
{
	glDeleteShader(shader->ID);
}

void Shader_Use(Shader* shader)
{
	glUseProgram(shader->ID);
}

void Shader_SetBool(Shader* shader, const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

void Shader_SetInt(Shader* shader, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void Shader_SetFloat(Shader* shader, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void Shader_SetVec2(Shader* shader, const char* name, const vec2 value)
{
	glUniform2fv(glGetUniformLocation(shader->ID, name), 1, glm::value_ptr(value));
}

void Shader_SetVec2(Shader* shader, const char* name, float x, float y)
{
	glUniform2f(glGetUniformLocation(shader->ID, name), x, y);
}

void Shader_SetVec3(Shader* shader, const char* name, const vec3 value)
{
	glUniform3fv(glGetUniformLocation(shader->ID, name), 1, glm::value_ptr(value));
}

void Shader_SetVec3(Shader* shader, const char* name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shader->ID, name), x, y, z);
}

void Shader_SetVec4(Shader* shader, const char* name, const vec4 value)
{
	glUniform4fv(glGetUniformLocation(shader->ID, name), 1, glm::value_ptr(value));
}

void Shader_SetVec4(Shader* shader, const char* name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shader->ID, name), x, y, z, w);
}

void Shader_SetMat2(Shader* shader, const char* name, const mat2 value)
{
	glUniformMatrix2fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader_SetMat3(Shader* shader, const char* name, const mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader_SetMat4(Shader* shader, const char* name, const mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

/**********************************************
****************    private    ****************
**********************************************/

char* shader_load(const char* path)
{
	// source: https://stackoverflow.com/a/2029227

	char* source = NULL;
	FILE* fp = fopen(path, "r");
	if (fp != NULL)
	{
		// Go to the end of the file
		if (fseek(fp, 0L, SEEK_END) == 0)
		{
			// Get the size of the file
			long bufsize = ftell(fp);
			if (bufsize == -1)
			{
				// TODO: error handling
			}

			source = malloc(sizeof(char) * (bufsize + 1));

			// Go back to the start of the file
			if (fseek(fp, 0L, SEEK_SET) != 0)
			{
				// TODO: error handling
			}

			/* Read the entire file into memory. */
			size_t newLen = fread(source, sizeof(char), bufsize, fp);
			if (ferror(fp) != 0)
			{
				// TODO: error handling
			}
			else
				source[newLen++] = '\0';
		}
		fclose(fp);
	}

	return source;
}

void v_shader_compile(Shader* shader, const char* code)
{
	shader->v_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader->v_shader, 1, &code, NULL);
	glCompileShader(shader->v_shader);
	// check for shader compile errors

	int success;
	char info_log[512];
	glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(v_shader, 512, nullptr, info_log);
		// log_error ("Shader::f_shader_compile", info_log);
		//throw runtime_error("Failed to compile fragment shader");
		// TODO: error handling
	}
}

void f_shader_compile(Shader* shader, const char* code)
{
	shader->f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->f_shader, 1, &code, NULL);
	glCompileShader(shader->f_shader);
	// check for shader compile errors

	int success;
	char info_log[512];
	glGetShaderiv(shader->f_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader->f_shader, 512, NULL, info_log);
		// log_error ("Shader::f_shader_compile", info_log);
		//throw runtime_error("Failed to compile fragment shader");
		// TODO: error handling
	}
}

void create_shader_program(Shader* shader)
{
	shader->ID = glCreateProgram();
	glAttachShader(shader->ID, shader->v_shader);
	glAttachShader(shader->ID, shader->f_shader);
	glLinkProgram(shader->ID);

	int success;
	char info_log[512];
	glGetProgramiv(shader->ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->ID, 512, NULL, info_log);
		// log_error ("Shader::create_shader_program", info_log);
		//throw runtime_error("Failed to compile shader program");
		// TODO: error handling
	}

	glDeleteShader(shader->v_shader);
	glDeleteShader(shader->f_shader);
}