#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "input_helper.h"
#include "debug_helper.h"

/* get_word: takes a pointer to a pointer to char
 * stops reading the input if a space is encountered
 * or EOF or new line */
int get_word(char** word) {
    int c, len = 0, maxlen = 1;

    /* Let's have a minimum of some memory
     * I know the OS will put some padded memory, but still
     * mann ki shaanti ke liye kar leta hun */
    *word = malloc((len+1) * sizeof **word);

    /* Skip the whitespaces */
    while((c=getchar()) == ' ')
        ;
    if (c != EOF)
        ungetc(c, stdin);

    while ((c = getchar()) != ' ' && c != '\n' && c != EOF) {
        if (len == maxlen) {
            maxlen *= 2;
            *word = realloc(*word, maxlen * sizeof **word);
        }
        (*word)[len++] = c;
    }

    if (len != 0)
        *word = realloc(*word, len * sizeof **word);
    
    (*word)[len] = '\0';

    return 0;
}

/* get_sentence: takes a pointer to a pointer to char
 * stops reading the input if a newline is encountered
 * or EOF */
int get_sentence(char** sentence) {
    int c, len = 0, maxlen = 1;

    /* Let's have a minimum of some memory
     * I know the OS will put some padded memory, but still
     * mann ki shaanti ke liye kar leta hun */
    *sentence = malloc((len+1) * sizeof **sentence);

    while ((c = getchar()) && c != '\n' && c != EOF) {
        if (len == maxlen) {
            maxlen *= 2;
            *sentence = realloc(*sentence, maxlen * sizeof **sentence);
        }
        (*sentence)[len++] = c;
    }
    
    if (len != 0)
        *sentence = realloc(*sentence, len * sizeof **sentence);
    
    (*sentence)[len] = '\0';

    return 0;
}

/* Takes a complete line of input and returns the length
 * because if you have len = 0 you can stop reasing */
int get_line(char** line) {
    int c, len = 0, maxlen = 1;

    *line = malloc((len+1) * sizeof **line);

    while ((c = getchar()) && c != '\n' && c != EOF) {
        if (len == maxlen) {
            maxlen *= 2;
            *line = realloc(*line, maxlen * sizeof **line);
        }
        (*line)[len++] = c;
    }

    if (len != 0)
        *line = realloc(*line, len * sizeof *line);
    
    /* removes the new line, if present */
    if ((*line)[len] == '\n' && len != 0) --len;
    (*line)[len] = '\0';

    return len;
}

/* DataTypes input */
int next_int() {
    char *read;
    get_word(&read);
    int integer = atoi(read);
    free(read);
    return integer;
}


/* Removes the leading and trailing spaces from the string */
char* sanitize_string(char* s) {
    size_t size;
    char* end;

    size = strlen(s);

    if (!size) return s;

    end = s + size - 1;

    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}

char* strlwr(char* s) {
    for (int i = 0 ; i < strlen(s) ; i++)
        s[i] = tolower(s[i]);

    return s;
}
