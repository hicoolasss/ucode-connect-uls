#include "../inc/uls.h"

extern t_flags current_flags;

void print_color(char *filename)
{
    struct stat st;

    if (current_flags.G)
    {
        if (stat(filename, &st) == 0)
        {
            switch (st.st_mode & S_IFMT)
            {
            case S_IFCHR:
                mx_printstr(BLUEYELLOW);
                break;
            case S_IFBLK:
                mx_printstr(BLUECYAN);
                break;
            case S_IFIFO:
                mx_printstr(YELLOW);
                break;
            case S_IFLNK:
                mx_printstr(MAGENTA);
                break;
            case S_IFSOCK:
                mx_printstr(GREEN);
                break;
            case S_IFDIR:
                if (st.st_mode & S_IWOTH)
                {
                    if (st.st_mode & S_ISTXT)
                    {
                        mx_printstr(BLACKGREEN);
                    }
                    else
                    {
                        mx_printstr(BLACKYELLOW);
                    }
                }
                else
                {
                    mx_printstr(BLUE);
                }
                break;
            default:
                if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                {
                    if (st.st_mode & S_ISUID)
                    {
                        mx_printstr(BLACKRED);
                    }
                    else if (st.st_mode & S_ISGID)
                    {
                        mx_printstr(BLACKCYAN);
                    }
                    else
                    {
                        mx_printstr(RED);
                    }
                }
                else
                {
                    mx_printstr(BLACK);
                }
                break;
            }
        }
        mx_printstr(filename);
        mx_printstr("\x1b[0m");
    }
    else
    {
        mx_printstr(filename);
    }
}
