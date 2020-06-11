// File: symtab.c  
// Description: symbol table source file for project_2 (CS243)
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symtab.h"

// the symbol table
static struct symbol_s *symbol_table;


/**
 *  create_symbol(): Adds an entry to the symbol table
 *  param name: name of entry
 *  param value: value of entry
 */
symbol_t *create_symbol(char *name, int val){
        symbol_t *new = ( symbol_t* )malloc(sizeof( symbol_t));
	new->var_name = NULL;
	new->val = 0;
	new->next = NULL;
	new->var_name = name;
	new->val = val;
	new->next = symbol_table;
	symbol_table = new;
	return symbol_table;
}

/**
 *  build_table(): Builds a symbol table given a txt file.
 *  param filename: name of txt file
 */
void build_table(char *filename){
	FILE *sym = fopen(filename,"r");
        if(sym == NULL){
                perror("Unable to open file");
                return ;
        }
	static char array[30][30];
	static int ints[30];
	int a = 0;
	int *val = (int*)malloc(sizeof(int));
	char str[BUFLEN];
	symbol_table = ( symbol_t* )malloc(sizeof( symbol_t));
	while(fscanf(sym, "%s %d", str ,val)!=EOF) {
		if(str[0]=='#'){
                        char c = ' ';
                        while(c!='\n'){
				fscanf(sym, "%c", &c);
                        }
                }
		else{
			strcpy(array[a],str);
			ints[a] = *val;
			a++;			
		}	
	}
	int c = 0;
	while(c!=a){
		if(symbol_table->var_name==NULL){
			symbol_table->var_name = array[c];
                        symbol_table->val = ints[c];
		}
		else{
			create_symbol(array[c],ints[c]);
		}
		c++;
	}
	free(val);
        fclose(sym);
	return;
}

/**
 *  dump_table(): Displays the symbol table to user.
 *  			printed in ( name: ____   val: ___ ) format.
 */
void dump_table(void){
	printf("SYMBOL TABLE:\n");
	symbol_t *temp = symbol_table;
	while(temp){
		printf("\tName: %s ",(*temp).var_name);
		printf("Value: %d \n",(*temp).val);
		temp = temp->next;
	}
	free(temp);
}

/**
 *  lookup_table(): looks up a variable in the symbol table.
 *  param variable: name of value being looked at.
 */
symbol_t *lookup_table(char *variable){
	symbol_t *temp;
	char* top = symbol_table->var_name;
	if(strcmp(top,variable)==0){
        	return symbol_table;
        }
        temp = symbol_table;
	while(temp){
		if(strcmp(temp->var_name,variable)==0){
			return temp;
		}
		else{
		temp = temp->next;
	     }
	}
	return NULL;
}

/**
 *  free_table(): Deallocated memory associated with the symbol table.
 */
void free_table(void){
	if(symbol_table->next == NULL){
		free(symbol_table);	
		return;
	}
	else{
		symbol_t *new = symbol_table->next;
		free(symbol_table);
		symbol_table = new;
		free_table();
	}
}

