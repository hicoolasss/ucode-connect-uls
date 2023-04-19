#include "../inc/uls.h"

extern t_flags current_flags;
extern t_dirs_to_show dirs_to_show;

void print_directory_contents(const char *directory_name)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory_name);

    if (dir == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char **filenames = NULL;
    int num_files = 0;

    while ((entry = readdir(dir)) != NULL)
    {

        if (!current_flags.a && entry->d_name[0] == '.')
        {
            continue;
        }

        char *name = malloc(mx_strlen(entry->d_name) + 1);
        if (name == NULL)
        {
            exit(EXIT_FAILURE);
        }
        mx_strcpy(name, entry->d_name);

        filenames = mx_realloc(filenames, (num_files + 1) * sizeof(char *));

        if (filenames == NULL)
        {
            exit(EXIT_FAILURE);
        }

        filenames[num_files] = name;
        num_files++;
    }

    dirs_to_show.num_of_files_in_dirs = num_files;


    sortStrings(filenames, num_files);

    if (current_flags.l)
    {
        print_l(directory_name, current_flags.is_isatty);
    }
    else if (current_flags.a)
    {
        print_filenames(filenames, num_files);
    }
    else
    {
        print_filenames(filenames, num_files);
    }

    for (int i = 0; i < num_files; i++)
    {

        free(filenames[i]);
    }

    free(filenames);

    closedir(dir);
}
