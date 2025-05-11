#include "ast.h"
#include <assert.h>
#include <stdlib.h>

#include "ast.h"
#include <assert.h>
#include <stdlib.h>

struct AST_node *to_ast(struct CST_node *cst) {
    if (cst == NULL) {
        return NULL;
    }

    struct AST_node *ast = NULL;
    switch (cst->type) {
        case NODE_EXPR: {
            // starting with the first term
            ast = to_ast(cst->expr.term);

            struct CST_node *rest = cst->expr.expr_rest;
            while (rest != NULL && rest->expr_rest.op != '\0') {

                // if the operator is not null, we need to create a new AST node
                struct AST_node *add = malloc(sizeof(struct AST_node));
                if (!add) { free_ast(ast); return NULL; }
                add->type  = NODE_ADD;
                add->left  = ast;                 

                struct AST_node *rhs = to_ast(rest->expr_rest.expr);

                if (rest->expr_rest.op == '-') {   
                    struct AST_node *neg = malloc(sizeof(struct AST_node));
                    if (!neg) { free_ast(add); return NULL; }
                    neg->type = NODE_NEG;
                    neg->left = rhs;
                    neg->right = NULL;
                    rhs = neg;
                }
                add->right = rhs;
                ast  = add;
                rest = rest->expr_rest.expr->expr.expr_rest;
            }
            break;
}

        case NODE_TERM: {
            // starting with the first factor
            ast = to_ast(cst->term.factor);
            struct CST_node *rest = cst->term.term_rest;
            // while the operator is not null, we need to create a new AST node
            while (rest != NULL && rest->term_rest.op != '\0') {
                struct AST_node *new_ast = malloc(sizeof(struct AST_node));
                if (new_ast == NULL) {
                    free_ast(ast);
                    return NULL;
                }
                new_ast->type = NODE_MUL;
                new_ast->left = ast;
                new_ast->right = to_ast(rest->term_rest.term);
                ast = new_ast;
                rest = rest->term_rest.term->term.term_rest;
            }
            break;
        }

        case NODE_FACTOR:
            if (cst->factor.expr != NULL) { 
                if (cst->factor.negated) {
                    ast = malloc(sizeof(struct AST_node));
                    if (ast == NULL) {
                        return NULL;
                    }

                    ast->type = NODE_NEG;
                    ast->left = to_ast(cst->factor.expr);
                    ast->right = NULL;
                }
                 else {
                    ast = to_ast(cst->factor.expr); 
                }
            } else { 

                ast = malloc(sizeof(struct AST_node));
                if (ast == NULL) {
                    return NULL;
                }

                ast->type = NODE_LITERAL;
                ast->literal = cst->factor.literal;
                ast->left = NULL;
                ast->right = NULL;
            }
            break;

        default:
            break;
    }
    return ast;
    
}

void free_ast(struct AST_node *ast) {
    if (ast == NULL) {
        return;
    }
    // freeing the left and right childern of the ast using recursion
    free_ast(ast->left);
    free_ast(ast->right);
    free(ast);

}
int interpret(struct AST_node *ast) { 
    if (ast == NULL) return 0 ; // base case of the recursion     
    // interpreting the ast based on the type of the ast
    switch (ast->type) {
        case NODE_ADD:
            return interpret(ast->left) + interpret(ast->right);
        case NODE_LITERAL:
            return ast->literal;
        case NODE_MUL:
            return interpret(ast->left) * interpret(ast->right);
        case NODE_NEG:
            return -interpret(ast->left);
        default:
            return -1;
    }
}
