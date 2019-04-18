#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_map.h"
#include "debug_helper.h"

HashMap* newHashMap() {
    HashMap* myhashmap = malloc(sizeof *myhashmap);
    myhashmap -> length = 0;
    myhashmap -> data = NULL;
    myhashmap -> add = add_to_hashmap;
    myhashmap -> contains = does_exist;
    myhashmap -> get = get_value;
    myhashmap -> set = set_value;
}

void add_to_hashmap(HashMap* mymap, char* key, void* value) {
    if (mymap -> contains(mymap, key)) {
        printf("\nKey already exists");
    } else {
        mymap -> data = realloc(mymap -> data, ((mymap -> length) + 1) * sizeof *(mymap -> data));
        mymap -> data[mymap -> length].key = key;
        mymap -> data[mymap -> length].value = value;
        mymap -> length++;
    }
}

bool does_exist(HashMap* mymap, char* key) {
    if (mymap -> data == NULL) {
        return false;
    }

    for (int i = 0 ; i < mymap -> length ; i++) {
        if (strcmp(mymap -> data[i].key, key) == 0) {
            return true;
        }
    }

    return false;
}

void set_value(HashMap* mymap, char* key, void* value) {
    if (mymap -> contains(mymap, key)) {
        for (int i = 0 ; i < mymap -> length ; i++) {
            if (strcmp(mymap -> data[i].key, key) == 0) {
                mymap -> data[i].value = value;
            }
        }
    } else {
        printf("\nKey does not exist\n");
    }
}

void* get_value(HashMap* mymap, char* key) {
    for (int i = 0 ; i < mymap -> length ; i++) {
        if (strcmp(mymap -> data[i].key, key) == 0) {
            return mymap -> data[i].value;
        }
    }

    return NULL;
}

void print_map_string(HashMap* mymap) {
    for (int i = 0; i < mymap->length; i++) {
        ds(mymap->data[i].key);
        ds(mymap->data[i].value);
    }
}

void print_map_int(HashMap* mymap) {
    for (int i = 0; i < mymap->length; i++) {
        ds(mymap->data[i].key);
        di(mymap->data[i].value);
    }
}

void print_map_double(HashMap* mymap) {
    for (int i = 0; i < mymap->length; i++) {
        ds(mymap->data[i].key);
        dd(*(double*)mymap->data[i].value);
        //printf("\nValue : %.10f\n", mymap->data[i].value);
    }
}
