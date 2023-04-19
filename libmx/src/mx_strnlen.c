#include "../inc/libmx.h"

size_t mx_strnlen(const char *s, size_t maxlen) {
	size_t len;
	for (len = 0; len < maxlen; len++, s++) {
		if (!*s)
			break;
	}
	return (len);
}
