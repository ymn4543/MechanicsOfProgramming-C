// 
// File: brace-topia.c
// Description:
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// 
// version control: git
// // // // // // // // // // // // // // // // // // // // // // // //
///
#define _DEFAULT_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> 
#include <unistd.h>
#include "display.h"



/// get() : returns the value at a certain position in a 2D array.
/// if the value is outside the bounds of the array, the function returns '0';
///
/// @param dim: square dimension of 2d array
/// @param board: 2d array
/// @param row: row position of wanted value in array
/// @param col: column position of wanted value in array
/// @returns a char representing a position in array, or a '0' char if out of
/// bounds
char get(int dim, char board[dim][dim], int row, int col){
	if(row>-1 && col >-1){
		if(row < dim && col < dim){
			return board[row][col];
		}
	}
	return '0';
}


/// measure_happiness() : returns the happiness of a an agent in the 2d array
/// by looking at it's neighbors
///
/// @param dim: square dimension of 2d array
/// @param board: 2d array
/// @param row: row position of agent
/// @param col: column position of agent
/// @returns a double representing the happiness of an agent (between 0 and 1)
double measure_happiness(int dim, char board[dim][dim], int row, int col){
	char this = board[row][col];
	int neighbors = 0;
	int friends = 0;
	char n[8] = { get(dim,board,row-1,col-1), get(dim,board,row-1,col),
	              get(dim,board,row-1,col+1), get(dim,board,row,col-1),
		      get(dim,board,row,col+1), get(dim,board,row+1,col-1),
		      get(dim,board,row+1,col), get(dim,board,row+1,col+1) };

	for(int x =0;x<8;x++){
		char person = n[x];
		if(person == 'e' || person == 'n'){
			neighbors++;
			if(person==this){
				friends++;
			}
		}
	}
	if(neighbors ==0){
		return 0;
	}
	double happiness = (double) friends/(double) neighbors;
	return happiness;
}

/// average_happiness() : returns the average happiness of all the agents
/// in the 2d array
///
/// @param dim: square dimension of 2d array
/// @param board: 2d array
/// @returns a double representing average happiness (between 0 and 1)
double average_happiness(int dim, char board[dim][dim],int people){
        double sum = 0;
        double p =(double) people;
        for(int row = 0;row<dim;row++){
                for(int col = 0;col<dim;col++){
                        if(board[row][col]!= '.'){
                                double happiness = measure_happiness(dim,board,row,col);
				sum += happiness;
                        }
                }
        }
        double average = sum/p;
        return average;
}




/// move() : moves an unsatisfied agent to the first available vacant spot 
///
/// @param dim: square dimension of 2d array
/// @param board: 2d array
/// @param row: row position of agent
/// @param col: column position of agent
/// @returns an int, 0 if agent was succesfully moved, 1 if agent was not moved.
int move(int dim, char board[dim][dim],int row, int col){
	char this;
	if(board[row][col] == 'e'){
		this = 'E';
	}
	if(board[row][col] == 'n'){
		this = 'N';
	}
	for(int r = 0;r<dim;r++){		//iterate from start of board to find first vacant spot
		for(int c = 0; c<dim;c++)  {
			if(board[r][c] == '.'){       //if its vacant
				board[r][c] = this;
				board[row][col] = '*';
				return 0;
			}
		}
	}
	return 1;
}

/// cycle(): iterates through every agent and measures their happiness. 
/// If agent's happiness is below the given happiness measure, they are moved
/// to a new, vacant location in the 2d array.c
///
/// @param dim: square dimension of 2d array
/// @param board: 2d array
/// @param measure: the required happiness measure for an agent to be satisfied
/// @returns an int representing the # of agents that were moved.
int cycle(int dim, char board[dim][dim], int measure){
	float hm = (float) measure / 100;
	int moves =0;
	for(int r =0;r<dim;r++){
		for(int c = 0; c<dim;c++){
			if(board[r][c] == 'e' || board[r][c] =='n'){		//if agent
				if(measure_happiness(dim,board,r,c)<hm){  	// if agent unhappy
					int m = move(dim,board,r,c);		//move them			
					if(m==0){
						moves+=1;		//add 1 to moves
					}									
				}	
			}
		}
	}

	//convert board
	 for(int q=0;q<dim;q++){
                for(int w =0;w<dim;w++){
                        if(board[q][w] == '*'){
                                board[q][w] = '.';
                        }
			if(board[q][w] == 'N'){				
                                board[q][w] = 'n';
                        }
			if(board[q][w] == 'E'){
                                board[q][w] = 'e';
                        }
                }
        }
	return moves; 
}


/// generate_board(): fills a 2d array with the correct specifications.
/// These specifications include percentages of vacant spots, spots occupied
/// by newline agents, and spots occupied by endline agents. 
/// The function places all the endline agents, then the vacant locations,
/// and finally the newline agents. After all spots are filled, the array
/// is randonly shuffled and moved around.
///
/// @param vacancy: percent of vacant locations, expressed as int
/// @param endliners: percent of endline agents, expressed as int
/// @param dim: square dimension of 2d array
/// @param board: 2d array
void generate_board(int vacancy, int endliners, int dim, char board[dim][dim]){
	float multiplier =  (float)dim*(float)dim /100;
	int total_endliners = multiplier*endliners; 
	int total_vacancies =  multiplier*vacancy; 
	int count = 0;
	char current = 'e';
	int placeholder = total_endliners;
	//place in order first
	for(int r=0;r<dim;r++){
		for(int c=0; c<dim; c++){
			if(count==placeholder){
                        	if(placeholder == total_endliners){
                        		placeholder = total_vacancies;
                        		current = '.';
                        		count = 0;
                        	}	
                        	else if(placeholder == total_vacancies){
                        		current = 'n';
                        	}
                	}
			board[r][c] = current;
			count++;
		}
	}	
 		
    // shuffle array
	for(int k=0;k<dim;k++){
        	for(int m=0;m< dim;m++){
			int r1 = rand()%dim;
        		int r2 = rand()%dim;
        		char temp = board[k][m];
			board[k][m] = board[r1][r2];
			board[r1][r2] = temp;
    		}	
	}
}


