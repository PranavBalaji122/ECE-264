#include <stdbool.h>
#include <stdio.h>


bool addFile(char * filename, int * sum)
{
  // You cannot assume * sum is zero. Thus, * sum needs to be set 0
  // open a file whose name is filename for reading
  // if fopen fails, return false. Do NOT fclose
  // if fopen succeeds, read integers using fscan (do not use fgetc)  
  //
  // * sum stores the result of adding all numbers from the file
  // When no more numbers can be read, fclose, return true
  //

  FILE *filePtr = fopen(filename, "r");
  if (filePtr == NULL) {
    return false;
  }
  *sum =0;
  int value = 0;
  while(fscanf(filePtr, "%d", &value) == 1){
    *sum += value;
  }
  if(fclose(filePtr) == EOF) {
    return false;
  }
  return true;
}



bool writeSum(char * filename, int sum)
{
  // open a file whose name is filename for writing
  // if fopen succeeds, write sum as an integer using fprintf
  // fprintf should use one newline '\n'
  // fclose, return true
  //
  FILE *filePtr = fopen(filename, "w");
  if (filePtr == NULL) {
    return false;
  }
  fprintf(filePtr, "%d\n", sum);
  if(fclose(filePtr) == EOF) {
    return false;
  }
  return true;
}