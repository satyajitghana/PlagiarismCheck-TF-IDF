#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "debug_helper.h"

Vector* newVector(void (*print_util)(Vector*),
        int (*compare)(const void*, const void*),
        int (*compare_r)(const void*, const void*)) {
    Vector* myVector = malloc(sizeof *myVector);
    init(myVector, print_util, compare, compare_r);
    return myVector;
}

Vector* newMinimalVector() {
    Vector* myVector = malloc(sizeof *myVector);
    myVector -> length = 0;
    myVector -> data = NULL;
    myVector -> add = add;
    myVector -> remove = del;
}

void init(Vector *list,
        void (*print_util)(Vector*),
        int (*compare)(const void*, const void*),
        int (*compare_r)(const void*, const void*)) {
    list -> length  = 0;
    list -> data    = NULL;
    list -> print   = print_util;
    list -> add     = add;
    list -> remove  = del;
    list -> comparator = compare;
    list -> comparator_r = compare_r;
    list -> sort = sort;
}

void add(Vector *list, void * DATA) {
    list -> data = realloc(list -> data, sizeof *(list -> data) * (list -> length + 1));
    (list -> data)[(list -> length)] = DATA;
    list -> length++;
}

void del(Vector *list, int index) {
    for (int i = index ; i < list -> length - 1 ; i++) {
        (list -> data)[i] = (list -> data)[i+1];
    }
    list -> length --;
    list -> data = realloc(list -> data, sizeof *(list -> data) * (list -> length));
}

void sort(Vector *list, bool descending) {
    if (descending)
        qsort(list -> data, list -> length,
            sizeof *(list -> data),
            list -> comparator_r);
    else 
        qsort(list -> data, list -> length,
            sizeof *(list -> data),
            list -> comparator);
}

/* Comparator Functions */
int int_compare(const void * a1, const void * a2) {
    // di(**((const int**)a1));
    if (**((const int**) a1) > **((const int**) a2)) return 1;
    if (**((const int**) a1) < **((const int**) a2)) return -1;
    return 0;
} 

int int_compare_r(const void * a1, const void * a2) {
    // di(**((const int**)a1));
    if (**((const int**) a1) > **((const int**) a2)) return -1;
    if (**((const int**) a1) < **((const int**) a2)) return 1;
    return 0;
} 

int string_compare(const void * s1, const void * s2) {
    return strcmp(*(const char**)s1, *(const char**)s2);
}

int string_compare_r(const void * s1, const void * s2) {
    return (-1)*strcmp(*(const char**)s1, *(const char**)s2);
}

/*Print Utils*/

void print_int(Vector *list) {
    for (int i = 0 ; i < list -> length ; i++) {
        di(*(int *)((list -> data)[i]));
    } 
}

void print_string(Vector *list) {
    for (int i = 0 ; i < list -> length ; i++) {
        ds((char *)((list -> data)[i]))
    }
}

/* New Data of Specific DataType Methods */

void* new_int(int data) {
    int* new_data = malloc(sizeof *new_data);
    *new_data = data;
    return new_data;
}

void* new_double(double data) {
    double* new_data = malloc(sizeof *new_data);
    *new_data = data;
    return new_data;
}

void* new_string(char* data) {
    char* new_data = malloc(strlen(data) * sizeof *new_data);
    strcpy(new_data, data);
    return new_data;
}

