//test program for queue ADT
//author: Youssef Naguib <ymn4543@rit.edu>


#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
#include "tree.h"

bool eqiu(void *a, void *b){
        tree_node_t *person_a = (tree_node_t*)a;
        tree_node_t *person_b = (tree_node_t*)b;
        if(strcmp(person_a->name,person_b->name) == 0 && person_a->num_kids == person_b->num_kids){
                return true;
        }
        return false;
}



int main(void){
	char * l = "john";
	
	queue_t queue = que_create(eqiu);

	que_enqueue(queue,(void*)l);
	printf("queue size: %d\n",queue->size);
	char * lem = (char*)que_front(queue); 
	  printf("queue front: %s\n",lem);
	que_dequeue(queue);
	 printf("queue size: %d\n",queue->size);







	return 0;
}
