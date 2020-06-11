// 
// File: tree.c
// Description: side module for CS243 project_3. Includes functions pertaining
// to tree_node_t struct implementation.
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// 
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
#include "tree.h"

/**
 *  eq(): comparison function used for queue. compares two void pointers.
 *  returns true if they are equal, false otherwise.
 *  param a: first object to compare
 *  param b: second object to compare.
 */
bool eq(void *a, void *b){
	tree_node_t *person_a = (tree_node_t*)a;
	tree_node_t *person_b = (tree_node_t*)b;
	if(strcmp(person_a->name,person_b->name) == 0 && person_a->num_kids == person_b->num_kids){
		return true;
	}
	return false;
}

/**
 *  makes one tree_node_t struct and returns a pointer to it.
 */
tree_node_t *create_node( char* name ){ // returns a node pointer or NULL if it fails.
        tree_node_t *tree =  (tree_node_t*)malloc(sizeof( tree_node_t));
	char* newname = (char*)malloc(strlen(name));
	strcpy(newname,name);
	tree->name = newname;
        tree->num_kids = 0;
	tree->gen = 0;
	tree->next = NULL;
	tree->child = NULL;
        return tree;
}

/**
 *  Destroys a tree structure, free's all memory
 */
void destroy_tree( tree_node_t *tree ){// frees all memory of the tree and its offspring.
        queue_t queue = que_create(eq);
        que_enqueue(queue,(void*)tree);
	while(queue->size > 0){
                tree_node_t *node = (tree_node_t*)(que_front(queue));
                que_dequeue(queue);
                tree_node_t *temp = node->child;
                while(temp!=NULL){
                        que_enqueue(queue,(void*)temp);
                        temp = temp->next;
                }
		free(node->name);			
		free(node);
        }
	que_destroy(queue); 
}


/**
 * finds a node in the family tree, representing a person
 */
tree_node_t *find_node( tree_node_t *tree, char* name ){// returns the node pointer or NULL.
        queue_t queue = que_create(eq);
        que_enqueue(queue,(void*)tree);
	while(queue->size > 0){
		tree_node_t *node = (tree_node_t*)(que_front(queue));
		que_dequeue(queue);
	 	if(strcmp(node->name,name)==0){
			que_destroy(queue);
			return node;	
		}
		else{
			tree_node_t *temp = node->child;
			while(temp!=NULL){
				que_enqueue(queue,(void*)temp);
				temp = temp->next;
			}
	 	}
		
	 }
	 que_destroy(queue);
	 return NULL;	
}
        
/**
 *  prints out the family tree
 */
void print_tree( tree_node_t *tree, char* name ){
	queue_t queue = que_create(eq);
        tree_node_t *top = find_node(tree, name);
	que_enqueue(queue,(void*)top);
        while(queue->size > 0){
 		tree_node_t *node = (tree_node_t*)(que_front(queue));
                que_dequeue(queue);
		if(node->num_kids==0){
               		printf("%s had no offspring.\n",node->name);
		}
		else{
               		tree_node_t *k = node->child;
			printf("%s had ",node->name);
                	while(k!=NULL){
          	       		if(k->next == NULL){
			      		printf("%s.\n",k->name);
                      		}
                        	else if(k->next->next==NULL){
       					printf("%s and ",k->name);
                	        	}
                      		else{
                                	printf("%s, ",k->name);
		      		}
                      		que_enqueue(queue,(void*)k);
                      		k = k->next;
            		}
			
		}	
        }
	que_destroy(queue);
}


/**
 *  Adds a node to the family tree
 */
tree_node_t *add_child( tree_node_t *tree, char *parent_name, char *child_name ){
	if(strcmp(parent_name,tree->name)==0){
		tree_node_t *kid = create_node(child_name);
		kid->gen = tree->gen;
		kid->gen+=1;
		if(tree->num_kids==0){
			tree->child = kid;
		}		 
		else{
		 	tree_node_t *temp = tree->child;
		 	while(temp->next!=NULL){
		 		if(strcmp(temp->name,child_name)==0){
					fprintf(stderr,"error: '%s' is already a child of '%s'.\n",child_name,parent_name);
					return NULL;
				}
				temp = temp->next;
				if(strcmp(temp->name,child_name)==0){
                                        fprintf(stderr,"error: '%s' is already a child of '%s'.\n",child_name,parent_name);
                                        return NULL;
				}
			}
			temp->next = kid;
		 }
		 tree->num_kids++;
                 return tree;  
	}
	tree_node_t *parent_node = find_node(tree,parent_name);
	if(parent_node==NULL){
		if(strcmp(tree->name,child_name)==0){
			tree_node_t *new_tree = create_node(parent_name);
			new_tree->child = tree;
			new_tree->num_kids = 1;
			queue_t queue = que_create(eq);
		        que_enqueue(queue,(void*)tree);
        		while(queue->size > 0){
                		tree_node_t *node = (tree_node_t*)(que_front(queue));
                		que_dequeue(queue);
				int g = node->gen;
				node->gen = g+1;
                        	tree_node_t *temp = node->child;
                        	while(temp!=NULL){
                                	que_enqueue(queue,(void*)temp);
                                	temp = temp->next;
                        	}
			}
			return new_tree;
			
		}
		fprintf(stderr,"error: '%s' is not in the tree and '%s' is not the root.\n",parent_name,child_name);
		return NULL;
	}
	else{
		tree_node_t *kid = create_node(child_name);
		kid->gen = parent_node->gen;
		kid->gen +=1;
		if(parent_node->num_kids==0){
        	        parent_node->child = kid;
                }
                else{
               		tree_node_t *temp = parent_node->child;
                        while(temp->next!=NULL){
		        	if(strcmp(temp->name,child_name)==0){
                                	fprintf(stderr,"error: '%s' is already a child of '%s'.\n",child_name,parent_name);
                                        return NULL;
                                }
                                temp = temp->next;
				if(strcmp(temp->name,child_name)==0){
                                        fprintf(stderr,"error: '%s' is already a child of '%s'.\n",child_name,parent_name);
                                        return NULL;
				}
			}
                        temp->next = kid;
                 }      
                 parent_node->num_kids++;
                 return tree;		
	}
}


/**
 *  finds the number of people in a family tree
 */
int tree_size(tree_node_t *tree, char* name){
	queue_t queue = que_create(eq);
        tree_node_t *top = find_node(tree,name);
	que_enqueue(queue,(void*)top);
	int size = 0;
        while(queue->size > 0){
        	tree_node_t *node = (tree_node_t*)(que_front(queue));
                que_dequeue(queue);
		size++;
                tree_node_t *temp = node->child;
                while(temp!=NULL){
              		que_enqueue(queue,(void*)temp);
                	temp = temp->next;
                }
         }
	 que_destroy(queue);
         return size;
}


/**
 *  find the height of a family tree
 */ 
int tree_height(tree_node_t *tree, char* name){
        queue_t queue = que_create(eq);
        tree_node_t *top = find_node(tree,name);
	if(top==NULL){
		int x = 0 - 1;
		return x;
	}
	int top_gen = top->gen;
        int bottom_gen = top_gen;
	que_enqueue(queue,(void*)top);
        while(queue->size > 0){
                tree_node_t *node = (tree_node_t*)(que_front(queue));
                que_dequeue(queue);
		if(node->gen > bottom_gen){
			bottom_gen = node->gen;		 
		}
                tree_node_t *temp = node->child;
                while(temp!=NULL){
                        que_enqueue(queue,(void*)temp);
                        temp = temp->next;
                }
	
         }
	 que_destroy(queue);
         return bottom_gen - top_gen;
}


