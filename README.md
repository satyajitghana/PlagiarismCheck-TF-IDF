# Plagiarism Check using TF IDF Cosine Similarity

This was a part of the Assignment given in Semester 03 - Data Structure and Algorithms, which demanded to create an algorithm to check if two given documents were plagiarised, the way the question was intended was to used string matching to check for exactness of the documents, but the time complexity for this is very bad and this is a very bad way of checking.

In this we i've used the Term Frequency - Inverse Document Frequency to create vectors out of the documents, and using Cosine Similarity it was checked if they are same

# Assignment Solution

[CSC202A.pdf](CSC202A.pdf)

# Usage

```
./pcheck

USAGE: ./pcheck <directory> <file> <threshold>
default directory = ./data
default threshold = 80.0%
Example: ./pcheck data query 92.2
```

```
./pcheck data query 92.2

TF-IDF COSINE SIMILARITY PLAGIARIZATION CHECKER -------------------


QUERY ------------------------------------------:
The domestic cat (Felis silvestris catus or Felis catus) is a small, typically furry, carnivorous mammal. They are often called house cats when kept as indoor pets or simply cats when there is no need to distinguish them from other felids and felines.


FOUND PLAGIARIZATION with 93.2975787527% Cosine similarity

ORIGINAL FILE ------------------------------------------:
The domestic cat (Felis silvestris catus or Felis catus) is a small, typically furry, carnivorous mammal. They are often called house cats when kept as indoor pets or simply cats when there is no need to distinguish them from other felids and felines. They are often valued by humans for companionship and for their ability to hunt vermin. There are more than seventy cat breeds recognized by various cat registries.

Searched 4 documents, found 1 matches with minimum threshold of 92.00%
```

# Algorithms

```
bag_words:
1.	Begin
2.	Create a HashMap mymap
3.	Read the data from the file and store it in char* data
4.	Declare variable tok and initilialize it with strtok(data, “.\n\t ”)
5.	While (tok ≠ 0)
6.	Convert every character of tok to lower alphabet, remove the trailing and leading spaces and store it in to_add
7.	If (to_add≠ ‘\n’ && to_add ≠ ‘\0’)
8.	If (mymap contains to_add) then increment the value of key to_add in mymap
9.	Else add to_add to hashmap and assign 1.0 as the value to the key to_add
10.	tok = strtok(0, “.\n\t ”)
11.	return mymap
12.	End
```

```
normalize_words:
1.	Begin
2.	Declare total_words <- 0
3.	for (j = 0; j < length of bag ; j++)
4.	       total_words = total_words + bag -> data[j].value
5.	for (j=0; j < length of bag ; j++)
6.	set the value for key bag -> data[j].key as current value for the key / total_words
7.	End
```

```
compute_tf_idf:
1.	Begin
2.	for (i = 0 ; i < length of bag ; i++)
3.	curr_word = bag - > data[i].key
4.	tf = bag -> data[i].value
5.	number_of_documents_with_word = 0
6.	for (j = 0 ; j < length of bags ; j++)
7.	    curr_bag = bags -> data[j]
8. 	    if (curr_bag contains curr_word) then number_of_documents_with_word++
9.	idf = 1 + log (length of bags / number_of_documents_with_word)
10.	set the bag with key curr_word as tf * idf
11.	End
```

```
compute_cosine_similarity:
1.	Begin
2.	modQuery = 0
3.	for (i = 0; i < length of query ; i++)
4.	modQuery  = modQuery + (query -> data[i].value)2
5.	modQuery = √modQuery
6.	modDocument = 0
7.	for (i = 0; i < length of document ; i++)
8.	modDocument  = modDocument + (document -> data[i].value)2
9.	modDocument = √modDocument
10.	querytimesdocument = 0
11.	for (i = 0; i < length of document ; i++)
12.	if (document)
13.	End
```

```
compare_query_with_documents:
1.	Begin
2.	Declare Vecor bags, HashMap query_bag
3.	Read all the document files and use bag_words to bag the words and store it in a HashMap and add it to the Vector bags
4.	Bag the Query using bag_words and store it in query_bag
5.	Normalize the bags using normalize_bags
6.	Normalize the Query using normalize_bags
7.	Compute TF*IDF using compute_tf_idf for bags
8.	Compute TF*IDF using compute_tf_idf fro query
9.	End
```

# Explanation

All the Source Documents are stored in a folder named data, which are text files, the query is also stored in a file named query that contains the potentially plagiarized document. These files are read, they are sanitized, i.e. the leading spaces, and trailing spaces are removes, they are split into words, bagged, and then each of the documents are converted to n-dimensional vector, the query is also converted to  n-dimensional vector, these vectors are then normalized, and the TF\*IDF is calculated for each of them, the advantage of using TF\*IDF is that common words across the documents are weighted down, i.e. they are assigned a lower score, and the unique words are weighted more, using logarithmic, now that we have a vector for each of the document and also the query, it can simply be compared using Dot Product, which is

![Alt](/img1.png "Dot Product")

![Alt](/img2.png "Cosine Similarity")

cos⁡θ will output a value from [-1,1], but for our implementation it won’t output a value less than 0, hence the output of Cosine Similarity will be from [0,1], this can be mapped from [0,100] to get a percentage of potential plagiarisation.

It then checks which documents have a minimum plagiarisation which was passed as a command line argument to the program, and those plagiarized documents aredisplayed along with the query.
