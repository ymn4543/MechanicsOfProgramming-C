// 
// File: offspring.c
// Description: main program for CS243 project_3. Runs offspring family tree 
// program using file or user input until told to quit.
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// 
// // // // // // // // // // // // // // // // // // // // // // // //

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "trimit.h"
#include "tree.h"
#include "queue.h"


/**
 * enum for command types. 
 */
typedef enum command_type_e {
    ADD,
    FIND,
    PRINT,
    SIZE,
    HEIGHT,
    INIT,
    HELP,
    QUIT,
    UNKNOWN
} command_type_t;

/**
 *  file_make_tree(): reads a file and constructs a family tree.
 *  param filename: name of file to be read.
 */
tree_node_t *file_make_tree( char* filename){
	FILE *file = fopen(filename,"r");
	if(file == NULL){
                perror("Unable to open file");
                return NULL;
        }
	ssize_t read;
 	char * line = NULL;
    	size_t len = 0; 
	read = getline(&line, &len, file);
	line = trim(line);
	char *head = strtok(line, ",");
        head = trim(head);
	tree_node_t *tree = create_node(head);
	head = strtok(NULL, ",");
        head = trim(head);
	while(head!=NULL){
		tree =	add_child(tree,tree->name,head);
		head = strtok(NULL, ",");
                head = trim(head);	
	}
	while ((read = getline(&line, &len, file)) != -1) {
		line = trim(line);
		if(strcmp(line,"")!=0){
			char *parent = strtok(line,",");
			parent = trim(parent);
			int x = strlen(parent);
			char top[x];
			strcpy(top,parent);
			parent = strtok(NULL,",");
			parent = trim(parent);
		        while(parent!=NULL && strcmp(parent,top)!=0){
				add_child(tree,top,parent);
				parent = strtok(NULL, ",");
                                parent = trim(parent);
			}
		}
	}
	return tree;
}


/**
 *  check_command(): checks if a command exits, if not returns NULL.
 *  param command: name of command
 */
command_type_t check_command( char* command){
        if(strcmp(command,"add") == 0){
                return ADD;
        }
        if(strcmp(command,"find") == 0){
                return FIND;
        }
        if(strcmp(command,"print") == 0){
                return PRINT;
        }
        if(strcmp(command,"size") == 0){
                return SIZE;
        }
        if(strcmp(command,"height") == 0){
                return HEIGHT;
        }
        if(strcmp(command,"init") == 0){
                return INIT;
        }
        if(strcmp(command,"help") == 0){
                return HELP;
        }
        if(strcmp(command,"quit") == 0){
                return QUIT;
        }
        return 8;
}

/**
 *  run_main_loop(): runs offspring program until told to quit.
 *  commands include help, add, find, height, size, print, init, and quit.
 *  param tree: pointer to a tree structure program will use.
 */
