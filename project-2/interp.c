// File: interp.c  
// Description: main interpreter source file for project_2 (CS243)
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // /

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interp.h"
#include "symtab.h"
#include "parser.h"
#include "tree_node.h"
#include "stack.h"

/**
 *  main(): Main function of program. 
 *  		- Creates a symbol table if given file, and displays it to user.
 *  		- Runs a loop until user hits CTR-D.
 *  		- Reads in postfix expressions from user
 *  		- Parses expression and evaluates result.
 *  		- Returns result to user and prints out infix expression.
 *  		- User may enter new expression
 *  		- After user ends program, symbol table is displayed again.
 *  		- Memory deallocated.
 *  		- Return 0, program terminates.
 *  param argc: number of command line args
 *  param argv[]: array of command line args.
 */
int main(int argc, char *argv[]){
        if(argc>2){
		printf("error too many args");
		return 1;
	}
	else if(argc==2){
		char *file = argv[1];
		printf("file: %s\n",file);
		build_table(file);
		dump_table();
	}
        printf("Enter postfix expressions (CTRL-D to exit):\n> ");
	char buff[MAX_LINE];
	while(fgets(buff,MAX_LINE,stdin)!=NULL){
	 	rep(buff);	
		printf("> ");
	}
	printf(" <-- user entered CTRL-D\n");
	dump_table();
	free_table();	
        return 0;
}

