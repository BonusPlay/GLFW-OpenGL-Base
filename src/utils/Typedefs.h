#pragma once
#include <assimp/material.h>
#include <assimp/scene.h>
#include <cglm/cglm.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef unsigned int Indice;
typedef versor quat; // quaternion
typedef struct aiScene aiScene;
typedef struct aiMesh aiMesh;
typedef struct aiNode aiNode;
typedef struct aiMaterial aiMaterial;
typedef struct aiFace aiFace;
typedef struct aiString aiString;
typedef enum aiTextureType aiTextureType;

#define PATH_SEP '/' // path separator

#ifdef _DEBUG
#define LogD(str, ...)  printf(str, __VA_ARGS__);
#else
#define LogD(str, ...)
#endif