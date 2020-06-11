// 
// File: queue.h
// Description: header file for queue.c, a side module for  CS243 project_3. 
// Includes functions pertaining to queue ADT implementation.
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// 
// // // // // // // // // // // // // // // // // // // // // // // //

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//queueStruct type
typedef struct queueStruct *queue_t;

//function pointer type
typedef bool (*equiv)(void *item1, void *item2);

/**
 * struct representing one item in the queue.
 */
typedef struct queue_item_t{
        void *data;
        struct queue_item_t *next;
}queue_item_t;

/**
 * struct representing a queue. Each queue has a head, tail, and size.
 */
typedef struct queueStruct{
        equiv e;
        int size;
        struct queue_item_t *head;
        struct queue_item_t *tail;
}queueStruct;


/**
 * que_create(): creates an empty queue.
 * param equiv: comparison function pointer, not needed for this project.
 */
queue_t que_create( bool (*equiv)( void * item1, void * item2 ) );


/**
 *  que_destroy(): destroys a queue ADT, freeing all memory
 *  param queue: the queue to be destoyed
 */
void que_destroy( queue_t queue );


/**
 *  que_destroy(): clears a queue ADT.
 *  param queue: the queue to be cleared
 */
void que_clear( queue_t queue );


/**
 *  que_enqueue(): adds an item to the back of queue
 *  param queue: the queue an item will be added to
 *  param data: item to be enqueued.
 */
void que_enqueue( queue_t queue, void * data );


/**
 *  que_dequeue(): removes an item from front of queue
 *  param queue: the queue an item will be removed from
 */
void que_dequeue( queue_t queue );

/**
 *  que_front(): shows item at front of queue
 *  param queue: the queue to be peeked at
 */
const void * que_front( const queue_t queue );


/**
 *  que_size(): returns number of items in queue (size)
 *  param queue: the queue who's size will be returned
 */
size_t que_size( queue_t queue );

#endif
