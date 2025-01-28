// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
  // initialize all elements
  // You may initialize the elements to a number of your choice (e.g., 0)
  for(int i =0; i<n;i++){
    arr[i] = 0;
  }
  // counting to k,
  // mark the eliminated element; you choose the mark (e.g., 1)
  // print the index of the marked element
  // repeat until only one element is unmarked


  int count = 0;
  int temp = -1;
  int increment = 0;

  
  while(count < n){
    while(increment < k){
      temp = temp + 1;
      temp = temp % n;
      if(arr[temp] != 1){
        increment ++;
      }
    }
    temp = temp % n;
    increment = 0;

    if(arr[temp] == 0){
      count++;
      arr[temp] = 1;
      printf("%d\n", temp);
    }
  }



  // print the last remaining index
  for(int i =0; i < n; i++){
    if(arr[i] == 0){
      printf("%d\n", i);
    }
  }
  
  // release the memory of the array
  free (arr);
}

