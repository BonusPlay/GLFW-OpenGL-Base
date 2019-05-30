#pragma once
#include "../Common.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "GameObject.hpp"

class Model : public GameObject
{
public:
	Model(const string& file);

	void draw(const Shader& shader);

private:
	vector<unique_ptr<Texture>> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture*> load_material_textures(aiMaterial *mat, aiTextureType type);
};
