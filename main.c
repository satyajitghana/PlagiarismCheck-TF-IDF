#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <math.h>
#include "hash_map.h"
#include "pcheck.h"
#include "debug_helper.h"
#include "file_reader.h"
#include "input_helper.h"
#include "vector.h"

int main(int argc, char** argv) {

    char* file_name = argv[0];
    char* directory = "./data";
    char* query_file;
    float threshold = 80.0f;;

    switch(argc) {
        case 2:
            query_file = argv[1];
            break;
        case 3:
            query_file = argv[1];
            threshold = atoi(argv[2]);
            break;
        case 4:
            directory = argv[1];
            query_file = argv[2];
            threshold = atoi(argv[3]);
            break;
        default:
            printf( "\nUSAGE: %s <directory> <file> <threshold>"
                    "\ndefault directory = ./data"
                    "\ndefault threshold = 80.0%%"
                    "\nExample: %s data query 92.2\n", file_name, file_name);
            break;
    }

    if (argc <= 1 || argc > 4)
        return -1;

    struct dirent* in_file;
    FILE* entry_file;
    DIR *FD;

    if ((FD = opendir(directory)) == NULL) {
        printf("\nError Opening %s Directory\n", directory);
        return -1;
    }

    Vector* file_list = newMinimalVector();

    while (in_file = readdir(FD)) {
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
        
        //ds(in_file -> d_name);
        char* path = new_string(directory);
        strcat(path, "/");
        strcat(path, in_file -> d_name);
        file_list -> add(file_list, path);
    }

    //return 0;

    Vector* bags;
    HashMap* query_bag;

    bags = newMinimalVector();
    query_bag = newHashMap();

    /* Bag the Worlds */
    for (int i = 0 ; i < file_list -> length ; i++)
        bags -> add(bags, bag_words(file_list -> data[i]));

    /* bag the query */
    query_bag = bag_words(query_file);

    /* Normalize the Bags */
    for (int i = 0 ; i < bags -> length ; i++)
        normalize_words(bags -> data[i]);

    /* Normalize the Query */
    normalize_words(query_bag);

    /* Compute tf*idf */
    /* Make sure that you have already computed TF and also normalized it */
    for (int i = 0 ; i < bags -> length ; i++)
        compute_tf_idf(bags -> data[i], bags);

    compute_tf_idf(query_bag, bags);

    printf("\nTF-IDF COSINE SIMILARITY PLAGIARIZATION CHECKER -------------------\n\n");

    /* find the cosine similarity */
    int count = 0;
    printf("\nQUERY ------------------------------------------: \n");
    printf("%s\n\n", read_string_file(query_file));
    for (int i = 0 ; i < bags -> length ; i++) {
        double similarity = compute_cosine_similarity(query_bag, bags -> data[i]);
        if (similarity * 100 > threshold) {
            count++;
            printf("\nFOUND PLAGIARIZATION with %.10f%% Cosine similarity\n", similarity*100);
            printf("\nORIGINAL FILE ------------------------------------------: \n");
            printf("%s\n",read_string_file(file_list -> data [i]));
        }
    }
    
    printf("\nSearched %d documents, found %d matches with minimum threshold of %.2f%%\n\n",
        bags -> length, count, threshold);

    return 0;
}
