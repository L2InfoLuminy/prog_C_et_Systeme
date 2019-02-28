#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mystring.h"

void mystringTest_strlen (void) {
  assert(mystring_strlen("banana") == 6);
  assert(mystring_strlen("x") == 1);
  assert(mystring_strlen("") == 0);
}

void mystringTest_strch (void) {
  char str[] = "bob";

  assert(mystring_strch(str, 'o') == &str[1]);
  assert(mystring_strch(str, 'b') == &str[0]);
  assert(mystring_strch(str, 'y') == NULL);
}

void mystringTest_strrch (void) {
  char str[] = "bobby";

  assert(mystring_strrch(str, 'o') == &str[1]);
  assert(mystring_strrch(str, 'b') == &str[3]);
  assert(mystring_strrch(str, 'x') == NULL);
}

void mystringTest_strpbrk (void) {
  char str[] = "bobby";
  char reject[] = {'a', 'c', 'z', '\0'};
  char accept[] = {'a', 'y', 'z', '\0'};

  assert(mystring_strpbrk(str, reject) == NULL);
  assert(mystring_strpbrk(str, accept) == &str[4]);
}

void mystringTest_compareChar (void) {
  assert(mystring_compareChar('A', 'B') < 0);
  assert(mystring_compareChar('A', 'a') < 0); // yes
  assert(strcmp("Z", "a") < 0);
  assert(mystring_compareChar('Z', 'a') < 0); // and yes
  assert(mystring_compareChar('a', 'a') == 0);
  assert(mystring_compareChar('z', 'y') > 0);
}

void mystringTest_commonPrefixLength (void) {
  char str1[] = "super gastropod disco club";
  char str2[] = "super gastropod on steroids";
  char str3[] = "";
  char str4[] = "bob";

  assert(mystring_commonPrefixLength(str1, str2) == 16);
  assert(mystring_commonPrefixLength(str1, str3) == 0);
  assert(mystring_commonPrefixLength(str1, str4) == 0);
}

void mystringTest_commonPrefixLengthUpTo (void) {
  char str1[] = "super gastropod disco club";
  char str2[] = "super gastropod on steroids";
  char str3[] = "";
  char str4[] = "super gastropod on steroids";

  assert(mystring_commonPrefixLengthUpTo(str1, str2, 3) == 3);
  assert(mystring_commonPrefixLengthUpTo(str1, str2, 18) == 16);
  assert(mystring_commonPrefixLengthUpTo(str1, str2, 100) == 16);
  assert(mystring_commonPrefixLengthUpTo(str1, str3, 100) == 0);
  assert(mystring_commonPrefixLengthUpTo(str3, str3, 1) == 0);
  assert(mystring_commonPrefixLengthUpTo(str2, str4, 100) == 27);
}

void mystringTest_strcmp (void) {
  char str1[] = "super gastropod disco club";
  char str2[] = "super gastropod on steroids";
  char str3[] = "";
  char str4[] = "super gastropod on steroids";

  assert(mystring_strcmp(str1, str2) < 0);
  assert(mystring_strcmp(str2, str1) > 0);
  assert(mystring_strcmp(str3, str1) < 0);
  assert(mystring_strcmp(str1, str3) > 0);
  assert(mystring_strcmp(str2, str4) == 0);
}

void mystringTest_strncmp (void) {
  char str1[] = "super gastropod disco club";
  char str2[] = "super gastropod on steroids";
  char str3[] = "";
  char str4[] = "super gastropod on steroids";

  assert(mystring_strncmp(str1, str2, 15) == 0);
  assert(mystring_strncmp(str2, str1, 17) > 0);
  assert(mystring_strncmp(str3, str1, 0) < 0);
  assert(mystring_strncmp(str1, str3, 2) > 0);
  assert(mystring_strncmp(str2, str4, 6) == 0);
}


void mystringTest_strstr (void) {
  char str[] = "super gastropod on steroids";

  assert(mystring_strstr(str, "oids") == &str[23]);
  assert(mystring_strstr(str, "strop") == &str[8]);
  assert(mystring_strstr(str, "st") == &str[8]);
  assert(mystring_strstr(str, "") == str);
  assert(mystring_strstr("", "needle") == NULL);
}

void mystringTest_strcpy (void) {
  char dest[100];
  char src[] = "super gastropod on steroids";

  mystring_strcpy(dest, src);
  assert(strcmp(dest, src) == 0);
  mystring_strcpy(dest, "");
  assert(strcmp(dest, "") == 0);
}

void mystringTest_strncpy (void) {
  char dest[100];
  char src[] = "super gastropod on steroids";

  mystring_strncpy(dest, src, 5*sizeof(char));
  dest[5] = '\0'; // no null character in the first 5 bytes of src
  assert(strcmp("super", dest) == 0);
  mystring_strncpy(dest, src, 100*sizeof(char));
  assert(strcmp(src, dest) == 0);
}

