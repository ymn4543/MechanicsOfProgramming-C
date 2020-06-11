// File: hist.c 
// Description: Source file for CS243 HW2 Implementation
// @author Youssef Naguib <ymn4543@rit.edu> 
// Section: 5
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hist.h"

/// Reads text and stores count of alphabetical characters, while
// updating individual character counts in the array
int read_text(int array[]){
	int charSum = 0;
	int ch = getchar();
	while(ch!=EOF){
		if (!(ch >= 'a' && ch <= 'z')&&!(ch >= 'A' && ch <= 'Z')) {
		ch = getchar();	
		}
		else{
		charSum+=1;
	
		if (ch >= 'a' && ch <= 'z') {
			ch = toupper(ch);
		}
		int ord = ch - 65;
		int val = array[ord];
		val++;
		array[ord] = val;
		ch = getchar();
	}
	}
	return charSum;
}
/// takes the data from the array and displays a histogram to user,
// also outputing the total alphabetical  character count
void display_text(int array[]){
	int maxval = 0;
	for(int i=0;i<HIST_SIZE;i++){
		if(array[i]>maxval){
			maxval=array[i];
		}
	}
	for(int r=0;r<maxval;r++){
		for(int a = 0;a<HIST_SIZE;a++){
			if(array[a]>=maxval-r){
				printf("%c", 'X');
				}	
			else{
				printf("%c", ' ');
				}
		}
		printf("\n");
	}	

for(int l=0;l<26;l++){
	printf("%c", '-');
}
printf("\n");
printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
}

//main function creates empty array for counts,
//calls read_text and display_text on the standard input.
//Handles cases of zero input.
int main( void  ) {
	int array[HIST_SIZE]= {0}; ;
        int x = read_text(array);
	if(x==0){
	printf("no alphabetic characters read\n");	
	}	
	else{
		printf("%d",x);
		printf(" alphabetic characters read\n");
		display_text(array);
    }
   
    return EXIT_SUCCESS ;
}

// end
