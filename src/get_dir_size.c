#include "../inc/uls.h"

// Функция для рекурсивного подсчета размера файлов и директорий
int get_dir_size(const char *dirPath)
{
    struct stat st;
    int total = 0;
    DIR *dir;
    struct dirent *entry;
    char filePath[100];

    dir = opendir(dirPath);
    if (dir == NULL)
    {
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if ((unsigned long)mx_strlen(dirPath) + (unsigned long)mx_strlen(entry->d_name) + 2 > sizeof(filePath))
        {
            continue;
        }
        mx_strcpy(filePath, dirPath);
        mx_strcat(filePath, "/");
        mx_strcat(filePath, entry->d_name);

        if (lstat(filePath, &st) == -1)
        {
            continue;
        }

        if (S_ISDIR(st.st_mode))
        { // если это директория
            if (mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }
            total += get_dir_size(filePath);
        }
        else
        { // если это файл
            total += st.st_blocks;
        }
    }

    closedir(dir);
    return total;
}
