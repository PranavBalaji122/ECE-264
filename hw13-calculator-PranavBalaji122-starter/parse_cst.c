#include "cst.h"

#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

// grammar rules:
// expr := term expr_rest
// expr_rest := '+ expr | {}

// term := factor term_rest
// term_rest := '*' term | {}

// factor := int | '(' expr ')' | '-' factor



struct CST_node *parse_expr(struct stream *s) { 
    struct CST_node *node = malloc(sizeof(struct CST_node));
    if (node == NULL) return NULL;
    
    node->type = NODE_EXPR;
    node->expr.term = parse_term(s); // here we are parsing the first term to follow the rules of the grammar
    if (node->expr.term == NULL) { // checking if the term is NULL
        free(node); 
        return NULL;
    }

    node->expr.expr_rest = parse_expr_rest(s); // parsing the next expression
    if (node->expr.expr_rest == NULL) { // if null free and return null
        free_cst(node->expr.term);
        free(node);
        return NULL;
    }
    return node;
}

struct CST_node *parse_expr_rest(struct stream *s) { 
    struct CST_node *node = malloc(sizeof(struct CST_node));
    if (node == NULL) {
        return NULL;
    }
    
    node->type = NODE_EXPR_REST; // setting the type to expr_rest
    struct token tok;
    tok = peek(s); // peek the next token
    if (tok.type == TOK_ADD) { 
        node->expr_rest.op = '+';
        next(s);         
        // Parse expr
        node->expr_rest.expr = parse_expr(s);
        if (node->expr_rest.expr == NULL) {
            free(node);
            return NULL;
        }
    } else {
        // if it not an add, set the operator to null
        node->expr_rest.op = '\0';
        node->expr_rest.expr = NULL;
    }
    return node;
}

struct CST_node *parse_term(struct stream *s) { 

    struct CST_node *node = malloc(sizeof(struct CST_node));
    if (node == NULL) return NULL;
    node->type = NODE_TERM;
 

    node->term.factor = parse_factor(s);
    if (node->term.factor == NULL) {
        free(node);
        return NULL;
    }


    node->term.term_rest = parse_term_rest(s);
    if (node->term.term_rest == NULL) {
        free_cst(node->term.factor);
        free(node);
        return NULL;
    }
    return node;


}
struct CST_node *parse_term_rest(struct stream *s) { 
    
    struct CST_node *node = malloc(sizeof(struct CST_node));
    if (node == NULL) return NULL;
    node->type = NODE_TERM_REST;
    struct token tok;
    tok = peek(s);


    if (tok.type == TOK_MUL) {
        node->term_rest.op = '*';
        next(s);
        node->term_rest.term = parse_term(s);
        if (node->term_rest.term == NULL) {
            free(node);
            return NULL;
        }
    } else {
        node->term_rest.op = '\0';
        node->term_rest.term = NULL;
    }

    return node;
}

struct CST_node *parse_factor(struct stream *s) { 
    struct CST_node *node = malloc(sizeof(struct CST_node));
    
    if (node == NULL){ 
        return NULL;
    }
    node->type = NODE_FACTOR;
    struct token tok;
    tok = peek(s);
    if (tok.type == TOK_LITERAL) {
        node->factor.literal = atoi(tok.start);
        node->factor.expr = NULL;
        node->factor.negated = false;
        next(s);
    } else if (tok.type == TOK_LPAREN) {
        next(s); 
        node->factor.expr = parse_expr(s);
        if (node->factor.expr == NULL) {
            free(node);
            return NULL;
        }
        node->factor.literal = 0; 
    } else if (tok.type == TOK_NEG) {
        next(s);
        node->factor.negated = true;
        node->factor.expr = parse_factor(s);
        if (node->factor.expr == NULL) {
            free(node);
            return NULL;
        }
    } else {
        free(node);
        return NULL; 
    }
    return node;
}    

void free_cst(struct CST_node *cst) {
    if (!cst) return;
    // freeing the chlidern nmodes based on the type of the cst using recursion
    switch (cst->type) {
        case NODE_EXPR:
            free_cst(cst->expr.term);
            free_cst(cst->expr.expr_rest);
            break;

        case NODE_EXPR_REST:
            free_cst(cst->expr_rest.expr);
            break;
        case NODE_FACTOR:
            free_cst(cst->factor.expr);
            break;
        case NODE_TERM:
            free_cst(cst->term.factor);
            free_cst(cst->term.term_rest);
            break;

        case NODE_TERM_REST:
            free_cst(cst->term_rest.term);
            break;
    }
    free(cst);

}
