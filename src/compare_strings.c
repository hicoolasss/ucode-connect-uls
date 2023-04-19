#include "../inc/uls.h"

int isDirectory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int isExecutable(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return (path_stat.st_mode & S_IXUSR);
}

// Функция для сравнения двух строк
int compareStrings(const char *str1, const char *str2) {
    
    int startsWithDot1 = (*str1 == '.');
    int startsWithDot2 = (*str2 == '.');

    if (startsWithDot1 && !startsWithDot2)
        return -1;
    if (!startsWithDot1 && startsWithDot2)
        return 1;


    if (*str1 == '.') {
        
        str1++;
    
    }
    
    if (*str2 == '.') {
        
        str2++;
    
    }

    int isDir1 = isDirectory(str1);
    int isDir2 = isDirectory(str2);
    int isExec1 = isExecutable(str1);
    int isExec2 = isExecutable(str2);

    if ((isDir1 || isExec1) && !(isDir2 || isExec2))
        return 1;
    if (!(isDir1 || isExec1) && (isDir2 || isExec2))
        return -1;
        
    return mx_strcmp(str1, str2);

} 
