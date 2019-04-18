#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdbool.h>

struct MapData {
    char *key;
    void *value;
};

typedef struct MapData MapData;

struct HashMap {
    MapData *data;
    int length;
    void (*add)(struct HashMap*, char*, void*);
    bool (*contains)(struct HashMap*, char*);
    void* (*get)(struct HashMap*, char*);
    void (*set)(struct HashMap*, char*, void*);
};

typedef struct HashMap HashMap;

/* Initializer */
HashMap* newHashMap();

/* Generic Methods */
void add_to_hashmap(HashMap*, char*, void*);
bool does_exist(HashMap*,  char*);
void set_value(HashMap*, char*, void*);
void* get_value(HashMap*, char*);

/* String Value Print */
void print_map_string(HashMap* mymap);
void print_map_int(HashMap* mymap);
void print_map_double(HashMap* mymap);

#endif
