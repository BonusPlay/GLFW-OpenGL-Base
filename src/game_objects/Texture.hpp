#pragma once
#include "../Common.hpp"

class Texture
{
public:
<<<<<<< HEAD
	Texture(string file, aiTextureType type);
=======
	Texture(const string& file, aiTextureType type);
>>>>>>> a4a49d8... fafa
	//~Texture(); BUG: declaring deconstructor breaks a lot of stuff

	unsigned int get_id() const;
	aiTextureType get_type() const;
	string get_path() const;

private:
	unsigned int ID;
	aiTextureType type;
	string path;
};