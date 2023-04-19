#include "../inc/uls.h"

t_flags current_flags;
t_dirs_to_show dirs_to_show;
t_files_to_show files_to_show;

int is_directory(const char *path)
{
    struct stat statbuf;
    if (lstat(path, &statbuf) == -1)
    {
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    current_flags.dir_to_show = ".";

    dirs_to_show.num_of_dirs = 0;
    files_to_show.num_of_files = 0;

    if (isatty(STDOUT_FILENO) == 1)
    {
        current_flags.is_isatty = true;
    }

    flags_checker(argv, argc);

    dir = opendir(current_flags.dir_to_show);

    if (dir == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char **filenames = NULL;
    int num_files = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (current_flags.A) // если флаг А задействован то пропускаем . и ..
        {
            if ((entry->d_name[0] == '.' && mx_strlen(entry->d_name) == 1) || (entry->d_name[1] == '.' && mx_strlen(entry->d_name) == 2))
            {
                continue;
            }
        }
        else if (!current_flags.a && entry->d_name[0] == '.') // Пропускаем скрытые файлы, если флаг -a не указан
        {
            continue;
        }
        // Выделяем память для нового имени файла
        char *name = malloc(mx_strlen(entry->d_name) + 1);
        if (name == NULL)
        {
            exit(EXIT_FAILURE);
        }
        mx_strcpy(name, entry->d_name);

        // Добавляем имя файла в массив
        filenames = realloc(filenames, (num_files + 1) * sizeof(char *));

        if (filenames == NULL)
        {
            exit(EXIT_FAILURE);
        }

        filenames[num_files] = name;
        num_files++;
    }

    show_files_and_dirs(argc);

    if (current_flags.t)
    {
        sort_by_mtime(filenames, num_files);
    }
    else if (current_flags.u)
    {
        insertion_sort(filenames, num_files);
    }
    else if (current_flags.c)
    {
        ctime_sort(filenames, num_files);
    }
    else if (current_flags.S)
    {
        sort_by_size(filenames, num_files);
    }
    else
        sortStrings(filenames, num_files);

    if (current_flags.r)
    {
        reverse_array(filenames, num_files);
    }
    if (current_flags.l && mx_strcmp(current_flags.dir_to_show, ".") == 0)
    {
        print_l(current_flags.dir_to_show, current_flags.is_isatty);
    }
    else if (current_flags.a || current_flags.A)
    {
        print_filenames(filenames, num_files);
    }
    else if (argc >= 1 && mx_strcmp(current_flags.dir_to_show, ".") == 0 && files_to_show.num_of_files == 0)
    {
        print_filenames(filenames, num_files);
    }

    // Освобождаем память
    for (int i = 0; i < num_files; i++)
    {

        free(filenames[i]);
    }

    free(filenames);

    closedir(dir);

    return 0;
}
