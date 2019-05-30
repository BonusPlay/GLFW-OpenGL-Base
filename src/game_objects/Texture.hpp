#pragma once
#include "../Common.hpp"
#include "../utils/Handle.hpp"

class Texture : public Handle
{
public:
	Texture(const string& file, aiTextureType type);
	Texture(Texture&& other) = default;
	Texture& operator=(Texture&& other) = default;
	~Texture();

	unsigned int get_id() const;
	aiTextureType get_type() const;
	string get_path() const;

private:
	unsigned int ID;
	aiTextureType type;
	string path;
};