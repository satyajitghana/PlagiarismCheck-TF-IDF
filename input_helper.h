#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

int get_word(char**);

int get_sentence(char**);

int get_line(char** line);

int next_int();

char* sanitize_string(char*);
char* strlwr(char*);

#endif
