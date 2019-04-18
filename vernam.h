#ifndef VERNAM_H
#define VERNAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Read from the file, put it in message and set the bool flag, then do the necessary
 * operation in the ADT, simple */

struct SecureData {
    bool isEncrypted;
    char* message;
    int (*encrypt)(struct SecureData*, char**);
    int (*decrypt)(struct SecureData*, char*);
};

typedef struct SecureData SecureData;

SecureData* newSecureData(int (*encryptAlgo)(SecureData*, char**),
        int (*decryptAlgo)(SecureData*, char*));

int encrypt_vernam(SecureData*, char**); 

int decrypt_vernam(SecureData*, char*);

#endif
