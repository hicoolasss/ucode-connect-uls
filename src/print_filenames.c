#include "../inc/uls.h"

extern t_flags current_flags;
extern t_dirs_to_show dirs_to_show;
extern t_files_to_show files_to_show;

void print_column(char *str, int max_width)
{
    if (current_flags.G)
    {
        print_color(str);
    }
    else
    {
        mx_printstr(str);
    }
    for (int i = 0; i < max_width - mx_strlen(str); i++)
    {
        mx_printchar(' ');
    }
    mx_printstr(" ");
}

void print_filenames(char **filenames, int num_files)
{

    if (current_flags.is_isatty)
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int max_width = 0;
        for (int i = 0; i < num_files; i++)
        {
            int width = mx_strlen(filenames[i]);
            if (width > max_width)
            {
                max_width = width;
            }
        }

        int cols = w.ws_col / (max_width + 2);
        int rows = (num_files + cols - 1) / cols;

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                int index = row + col * rows;
                if (index < num_files)
                {
                    print_column(filenames[index], max_width);
                    if (col != cols - 1) // если не последняя колонка, добавляем отступ
                    {
                        mx_printchar(' ');
                    }
                }
            }
            mx_printchar('\n');
        }
    }
    else
    {
        for (int i = 0; i < num_files; i++)
        {

            mx_printstr(filenames[i]);
            mx_printchar('\n');
        }
    }
}
