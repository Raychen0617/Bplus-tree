# Bplus-tree
## makefile
## main.cpp
○ contains the main function which will be used to test your homework<br>
○ main function will read all files needed for you, as well as record time used by each task <br>

## utils.cpp
○ contains some utility functions for file reading and used time output<br>

## utils.h
○ header file for utils.cpp<br>

## data.txt
○ contains the data used in the homework<br>
○ each line consists of a key and a value, both are integer and are separated with a “,”<br>
○ the data is not sorted on key or value<br>
○ will be loaded as two vectors of integer in the main function<br>
○ note that the data TAs use to test your program will not be identical to the one provided<br>
## key_query.txt
○ contains the queries to test your index<br>
○ each line consists of a key, which is an integer<br>
○ will be loaded as a vector of int in the main function<br>
○ some of the key may not exist in the data<br>
○ note that the queries TAs use to test your program will not be identical to the one provided <br>
## key_query_ans.txt
○ answer to key_query.txt<br>
## range_query.txt
○ contains the queries to test your index on range search<br>
○ each line consists of two keys, which are integers, the first one is always<br>
smaller than second one, they are separated by a “,”<br>
○ will be loaded as a vector of pair of two integers in the main function<br>
○ note that the queries TAs use to test your program will not be identical to the one provided <br>
## range_query_ans.txt
○ answer to range_query.txt

## index.cpp
○ the code for your index, this file must contain a class named “Index”<br>
○ Index class is an implementation of B+ tree index<br>
○ At least four function needed to be implemented (add more if you need)<br>
### constructor Index()
### key_query
### range_query
### clear_index
`Index(num_rows, key, value)` <br>
takes three inputs, which are a integer indicates the number of data rows, <br>
a vector of integer represent keys and a vector of integer represent values.<br>
You need to construct your B+ tree index in this function by inserting the key,<br>
value pairs into the B+ tree one by one.<br>
`key_query(query_keys)`<br>
takes one input, which is a vector of integer indicating the key used for query.<br>
In this function you need to output a file named “key_query_out.txt”, each row <br>
consists of a integer which is the value corresponds to the keys in query_keys<br>
(output -1 if the key is not found).<br>
`range_query(query_pairs)`<br>
takes one input, which is a vector of pair of two integers indicating the range <br>
of query. In this function you need to output a file named “range_query_out.txt”,<br>
each row consists of a integer which is the MAXIMUM value in the given query key range<br>
(output -1 if no key found in the range).<br>
`clear_index()`<br>
takes no input, you need to free all the memory used by your B+ tree index in this function.
## index.h
○ header file for index.cpp<br>
