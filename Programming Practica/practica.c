#include "practica.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Reads the index from a binary file located at filename.
 * 
 * The index starts with a 4 byte integer denoting the index size
 * (that is, the number of entries in the index).
 *
 * Next, there are index.size entries defined as follows:
 *   Each entry starts with a 4 byte integer for the entry value.
 *   Next, the entry contains a 4 byte integer for the size of the entry key (excluding the null character).
 *   Finally, the entry contains all characters in the key, excluding the null character,
 *   as determined by the previously read key size.
 *
 * Entry keys will never contain more than non-null 99 characters, you are not required to validate this.
 * However, you are expected to ensure key is a valid string (i.e. it ends in a null character).
 *
 * If the file cannot be opened, or it can be opened but 0 is read for index.size,
 * return an index with null entries and size of 0.
 * Upon success where index.size > 0, allocate an array of entries on the heap and return it in the index struct.
 * Your task is to implement read_index in practica.c:
 * 
 
Index r e a d i n d e x ( const char∗ fil e n am e ) ;
This function reads data from a binary file into an index. The index in C is defined by the
following struct in practica.h:
typedef struct {
Entry∗ e n t r i e s ;
int s i z e ;
} Index ;
The index consists of an array of entries, with size determined by size. Entries are defined by
the following struct:
typedef struct {
char key [ 1 0 0 ] ;
int val u e ;
} Entry ;
key is a string stored directly in the entry as an array; since it is null terminated. value is a
4 byte integer which the index associates with the key (its exact usage is beyond the scope of this
function; you may assume any signed 4 byte integer is a possible input).
The purpose of read_index is to write all data from the index into the file located at filename.
If the file cannot be opened, the function returns an index with size == 0 and entries == NULL.
If the file can be opened, the entries are read from the file and returned in the index.
The format of the binary file you are to read is as follows:
• 4 byte little endian integer determining the number of entries.
• For each entry:
– 4 byte little endian integer representing the entry value.
– 4 byte little endian integer representing the size of the entry key (excluding the null
character).
– A number of characters up to the key size, representing the key contents (excluding the
null character).
Since the format of the entry in binary contains variable length strings, it is not possible to read the
entries using a single fread call. Rather, you will need multiple fread to read each field individually.
Additionally, since entries is a pointer, it will be necessary to allocate it using information
from the binary file to determine the size. The entry key is not a pointer, so does not need to be
allocated directly
 */
Index read_index(const char* filename) {
    Index index = { .entries = NULL, .size = 0 };
    FILE *file = fopen(filename, "rb");

    





    return index;
}
