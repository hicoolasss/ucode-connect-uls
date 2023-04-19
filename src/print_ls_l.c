#include "../inc/uls.h"

extern t_flags current_flags;

int count_digits(int number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

int find_max(int array[], int size)
{
    int max = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

void print_right_aligned(int num, int width)
{
    if (num == 0)
    {
        for (int i = 0; i < width - 1; i++)
        {
            write(STDOUT_FILENO, " ", 1);
        }
        write(STDOUT_FILENO, "0", 1);
        return;
    }

    int digits = 0;
    int n = num;

    while (n > 0)
    {
        digits++;
        n /= 10;
    }

    int spaces = width - digits;
    while (spaces > 0)
    {
        write(STDOUT_FILENO, " ", 1);
        spaces--;
    }

    char buf[16];
    int len = 0;
    n = num;
    while (n > 0)
    {
        buf[len++] = '0' + (n % 10);
        n /= 10;
    }
    while (len > 0)
    {
        write(STDOUT_FILENO, &buf[--len], 1);
    }
}

void print_l(const char *directory_name, bool is_isatty)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory_name);

    if (dir == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char **filenames = NULL;
    char **pathes = NULL;
    int num_files = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (current_flags.A)
        {
            if ((entry->d_name[0] == '.' && mx_strlen(entry->d_name) == 1) || (entry->d_name[1] == '.' && mx_strlen(entry->d_name) == 2))
            {
                continue;
            }
        }
        else if (!current_flags.a && entry->d_name[0] == '.')
        {
            continue;
        }

        char *name = malloc(mx_strlen(entry->d_name) + 1);
        char *path = (char *)malloc(1024 * sizeof(char));

        if (name == NULL)
        {
            exit(EXIT_FAILURE);
        }

        mx_strcpy(name, entry->d_name);

        mx_memcpy(path, directory_name, mx_strlen(directory_name) * sizeof(char));

        mx_memcpy(path + mx_strlen(directory_name), "/", 1 * sizeof(char));

        mx_memcpy(path + mx_strlen(directory_name) + 1, name, mx_strlen(name) * sizeof(char));

        filenames = realloc(filenames, (num_files + 1) * sizeof(char *));
        pathes = realloc(pathes, (num_files + 1) * sizeof(char *));

        if (filenames == NULL)
        {
            exit(EXIT_FAILURE);
        }

        filenames[num_files] = name;
        pathes[num_files] = path;
        num_files++;
    }

    sortStrings(filenames, num_files);

    for (int i = 0; i < num_files; i++)
    {
        char *path = (char *)malloc(1024 * sizeof(char));

        mx_memcpy(path, directory_name, mx_strlen(directory_name) * sizeof(char));

        mx_memcpy(path + mx_strlen(directory_name), "/", 1 * sizeof(char));

        mx_memcpy(path + mx_strlen(directory_name) + 1, filenames[i], mx_strlen(filenames[i]) * sizeof(char));

        pathes[i] = path;
    }

    struct stat fileStat;
    struct passwd *pw;
    struct group *gr;
    char permissions[11];
    int array[num_files];
    int array_links[num_files];
    int total = 0;

    for (int i = 0; i < num_files; i++)
    {
        if (stat(pathes[i], &fileStat) < 0)
        {
            exit(EXIT_FAILURE);
        }

        total += fileStat.st_blocks;

        array[i] = count_digits(fileStat.st_size);
        array_links[i] = count_digits(fileStat.st_nlink);
    }

    int max = find_max(array, num_files);
    int max_links = find_max(array_links, num_files);

    if (filenames)
    {
        mx_printstr("total ");
        mx_printint((long)total);
        mx_printchar('\n');
    }
    else if (!filenames && total == 0)
    {
        mx_printchar('\n');
        return;
    }

    for (int i = 0; i < num_files; i++)
    {

        if (stat(pathes[i], &fileStat) < 0)
        {
            exit(EXIT_FAILURE);
        }

        // Permissions
        permissions[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
        permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
        permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
        permissions[10] = '\0';

        // User and Group
        pw = getpwuid(fileStat.st_uid);
        gr = getgrgid(fileStat.st_gid);

        // Time
        time_t current_time = time(NULL);
        double time_difference = difftime(current_time, fileStat.st_mtime);
        double six_months_seconds = 6 * 30 * 24 * 60 * 60;
        char *time_temp = 4 + ctime((time_t *)&fileStat.st_mtime);

        char *time;
        if (time_difference > six_months_seconds)
        {
            time = mx_strndup(time_temp, mx_strlen(time_temp) - 14);
            // Add the year to the time string
            struct tm *file_time = localtime(&fileStat.st_mtime);
            int year = file_time->tm_year + 1900;
            char year_str[6] = {0};
            year_str[0] = ' ';
            year_str[1] = '0' + (year / 1000) % 10;
            year_str[2] = '0' + (year / 100) % 10;
            year_str[3] = '0' + (year / 10) % 10;
            year_str[4] = '0' + year % 10;
            year_str[5] = '\0';
            char *new_time = (char *)malloc(mx_strlen(year_str) + 1);
            mx_strcpy(new_time, time);
            mx_strcat(new_time, year_str);
            free(time);
            time = new_time;
        }
        else
        {
            time = mx_strndup(time_temp, mx_strlen(time_temp) - 9);
        }
        mx_printstr(permissions);
        mx_printstr("  ");
        print_right_aligned(fileStat.st_nlink, max_links);
        mx_printchar(' ');
        mx_printstr(pw->pw_name);
        mx_printchar(' ');
        mx_printstr(gr->gr_name);
        mx_printchar(' ');
        print_right_aligned(fileStat.st_size, max);
        mx_printchar(' ');
        mx_printstr(time);
        mx_printchar(' ');
        if (is_isatty)
        {
            if (current_flags.G)
            {
                print_color(filenames[i]);
            }
            else
            {
                mx_printstr(filenames[i]);
            }
            mx_printchar('\n');
        }
        else
        {
            mx_printstr(filenames[i]);
            mx_printchar('\n');
        }
    }
}

void print_l_file(char *filename, bool is_isatty)
{

    struct stat fileStat;
    struct passwd *pw;
    struct group *gr;
    char permissions[11];
    if (stat(filename, &fileStat) < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Permissions
    permissions[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
    permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    // User and Group
    pw = getpwuid(fileStat.st_uid);
    gr = getgrgid(fileStat.st_gid);

    // Time
    time_t current_time = time(NULL);
    double time_difference = difftime(current_time, fileStat.st_mtime);
    double six_months_seconds = 6 * 30 * 24 * 60 * 60;
    char *time_temp = 4 + ctime((time_t *)&fileStat.st_mtime);

    char *time;
    if (time_difference > six_months_seconds)
    {
        time = mx_strndup(time_temp, mx_strlen(time_temp) - 14);
        // Add the year to the time string
        struct tm *file_time = localtime(&fileStat.st_mtime);
        int year = file_time->tm_year + 1900;
        char year_str[6] = {0};
        year_str[0] = ' ';
        year_str[1] = '0' + (year / 1000) % 10;
        year_str[2] = '0' + (year / 100) % 10;
        year_str[3] = '0' + (year / 10) % 10;
        year_str[4] = '0' + year % 10;
        year_str[5] = '\0';
        char *new_time = (char *)malloc(mx_strlen(year_str) + 1);
        mx_strcpy(new_time, time);
        mx_strcat(new_time, year_str);
        free(time);
        time = new_time;
    }
    else
    {
        time = mx_strndup(time_temp, mx_strlen(time_temp) - 9);
    }
    mx_printstr(permissions);
    mx_printstr("  ");
    int count1 = count_digits(fileStat.st_nlink);
    print_right_aligned(fileStat.st_nlink, count1);
    mx_printchar(' ');
    mx_printstr(pw->pw_name);
    mx_printchar(' ');
    mx_printstr(gr->gr_name);
    mx_printchar(' ');
    int count2 = count_digits(fileStat.st_nlink);
    print_right_aligned(fileStat.st_size, count2);
    mx_printchar(' ');
    mx_printstr(time);
    mx_printchar(' ');
    if (is_isatty)
    {
        if (current_flags.G)
        {
            print_color(filename);
        }
        else
        {
            mx_printstr(filename);
        }
        mx_printchar('\n');
    }
    else
    {
        mx_printstr(filename);
        mx_printchar('\n');
    }
}
