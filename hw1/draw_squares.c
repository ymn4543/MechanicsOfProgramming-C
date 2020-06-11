// Author: Youssef Naguib <ymn4543@rit.edu>
// assignment: CS243 HW1 part4
// Description: This program draws ASCII Square art using loops.

#include <stdio.h>
#include <stdlib.h>

//Function: draw_square draws a square using the given parameters
//param: side, the length of the square's side
//param: indent, the number of spaces from the left edge to indent the square
//param: char, the character to use for filling the square
void draw_square(int side, int indent, char ch){
int sidenum;
sidenum = 0;

while(sidenum!=side){
	printf("%*c", indent, ' ');
	for ( int x = 0; x < side; x ++) {
		putchar(ch);
}
//print indent # of spaces followed by side number of ch
sidenum+=1;
printf("\n");
}

// print new line
printf("\n");
}

//Function: Main calls draw_square several times in order to draw different squares.
//returns 0
int main(){
draw_square(3,2,'#');
draw_square(5,4,'*');
draw_square(8,3,'+');
	return 0;
}
