/** @file */
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "SwissArmyKnife.h"

Vector* Vector_Ctor()
{
	Vector* v = (Vector*)malloc(sizeof(Vector));
	if(!v)
		panic("malloc failed in Vector_Ctor");

	v->data = NULL;
	v->size = 0;
	v->count = 0;

	return v;
}

void Vector_DCtor(Vector* v)
{
	assert(v);

	if(v->count != 0)
		free(v->data);
	free(v);
}

void Vector_Add(Vector* v, void* item)
{
	assert(v);

	// batch add to prevent intense mallocs
	if (v->size == 0)
	{
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
		if(!v->data)
			panic("malloc failed in Vector_Add");
		memset(v->data, '\0', sizeof(void) * v->size);
	}

	// condition to increase v->data:
	// last slot exhausted
	if (v->size == v->count)
	{
		v->size *= 2;
		v->data = realloc(v->data, sizeof(void*) * v->size);
	}

	v->data[v->count] = item;
	v->count++;
}

void Vector_Set(Vector* v, unsigned int index, void* item)
{
	assert (index < v->count);

	v->data[index] = item;
}

void* Vector_Get(Vector* v, unsigned int index)
{
	assert(v);

	if (index >= v->count)
		return;

	return v->data[index];
}

void Vector_Delete(Vector *v, unsigned int index)
{
	assert(v);

	if (index >= v->count)
		return;

	v->data[index] = NULL;

	void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
	if(!newarr)
		panic("malloc failed in Vector_Delete");

	for (unsigned int i = 0, j = 0; i < v->count; i++)
	{
		if (v->data[i] != NULL)
		{
			newarr[j] = v->data[i];
			j++;
		}
	}

	free(v->data);

	v->data = newarr;
	v->count--;
}