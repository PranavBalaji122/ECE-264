#include "hw09.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>


#include <stdio.h>

#define INV_SYMBOL 36

// useful static helper functions
static int char_to_int(char c);
const char *skip_whitespace(const char *ptr);

long string_to_long(const char *string, const char **endptr, int base) {
  // checking that the first argument is not null, as specified in hw09.h
  assert(string != NULL);

  // setting errno to zero before function body starts
  errno = 0;

  long ret_value = 0;

  // Check if the base provided is invalid, i.e. it is less than 2 or more than
  // 36. Remember that base 0 is valid, and you need to check the string to see
  // if it is octal or hexadecimal.
  // If the base is invalid, set errno to EINVAL and return 0

  if((base < 2 || base > 36) && base !=0){
    errno = EINVAL;
    return 0;
  }

  // Skip over any whitespace present
  string = skip_whitespace(string);

  // Find the sign before the start of the number, if any
  int sign = 1;
  if(string[0] == 45){
    sign = -1;
    string++; // moving on to next char if there is a negative sign
  }
  
  // Handle the case where base == 0
  if(char_to_int(string[0]) == 0 && (char_to_int(string[1]) == 33) && base == 0){
    base = 16;
    string +=2;
  }else if(char_to_int(string[0]) == 0 && base == 0){
    base = 8;
    string+=1;
  }else if(base == 0){
    base = 10;
  }


  
  // Continue conversion while
  // 1) the string has not ended
  // 2) the current symbol is valid
  // 3) the current symbol is not a numeric value more than the base
  // Remember to deal with overflow! If overflow occurs, set errno to ERANGE

  const char *strPtr = string;
  int digit;
  while((*strPtr != '\0')){
    digit = char_to_int(*strPtr);

    if(digit >= base || digit == INV_SYMBOL){
      break;
    }
    if(ret_value > LONG_MAX / base){
      errno = ERANGE;
      if(sign == -1){
        return LONG_MIN;
      }else{
        return LONG_MAX;  
      }
    }
    
    

    ret_value = ret_value * base + (char_to_int(*strPtr));

    strPtr+=1;
  }

  // Deal with signs
  ret_value *= sign;
  *endptr = strPtr;

  return ret_value;
}

static int char_to_int(char c) {
  // what if c is '0' -- '9'
  if (isdigit(c)) {
    return c - '0';
    
  }

  // what if c is 'a' -- 'z'
  if (islower(c)) {
    // only deal with one alphabetic case
    c = toupper(c);
  }

  if (isupper(c)) {
    // 'A' becomes 65 - 65 + 10 = 10, 'B' becomes 11 and so on
    return c - 'A' + 10;
  }

  return INV_SYMBOL;
}

const char *skip_whitespace(const char *ptr) {
  while (isspace(*ptr)) {
    ptr++;
  }

  return ptr;
}
