#pragma once
#include <unistd.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
//#include <malloc.h>
#include <malloc/malloc.h>
typedef struct s_list
{
    void *data; //char
    struct s_list *next;
} t_list;

t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_back(t_list **head);
void mx_pop_front(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *list, bool (*cmp)(void *a, void *b));
void mx_clear_list(t_list **list);

void mx_printchar(char c);
void mx_print_unicode(wchar_t c);
void mx_printint(int n);
void mx_print_strarr(char **arr, const char *delim);
void mx_printstr(const char *s);
void mx_printerr(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
void mx_foreach(const int *arr, int size, void (*f)(int));
void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

double mx_pow(double n, unsigned int pow);
unsigned long mx_hex_to_nbr(const char *hex);

int mx_strlen(const char *s);
int mx_strcmp(const char *s1, const char *s2);
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);
int mx_count_words(const char *str, char delimiter);
int mx_count_substr(const char *str, const char *sub);
int mx_strncmp(const char *s1, const char *s2, int n);
int mx_sqrt(int x);
int mx_get_char_index(const char *str, char c);
int mx_get_substr_index(const char *str, const char *sub);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);
int mx_memcmp(const void *s1, const void *s2, size_t n);
int mx_atoi(const char *str);
int mx_tolower(int c);
int mx_toupper(int c);
int mx_strcasecmp(const char *s1, const char *s2);

char *mx_strtrim(const char *str);
char *mx_strcat(char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
char *mx_strnew(const int size);
char *mx_nbr_to_hex(unsigned long nbr);
char *mx_itoa(int number);
char *mx_strchr(const char *s, int c);
char *mx_strstr(const char *haystack, const char *needle);
char *mx_strdup(const char *str);
char *mx_strjoin(char const *s1, char const *s2);
char *mx_strndup(const char *str, size_t n);
char **mx_strsplit(const char *s, char c);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_del_extra_spaces(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
char *mx_file_to_str(const char *filename);

bool mx_isalpha(int c);
bool mx_isspace(char c);
bool mx_isdigit(int c);
bool mx_islower(int c);
bool mx_isupper(int c);
bool mx_is_node(t_list *list, char *data);

char *mx_strrejoin(char *s1, char const *s2);
