// File: tree_node.c  
// Description: tree_node source file for project_2 (CS243)
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree_node.h"

/**
 *  make_interior(): creates an interior tree_node with given parameters.
 *  param op: interior node's operation type
 *  param token: interior node's token
 *  param left: pointer to interior node's left node
 *  param right: pointer to interior node's right node.
 */
tree_node_t *make_interior(op_type_t op, char *token, tree_node_t *left, tree_node_t *right){
	tree_node_t *interior = (tree_node_t*)malloc(sizeof(tree_node_t));
	interior->type = INTERIOR;
	interior->token =token;
	interior_node_t* node = (interior_node_t*)malloc(sizeof(interior_node_t));
	node->op = op;
	node->left = left;
	node->right = right;
	interior->node = (interior_node_t*) node;
	return interior;

}

/**
 *  make_leaf(): creates a leaf tree_node with given parameters.
 *  param exp_type: leaf node's expression type (SYMBOL OR INTEGER)
 *  param token: leaf node's token
 */
tree_node_t *make_leaf(exp_type_t exp_type, char *token){
	tree_node_t *leaf = (tree_node_t*)malloc(sizeof(tree_node_t));
        leaf->type = LEAF;
	leaf->token = token;
	leaf_node_t* node = (leaf_node_t*)malloc(sizeof(leaf_node_t));
	node->exp_type = exp_type;	
	leaf->node =(leaf_node_t*)node;
	return leaf;
}





