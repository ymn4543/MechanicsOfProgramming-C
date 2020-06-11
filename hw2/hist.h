// 
// File: hist.h 
// A header file for hist.c , Part of the CS243 HW2 Implementation.
// @author Youssef Naguib <ymn4543@rit.edu>
// Section: 5 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef HIST_H
#define HIST_H
#define HIST_SIZE 26  // the size of the character count array

// TODO_ add include files only if needed for the declarations.

/* Reads standard input and keeps track of letter counts
 * @param array: the integer array that stores letter counts
 * @return an int representing the number of alphabetical letters read
 */
int read_text( int array[]);

/*Displays a histogram of the character counts
 *@param array: the integer array that stores the letter counts
 */
void display_histogram( int array[]);

#endif // HIST_H

