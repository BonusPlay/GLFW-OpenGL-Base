#pragma once

// https://stackoverflow.com/q/12167093
/**
 * \brief Gets index of first occurence of char in string.
 * \param str String to search
 * \param ch char to find
 */
unsigned int strlstchar(const char *str, const char ch);

//https://stackoverflow.com/a/8465083
// these functions concats 2 strings together. User is responsible to call free on all strings.
char* concatc(const char* s1, const char s2);
char* concat2(const char* s1, const char* s2);
char* concat3(const char* s1, const char* s2, const char* s3);
char* concat4(const char* s1, const char* s2, const char* s3, const char* s4);

/**
 * \brief Prints error output and exits the program gracefully
 * \param str format string
 * \param ... parameters for formatted string
 */
void panic(const char* str, ...);