// File: stack.c  
// Description: stack source file for project_2 (CS243)
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "stack_node.h"

/**
 *  make_stack(): Creates an empty stack.
 */
stack_t *make_stack(void){
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	(*stack).top = NULL;
        return stack;	
}

/**
 *  push(): adds an element to the top of the stack.
 *  param stack: the stack element will be added to.
 *  param data: element being added to stack
 */
void push(stack_t *stack, void *data){
	static char* new;
	new = data;
	stack_node_t *s = (stack_node_t *)malloc(sizeof(stack_node_t));
	if(s!=NULL){
		s->data = new;
		s->next = stack->top;
		stack->top = s;
	}

}

/**
 *  empty_stack(): Determine whether or not a stack is empty.                  
 *  param stack: the stack being examined.
 *  return: 1 if stack is empty and 0 otherwise.
 */
int empty_stack(stack_t * stack){
        if((*stack).top == NULL){
                return 1;
        }
        else{
                return 0;
        }
}



/**
 *  top(): Reveals top element of the stack.
 *  param stack: stack being looked at.
 */
void *top(stack_t * stack){
	if(empty_stack(stack)==1 ){
                return NULL;
        }
	char* t = stack->top->data;
        return t;
}

/**
 *  pop(): removes top element of stack
 *  param stack: stack who's top element will be removed
 */
void pop(stack_t *stack){
	if(empty_stack(stack)==1 ){
		return;
	}
	if(top(stack) != NULL){
		stack_node_t* top;
	        top = stack->top;
		stack->top = stack->top->next;
		free(top);
	}
}


/**
 *  free_stack(): Deallocates memory assigned to a stack.
 *  param stack: stack to be freed.
 */
void free_stack(stack_t * stack){
	while((*stack).top!=NULL){
		pop(stack);
	}
 	free(stack);
}

/**
 *  print_stack(): prints out elements of stack. Helped function used for 
 *  		   debugging purposes, signature not included in stack.h
 *  param stack: stack to be printed out.
 */
extern void print_stack(stack_t* stack){
	 stack_node_t *s;
	 s = stack->top;
	 printf("stack: \n");
	 while(s){
		 char *str = s->data;
		 printf("%s\n",str);
		 s = s->next;
	 }
}



