#include "../inc/uls.h"

extern t_flags current_flags;
extern t_dirs_to_show dirs_to_show;
extern t_files_to_show files_to_show;

void show_files_and_dirs(int n)
{
    if (current_flags.is_isatty)
    {

        sortStrings(files_to_show.files, files_to_show.num_of_files);

        if (current_flags.show_file && current_flags.l)
        {
            for (int i = 0; i < files_to_show.num_of_files; i++)
            {
                print_l_file(files_to_show.files[i], current_flags.is_isatty);
            }
        }
        else if (current_flags.show_file && !current_flags.l && !current_flags.no_such_file_err)
        {
            for (int i = 0; i < files_to_show.num_of_files; i++)
            {
                if (files_to_show.num_of_files != 0)
                {
                    print_color(files_to_show.files[i]);
                    mx_printchar(' ');
                }
                else
                {
                    print_color(files_to_show.files[i]);
                }
            }
            mx_printchar('\n');
        }
        else if (current_flags.show_file && !current_flags.l && current_flags.no_such_file_err)
        {
            for (int i = 0; i < files_to_show.num_of_files; i++)
            {
                if (files_to_show.num_of_files != 0)
                {
                    print_color(files_to_show.files[i]);
                    mx_printchar(' ');
                }
                else
                {
                    print_color(files_to_show.files[i]);
                }
            }
            mx_printchar('\n');
            mx_printchar('\n');
        }

        sortStrings(dirs_to_show.dirs, dirs_to_show.num_of_dirs);

        if (current_flags.show_dir && current_flags.show_file && current_flags.no_such_file_err)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                if (i != 0)
                {
                    mx_printchar('\n');
                }
                mx_printstr(dirs_to_show.dirs[i]);
                mx_printchar(':');
                mx_printchar('\n');
                print_directory_contents(dirs_to_show.dirs[i]);
            }
        }
        else if (current_flags.show_dir && current_flags.show_file)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                mx_printchar('\n');
                mx_printstr(dirs_to_show.dirs[i]);
                mx_printchar(':');
                mx_printchar('\n');
                print_directory_contents(dirs_to_show.dirs[i]);
            }
        }
        else if (current_flags.show_dir && n == 3 && current_flags.l)
        {
            print_l(current_flags.dir_to_show, current_flags.is_isatty);
        }
        else if (current_flags.show_dir && n != 2)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                if (i != dirs_to_show.num_of_dirs - 1)
                {
                    mx_printstr(dirs_to_show.dirs[i]);
                    mx_printchar(':');
                    mx_printchar('\n');
                    print_directory_contents(dirs_to_show.dirs[i]);
                    mx_printchar('\n');
                }
                else
                {
                    mx_printstr(dirs_to_show.dirs[i]);
                    mx_printchar(':');
                    mx_printchar('\n');
                    print_directory_contents(dirs_to_show.dirs[i]);
                }
            }
        }
        else if (current_flags.show_dir && n == 2)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                print_directory_contents(dirs_to_show.dirs[i]);
            }
        }
    }
    else
    {
        if (current_flags.show_file)
        {
            for (int i = 0; i < files_to_show.num_of_files; i++)
            {
                print_color(files_to_show.files[i]);
                mx_printchar('\n');
            }
            if (current_flags.show_dir)
                mx_printchar('\n');
        }

        sortStrings(dirs_to_show.dirs, dirs_to_show.num_of_dirs);

        if (current_flags.show_dir && current_flags.show_file)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                if (i != dirs_to_show.num_of_dirs - 1)
                {
                    mx_printstr(dirs_to_show.dirs[i]);
                    mx_printchar(':');
                    mx_printchar('\n');
                    print_directory_contents(dirs_to_show.dirs[i]);
                    mx_printchar('\n');
                }
                else
                {
                    mx_printstr(dirs_to_show.dirs[i]);
                    mx_printchar(':');
                    mx_printchar('\n');
                    print_directory_contents(dirs_to_show.dirs[i]);
                }
            }
        }
        else if (current_flags.show_dir && n != 2)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                if (i != dirs_to_show.num_of_dirs - 1)
                {
                    mx_printstr(dirs_to_show.dirs[i]);
                    mx_printchar(':');
                    mx_printchar('\n');
                    print_directory_contents(dirs_to_show.dirs[i]);
                    mx_printchar('\n');
                }
                else
                {
                    mx_printstr(dirs_to_show.dirs[i]);
                    mx_printchar(':');
                    mx_printchar('\n');
                    print_directory_contents(dirs_to_show.dirs[i]);
                }
            }
        }
        else if (current_flags.show_dir && n == 2)
        {
            current_flags.a = false;
            for (int i = 0; i < dirs_to_show.num_of_dirs; i++)
            {
                print_directory_contents(dirs_to_show.dirs[i]);
            }
        }
    }
}
