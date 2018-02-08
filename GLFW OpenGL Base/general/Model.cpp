#include "Model.hpp"

/**
 * \throws runtime_error Failed to load model
 */
Model::Model (const string& file)
	: GameObject()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile (file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		throw runtime_error ("Failed to load model '" + file + "'");

	// retrieve the directory path of the filepath
	directory = file.substr (0, file.find_last_of (PATH_SEP));

	process_node (scene->mRootNode, scene);
}

void Model::draw (shared_ptr<Shader> shader)
{
	GameObject::draw(shader);

	for (auto &mesh : meshes)
		mesh.draw (shader);
}

void Model::process_node (aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back (process_mesh (mesh, scene));
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		process_node (node->mChildren[i], scene);
}

Mesh Model::process_mesh (aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.tex_coords = vec;
		}
		else
			vertex.tex_coords = glm::vec2 (0.0f, 0.0f);

		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.tangent = vector;

		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.bitangent = vector;

		vertices.push_back (vertex);
	}

	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back (face.mIndices[j]);
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
	vector<Texture> diffuseMaps = load_material_textures (material, aiTextureType_DIFFUSE);
	textures.insert (textures.end (), diffuseMaps.begin (), diffuseMaps.end ());

	// 2. specular maps
	vector<Texture> specularMaps = load_material_textures (material, aiTextureType_SPECULAR);
	textures.insert (textures.end (), specularMaps.begin (), specularMaps.end ());

	// 3. normal maps
	vector<Texture> normalMaps = load_material_textures (material, aiTextureType_HEIGHT);
	textures.insert (textures.end (), normalMaps.begin (), normalMaps.end ());

	// 4. height maps
	vector<Texture> heightMaps = load_material_textures (material, aiTextureType_AMBIENT);
	textures.insert (textures.end (), heightMaps.begin (), heightMaps.end ());

	// return a mesh object created from the extracted mesh data
	return Mesh (vertices, indices, textures);
}

vector<Texture> Model::load_material_textures (aiMaterial* mat, aiTextureType type)
{
	vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount (type); i++)
	{
		aiString str;
		mat->GetTexture (type, i, &str);

		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;

		for (auto &texture : textures_loaded)
		{
			string path = texture.get_path ();
			path = path.substr(path.find_last_of(PATH_SEP) + 1, path.size());

			if (std::strcmp (path.c_str(), str.C_Str ()) == 0)
			{
				textures.push_back (texture);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}

		if (!skip)
		{   // if texture hasn't been loaded already, load it
			const Texture texture (this->directory + PATH_SEP + str.C_Str (), type);
			textures.push_back (texture);
			textures_loaded.push_back (texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}