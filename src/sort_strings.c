#include "../inc/uls.h"

int compare(const char *str1, const char *str2) {
    
    if (*str1 == '.') {
        
        str1++;
    
    }

    if (*str2 == '.') {
        
        str2++;
    
    }
    
    return mx_strcmp(str1, str2);

}

// Функция для сортировки массива строк
void sortStrings(char **arr, int n)
{
    // Сортировка вставками
    for (int i = 1; i < n; i++)
    {

        for (int j = i; j > 0 && compareStrings(arr[j - 1], arr[j]) > 0; j--)
        {

            swapStrings(arr, j - 1, j);
        }
    }
}

void reverse_array(char **arr, int n)
{
    int i, j;
    char *temp;

    for (i = 0, j = n - 1; i < j; i++, j--)
    {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void sort_by_mtime(char *files[], int len)
{
    int i, j;
    struct stat statbuf1, statbuf2;

    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (stat(files[i], &statbuf1) == -1 || stat(files[j], &statbuf2) == -1)
            {
                exit(EXIT_FAILURE);
            }

            // Compare modification time
            if (statbuf1.st_mtime < statbuf2.st_mtime)
            {
                swapStrings(files, i, j);
            }
            else if (statbuf1.st_mtime == statbuf2.st_mtime)
            {
                if (compare(files[i], files[j]) > 0)
                {
                    swapStrings(files, i, j);
                }
            }
        }
    }
}

void insertion_sort(char *files[], int len)
{
    int i, j;
    struct stat statbuf1, statbuf2;

    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (stat(files[i], &statbuf1) == -1 || stat(files[j], &statbuf2) == -1)
            {
                exit(EXIT_FAILURE);
            }

            // Compare modification time
            if (statbuf1.st_atime < statbuf2.st_atime)
            {
                swapStrings(files, i, j);
            }
            else if (statbuf1.st_atime == statbuf2.st_atime)
            {
                if (compare(files[i], files[j]) > 0)
                {
                    swapStrings(files, i, j);
                }
            }
        }
    }
}

void ctime_sort(char *files[], int len)
{
    int i, j;
    struct stat statbuf1, statbuf2;

    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (stat(files[i], &statbuf1) == -1 || stat(files[j], &statbuf2) == -1)
            {
                exit(EXIT_FAILURE);
            }

            // Compare modification time
            if (statbuf1.st_ctime < statbuf2.st_ctime)
            {
                swapStrings(files, i, j);
            }
            else if (statbuf1.st_ctime == statbuf2.st_ctime)
            {
                if (compare(files[i], files[j]) > 0)
                {
                    swapStrings(files, i, j);
                }
            }
        }
    }
}

void sort_by_size(char *files[], int len)
{
    int i, j;
    struct stat statbuf1, statbuf2;
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (stat(files[i], &statbuf1) == -1 || stat(files[j], &statbuf2) == -1)
            {
                exit(EXIT_FAILURE);
            }

            // Compare modification size
            if (statbuf1.st_size < statbuf2.st_size)
            {
                swapStrings(files, i, j);
            }
            else if (statbuf1.st_size == statbuf2.st_size)
            {
                if (compare(files[i], files[j]) > 0)
                {
                    swapStrings(files, i, j);
                }
            }
        }
    }
}
