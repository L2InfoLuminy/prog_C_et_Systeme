#ifndef _MYSTRING_H
#define _MYSTRING_H

#include <stdlib.h>
#include <string.h>

size_t mystring_strlen (char const s[]);

char* mystring_strch (char const s[], int c);
char* mystring_strrch (char const s[], int c);

char* mystring_strpbrk (char const s[], char const *accept);

int mystring_strcmp (char const string1[], char const string2[]);
int mystring_strncmp (char const string1[], char const string2[], size_t n);
int mystring_compareChar (char char1, char char2);
size_t mystring_commonPrefixLength (char const s1[], char const s2[]);
size_t mystring_commonPrefixLengthUpTo (char const s1[], char const s2[], int n);

char* mystring_strstr (char const string[], char const needle[]);

void mystring_strcpy (char target[], char const source[]);
void mystring_strncpy (char target[], char const source[], size_t n);

char* mystring_strcat (char target[], char const source[]);
char* mystring_strncat (char target[], char const source[], size_t n);

size_t mystring_strspn (char const string[], char const accept[]);
size_t mystring_strcspn (char const string[], char const reject[]);

char* mystring_strdup (char const string[]);
char* mystring_strndup (char const string[], size_t max_length);

char* mystring_trim (char const string[], char const blanks[]);

int mystring_memcmp (const void *memory1, const void *memory2, size_t n);

void* mystring_memset (void *memory, int value, size_t n);
#endif
