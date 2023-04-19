#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>


#include "../libmx/inc/libmx.h"

#define MAX_FILES 100
typedef struct s_flags {
    bool a;
    bool l;
    bool show_dir;
    bool show_file;
    char *dir_to_show;
    bool is_isatty;
    bool no_such_file_err;
    bool A;
    bool h;
    bool i;
    bool r;
    bool t;
    bool u;
    bool c;
    bool S;
    bool G;
} t_flags;

typedef struct s_dirs_to_show {

    char **dirs;
    int num_of_dirs;
    int num_of_files_in_dirs;

} t_dirs_to_show;

typedef struct s_files_to_show {

    char **files;
    int num_of_files;

} t_files_to_show;

#define BLUEYELLOW "\033[34;43m"
#define BLUECYAN "\033[34;46m"
#define YELLOW "\033[34m"
#define MAGENTA "\033[35m"
#define GREEN "\033[32m"
#define BLACKGREEN "\033[30;42m"
#define BLACKYELLOW "\033[30;43m"
#define BLUE "\033[34m"
#define BLACKRED "\033[30;41m"
#define BLACKCYAN "\033[30;46m"
#define RED "\033[31m"
#define BLACK   "\033[0m"


void show_files_and_dirs(int n);
void print_filenames(char **filenames, int num_files);
void print_directory_contents(const char *directory_name);
void flags_checker(char **flags, int flags_count);
char *add_color_to_string(char *str, const char* str1, const char* str2);
void sortStrings(char **arr, int n);
void swapStrings(char **arr, int i, int j);
int compareStrings(const char *str1, const char *str2);
bool check_tar_gz(char* haystack, char* needle);
void print_color(char *filename);
bool is_file_executable(const char *filename);
int get_dir_size(const char* dirPath);
int is_directory(const char *path);
void print_l(const char *directory_name,  bool is_isatty);
void flag_R(char *dir, int depth);
void list_files_recursively(const char *path);
void reverse_array(char **arr, int n);
void sort_by_mtime(char *files[], int len);
void insertion_sort(char *files[], int len);
void ctime_sort(char *files[], int len);
void sort_by_size(char *files[], int len);
void print_l_file( char *filename, bool is_isatty);
