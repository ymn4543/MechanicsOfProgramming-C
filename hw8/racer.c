// 
// File: racer.c
// Description: source file for racer structure
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "display.h"
#include "racer.h"

long MAX_WAIT; //maximum waiting time between moves


/**
 * init_racers(): Sets the MAX_WAIT time.
 * @param milliseconds: waiting time in milliseconds
 */
void init_racers( long milliseconds ){
	if(milliseconds == 0){
		MAX_WAIT = DEFAULT_WAIT;
	}
	else{
		MAX_WAIT = milliseconds;
	
	}
}



/**
 * make_racer(): creates an instance of a racer struct.
 * param name: name of racer.
 * param position: row of racer.
 * return: pointer to racer created.
 */
racer_t *make_racer( char *name, int position ){
	racer_t *racer = (racer_t*)malloc(sizeof(racer_t));
	int x = strlen(name);
	if(x>MAX_NAME_LEN){
		fprintf(stderr,"Usage: racer names must not exceed length %d.\n",MAX_NAME_LEN);
		free(racer);
		return NULL;
	}
	else if(x==MAX_NAME_LEN){
		char *str = (char*)malloc(MAX_NAME_LEN);
		strcpy(str,name);
		racer->graphic = str;
	}
	else{
		char *str = (char*)malloc(MAX_NAME_LEN);
	        int rem = MAX_NAME_LEN - x;
       		if(rem%2 !=0){
                	rem--;
        	}
        	int before = rem/2;
        	int c = 0;
        	while(c<before){
                	str[c] = '_';
                	c++;
        	}
        	int w = 0;
        	while(w<x){
        	        str[c] = name[w];
        	        w++;
        	        c++;
        	}
        	while(c<MAX_NAME_LEN){
                	str[c] = '_';
               		c++;
        	}
        	racer->graphic = str;
	}
	racer->dist = 1;
	racer->row = position;
	return racer;
}

/**
 * destroy_racer(): deallocates all memory associated with a racer.
 * param racer: racer to destroy
 */
void destroy_racer( racer_t *racer ){
	free(racer->graphic);
	free(racer);
}

/**
 * run(): is the main function of a racer. A racer moves across the screen in
 *        random intervals.
 * param racer: racer to run.       
 */
void *run( void *racer ){
	racer_t *Racer = (racer_t*)racer;
	set_cur_pos(Racer->row+1,1);
	int x = 0;
	int r = Racer->row+1;
	int d = Racer->dist;
	while(x<MAX_NAME_LEN){
		put(Racer->graphic[x]);
		x++;
		d++;
		set_cur_pos(r,d);
	}
	x = 0;
	d = Racer->dist;
	set_cur_pos(r,d);
	while(Racer->dist!=FINISH_LINE){
		int t = rand() % MAX_WAIT*1000;
		usleep(t);
		//erase
		int a =d;
		int c = 0;
		set_cur_pos(r,a);
		while(c<MAX_NAME_LEN){
			put(' ');
                	c++;
			a++;
                	set_cur_pos(r,a);
	        }
		d++;
		set_cur_pos(r,d);
		Racer->dist=d;
		int z = 0;
		int v = Racer->dist;
        	while(z<MAX_NAME_LEN){
        	        put(Racer->graphic[z]);
                	z++;
                	v++;
			set_cur_pos(r,v);
        	}
		set_cur_pos(r,d);
	}	
	return NULL;
}






