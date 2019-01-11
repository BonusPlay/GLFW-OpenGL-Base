#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector* Vector_Ctor()
{
	Vector* v = (Vector*)malloc(sizeof(Vector));

	v->data = NULL;
	v->size = 0;
	v->count = 0;

	return v;
}

void Vector_DCtor(Vector* v)
{
	free(v->data);
}

int Vector_Count(Vector* v)
{
	return v->count;
}

void Vector_Add(Vector* v, void* item)
{
	// batch add to prevent intense mallocs
	if (v->size == 0)
	{
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
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

void Vector_Set(Vector* v, int index, void* item)
{
	if (index >= v->count)
		return;

	v->data[index] = item;
}

void* Vector_Get(Vector* v, int index)
{
	if (index >= v->count)
		return;

	return v->data[index];
}

void Vector_Delete(Vector *v, int index)
{
	if (index >= v->count)
		return;

	v->data[index] = NULL;

	int i, j;
	void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
	for (i = 0, j = 0; i < v->count; i++)
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