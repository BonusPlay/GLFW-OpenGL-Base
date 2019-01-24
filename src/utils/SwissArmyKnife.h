#pragma once

// https://stackoverflow.com/q/12167093
/**
 * @brief Gets index of first occurence of char in string.
 * @param str String to search
 * @param ch char to find
 * @returns index of char in string
 */
unsigned int strlstchar(const char *str, const char ch);

//https://stackoverflow.com/a/8465083
/**
 * @brief concats string and char together
 * @param s1 string to concat
 * @param s2 char to concat
 * @returns resulted string
 */
char* concatc(const char* s1, const char s2);

/**
 * @brief concats 2 strings together
 * @param s1 string to concat
 * @param s2 string to concat
 * @returns resulted string
 */
char* concat2(const char* s1, const char* s2);

/**
 * @brief concats 3 strings together
 * @param s1 string to concat
 * @param s2 string to concat
 * @param s3 string to concat
 * @returns resulted string
 */
char* concat3(const char* s1, const char* s2, const char* s3);

/**
 * @brief concats 4 strings together
 * @param s1 string to concat
 * @param s2 string to concat
 * @param s3 string to concat
 * @param s4 string to concat
 * @returns resulted string
 */
char* concat4(const char* s1, const char* s2, const char* s3, const char* s4);

/**
 * @brief Prints error output and exits the program gracefully
 * @param str format string
 * @param ... parameters for formatted string
 */
void panic(const char* str, ...);

/**
 * @brief helper macro to handle errors in memcpy_s, strncpy_s, strcat_s
 */
#define CheckedMemory(x) if(x) panic("Memory operation failed!")