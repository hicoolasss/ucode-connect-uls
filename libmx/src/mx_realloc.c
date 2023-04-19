#include "../inc/libmx.h"
void *mx_realloc(void * ptr, size_t size) {
    void *new;

    if (!ptr) {
        new = malloc(size);
        
        if (!new) return NULL;
    } else {
        if (malloc_size(ptr) < size) { //malloc_usable_size
            new = malloc(size);
            
            if (!new) return NULL;

            mx_memcpy(new, ptr, malloc_size(ptr)); //malloc_usable_size
            free(ptr);
        } else new = ptr;
    }
    return new;
}

