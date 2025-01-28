#include <stdio.h>
#include <stdbool.h>


bool countChar(char * filename, int * counts, int size)
{
  // open a file whose name is filename for reading
  // if fopen fails, return false. Do NOT fclose
  // if fopen succeeds, read every character from the file
  //

  // if a character (call it onechar) is between
  // 0 and size - 1 (inclusive), increase
  // counts[onechar] by one
  // You should *NOT* assume that size is 256
  // reemember to call fclose
  // you may assume that counts already initialized to zero
  // size is the size of counts
  // you may assume that counts has enough memory space
  //
  // hint: use fgetc
  // Please read the document of fgetc carefully, in particular
  // when reaching the end of the file
  //
  
  FILE *filePtr = fopen(filename, "r");

  if (filePtr == NULL) {
    return false;
  }

  int oneChar = fgetc(filePtr);
  while(oneChar != EOF){
    if(oneChar >= 0 && oneChar <= (size - 1)){
      counts[oneChar] += 1;
    }
    oneChar = fgetc(filePtr);
  }


  if(fclose(filePtr) == EOF) {
    return false;
  }
  
  return true;
}


void printCounts(int * counts, int size)
{
  // print the values in counts in the following format
  // each line has three items:
  // ind, onechar, counts[ind]
  // ind is between 0 and size - 1 (inclusive)
  // onechar is printed if ind is between 'a' and 'z' or
  // 'A' and 'Z'. Otherwise, print space
  // if counts[ind] is zero, do not print
  
  char oneChar;
  for(int i =0; i< size; i++){
    if(counts[i] != 0){
      if(i >= 'a' && i <= 'z'){
        oneChar = (char) i;
      }else if(i >= 'A' && i <= 'Z'){
        oneChar = (char) i;
      }else{
        oneChar = ' ';
      }
      printf("%d, %c, %d\n", i, oneChar,counts[i]);
    }
  }
}