int run_main_loop(tree_node_t *tree){
	printf("offspring> ");
        char buff[1024];
	while(fgets(buff,1024,stdin)!=NULL){
		trim(buff);
		char copy[1024];
		strcpy(copy,buff);
                char* command = strtok(buff," ");
		trim(command);
		int l = strlen(command);
  		char *real = copy+l;
		trim(real);
		if(strcmp(command,"")==0||strcmp(command,"EOF")==0){
			printf("+ EOF\n\n");
		}
		else{
                command_type_t COMMAND_TYPE = check_command(command);
                switch(COMMAND_TYPE){
			case ADD:
				printf("+ add %s\n\n",real);
				if(strcmp(real,"")==0){
					break;
				}
				char *parent =  strtok(real,",");
				trim(parent);
				if(strcmp(parent,"")==0){
					printf("Usage: 'add parent name , child name'\n");
					break;
				}
				char*parent_name = (char*)malloc(strlen(parent));
				strcpy(parent_name,parent);
				parent = strtok(NULL,",");
				trim(parent);
				if(strcmp(parent,"")==0){
					printf("Usage: 'add parent name , child name'\n");
					break;	
				}
				char *kid = (char*)malloc(strlen(parent));
				strcpy(kid,parent);
				trim(kid);
				trim(parent_name);
				parent = strtok(NULL,",");
				if(parent!=NULL){
					printf("Usage: 'add parent name , child name'\n");
					break;
				}
				if(strcmp(parent_name,"")==0 || strcmp(kid,"")==0){
					printf("Usage: 'add parent name , child name'\n");
					break;	
				}
				else{
					if(tree==NULL){
						tree = create_node(parent_name);
						add_child(tree,parent_name,kid);		
					
					}
					else if(strcmp(tree->name,kid)==0){	
						tree = add_child(tree,parent_name,kid);
						run_main_loop(tree);
					}
					else{
						 add_child(tree,parent_name,kid);
					}
				}    
				break;                                     
			case FIND:
				printf("+ find %s\n\n",real);
				if(tree ==NULL){
                                       	fprintf(stderr,"error: '' not found\n");
					break;
                                }	
				if(strcmp(real,"")==0){
					printf("%s had ",tree->name);
                                        tree_node_t *kid = tree->child;
                                        if(kid==NULL){
                                        	printf("no offspring.\n");
                                                break;
                                        }
					while(kid!=NULL){
                                        	if(kid->next == NULL){
                                	                printf("%s.",kid->name);
                                                }
                                                else if(kid->next->next==NULL){
                                                	printf("%s and ",kid->name);
                                                }
                                                else{
                        	                        printf("%s, ",kid->name);
                                                }
                                                kid = kid->next;
                                        }
					printf("\n");
                                        break;
                                }
				char *real_name = (char*)malloc(strlen(real));
			        strcpy(real_name,real);
                                real = strtok(real,",");
				real = strtok(NULL,",");
				if(real!=NULL){
					fprintf(stderr,"error: please enter only one name\n");
					break;
				}
				else{
					tree_node_t *found = find_node(tree,real_name);
					if(found==NULL){
						fprintf(stderr,"error: '%s' not found.\n",real_name);
					}
					else{
						printf("%s had ",found->name);
						tree_node_t *kid = found->child;
						if(kid==NULL){
							printf("no offspring.\n");
							break;
						}
						while(kid!=NULL){
							if(kid->next == NULL){
								printf("%s.",kid->name);
							}
							else if(kid->next->next==NULL){
								printf("%s and ",kid->name);
							}
							else{
								printf("%s, ",kid->name);
							}
							kid = kid->next;	
						}
						printf("\n");
					}
                                }
				break;
		       	case PRINT:
				printf("+ print %s\n\n",real);
				if(tree ==NULL){
					fprintf(stderr,"error: '%s' not found.\n",real);
					break;
				}
				if(strcmp(real,"")==0){
					print_tree(tree,tree->name);
					break;
				}
				else{
					char *n =  strtok(real,",");
					trim(n);	
					if(strcmp(n,"")==0){
						print_tree(tree,tree->name);
                                        	break;
                                	}
					else{
		                                char *print_name = (char*)malloc(strlen(n));
                	                	strcpy(print_name,n);
						n = strtok(NULL,",");
                                		if(n!=NULL){
     							fprintf(stderr,"error: please enter only one name'\n");
                                        		break;
                                 		}
						
						else{
							tree_node_t *find = find_node(tree,print_name);
							if(find ==NULL){
								fprintf(stderr,"error: '%s' not found\n",print_name);
								break;
							}	
						print_tree(tree,print_name);
						}
					}
				}
				break;
			case SIZE:
				printf("+ size %s\n\n",real);
				if(tree ==NULL){
					printf("size: 0\n");
					break;
				}
				if(strcmp(real,"")==0){	
					int s = tree_size(tree,tree->name);
                                        printf("size: %d\n",s);
                                        break;
				}		
				char *s =  strtok(real,",");
				trim(s);
				char *find_size = (char*)malloc(strlen(s));
				strcpy(find_size,s);
				s = strtok(NULL,",");
				if(s!=NULL){
					fprintf(stderr,"error: please enter only one name'\n");
					break;
				}
				else{
					tree_node_t *exist = find_node(tree,find_size);
					if(exist==NULL){
						printf("size: 0\n");
						break;
					}
					int size = tree_size(tree,find_size);
					printf("size: %d\n",size);
				}
				break;
			case HEIGHT:	
				printf("+ height %s\n\n",real);
				if(tree ==NULL){
					printf("height: -1\n");
					break;
				}
				if(strcmp(real,"")==0){
					int hh = tree_height(tree,tree->name);
					printf("height: %d\n",hh);
					break;
				}                        
				char *find_height = (char*)malloc(strlen(real));
				strcpy(find_height,real);
				real = strtok(real,",");
				real = strtok(NULL,",");
				if(real!=NULL){
					fprintf(stderr,"error: please enter only one name'\n");
					break;
				}
				else{
					tree_node_t *e = find_node(tree,find_height);
					if(e==NULL){
						printf("height: -1\n");
						break;
					}
					int height = tree_height(tree,find_height);
					printf("height: %d\n",height);
				}
				break;
			case INIT:
				printf("+ init %s\n\n",real);
				if(tree==NULL){
					break;
				}
				destroy_tree(tree);
				run_main_loop(NULL);
				break;
			case HELP:
				printf("+ help\n\n");
				printf("User Commands for offspring:\n"
 						"add parent-name, child-name # find parent and add child.\n"
 						"find name     # search and print name and children if name is found.\n"
 						"print [name]  # breadth first traversal of offspring from name.\n"
 						"size [name]   # count members in the [sub]tree.\n"
 						"height [name] # return the height of [sub]tree.\n"
 						"init          # delete current tree and restart with an empty tree.\n"
						"help          # print this information.\n"
 						"quit          # delete current tree and end program.\n");
				break;
			case QUIT:
				printf("+ quit\n\n");
				if(tree!=NULL){
					destroy_tree(tree);					
				}
				exit(0);
                        default:
                                fprintf(stderr,"error: unknown command, use help for list of commands\n");
                }
		}
		printf("offspring> ");
        
	}
	return 0;
}

/**
 *  main(): main function takes one optional command line argument, a filename.
 *  If given, a tree is constructed using file and main loop is run. Otherwise,
 *  the main loop is run right away.
 *  param argc: number of command line arguments
 *  param argv: array of command line arguments
 */
int main(int argc, char * argv[]){
	if(argc >2){
		printf("error");	
		return EXIT_FAILURE;	
	}
	if(argc == 2){
		 int file_exists = access(argv[1],F_OK);
		 if(file_exists!=0){
			printf("error");
			return EXIT_FAILURE;	
		 }
		 else{
			tree_node_t *tree = file_make_tree(argv[1]);
		 	run_main_loop(tree);
			return 0;
		 }
	}
	else{
		tree_node_t *tree = NULL;
		run_main_loop(tree);
	}
	return 0;
}
