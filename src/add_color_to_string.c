#include "../inc/uls.h"

char *add_color_to_string(char *str, const char* str1, const char* str2) {

    // Определяем длину каждой строки
    size_t str_len = mx_strlen(str);
    size_t str1_len = mx_strlen(str1);
    size_t str2_len = mx_strlen(str2);
    
    // Выделяем память для новой строки
    char* new_str = malloc((str_len + str1_len + str2_len + 1) * sizeof(char));
    
    if (new_str == NULL) {
        exit(EXIT_FAILURE);
    }
    
    // Копируем str1 в начало новой строки
    mx_memcpy(new_str, str1, str1_len * sizeof(char));
    
    // Копируем str в середину новой строки
    mx_memcpy(new_str + str1_len, str, str_len * sizeof(char));
    
    // Копируем str2 в конец новой строки
    mx_memcpy(new_str + str1_len + str_len, str2, str2_len * sizeof(char));
    
    // Добавляем нулевой символ в конец новой строки
    new_str[str_len + str1_len + str2_len] = '\0';
    
    return new_str;


}
