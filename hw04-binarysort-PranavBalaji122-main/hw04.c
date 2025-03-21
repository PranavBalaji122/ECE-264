#include <stdlib.h>
#include <stdio.h>
#include "hw04.h"

/* The first function you write counts the numbers of vectors
(that is, the number of triads of 32-bit integers) found in the
file with name 'filename'.  It assigns this value to the location
pointed to by 'vector_count'.  If it is unable to open the file,
OR if the file cannot be interpreted as a binary file of vectors
(that is, it does not contain a multiple of three integers' worth of data), it returns
EXIT_FAILURE.  Else, it returns EXIT_SUCCESS.  */
int count_vectors_in_file(char * filename, int * vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE *filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        return EXIT_FAILURE;
    }
    
    // Set up a buffer of three integers to read to,
    // a count of how many integers are read in on the last pass,
    // and a count of how many times three integers have been read in
    int buffer[3];
    int lastPass = 0;
    int count_intReadIn = 0;

    // While not encountering the end of the file or receiving an error,
    // call f_read with the buffer to retrieve three integers.  Update
    // the counts.
    // If the last pass reached the end of the file and retrieved no integers
    // (rather than a stray one or two) and didn't throw an error, return EXIT_SUCCESS
    // Else, return EXIT_FAILURE

    while((lastPass = fread(buffer, sizeof(int), 3, filePtr))){
        count_intReadIn += 1;
    }
    *vector_count = count_intReadIn;
    fclose(filePtr);
    if (lastPass != 0){
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

/* The second function you write allocates space for the vectors
counted before - there are vector_count vectors stored in the file at
filename.  It reads in those vector_count vectors from the file 'filename'
to the space it allocates and returns a pointer to that space.

That space will need to be freed - though, of course, not before
the program is done using it.  Free it in an appropriate place (hint: not in this function.)

In the event of a file read failure or memory allocation failure (both
are unlikely), you can return NULL.*/


struct vector * read_vectors_from_file(char * filename, int vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE *filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        return NULL;
    }
    // Allocate sufficient space for all of the vector structs
    struct vector *vector_list = malloc(vector_count * sizeof(struct vector));
    if (vector_list == NULL) {
        fclose(filePtr);
        return NULL;
    }
    // Read in all the integers from the file.  Place each
    // set into the x-, y-, and z-coordinates of a vector in the list
    
    if (fread(vector_list, sizeof(struct vector), vector_count, filePtr) != (size_t)vector_count) {
        fclose(filePtr);
        free(vector_list);
        return NULL;
     }
    if(vector_list == NULL){
        return NULL;
    }
    fclose(filePtr);

    // Return the list of vectors
    return vector_list;
}




/* The third function you write takes in two pointers of type
const void*, casts them to access the attributes of the 
structs to which they point, and returns a positive value if the
first is greater, a negative value if the second is greater,
and 0 if they are equal.  Being greater is determined by the 
x-coordinate's being greater, or, those being equal, by the
y-coordinate's being greater, or, those also being equal, by 
the z-coordinate's being greater.

This function is meant to be sent to qsort - see 
https://en.cppreference.com/w/c/algorithm/qsort for an example
of using qsort and a warning about comparison functions.*/
int compare_vectors(const void* a, const void* b) {
    // Cast the void pointers to pointers to struct vector.
    struct vector *vec1 = (struct vector *)a;
    struct vector *vec2 = (struct vector *)b;
    if((*vec1).x > (*vec2).x){
        return 1;
    }else if((*vec1).x < (*vec2).x){
        return -1;
    }else if((*vec1).y > (*vec2).y){
        return 1;
    }else if((*vec1).y < (*vec2).y){
        return -1;
    }else if((*vec1).z > (*vec2).z){
        return 1;
    }else if((*vec1).z < (*vec2).z){
        return-1;
    }
    return EXIT_FAILURE;
}

/* The fourth function calls qsort with the appropriate
parameters, including the function above. */
void call_qsort(struct vector * vector_list, int vector_count) {
    qsort(vector_list, vector_count, sizeof(struct vector), compare_vectors);
}

/* The fifth function writes the vectors in 'vector_list' (which
has length 'vector_count') to a binary file at 'filename'.  If the
file cannot be opened, it returns EXIT_FAILURE. */
int write_vectors_to_file(char * filename, struct vector * vector_list, int vector_count) {
    // Open the file in "wb" (write binary) mode
    FILE *fileptr = fopen(filename, "wb");
    // Write the coordinates of each vector to the binary file
    for(int i = 0 ; i< vector_count; i++){
        if(fwrite(&vector_list[i], sizeof(struct vector), 1, fileptr) != 1){
            fclose(fileptr);
            free(vector_list);
            return(EXIT_FAILURE);
        }
    }

    fclose(fileptr);
    free(vector_list);
    return EXIT_SUCCESS;
}