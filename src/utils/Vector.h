#pragma once

typedef struct {
	void** data;
	unsigned int size;
	unsigned int count;
} Vector;

/**
 * @brief Vector constructor
 * @returns Vector
 */
Vector* Vector_Ctor();

/**
 * @brief Vector deconstructor
 * @param v Vector to deconstruct
 */
void Vector_DCtor(Vector* v);

/**
 * @brief Add item to vector
 * @param v Vector to add to
 * @param item Item to add
 */
void Vector_Add(Vector* v, void* item);

/**
 * @brief Set item at index
 * @param v Vector to set item to
 * @param index Index of item to set
 * @param item Item to set
 */
void Vector_Set(Vector* v, unsigned int index, void* item);

/**
 * @brief Get item at index
 * @param v Vector to get item from
 * @param index Index of item to get
 * @returns item
 */
void* Vector_Get(Vector* v, unsigned int index);

/**
 * @brief Delete item at index
 * @param v Vector to delete item from
 * @param index Index to delete at
 */
void Vector_Delete(Vector* v, unsigned int index);