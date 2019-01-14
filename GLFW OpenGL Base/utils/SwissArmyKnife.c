#include "SwissArmyKnife.h"
#include <string.h>
#include <stdlib.h>

unsigned int strlstchar(const char *str, const char ch)
{
	const char* chptr = strrchr(str, ch);
	return chptr - str + 1;
}

char* concat2(const char *s1, const char *s2)
{
	const unsigned int size = strlen(s1) + strlen(s2) + 1; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	strcpy_s(result, size, s1);
	strcat_s(result, size, s2);
	return result;
}

char* concat3(const char* s1, const char* s2, const char* s3)
{
	const unsigned int size = strlen(s1) + strlen(s2) + strlen(s3) + 1; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	strcpy_s(result, size, s1);
	strcat_s(result, size, s2);
	strcat_s(result, size, s3);
	return result;
}

char* concat4(const char* s1, const char* s2, const char* s3, const char* s4)
{
	const unsigned int size = strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4) + 1; // +1 for the null-terminator
	char* result = malloc(size * sizeof(char));
	strcpy_s(result, size, s1);
	strcat_s(result, size, s2);
	strcat_s(result, size, s3);
	strcat_s(result, size, s4);
	return result;
}