void mystringTest_strcat (void) {
  char dest[100] = "super gastropod";
  char src[100] = " on steroids";
  char empty_str[100] = "";

  assert(strcmp(mystring_strcat(dest, src), "super gastropod on steroids") == 0);
  assert(strcmp(mystring_strcat(dest, ""), dest) == 0);
  assert(strcmp(mystring_strcat(empty_str, src), src) == 0);
}

void mystringTest_strncat (void) {
  char dest[100] = "super gastropod";
  char src[100] = " on steroids";
  char empty_str[100] = "";

  assert(strcmp(mystring_strncat(dest, src, 3 * sizeof(char)), "super gastropod on") == 0);
  assert(strcmp(mystring_strncat(dest, "", 3 * sizeof(char)), dest) == 0);
  assert(strcmp(mystring_strncat(empty_str, src, 3 * sizeof(char)), " on") == 0);
}

void mystringTest_strspn (void) {
  char str[] = "super gastropod on steroids";

  assert(mystring_strspn(str, "gas") == 1);
  assert(mystring_strspn(str, "gad") == 0);
  assert(mystring_strspn(str, "sprue") == 5);
}

void mystringTest_strcspn (void) {
  char str[] = "super gastropod on steroids";
  //fprintf(stderr, "%ld\n", strcspn(str, "gas"));
  //fprintf(stderr, "%ld\n", strcspn(str, "gadxy"));
  //fprintf(stderr, "%ld\n", strcspn(str, "idxy"));

  assert(mystring_strcspn(str, "gas") == 0);
  assert(mystring_strcspn(str, "gadxy") == 6);
  assert(mystring_strcspn(str, "idxy") == 14);
}

void mystringTest_strdup (void) {
  char *copy = NULL;
  char src[] = "super gastropod on steroids";
  char empty_str[] = "";

  copy = mystring_strdup(src);
  assert(strcmp(copy, src) == 0);
  free(copy);

  copy = mystring_strdup(empty_str);
  assert(strcmp(copy, empty_str) == 0);
  free(copy);
}

void mystringTest_strndup (void) {
  char *copy = NULL;
  char src[] = "super gastropod on steroids";

  copy = mystring_strndup(src, 5);
  assert(strcmp(copy, "super") == 0);
  free(copy);

  copy = mystring_strndup(src, 2000);
  assert(strcmp(copy, src) == 0);
}

void mystringTest_trim (void) {
  char *copy = NULL;

  copy = mystring_trim("  super gastropod       ", " ");
  assert(strcmp(copy, "super gastropod") == 0);
  free(copy);

  copy = mystring_trim(" A B super gastropod  AB A    ", "AB ");
  assert(strcmp(copy, "super gastropod") == 0);
  free(copy);

  copy = mystring_trim(" A B  B C AB A    ", "ABC ");
  assert(strcmp(copy, "") == 0);
  free(copy);

  copy = mystring_trim(" A B  B C AB A    ", "AB ");
  assert(strcmp(copy, "C") == 0);
  free(copy);
}

void mystringTest_memcmp (void) {
  char str1[] = "super gastropod disco club";
  char str2[] = "super gastropod on steroids";
  char str3[] = "";
  char str4[] = "super gastropod on steroids";

  assert(mystring_memcmp(str1, str2, 15) == 0);
  assert(mystring_memcmp(str2, str1, 17) > 0);
  assert(mystring_memcmp(str3, str1, 1) < 0);
  assert(mystring_memcmp(str1, str3, 2) > 0);
  assert(mystring_memcmp(str2, str4, 6) == 0);
}

void mystringTest_memset (void) {
  char str1[] = "super gastropod disco club";

  assert(memcmp(mystring_memset(str1, 32, 6), "      gastropod disco club", 26 * sizeof(char)) == 0);
  assert(memcmp(mystring_memset(str1, 45, 21), "--------------------- club", 26 * sizeof(char)) == 0);
}

int main (void) {
  mystringTest_strlen();
  mystringTest_strch();
  mystringTest_strrch();
  mystringTest_strpbrk();
  mystringTest_compareChar();
  mystringTest_commonPrefixLength();
  mystringTest_commonPrefixLengthUpTo();
  mystringTest_strcmp();
  mystringTest_strncmp();
  mystringTest_strstr();
  mystringTest_strcpy();
  mystringTest_strncpy();
  mystringTest_strcat();
  mystringTest_strncat();
  mystringTest_strspn();
  mystringTest_strcspn();
  mystringTest_strdup();
  mystringTest_strndup();
  mystringTest_trim();
  mystringTest_memcmp();
  mystringTest_memset();
  fprintf(stdout, "tests : 21 / 21 passed\n");
  return EXIT_SUCCESS;
}