/// print_board(): this function simply prints out the 2d array to standard 
/// output, displaying it to the user.
///
/// @param dim: square dimension of 2d array
/// @param board: 2d array
void print_board(int dim, char board[dim][dim]){
	for(int row = 0; row<dim; row++){
		for( int col = 0;col<dim;col++){
			printf("%c",board[row][col]);
		}
		puts(" ");
	}
}


/// Main function for the brace-topia program.
///
/// @param argc  integer number of command line arguments including program name
/// @param argv  array of command line arguments
/// @returns EXIT_SUCCESS if no error, or EXIT_FAILURE on error
int main(int argc, char *argv[]){
  int dim = 15;  		//default dimension
  int pref_strength = 50;       //default strength of preference
  int vacancy = 20;		//default vacancy percent
  int endline_percent = 60;     //default endliner percent
  int cycles;			//cyles for print mode
  int time= 900000;		//default time between cycles
  int opt;
  int print_mode = 0;           //print_mode set to false
  srandom(41);			//random seed
  while ( (opt = getopt( argc, argv, "ht:c:d:s:v:e:") ) != -1 ) {
        switch ( opt ){
        case 'h': //print help message
            printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","usage:",
		"brace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %vac] [-e %%end]",
		"Option      Default   Example   Description",
		"'-h'        NA        -h        print this usage message.",
		"'-t N'      900000    -t 5000   microseconds cycle delay.",
		"'-c N'      NA        -c4       count cycle maximum value.",
		"'-d dim'    15        -d 7      width and height dimension.",
		"'-s %%str'  50        -s 30     strength of preference.",
		"'-v %vac'   20        -v30      percent vacancies.",
		"'-e %%endl' 60        -e75      percent Endline braces. Others want Newline.");
	    return (1 + EXIT_FAILURE);
	    break;

        case 't': //change time
            time = atoi(optarg);
	    if(time<1){
		fprintf(stderr,"time (%d) must be a non-negative integer.\n",time);
                fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
                return (1 + EXIT_FAILURE);
	    }
            break;
        case 'c': //change cycles
            cycles = atoi(optarg);
	    print_mode = 1;
	    if(cycles<0){
		fprintf(stderr,"count (%d) must be a non-negative integer.\n",cycles);
		fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
	    	return (1 + EXIT_FAILURE);
	    }

                break;	
            
	case 'd': //change dimensions
            dim = atoi(optarg);
	    if(dim<5 || dim>39){
		fprintf(stderr,"dimension (%d) must be a value in [5...39] \n",dim);
                fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
                return (1 + EXIT_FAILURE);
            }

            break;
	case 's': //change strength of preference
            pref_strength = atoi(optarg);
	     if(pref_strength < 1 || pref_strength >99){
                fprintf(stderr,"preference strength (%d) must be a value in [1...99] \n",pref_strength);
                fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
                return (1 + EXIT_FAILURE);
            }

            break;
	case 'v': //change percent of vacancies
            vacancy = atoi(optarg);
	    if(vacancy<1 || vacancy>99){
		fprintf(stderr,"vacancy (%d) must be a value in [1...99] \n",vacancy);
                fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
                return (1 + EXIT_FAILURE);
	    }
            break;    
	case 'e': //change percent of endliners
            endline_percent = atoi(optarg);
	    if(endline_percent < 1 || endline_percent >99){
		fprintf(stderr,"endline proportion (%d) must be a value in [1...99] \n",endline_percent);
                fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
                return (1 + EXIT_FAILURE);
            }
            break;
	
        default:
            fprintf( stderr, "usage: \nbrace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n" );
            exit( EXIT_FAILURE );
        }
  }  
	//make board and shuffle
	char board[dim][dim];
	generate_board(vacancy,endline_percent,dim,board);
	int spots = dim*dim;
  	int people = spots -(float) ((float)(spots)/100)*vacancy;
	//if print_mode true, run PRINT MODE  
	if(print_mode == 1){
		for(int c =0;c!=cycles+1;c++){
			print_board(dim,board);
			int m = 0;
			m = cycle(dim,board,pref_strength);
			double avrg = average_happiness(dim,board,people);
			printf("cycle: %d\n", c);
                	printf("moves this cycle: %d  moves \n", m);
                	printf("teams' happiness: %1.4f\n", avrg);
                	printf("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d\n",dim,pref_strength,vacancy,endline_percent);
                	printf("Use Control-C to quit.\n");

		}
	}	
	
	//otherwise, run INFINITE MODE	
	else{
		int round=0;
		clear();
		while(1){
			int moves = 0;
			round++;
			moves = cycle(dim,board,pref_strength);
			set_cur_pos(1,1);
			for(int row = 0; row<dim; row++){
				for(int col = 0;col<dim;col++){
					put(board[row][col]);
				}
			puts(" ");
			}
			double avrg = average_happiness(dim,board,people);
			printf("cycle: %d\n", round);
	        	printf("moves this cycle: %d  moves \n", moves);
			printf("teams' happiness: %1.4f\n", avrg);
			printf("dim: %d, %%strength of preference:  %d%%, %%vacancy:  %d%%, %%end:  %d\n",dim,pref_strength,vacancy,endline_percent);
			printf("Use Control-C to quit.");		
			usleep(time);
		}
	}

return EXIT_SUCCESS;
}
