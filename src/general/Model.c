#include "Model.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include "Mesh.h"
#include <assimp/postprocess.h>
#include "Texture.h"
#include "../utils/SwissArmyKnife.h"
#include "../utils/VectorGL.h"

void process_node(Model* model, aiNode* node, const aiScene* scene);
Mesh* process_mesh(Model* model, aiMesh* mesh, const aiScene* scene);
Vector* load_material_textures(Model* m, aiMaterial *mat, enum aiTextureType type);

/*********************************************
****************    public    ****************
*********************************************/

Model* Model_Ctor(const char* file)
{
	LogD("Model_Ctor");
	Model* m = (GameObject*)GameObject_Ctor0();

	m->textures_loaded = Vector_Ctor();
	m->meshes = Vector_Ctor();
	m->directory = (char*)calloc((strlstchar(file, PATH_SEP) + 1), sizeof (char)); // +1 for null terminator
	memcpy(m->directory, file, strlstchar(file, PATH_SEP));

	const aiScene* scene = aiImportFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode);
		//throw runtime_error("Failed to load model '" + file + "'");
		// TODO: error handling

	process_node(m, scene->mRootNode, scene);

	return m;
}

void Model_DCtor(Model* m)
{
	Vector_DCtor(m->textures_loaded);
	Vector_DCtor(m->meshes);
	GameObject_DCtor((GameObject*)m); // free called by GameObject_DCtor
}

void Model_Draw(Model* m, Shader* shader)
{
	GameObject_Draw((GameObject*)m, shader);

	for(unsigned int i = 0; i < m->meshes->count; i++)
	{
		Mesh_Draw((Mesh*)Vector_Get(m->meshes, i), shader);
	}
}

/**********************************************
****************    private    ****************
**********************************************/

void process_node(Model* model, aiNode* node, const struct aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Vector_Add(model->meshes, process_mesh(model, mesh, scene));
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		process_node(model, node->mChildren[i], scene);
}

Mesh* process_mesh(Model* model, aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	// vertices and indices will be bound to OpenGL so they need to be in VectorGL
	Vertex* vertices = NULL;
	Indice* indices = NULL;
	Vector* textures = Vector_Ctor();

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		//Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
		Vertex vertex;
		vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

		// positions
		vector[0] = mesh->mVertices[i].x;
		vector[1] = mesh->mVertices[i].y;
		vector[2] = mesh->mVertices[i].z;
		memcpy_s(vertex.position, sizeof(vertex.position), vector, sizeof(vector));

		// normals
		vector[0] = mesh->mNormals[i].x;
		vector[1] = mesh->mNormals[i].y;
		vector[2] = mesh->mNormals[i].z;
		memcpy_s(vertex.normal, sizeof(vertex.normal), vector, sizeof(vector));

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec[0] = mesh->mTextureCoords[0][i].x;
			vec[1] = mesh->mTextureCoords[0][i].y;
			memcpy_s(vertex.tex_coords, sizeof(vertex.tex_coords), vec, sizeof(vec));
		}
		else
			memset(vertex.tex_coords, 0, 2);

		// tangent
		vector[0] = mesh->mTangents[i].x;
		vector[1] = mesh->mTangents[i].y;
		vector[2] = mesh->mTangents[i].z;
		memcpy_s(vertex.tangent, sizeof(vertex.tangent), vector, sizeof(vector));

		// bitangent
		vector[0] = mesh->mBitangents[i].x;
		vector[1] = mesh->mBitangents[i].y;
		vector[2] = mesh->mBitangents[i].z;
		memcpy_s(vertex.bitangent, sizeof(vertex.bitangent), vector, sizeof(vector));

		vector_push_back(vertices, vertex);
	}

	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			vector_push_back(indices, face.mIndices[j]);
			//Vector_Add(indices, &face.mIndices[j]); // BUG: ?
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuse_N
	// specular: texture_specular_N
	// normal: texture_normal_N

	// 1. diffuse maps
	Vector* diffuseMaps = load_material_textures(model, material, aiTextureType_DIFFUSE);
	for(unsigned int i= 0; i < diffuseMaps->count; i++)
		Vector_Add(textures, Vector_Get(diffuseMaps, i));

	// 2. specular maps
	Vector* specularMaps = load_material_textures(model, material, aiTextureType_SPECULAR);
	for(unsigned int i= 0; i < specularMaps->count; i++)
		Vector_Add(textures, Vector_Get(specularMaps, i));

	// 3. normal maps
	Vector* normalMaps = load_material_textures(model, material, aiTextureType_HEIGHT);
	for(unsigned int i= 0; i < normalMaps->count; i++)
		Vector_Add(textures, Vector_Get(normalMaps, i));

	// 4. height maps
	Vector* heightMaps = load_material_textures(model, material, aiTextureType_AMBIENT);
	for(unsigned int i= 0; i < heightMaps->count; i++)
		Vector_Add(textures, Vector_Get(heightMaps, i));

	// return a mesh object created from the extracted mesh data
	return Mesh_Ctor(vertices, indices, textures);
}

Vector* load_material_textures(Model* model, aiMaterial *mat, enum aiTextureType type)
{
	Vector* textures = Vector_Ctor();

	for (unsigned int i = 0; i < aiGetMaterialTextureCount(mat, type); i++)
	{
		aiString str;
		aiGetMaterialTexture(mat, type, i, &str, NULL, NULL, NULL, NULL, NULL, NULL);

		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;

		for (unsigned int j = 0; j < model->textures_loaded->count; j++)
		{
			Texture* texture = NULL;
			texture = (Texture*)Vector_Get(model->textures_loaded, j);
			char* texture_path = texture->path;
			char* path = (char*)calloc(strlen(texture_path) - strlstchar(texture_path, PATH_SEP) + 1, sizeof (char)); // +1 for null terminator
			memcpy(path, &texture_path[strlstchar(texture_path, PATH_SEP)], strlen(texture_path) - strlstchar(texture_path, PATH_SEP));

			if (strcmp(path, str.data) == 0)
			{
				Vector_Add(textures, texture);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			// if texture hasn't been loaded already, load it
			Texture* texture = Texture_Ctor(concat2(model->directory, str.data), type);

			Vector_Add(textures, texture);
			Vector_Add(model->textures_loaded, texture); // store it as texture loaded for entire model, to ensure we won't load duplicate textures.
		}
	}
	return textures;
}