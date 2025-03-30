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
 */
Index read_index(const char* filename) {
}

