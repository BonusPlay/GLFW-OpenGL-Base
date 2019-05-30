#pragma once
#include "../Common.hpp"

class Shader
{
public:
	Shader(const string& v_shader_path, const string& f_shader_path);
	~Shader();

	unsigned int get_id() const;
	void use() const;
	void set_bool(const string& name, bool value) const;
	void set_int(const string& name, int value) const;
	void set_float(const string& name, float value) const;
	void set_vec2(const string& name, const glm::vec2& value) const;
	void set_vec2(const string& name, float x, float y) const;
	void set_vec3(const string& name, const glm::vec3& value) const;
	void set_vec3(const string& name, float x, float y, float z) const;
	void set_vec4(const string& name, const glm::vec4& value) const;
	void set_vec4(const string& name, float x, float y, float z, float w) const;
	void set_mat2(const string& name, const glm::mat2& value) const;
	void set_mat3(const string& name, const glm::mat3& value) const;
	void set_mat4(const string& name, const glm::mat4& value) const;

private:
	unsigned int ID;
	unsigned int v_shader;
	unsigned int f_shader;

	string v_shader_load(const string& v_shader_path) const;
	string f_shader_load(const string& f_shader_path) const;
	void v_shader_compile(const char* code);
	void f_shader_compile(const char* code);
	void create_shader_program();
};