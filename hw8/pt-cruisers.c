// 
// File: pt-cruisers.c  
// Description: program runs threads of multiple racer structs to simulate a
// race.
// 
// @author Youssef Naguib <ymn4543@rit.edu>
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "racer.h"
#include "display.h"


/**
 * main(): does the following:
 * 		- If first argument given is numeric, sets it as maximum value
 * 		  for the random number generator.
 * 		- All other arguments will be names of racers.
 * 		- All racers created, and corresponding threads are created.
 * 		- threads all run concurrently, and program does not end until
 * 		  all racers reach the finish line.
 * 		- memory deallocated
 * 		- program exits.   
 */
int main( int argc, char** argv){
	if(argc ==1){
		fprintf(stderr,"Usage: pt-cruisers [ delay ] racer1 racer2 [racer3...]\n");
                return EXIT_FAILURE;
	}
	int num_racers = 0;
	racer_t* racers[argc];
	//seed random number gen
	srand(time(NULL));
	char *eptr;
	long first = strtol(argv[1],&eptr,0);
	if (first!=0){
		if(first<0){
			fprintf(stderr,"Delay %ld is invalid.\n",first);
			fprintf(stderr,"Usage: pt-cruisers [ delay ] racer1 racer2 [racer3...]\n");
                	return EXIT_FAILURE;
		}
		//if > 0 , make max wait time
		//pass to init_racers
		
		char *ptr;
		long millisecs;
		millisecs = strtol(argv[1],&ptr,10);
		
		init_racers(millisecs);
		int x = 2;
		int p = 0;
		int r = 0; 
   	    	while(x<argc){
               		racer_t *racer = make_racer(argv[x],p);   //create racer
                        p++;
			if(racer!=NULL){
                                racers[r] = racer;
                                r++;
                                num_racers++;
                        }   
			x++;
		}
		if(num_racers==0){
			fprintf(stderr,"Usage: pt-cruisers [ delay ] racer1 racer2 [racer3...]\n");
                	return EXIT_FAILURE;
		}
	}
	else{
		init_racers(0);
		int r = 0;
		int x = 1;
		int p = 0;
        	while(x<argc){
               		racer_t *racer = make_racer(argv[x],p);   //create racer
     			p++;
			if(racer!=NULL){
				racers[r] = racer;
				r++;
				num_racers++;
			}	
                        x++;
        	}
	
	}
	if(num_racers<2){
		fprintf(stderr,"Usage: pt-cruisers [ delay ] racer1 racer2 [racer3...]\n");
		destroy_racer(racers[0]);
		return EXIT_FAILURE;
	}
	void *retval;
	int num_threads = num_racers;
	pthread_t threads[num_threads];
	//printf("There are %d racers: %s and %s\n",num_racers,racers[0]->graphic,racers[1]->graphic);
	clear();
	for(int f = 0;f<num_racers;f++){
		pthread_create( &threads[f], NULL, run, (void*)(racers[f]) );
	}
	
	for ( int t = 0; t < num_threads; ++t ) {
        	pthread_join( threads[t], &retval );
	       // printf( "Thread #%d returned %lu.\n", t, (unsigned long) retval );
	}
	for(int v = 0;v<num_racers;v++){
		destroy_racer(racers[v]);
	}
	printf("\n\n");
	return EXIT_SUCCESS;

}
