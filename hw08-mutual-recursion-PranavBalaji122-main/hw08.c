#include "hw08.h"

#include <string.h>

/**
 * Grammar:
 *
 * expr := term expr_rest
 * expr_rest := '+' expr | '-' expr | { }
 *
 * term := factor term_rest
 * term_rest = '*' term | { }
 *
 * factor := int | '(' expr ')'
 */

#ifndef INSTRUCTOR_EXPR
enum parse_result parse_expr(struct stream *s) {
    // parseing the term and checking if it is a failure
    if(parse_term(s) == PARSE_FAILURE) {
      return PARSE_FAILURE;
    }
    
  // if it is not a failure we need to call the expr_rest method 
   return parse_expr_rest(s); 
   }

enum parse_result parse_expr_rest(struct stream *s) { 
    // peeking at the next token and chekcing if it is a binary op, then checking if it is a + or -
    if((peek(s).type == TOK_BINOP) && (*peek(s).start == '+' || *peek(s).start == '-')){
      next(s);

      // checking if the term is a failure
      if(parse_term(s) == PARSE_FAILURE) {
        return PARSE_FAILURE;
      }

      // returning the expr_rest method to run it recursively
      return parse_expr_rest(s);
    }


    return PARSE_SUCCESS;
  }

#endif

#ifndef INSTRUCTOR_TERM
enum parse_result parse_term(struct stream *s) {
    // checking if the parse factor is a failure
    if(parse_factor(s) == PARSE_FAILURE) {
      return PARSE_FAILURE;
    }


  // if its not a failure you need to call the term_rest method
   return parse_term_rest(s); 
   }

enum parse_result parse_term_rest(struct stream *s) { 
  // checking if the next token is a binary op and if it is a *
    if(peek(s).type == TOK_BINOP && (*peek(s).start == '*')) {
      next(s);

      // checking if the parse factor is a failure
      if(parse_factor(s) == PARSE_FAILURE) {
        return PARSE_FAILURE;
      } 

      // returning the term_rest method to run it recursively
      return parse_term_rest(s);
    }
    return PARSE_SUCCESS;
  }

#endif

#ifndef INSTRUCTOR_FACTOR
enum parse_result parse_factor(struct stream *s) { 

    // checking if the next token is a literal or if it is a left paren
    if(peek(s).type == TOK_LITERAL){
      next(s);
      return PARSE_SUCCESS;
    }

    // else checking if the term is an open parenthesise
    if(peek(s).type == TOK_LPAREN) {
          next(s);

          // checking if the term is a success or not
          if(parse_expr(s) == PARSE_FAILURE) {
            return PARSE_FAILURE;
          }

          // checking if the parenthesis is closes the open parenthesis above
          if(peek(s).type == TOK_RPAREN) {
            next(s);
            return PARSE_SUCCESS;
          }
      }
    return PARSE_FAILURE; 
  }
#endif

// You do NOT need to modify this function!
enum parse_result is_valid_expr(const char *expr) {
  // Create the stream
  struct stream s = {.text = expr, .pos = 0, .length = strlen(expr)};

  // Try to parse an expr and make sure there's nothing left to parse
  if (parse_expr(&s) == PARSE_SUCCESS && next(&s).type == TOK_EOF) {
    return PARSE_SUCCESS;
  }
  return PARSE_FAILURE;
}