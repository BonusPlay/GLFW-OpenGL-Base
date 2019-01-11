#pragma once

typedef struct {
	void** data;
	int size;
	int count;
} Vector;

Vector* Vector_Ctor();
void Vector_DCtor(Vector* v);

int Vector_Count(Vector* v);
void Vector_Add(Vector* v, void* item);
void Vector_Set(Vector* v, int index, void* item);
void* Vector_Get(Vector* v, int index);
void Vector_Delete(Vector* v, int index);