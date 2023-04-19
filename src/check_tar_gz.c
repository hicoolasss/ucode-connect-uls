#include "../inc/uls.h"

bool check_tar_gz(char *haystack, char *needle)
{
    if (mx_strstr(haystack, needle) != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
