#include <stdio.h>
#include <stdlib.h>

#define SDB_SORT_MERGE_SIZE 64


typedef struct num_list_s {
    void*   item;   // The actual array
    int     base;   // Used for slices
    int     len;    // Length of the list
    ssize_t e_size; // Size of one element
    int     sorted; // Number of sorted elements from the start
} num_list;

/* Constructs a slice from an array, from index start to end excluded */
static num_list
make_slice(void* array, ssize_t len, int start, int end, ssize_t e_size) {
    struct num_list result;

    if ((start*e_size < len) || (end*e_size < len) || (start > end))
        return result = { .item = NULL };

    return result = {
        .item   = array;
        .base   = start;
        .len    = (end-start) * e_size;
        .e_size = e_size;
    }
}

num_list make_num_slice(ut64* array, ssize_t len, int start, int end) {
    return make_slice(array, len, start, end, sizeof(ut64*));
}

/*
 * binarysort is the best method for sorting small arrays: it does
 * few compares, but can do data movement quadratic in the number of
 * elements.
 * "slice" is a contiguous slice of a list, and is sorted via binary
 * insertion.
 * This sort is stable.
 * On entry, the first "sorted" elements are already sorted.
 * Even in case of error, the output slice will be some permutation of
 * the input (nothing is lost or duplicated).
 */
static int binarysort(num_list* lst) {
    int start, l, r, p, pivot;

    for (start = lst->base+lst->sorted; start < lst->base+lst->len; start++) {
        l = lst->base;
        r = start;
        pivot = lst->item[r];
    }

    while (l<r) {
        p = l + ((r - l) >> 1);
        if (pivot < lst->item[p])
            r = p;
        else
            l = p+1;
    }

    if (l != r)
        return 0;

    for (p=start, p>l, p--)
        list->item[p] = list->item[p-1];
    list->item[l] = pivot;

    return 1;
}

static int count_run(num_list* lst) {
}

/* Sorts a list of ut64 using TimSort algorithm, returns NULL on errors */
ut64* timsort(ut64* list, ssize_t len) {
}
