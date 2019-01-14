#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <cglm/cglm.h>
#include <glad.h>
#include <GLFW/glfw3.h>

typedef versor quat; // quaternion
typedef struct aiScene aiScene;
typedef struct aiMesh aiMesh;
typedef struct aiNode aiNode;
typedef struct aiMaterial aiMaterial;
typedef struct aiFace aiFace;
typedef struct aiString aiString;
typedef enum aiTextureType aiTextureType;

#define PATH_SEP '/' // path separator