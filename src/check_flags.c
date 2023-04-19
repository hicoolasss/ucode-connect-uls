#include "../inc/uls.h"

extern t_flags current_flags;

extern t_dirs_to_show dirs_to_show;

extern t_files_to_show files_to_show;


int is_regular_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return 0;
    }
    return S_ISREG(path_stat.st_mode);
}

bool contains_char(char *str, char ch)
{
    while (*str)
    { // пока не достигнут конец строки
        if (*str == ch)
        {
            return true; // символ найден
        }
        str++; // перейти к следующему символу строки
    }
    return false; // символ не найден
}

void flags_checker(char **flags, int flags_count)
{
    if (flags_count < 1)
    {
        exit(-1);
    }
    struct stat fileStat;
    for (int i = 1; i < flags_count; i++)
    {
        if (flags[i][0] != '-' && stat(flags[i], &fileStat) < 0)
        {
            perror(mx_strjoin("uls: ", flags[i]));
            current_flags.no_such_file_err = true;
            continue;
        }

        if (flags[i][0] != '-' && is_directory(flags[i]))
        {
            current_flags.show_dir = true;
            current_flags.dir_to_show = flags[i];
            dirs_to_show.num_of_dirs++;
        }

        if (flags[i][0] != '-' && is_regular_file(flags[i]))
        {
            current_flags.show_file = true;
            files_to_show.num_of_files++;
        }
    }

    dirs_to_show.dirs = (char **)malloc(dirs_to_show.num_of_dirs * sizeof(char *));

    for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
    {
        dirs_to_show.dirs[i] = (char *)malloc(50 * sizeof(char));
    }

    files_to_show.files = (char **)malloc(files_to_show.num_of_files * sizeof(char *));

    for (int i = 0; i < files_to_show.num_of_files; i++)
    {
        files_to_show.files[i] = (char *)malloc(50 * sizeof(char));
    }

    int count = 0;
    int count_of_files = 0;

    for (int i = 1; i < flags_count; i++)
    {

        if (flags[i][0] != '-' && is_directory(flags[i]))
        {

            dirs_to_show.dirs[count] = flags[i];
            count++;
        }
        else if (flags[i][0] != '-' && !is_directory(flags[i]))
        {

            files_to_show.files[count_of_files] = flags[i];
            count_of_files++;
        }
    }

    if (flags_count < 1)
    {
        exit(-1);
    }

    for (int i = 1; i < flags_count; i++)
    {

        if (mx_strcmp(flags[i], "-a") == 0)
        {
            current_flags.a = true;
        }
        else if (mx_strcmp(flags[i], "-A") == 0)
        {
            current_flags.A = true;
        }
        else if (mx_strcmp(flags[i], "-l") == 0)
        {
            current_flags.l = true;
        }
        else if (mx_strcmp(flags[i], "-i") == 0)
        {
            current_flags.i = true;
        }
        else if (mx_strcmp(flags[i], "-r") == 0)
        {
            current_flags.r = true;
        }
        else if (mx_strcmp(flags[i], "-t") == 0)
        {
            current_flags.t = true;
        }
        else if (mx_strcmp(flags[i], "-u") == 0)
        {
            current_flags.u = true;
        }
        else if (mx_strcmp(flags[i], "-c") == 0)
        {
            current_flags.c = true;
        }
        else if (mx_strcmp(flags[i], "-S") == 0)
        {
            current_flags.S = true;
        }
        else if (mx_strcmp(flags[i], "-G") == 0)
        {
            current_flags.G = true;
        }
        else if (flags[i][0] != '-' && is_directory(flags[i]))
        {
            current_flags.show_dir = true;
            current_flags.dir_to_show = flags[i];
        }
        else if ((flags[i][0] == '-') && mx_strlen(flags[i]) > 1)
        {

            for (int j = 0; j < mx_strlen(flags[i]); j++)
            {
                if (contains_char("-laAhrtucSG", flags[i][j]))

                {
                    if (flags[i][j] == 'a')
                    {
                        current_flags.a = true;
                    }
                    else if (flags[i][j] == 'l')
                    {
                        current_flags.l = true;
                    }
                    else if (flags[i][j] == 'A')
                    {
                        current_flags.A = true;
                    }
                    else if (flags[i][j] == 'i')
                    {
                        current_flags.i = true;
                    }
                    else if (flags[i][j] == 'r')
                    {
                        current_flags.r = true;
                    }
                    else if (flags[i][j] == 't')
                    {
                        current_flags.t = true;
                    }
                    else if (flags[i][j] == 'u')
                    {
                        current_flags.u = true;
                    }
                    else if (flags[i][j] == 'c')
                    {
                        current_flags.c = true;
                    }
                    else if (flags[i][j] == 'S')
                    {
                        current_flags.S = true;
                    }
                    else if (flags[i][j] == 'G')
                    {
                        current_flags.G = true;
                    }
                }
                else
                {
                    mx_printerr("uls: illegal option -- ");
                    write(2, &flags[i][j], 1);
                    mx_printerr("\n");
                    mx_printerr("usage: uls [-AGSacirtu] [file ...]\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}
