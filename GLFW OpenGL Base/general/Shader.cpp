#include "Shader.hpp"
#include <fstream>
#include <sstream>

/**
 * \throws runtime_error failed to load vertex shader
 * \throws runtime_error failed to load fragment shader
 * \throws runtime_error failed to compile vertex shader
 * \throws runtime_error failed to compile fragment shader
 * \throws runtime_error failed to compile program
 */
Shader::Shader(string v_shader_path, string f_shader_path)
{
	try
	{
		string v_shader_code = v_shader_load("res/shaders/" + v_shader_path + ".vert");
		string f_shader_code = f_shader_load("res/shaders/" + f_shader_path + ".frag");

		v_shader_compile(v_shader_code.c_str());
		f_shader_compile(f_shader_code.c_str());

		create_shader_program();
	}
	catch (exception& e)
	{
		throw e;
	}
}

Shader::~Shader()
{
	glDeleteShader(ID);
}

unsigned Shader::get_id() const
{
	return ID;
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::set_bool(const string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::set_int(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_vec2(const string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec2(const string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::set_vec3(const string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec3(const string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::set_vec4(const string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec4(const string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_mat3(const string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_mat4(const string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/**
 * \throws runtime_error failed to load vertex shader
 */
string Shader::v_shader_load(string v_shader_path) const
{
	std::ifstream v_shader_file;
	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream v_shader_stream;

	try
	{
		v_shader_file.open(v_shader_path);
		v_shader_stream << v_shader_file.rdbuf();
		v_shader_file.close();

		return v_shader_stream.str();
	}
	catch (std::ifstream::failure& e)
	{
		// log_error ("Shader::v_shader_load", "Failed to load vertex shader");
		throw e;
	}
}

/**
 * \throws runtime_error failed to load fragment shader
 */
string Shader::f_shader_load(string f_shader_path) const
{
	std::ifstream f_shader_file;
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream f_shader_stream;

	try
	{
		f_shader_file.open(f_shader_path);
		f_shader_stream << f_shader_file.rdbuf();
		f_shader_file.close();

		return f_shader_stream.str();
	}
	catch (std::ifstream::failure& e)
	{
		// log_error ("Shader::f_shader_load", "Failed to load fragment shader");
		throw e;
	}
}

/**
 * \throws runtime_error failed to compile vertex shader
 */
void Shader::v_shader_compile(const char* code)
{
	v_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_shader, 1, &code, nullptr);
	glCompileShader(v_shader);

	// check for shader compile errors
	int success;
	char info_log[512];
	glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(v_shader, 512, nullptr, info_log);
		// log_error ("Shader::v_shader_compile", info_log);
		throw runtime_error("Failed to compile vertex shader");
	}
}

/**
 * \throws runtime_error failed to compile fragment shader
 */
void Shader::f_shader_compile(const char* code)
{
	f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_shader, 1, &code, nullptr);
	glCompileShader(f_shader);
	// check for shader compile errors

	int success;
	char info_log[512];
	glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(f_shader, 512, nullptr, info_log);
		// log_error ("Shader::f_shader_compile", info_log);
		throw runtime_error("Failed to compile fragment shader");
	}
}

/**
 * \throws runtime_error failed to compile program
 */
void Shader::create_shader_program()
{
	ID = glCreateProgram();
	glAttachShader(ID, v_shader);
	glAttachShader(ID, f_shader);
	glLinkProgram(ID);

	int success;
	char info_log[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, nullptr, info_log);
		// log_error ("Shader::create_shader_program", info_log);
		throw runtime_error("Failed to compile shader program");
	}

	glDeleteShader(v_shader);
	glDeleteShader(f_shader);
}