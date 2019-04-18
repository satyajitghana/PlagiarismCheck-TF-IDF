#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* The Vector structure */
struct Vector {
    int     length;
    void    **data;
    //void  (*init)(struct Vector*, void (*)(struct Vector*));
    void    (*print)(struct Vector*);
    void    (*add)(struct Vector*, void *);
    void    (*remove)(struct Vector*, int);
    int     (*comparator)(const void *, const void *);
    int     (*comparator_r)(const void *, const void *);
    void    (*sort)(struct Vector*, bool);
};

typedef struct Vector Vector;

/* Generic methods */
Vector* newVector(void (*)(Vector*),
        int (*)(const void *, const void *),
        int (*)(const void *, const void *));
Vector* newMinimalVector();
void add(Vector *, void *);
void init(Vector *, void (*)(Vector *),
        int (*)(const void *, const void *),
        int (*)(const void *, const void *));
void del(Vector*, int);
void sort(Vector*, bool descending);

/* DataType specific methods */
void*   new_int(int);
void*   new_double(double);
void*   new_string(char*);
void    print_int(Vector *);
void    print_string(Vector *);
/* Comparator methods */
int     int_compare(const void *, const void *);
int     int_compare_r(const void *, const void *);
int     string_compare(const void *, const void *);
int     string_compare_r(const void *, const void *);

#endif
