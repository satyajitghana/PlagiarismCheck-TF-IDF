#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "hash_map.h"
#include "pcheck.h"
#include "debug_helper.h"
#include "file_reader.h"
#include "input_helper.h"
#include "vector.h"

const char *delim = ".\n\t ";

HashMap *bag_words(char *file) {
    HashMap *mymap = newHashMap();
    char *data = read_string_file(file);
    char *tok;
    tok = strtok(data, delim);
    while (tok != 0) {
        char *to_add = strlwr(new_string(sanitize_string(tok)));
        if (*to_add != '\n' && *to_add != '\0' && strlen(to_add) > 0) {
            if (mymap->contains(mymap, to_add))
                mymap->set(mymap, to_add, new_double((*(double *)mymap->get(mymap, to_add)) + 1.0));
            else
                mymap->add(mymap, to_add, new_double(1.0));
        }
        tok = strtok(0, delim);
    }
    return mymap;
}

/* found normalized TF */
void normalize_words(HashMap *bag) {
    double total_words = 0;
    for (int j = 0; j < bag->length; j++)
        total_words += *(double *)bag->data[j].value;
    for (int j = 0; j < bag->length; j++)
        bag->set(bag, bag->data[j].key, new_double((*(double *)bag->data[j].value) / total_words));
}

/* TF*IDF
** IDF = 1 + log(Total number of documents / Number of documents with that word)*/
void compute_tf_idf(HashMap *bag, Vector *bags) {
    for (int i = 0; i < bag->length; i++) {
        char *curr_word = bag->data[i].key;
        double tf = *(double *)bag->data[i].value;
        int number_of_documents_with_word = 0;
        for (int j = 0; j < bags->length; j++) {
            HashMap *curr_bag = (HashMap *)(bags->data[j]);
            if (curr_bag->contains(curr_bag, curr_word))
                number_of_documents_with_word++;
        }
        double idf = 1.0 + log(((double)bags->length) / number_of_documents_with_word);
        bag->set(bag, curr_word, new_double(tf * idf));
    }
}

/* cos(theta) = A.B / (||A||*||B||)
** here ||A|| = (TF*IDF for word 1)^2 + (TF*IDF for word 2)^2 and so on,
** same is applied for ||B||*/
double compute_cosine_similarity(HashMap *query, HashMap *document) {

    /* computer ||query|| */
    double modQuery = 0.0;
    for (int i = 0; i < query->length; i++)
        modQuery += pow(*(double *)(query->data[i].value), 2);
    modQuery = sqrt(modQuery);
    //dd(modQuery);

    /* compute ||document||, only take the words that are present in the query */
    double modDocument = 0.0;
    for (int i = 0; i < document->length; i++)
        if (query->contains(query, document->data[i].key))
            modDocument += pow(*(double *)(document->data[i].value), 2);
    modDocument = sqrt(modDocument);
    //dd(modDocument);

    /* compute query.document = q1*d1+q1*d2 . . . .qn*dn */
    double querytimesdocument = 0.0;
    for (int i = 0; i < query->length; i++)
        if (document->contains(document, query->data[i].key))
            querytimesdocument += *(double *)(query->data[i].value) * *(double *)(document->get(document, query->data[i].key));
    //dd(querytimesdocument);

    double cosine_similarity = 0.0;
    cosine_similarity = querytimesdocument / (modQuery * modDocument);
    //dd(cosine_similarity);

    return cosine_similarity;
}