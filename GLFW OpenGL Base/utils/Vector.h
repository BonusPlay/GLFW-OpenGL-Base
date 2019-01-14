#pragma once

typedef struct {
	void** data;
	unsigned int size;
	unsigned int count;
} Vector;

Vector* Vector_Ctor();
void Vector_DCtor(Vector* v);

void Vector_Add(Vector* v, void* item);
void Vector_Set(Vector* v, unsigned int index, void* item);
void* Vector_Get(Vector* v, unsigned int index);
void Vector_Delete(Vector* v, unsigned int index);