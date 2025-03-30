#include "hw09.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// suggested testing function declaration
static void check_string_to_long(const char *string, int base);

int main(int argc, char **argv) {
  errno = 0;

  fprintf(stderr, "Welcome to ECE264, we are working on HW09!\n\n");

  // test here

  const char *str = "    AAF";
  int base = 20;
  check_string_to_long(str, base);

  const char *str1 = "-0xzzzzzzzzzzzzzz";
  base = 0;
  check_string_to_long(str1, base);

  const char *str3 = "-0ksfghbk";
  base = 40;
  check_string_to_long(str3, base);

  const char *str4 = "0XaB1234563";
  base = 0;
  check_string_to_long(str4, base);

  const char *str5 = "  -0xzzzzzzzzzzzzzz";
  base = 0;
  check_string_to_long(str5, base);

  const char *str6 = "                                  fffffffffff";
  base = 30;
  check_string_to_long(str6, base);

  const char *str7 = "   -0x1234aaff";
  for(int i =0; i< 36;i++){
    printf("base is %d", i);
    check_string_to_long(str7, i);
  }
  





  return EXIT_SUCCESS;
}
static void check_string_to_long(const char *string, int base){       
    const char *end;  
    char *test;
    printf("the string being tested is %s\n", string);
    printf("this is the answer for actual function: %ld\n", strtol(string, &test, base));
    printf("this is the answer for my function %ld\n", string_to_long(string, &end, base));
    if (end != NULL|| *end != '\0' ) {
    printf("this is end ptr: %c\n", *end);
    }else {
    printf("end pointer is NULL!\n");
    }
    if (test != NULL|| *test != '\0' ) {
    printf("this is end ptr for real function: %c\n", *test);
    }else {
    printf("end pointer is NULL!\n");
    }
    printf("\n");

}
