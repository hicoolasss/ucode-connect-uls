#include "../inc/uls.h"

bool is_file_executable(const char *filename) {
   
    struct stat sb;
        
        if (stat(filename, &sb) == 0 && sb.st_mode & S_IXUSR && S_ISREG(sb.st_mode)) {
            
            return true;  // файл является запускаемым
        
        } else {
        
        return false;  // файл не является запускаемым
    
    }

}
