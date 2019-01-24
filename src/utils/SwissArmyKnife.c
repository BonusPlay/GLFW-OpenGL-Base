/** @file */
#include "SwissArmyKnife.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

unsigned int strlstchar(const char* str, const char ch)
{
	assert(str);
	const char* chptr = strrchr(str, ch);
	return chptr - str + 1;
}

char* concatc(const char* s1, const char s2)
{
	assert(s1);

	const unsigned int size = strlen(s1) + 2; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	if (!result)
		panic("malloc failed in concatc");

	CheckedMemory(strcpy_s(result, size, s1));
	CheckedMemory(strcat_s(result, size, s2));
	return result;
}

char* concat2(const char *s1, const char *s2)
{
	assert(s1);
	assert(s2);

	const unsigned int size = strlen(s1) + strlen(s2) + 1; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	if (!result)
		panic("malloc failed in concat2");

	CheckedMemory(strcpy_s(result, size, s1));
	CheckedMemory(strcat_s(result, size, s2));
	return result;
}

char* concat3(const char* s1, const char* s2, const char* s3)
{
	assert(s1);
	assert(s2);

	const unsigned int size = strlen(s1) + strlen(s2) + strlen(s3) + 1; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	if (!result)
		panic("malloc failed in concat3");

	CheckedMemory(strcpy_s(result, size, s1));
	CheckedMemory(strcat_s(result, size, s2));
	CheckedMemory(strcat_s(result, size, s3));
	return result;
}

char* concat4(const char* s1, const char* s2, const char* s3, const char* s4)
{
	const unsigned int size = strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + 1; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	if (!result)
		panic("malloc failed in concat4");

	CheckedMemory(strcpy_s(result, size, s1));
	CheckedMemory(strcat_s(result, size, s2));
	CheckedMemory(strcat_s(result, size, s3));
	CheckedMemory(strcat_s(result, size, s4));
	return result;
}

void panic(const char* str, ...)
{
	assert(str);

	va_list argptr;
	va_start(argptr, str);
	vfprintf_s(stderr, str, argptr);
	va_end(argptr);

	exit(1);
}