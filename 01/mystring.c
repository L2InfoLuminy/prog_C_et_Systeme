#include "mystring.h"

size_t mystring_strlen (char const s[]) {
  int len;

  for (len = 0; s[len]; len++);

  return (long int) len;
}

char* mystring_strch (char const s[], int c) {
  while (*s) {
    if (*s == c)
      return (char *) s;
    s++;
  }
  return NULL;
}

char* mystring_strrch (char const s[], int c) {
  char *needle = NULL;
  while (*s) {
    if (*s == c) needle = (char *) s;
    s++;
  }
  return needle;
}

char* mystring_strpbrk (char const s[], char const *accept) {
  char const *occ;

  while (*s) {
    occ = accept;
    while (*occ) {
      if (*s == *occ) return (char *) s;
      occ++;
    }
    s++;
  }
  return NULL;
}

int mystring_strcmp (char const string1[], char const string2[]) {
  int equal_prefix_len = (int) mystring_commonPrefixLength(string1, string2);

  return mystring_compareChar(string1[equal_prefix_len], string2[equal_prefix_len]);
}

int mystring_strncmp (char const string1[], char const string2[], size_t n) {
  int equal_prefix_len = (int) mystring_commonPrefixLengthUpTo(string1, string2, n);

  return mystring_compareChar(string1[equal_prefix_len], string2[equal_prefix_len]);
}

int mystring_compareChar (char char1, char char2) {
  return char1 - char2;
}

size_t mystring_commonPrefixLength (char const s1[], char const s2[]) {
  size_t prefix_len = 0;

  while (*s1 && (*s1++ == *s2++))
    prefix_len++;
  return prefix_len;
}

size_t mystring_commonPrefixLengthUpTo (char const s1[], char const s2[], int n) {
  size_t prefix_len = 0;
  if (n >= (int) strlen(s1)) return mystring_commonPrefixLength(s1, s2);

  for (int i = 0; s1[i] && i < n && (s1[i] == s2[i]); ++i)
    prefix_len++;
  return prefix_len;
}

char* mystring_strstr (char const string[], char const needle[]) {
  int equal_prefix_len;
  int needle_len  = (int) strlen(needle);
  while (*string) {
    equal_prefix_len = mystring_commonPrefixLength(string, needle);
    if (equal_prefix_len == needle_len) return (char *) string;
    string++;
  }
  return NULL;
}

void mystring_strcpy (char target[], char const source[]) {
  int i;
  for (i = 0; source[i]; ++i)
    target[i] = source[i];

  if (source[i] == '\0')
    target[i] = source[i];
}

void mystring_strncpy (char target[], char const source[], size_t n) {
  int i;
  size_t src_len = strlen(source), boundary;
  boundary = n < src_len ? n : src_len;

  for (i = 0; i < (int) boundary; ++i)
    target[i] = source[i];

  while (src_len < n)
    target[src_len++] = '\0';
}

char* mystring_strcat (char target[], char const source[]) {
  int i;

  for (i = strlen(target); *source; ++i)
    target[i] = *source++;

  target[i] = '\0';
  return target;
}

char* mystring_strncat (char target[], char const source[], size_t n) {
  size_t from = strlen(target);
  size_t i = 0;

  while (i < n)
    target[from++] = source[i++];

  target[from] = '\0';
  return target;
}

size_t mystring_strspn (char const string[], char const accept[]) {
  size_t count = 0;
  int accept_len = (int) strlen(accept);
  int match = 0;

  while (*string) {
    match = 0;
    for (int i = 0; i < accept_len; ++i) {
      if (*string == accept[i]) {
        count++;
        match = 1;
        break;
      }
    }
    if (!match) return count;
    string++;
  }
  return count;
}

size_t mystring_strcspn (char const string[], char const reject[]) {
  size_t count = 0;
  int reject_len = (int) strlen(reject);

  while (*string) {
    for (int i = 0; i < reject_len; ++i)
      if (*string == reject[i]) return count;
    count++;
    string++;
  }
  return count;
}

char* mystring_strdup (char const string[]) {
  char *copy = calloc((int) strlen(string) + 1, sizeof(char));

  for (int i = 0; *string; ++i)
    copy[i] = *string++;

  return copy;
}

char* mystring_strndup (char const string[], size_t max_length) {
  size_t str_len = strlen(string);
  if (max_length >= str_len) return mystring_strdup(string);

  char *copy = calloc((int) max_length + 1, sizeof(char));

  for (int i = 0; i < (int) max_length; ++i)
    copy[i] = string[i];

  return copy;
}

char* mystring_trim (char const string[], char const blanks[]) {
  int match = 1;
  size_t blanks_len = strlen(blanks);
  char const *from = string;
  char const *to = string + (strlen(string) -1);

  while (*from) {
    match = 0;
    for (size_t i = 0; i < blanks_len; ++i) {
      if (*from == blanks[i]) {
        match = 1;
        from++;
        break;
      }
    }
    if (!match) break;
  }

  while (to > string) {
    match = 0;
    for (size_t i = 0; i < blanks_len; ++i) {
      if (*to == blanks[i]) {
        match = 1;
        to--;
        break;
      }
    }
    if (!match) break;
  }

  if (to < from) return calloc(1, sizeof(char));

  char *str = calloc((to - from) + 2, sizeof(char));
  int i = 0;
  while (from <= to)
    str[i++] = *from++;

  return str;
}

int mystring_memcmp (const void *memory1, const void *memory2, size_t n) {
  const unsigned char *p1 = (const unsigned char *) memory1;
  const unsigned char *p2 = (const unsigned char *) memory2;
  while (n--) {
    if (*p1++ != *p2++)
      return *(p1 - 1) - *(p2 -1);
  }
  return 0;
}

void* mystring_memset (void *memory, int value, size_t n) {
  char *mem = memory;
  while (n--)
    *mem++ = value;
  return memory;
}
