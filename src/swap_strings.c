#include "../inc/uls.h"

// Функция для обмена двух строк в массиве
void swapStrings(char **arr, int i, int j) {
    
    char *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;

}
