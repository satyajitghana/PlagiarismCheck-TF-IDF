#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "file_reader.h"

char* read_string_file(char* filename) {
    FILE* to_read = fopen(filename, "r");
    if (to_read == NULL) {
        printf("\nError Opening %s\n", filename);
        return NULL;
    }
    fseek(to_read, 0, SEEK_END);
    long length = ftell(to_read);
    fseek(to_read, 0, SEEK_SET);
    
    char* buffer = malloc(length + 1);
    fread(buffer, 1, length, to_read);
    fclose(to_read);

    buffer[length] = '\0';

    return buffer;
}

void write_string_file(char* filename, char* data) {
    FILE* to_write = fopen(filename, "w");
    if (to_write == NULL) {
        printf("\nError Opening %s\n", filename);
        return NULL;
    }
    fwrite(data, strlen(data)*sizeof *data, 1, to_write);
    fclose(to_write);
}
