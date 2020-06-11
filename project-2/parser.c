// File: parser.c  
// Description: parser source file for project_2 (CS243)
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "tree_node.h"
#include "symtab.h"
#include "stack.h"

parse_error_t PARSE_ERROR = PARSE_NONE; //parse error, initialized to no error
eval_error_t EVAL_ERROR = EVAL_NONE; //eval error, initialized to no error


/**
 *  handle_parse_error(): helper function that handles parse errors
 *  param error: the type of error being handled
 */

void handle_parse_error( parse_error_t error){
	switch (error){
		case TOO_FEW_TOKENS:
			printf("Invalid expression, not enough tokens\n");
			break;
		case TOO_MANY_TOKENS:
			printf("Invalid expression, too many tokens\n");
			break;
		case INVALID_ASSIGNMENT:
			printf("Invalid expression, invalid assignment\n");
                        break;
		case ILLEGAL_TOKEN:
			printf("Invalid expression, illegal token\n");
                        break;
		default:
			break;
	}
	return;

}

/**
 *  handle_eval_error(): helper function that handles evaluation errors
 *  param error: the type of error being handled 
 */
void handle_eval_error(eval_error_t error){
	switch (error){
                case DIVISION_BY_ZERO:
                        printf("error: division by 0\n");
			break;
                case INVALID_MODULUS:
			printf("error: invalid modulus\n");
                        break;
                case UNDEFINED_SYMBOL:
			printf("error: undefined symbol\n");
                        break;
                case UNKNOWN_OPERATION:
			printf("error: unknown operation\n");
                        break;
                case UNKNOWN_EXP_TYPE:
			printf("error: unknown expression type\n");
                        break;
                case MISSING_LVALUE:
			printf("error: missing value\n");
                        break;
		case INVALID_LVALUE:
			printf("error: invalid value\n");
                        break;
		case SYMTAB_FULL:
			printf("error: symbol table is full\n");
                        break;	
                default:
                        break;
        }
        return;
}


/**
 *  rep(): main read, evaluate, print loop.
 *  param exp: expression being read in (postfix notation)
 */
void rep(char *exp){
        tree_node_t *tree ;
        tree = make_parse_tree(exp);
        if(PARSE_ERROR!=PARSE_NONE){
                handle_parse_error(PARSE_ERROR);
                if(tree!=NULL){
			cleanup_tree(tree);
		}
        }
        else{
                int result = 0;
                result = eval_tree(tree);
                if(EVAL_ERROR!=EVAL_NONE){
                        handle_eval_error(EVAL_ERROR);
                        cleanup_tree(tree);
                }
                else{
                        print_infix(tree);
                        printf(" = %d\n",result);
                        cleanup_tree(tree);
                }
        }
        PARSE_ERROR =PARSE_NONE;
        EVAL_ERROR = EVAL_NONE;
}


/**
 *  parse(): Fills out the parse tree given a stack.
 *  param stack: stack generated from user expression.
 */
tree_node_t *parse(stack_t *stack){
	if(empty_stack(stack) == 1){
		PARSE_ERROR = ILLEGAL_TOKEN;
		return NULL;	
	}
	else{
            	tree_node_t *tree;	
		char *token;
	    	token = top(stack);
		int le = 0;
		le = strlen(token);
		token[le] = '\0';
	    	pop(stack);
	    	op_type_t operation;
		operation = 8;

		if(strcmp(token,"+")==0){
			operation = ADD_OP;
		}
   		if(strcmp(token,"-")==0){
        	        operation = SUB_OP;
                }
		if(strcmp(token,"*")==0){
        	        operation = MUL_OP;
                }
		if(strcmp(token,"/")==0){
        	        operation = DIV_OP;
                }		
		if(strcmp(token,"%")==0){
        	        operation = MOD_OP;
                }
		if(strcmp(token,"=")==0){
        	        operation = ASSIGN_OP;
                }		
		if(strcmp(token,"?")==0){
        	        operation = Q_OP;
                }
		if(strcmp(token,":")==0){
        	        operation = ALT_OP;
		}
	

		if(operation==Q_OP){
			tree_node_t *left;
               		tree_node_t *right;
			tree_node_t *alt_left;
                	tree_node_t *alt_right;
			alt_right = parse(stack);
			alt_left = parse(stack);
			right =  make_interior(ALT_OP, ":", alt_left, alt_right);
			left= parse(stack);
			tree =  make_interior(Q_OP, token, left, right);
			return tree;
		}


		if(operation!=NO_OP){
			tree_node_t *left;
			tree_node_t *right;
			left = NULL;
			right = NULL;
		        right = parse(stack);
		        left = parse(stack);
			if(operation==ASSIGN_OP){
				leaf_node_t* l= (leaf_node_t*)(left->node);
				if(l->exp_type!=SYMBOL){
					PARSE_ERROR = INVALID_ASSIGNMENT;
				}
			}
			tree = make_interior(operation, token, left, right);
			return tree;
		}
		else{	
			exp_type_t exp_type = SYMBOL;
			
			if(isalpha(token[0])){
		      		exp_type = SYMBOL;	
			}

			else if(isdigit(token[0])){
		      		exp_type = INTEGER;
			}	
			else{
				PARSE_ERROR = ILLEGAL_TOKEN;
				
			}
        		tree = make_leaf(exp_type, token);
		
			return tree;
		}
	}
	
}

