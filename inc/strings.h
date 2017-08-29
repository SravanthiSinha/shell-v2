#ifndef _STRINGS_H_
#define _STRINGS_H_

unsigned int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, int c);
int _strncmp(const char *s1, const char *s2, unsigned int k);
char *_strdup(const char *str);
char *_strndup(char *str, size_t n);
char *_strstr(char *haystack, char *needle);
int _strcasecmp(const char *s1, const char *s2);
char *_strrchr(const char *s, int c);
char *_strcpy(char *dest, const char *src);
char *ltrim(char *src, char delim);
char **_stringsplit(char *str, char delim, int *count);
char *_strrev(char *str);
char *_stradd(const char *s1, const char *s2, char *delim);
void _removeafter(char *s, char delim);
char *_strapp(char *s1, char *s2);
void _memcpy(void *dest, void *src, size_t n);
char *_memset(char *s, char b, unsigned int n);
void swap(char *a, char *b);
void *_realloc(void *ptr, size_t size, size_t msize);
#endif
