#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) return -1;
    int count = 0;
    if (left < right) {
        int i = left;
        int j = right;
        char *middle = arr[(i + j) / 2];

        while (i <= j) {
            while(mx_strlen(arr[i]) < mx_strlen(middle)) 
                i++;
            while(mx_strlen(arr[j]) > mx_strlen(middle))
                j--;
            if (i <= j) {
                if (mx_strlen(arr[i]) != mx_strlen(arr[j])) {
                    char *temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    count++;
                }
                j--;
                i++;
            }
        }
        count += mx_quicksort(arr, left, j);
        count += mx_quicksort(arr, i, right);
    }
    return count;
}