/**
 *  make_parse_tree(): Creates a parse tree given an expression
 *  param exp: expression that will be converted to stack and parsed.
 */
tree_node_t *make_parse_tree(char *expr){
	stack_t* stack = make_stack();
	tree_node_t *tree = NULL;
	expr = strtok(expr, "\n");
	char* token = strtok(expr, " ");
	int count = 0;
	while(token!=NULL){
		count++;
              	push(stack,token);
		token = strtok(NULL, " ");      
        }
	if(count==0){
		PARSE_ERROR = TOO_FEW_TOKENS;
		return tree;
	}
	tree = parse(stack);
	if(empty_stack(stack)!=1){
		PARSE_ERROR = TOO_MANY_TOKENS;
		return tree;
	}
	free_stack(stack);
	return tree;
}

/**
 *  eval_tree(): Evaluates result of given parse tree.
 *  param node: head node of parse tree being evaluated
 */
int eval_tree(tree_node_t * node){
	int result= 0;
	interior_node_t *next;
	next = (interior_node_t*)(node->node);
	if(node->type == INTERIOR && next->op == Q_OP){
		tree_node_t *alt_left, *alt_right;
		interior_node_t *alt_next;
		alt_next = (interior_node_t*)(next->right->node);
		alt_right = (tree_node_t*)(alt_next->right);
		alt_left = (tree_node_t*)(alt_next->left);
		int l = eval_tree(next->left);
		int a,b;
		a = eval_tree(alt_left);
		b = eval_tree(alt_right);
		int result = l ? a:b; 
		return result;
	}
	if(node->type == LEAF){
		leaf_node_t *temp;
	        temp = (leaf_node_t*)(node->node);
	   	if(temp->exp_type!= SYMBOL && temp->exp_type!= INTEGER){
			EVAL_ERROR = UNKNOWN_EXP_TYPE;
			return 0;
		}	
		if(temp->exp_type == SYMBOL){
			static symbol_t *a;
			a = lookup_table(node->token);
			if(a==NULL){
				EVAL_ERROR = UNDEFINED_SYMBOL;
				return 0;
			}
			return a->val;
		}
		else{
			return atoi(node->token);
		}
    	}
  	else{ 
		op_type_t op;
	        tree_node_t *left;
		tree_node_t *right;	
		static interior_node_t *temp;
	        temp = (interior_node_t*)(node->node);
		op = temp->op;
	        left = temp->left;
	        right = temp->right;
	        int leftVal = 0;
		int rightVal = 0;
		exp_type_t l;
		if(op == ASSIGN_OP){
			if(left->type!=LEAF){
				EVAL_ERROR = INVALID_LVALUE;
				return 1;
			}
			leaf_node_t *t;
	      		t = (leaf_node_t*)(left->node);
			l = t->exp_type;
			if(l!=SYMBOL){
				return 1;
			}
			char* new;
			new = left->token;
			if(lookup_table(new)==NULL){
				rightVal = eval_tree(right);
				create_symbol(new,rightVal);
			}
			else{
				symbol_t *a;
				rightVal = eval_tree(right);
				a = lookup_table(new);
				a->val = rightVal;
			}
			return rightVal;

		}

		leftVal = eval_tree(left);
	        rightVal = eval_tree(right);


		if(op == ADD_OP){
			result = leftVal + rightVal;
		}
		if(op == SUB_OP){
        	        result = leftVal - rightVal;
       		}
	 	if(op == MUL_OP){
                	result = leftVal * rightVal;
        	}
	   	if(op == DIV_OP){
			if(rightVal==0){
				EVAL_ERROR = DIVISION_BY_ZERO;
				return 0;
			}
			else{
                		result = leftVal/rightVal;
			}
        	}


	    	if(op == MOD_OP){
			if(leftVal < 0 || rightVal < 0){
				EVAL_ERROR = INVALID_MODULUS;
				return 0;
			}
                	result = leftVal % rightVal;
        	}
		if(op > 9){
			EVAL_ERROR = UNKNOWN_OPERATION;
		}
	
	}
	return result;
}


/**
 *  print_infix(): Prints out parse tree expression in infix fashion.
 *  param node: head of parse tree being printed.
 */
void print_infix(tree_node_t * node){
	tree_node_t *temp;
	temp = node;
	interior_node_t *next;
	if(temp->type == INTERIOR){
		next = (interior_node_t*)(node->node);
		printf("(");
		print_infix(next->left);
		printf("%s",temp->token);
		print_infix(next->right);
		printf(")");
		return;
	}
	if(temp->type == LEAF){
		printf("%s",temp->token);
		return;
	}	
}

/**
 *  cleanup_tree(): Deallocates memory associated with parse tree.
 *  param node: head of parse tree being freed.
 */
void cleanup_tree(tree_node_t * node){
	if(node==NULL){
		return;
	}
	if(node->type==LEAF){
		leaf_node_t *next;
                next = (leaf_node_t*)(node->node);
		free(next);
		free(node);
		return;
	}
	else{
		interior_node_t *next;
		next = (interior_node_t*)(node->node);
		tree_node_t *left,*right;
		left = next->left;
		right = next->right;
		cleanup_tree(left);
		cleanup_tree(right);
		free(next);
		free(node);
		return;
	}
}


