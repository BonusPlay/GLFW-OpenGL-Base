//#include "VectorGL.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//VectorGL* VectorGL_Ctor()
//{
//	VectorGL* v = (VectorGL*)malloc(sizeof(VectorGL));
//
//	v->data = NULL;
//	v->size = 0;
//	v->count = 0;
//
//	return v;
//}
//
//void VectorGL_DCtor(VectorGL* v)
//{
//	if(v->count != 0)
//		free(v->data);
//	free(v);
//}
//
//void VectorGL_Add(VectorGL* v, void* item)
//{
//	// batch add to prevent intense mallocs
//	if (v->size == 0)
//	{
//		v->size = 10;
//		v->data = malloc(sizeof(void*) * v->size);
//		memset(v->data, '\0', sizeof(void) * v->size);
//	}
//
//	// condition to increase v->data:
//	// last slot exhausted
//	if (v->size == v->count)
//	{
//		v->size *= 2;
//		v->data = realloc(v->data, sizeof(void*) * v->size);
//	}
//
//	v->data[v->count];
//	//memcpy(&v->data[v->count], item, sizeof item);
//	v->count++;
//}
//
//void VectorGL_Set(VectorGL* v, unsigned int index, void* item)
//{
//	if (index >= v->count)
//		return;
//
//	memcpy(&v->data[index], item, sizeof item);
//}
//
//void* VectorGL_Get(VectorGL* v, unsigned int index)
//{
//	if (index >= v->count)
//		return;
//
//	return &v->data[index];
//}
//
////void VectorGL_Delete(VectorGL *v, unsigned int index)
////{
////	if (index >= v->count)
////		return;
////
////	v->data[index] = NULL;
////
////	int i, j;
////	void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
////	for (i = 0, j = 0; i < v->count; i++)
////	{
////		if (v->data[i] != NULL)
////		{
////			newarr[j] = v->data[i];
////			j++;
////		}
////	}
////
////	free(v->data);
////
////	v->data = newarr;
////	v->count--;
////}