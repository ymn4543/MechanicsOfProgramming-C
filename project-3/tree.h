// 
// File: tree.h
// Description: header file for tree.c, a side module for  CS243 project_3. 
// Includes functions pertainingto tree_node_t struct implementation.
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// 
// // // // // // // // // // // // // // // // // // // // // // // //

#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/**
 * struct representing one node (person) in the family tree.
 * Each node has a name, number of kids, generation number, pointer to sibling,
 * and pointer to first child.
 */
typedef struct tree_node {
    char *name;
    int num_kids;
    int gen;
    struct tree_node *next;   
    struct tree_node *child;	
}tree_node_t;


/**
 *  create_node(): makes one tree_node_t struct and returns a pointer to it.
 *  param name: name of the person this node will represent.
 *  returns: pointer to new node created.	
*/
tree_node_t *create_node( char* name );


/**
 *  destroy_tree(): Destroys a tree structure, free's all memory
 *  param tree: head node of tree to be destroyed
 */
void destroy_tree( tree_node_t *tree );


/**
 *  find_node(): finds a node in the family tree, representing a person
 *  param tree: head node of tree where node is located
 *  param name: the name of the node being searched for
 */
tree_node_t *find_node( tree_node_t *tree, char* name );


/**
 *  print_tree(): prints out the family tree
 *  param tree: head node of tree
 *  param name: name of first individual user wants printed, the function
 *              will print tree from this individual down.
 */
void print_tree( tree_node_t *tree, char* name );


/**
 *  add_child(): Adds a node to the family tree
 *  param tree: tree that node will be added to
 *  param parent_name: name of the parent of new node
 *  param child_name: name of new noded
 */
tree_node_t *add_child( tree_node_t *tree, char* parent_name, char* child_name );


/**
 *  tree_size(): find the number of people in a family tree
 *  param tree: tree who's size will be returned
 *  param name: name of individual at top of subtree. Size of tree starting
 *              at this individual will be returned.
 */
int tree_size(tree_node_t *tree, char* name);


/**
 *  tree_height(): find the height of a family tree
 *  param tree: tree who's height will be returned
 *  param name: name of individual at top of subtree. Height of tree starting
 *              at this individual will be returned.
 */
int tree_height(tree_node_t *tree, char* name);

#endif
