#include "../inc/libmx.h"

int mx_strcasecmp(const char *s1, const char *s2) {
    
    int c1, c2;
    
    while (*s1 && (c1 = mx_tolower(*s1++)) == (c2 = mx_tolower(*s2++)));
    
    return c1 - c2;

}  

