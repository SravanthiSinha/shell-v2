#ifndef _UTILS_H_
#define _UTILS_H_

int is_dir(const char *filepath);
int are_numbers(char **args);
int isNumericChar(char x);
int _atoi(char *input);
void swap(char *a, char *b);
int exe_exists(char *path);
void print_array(char **arr);
void free_array(char **arr);
int array_size(char **arr);

#endif
