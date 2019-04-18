#ifndef PCHECK_H
#define PCHECK_H

#include "vector.h"

/* TF-IDF Cosine Similarity Methods */

HashMap* bag_words(char*);
void normalize_words(HashMap*);
void compute_tf_idf(HashMap*, Vector*);
double compute_cosine_similarity(HashMap*, HashMap*);

#endif