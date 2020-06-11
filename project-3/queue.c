// 
// File: queue.c
// Description: side module for CS243 project_3. 
// Queue ADT implementation
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// 
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/**
 * que_create(): creates an empty queue.
 * param equiv: comparison function pointer, not needed for this project.
 */
queue_t que_create( bool (*equiv)( void * item1, void * item2 ) ){    
	queue_t queue = (queue_t)malloc(sizeof(struct queueStruct));
	queue->e = equiv;
	queue->head =  NULL; //(queue_item_t*)malloc(sizeof(queue_item_t));
	queue->tail = queue->head;// (queue_item_t*)malloc(sizeof(queue_item_t));
	queue->size = 0;
	return queue;
}

/**
 *  que_destroy(): destroys a queue ADT, freeing all memory
 *  param queue: the queue to be destoyed
 */
void que_destroy( queue_t queue ){
	while(queue->size!=0){
		queue_item_t *h = queue->head;
		que_dequeue(queue);	
		free(h);
	}	
	free(queue);
}

/**
 *  que_destroy(): clears a queue ADT.
 *  param queue: the queue to be cleared
 */
void que_clear( queue_t queue ){
	while(queue->size!=0){
                que_dequeue(queue);
        }
}

/**
 *  que_enqueue(): adds an item to the back of queue
 *  param queue: the queue an item will be added to
 *  param data: item to be enqueued.
 */
void que_enqueue( queue_t queue, void * data ){
	queue_item_t *item = malloc(sizeof(queue_item_t));
	item->data = data;
	item->next = NULL;
	if(queue->size==0){
		queue->head = item;
		queue->tail = item;
		queue->size+=1;
	}
	else{
		queue->tail->next = item;
		queue->tail = queue->tail->next;
		queue->size+=1;
	}
}


/**
 *  que_dequeue(): removes an item from front of queue
 *  param queue: the queue an item will be removed from
 */
void que_dequeue( queue_t queue ){
	queue->head = queue->head->next;
	queue->size-=1;
	
}


/**
 *  que_front(): shows item at front of queue
 *  param queue: the queue to be peeked at
 */
const void * que_front( const queue_t queue ){
	return queue->head->data;
}

/**
 *  que_size(): returns number of items in queue (size)
 *  param queue: the queue who's size will be returned
 */
size_t que_size( queue_t queue ){
	return queue->size;
}

