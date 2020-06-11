// 
// File: good-life.c
// Description: source file for Conway's game of life, CS243 hw3 implementation
// 
// @author Youssef Naguib <ymn4543@rit.edu>
// @author RIT CS Department
// 
// version control: git
// // // // // // // // // // // // // // // // // // // // // // // //

/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own, and function headers belong at the left margin.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 19 	//refactoring to remove magic numbers
#define WIDTH 20 	// refactoring to remove magic numbers
#define ROUNDS 100 	// refactoring to remove magic numbers



/// Header function for program
/// welcomes player to game by outputing a message
void header(void) /*function for program header*/ {
	  printf("\n\t..Welcome to the Game of life..\n");
}
	
/// CountNeighbors is a function that refactors repeated code
/// by allowing multiple functions to use it.
/// This function counts the number of neighbors of a certain 
/// cell in a matrix.
/// @param int y: square dimension of matrix
/// @param char life[y][y]: matrix being passed
/// @param int row,col: represent row and column of cell in matrix
/// @return an integer representing the number of live neighbors a cell has
int CountNeighbors(int y, char life[y][y],int row, int col){
        int neighbors = 0;
        if(life[row - 1%y][col - 1%y] == '*')
                neighbors++;
        if(life[row - 1%y][col%y] == '*')
                neighbors++;
        if(life[row - 1%y][col + 1%y] == '*')
                neighbors++;
        if(life[row%y][col - 1%y] == '*')
                neighbors++;
        if(life[row%y][col + 1%y] == '*')
                neighbors++;
        if(life[row + 1%y][col - 1%y] == '*')
                neighbors++;
        if(life[row + 1%y][col%y] == '*')
                neighbors++;
        if(life[row + 1%y][col + 1%y] == '*')
                neighbors++;
      
        return neighbors;
}


/// survivalRule function iterates through each cell and determines if it
/// should survive the next generation
/// @param life: matrix of cells
void survivalRule(int x, char life[x][x]){		//fix 5 unused param, refactored matrix-passing
	int row, col;
	int neighbors;
	for(row = 1; row<SIZE; row++){
		for(col = 1; col<SIZE; col++){
		        neighbors = CountNeighbors(x,life,row,col);
			if(life[row][col]== '*'){		//fix 4 string comparison
				if(neighbors == 2 || neighbors == 3){
					life[row][col] = '*';			//fix 3 (no effect)
			   	}	
			}
		}
	}
}

/// birthRule function iterates through each cell and determines if it
/// should be born next generation
/// @param life: matrix of cells
void birthRule(int x, char life[x][x]){ 		//fix 5 unused param, refactored matrix passing
	int row, col;
	int neighbors;
	for(row = 1; row<SIZE; row++){
		for(col = 1; col<SIZE; col++){
			 neighbors = CountNeighbors(x,life,row,col);
				if(life[row][col]== '*'){   
			   		if(neighbors == 3){
			   			life[row][col] = '*'; 			//fix 3 (no effect)
			        }
			}
		}
	}
       
}

/// PlayGeneration is a function that merges survivalRule and birthRule 
/// functions in a manner of refactoring. It follow's the four rules of
/// Conway's game of life, and updates the matrix for the next generation.
/// @param int x: the width of the square matrix
/// @param char life[x][x]: the matrix being passed represents the gen.
void PlayGeneration(int x, char life[x][x]){
	int row, col;
        char life2[x][x];
	for(row = 0; row<WIDTH; row++){
                for(col = 0; col<WIDTH; col++){
                      life2[row][col] = ' ';         
                }
        }
        for(row = 0; row<SIZE; row++){
                for(col = 0; col<SIZE; col++){
                	int neighbors = CountNeighbors(x,life,row,col);                      
		        if(life[row][col]== '*'){ 
				if(neighbors<=1){
					life2[row][col] = ' ';
				}
                                if(neighbors == 2 || neighbors == 3){
					life2[row][col] = '*'; 
				}
				if(neighbors >= 4){
					life2[row][col] = ' ';
				}
                        }
			if(life[row][col] == ' '){
				if(neighbors == 3){
					life2[row][col] = '*';
				}
			}
        	}
	}
	for(row = 0; row<WIDTH; row++){
                        for(col = 0; col<WIDTH; col++){
				life[row][col] = life2[row][col];
                        }

	}
}

	
/// Main function for program
/// Asks player for number of initial organisms and simulates
/// Conway's game of life for 100 generations. 
int main(void){
	char life[WIDTH][WIDTH];
	int orgs;			//fix 5 unused param
	int i, row, col; 		//fix 5 unused param
	int count = 1;
	  			 	//fix 5 unused param
	  		 		//fix 5 unused param
	                 		//fix 5 unused param   	
	header();
	printf("\nPlease enter the initial number of organisms: ");
	scanf("%i", &orgs);
	srand( 31 );
	printf("\n");
	for(i = 0; i<orgs; i++){
		row = rand();
		row %= WIDTH;
		col = rand();
		col %= WIDTH;
		life[row][col] = '*'; 		//fix 2
	}

	for(row = 0; row<WIDTH; row++){
		for(col = 0; col<WIDTH; col++){
			if(life[row][col] != '*')
				life[row][col] = ' ';		 //fix 2
		}
	}
			  
	for(row = 0; row<WIDTH; row++){
		for(col = 0; col<WIDTH; col++){
			printf("%c", life[row][col]); 		//fix 1
		}
		puts(" ");	
	}
	printf("\ninitial generation (generation 0): \n\n" );
	while (count<ROUNDS) {  		//fix 6 infinite loop
		//birthRule(WIDTH,life);		//fix 5 unused param, refactored matrix passing
		//survivalRule(WIDTH,life);		//fix 5 unused param, refactored matrix passing
		PlayGeneration(WIDTH,life);		// refactored Rule functions, combined them
		for(row = 0; row<WIDTH; row++){
			for(col = 0; col<WIDTH; col++){
				printf("%c", life[row][col]);		 //fix 1
			}
		puts(" ");
		}
		printf("generation: %d\n\n", count);
		count++;		//fix 6 infinite loop
	}

	return 0;
}
			
