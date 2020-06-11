
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#define MAX_NAME_LEN 9


char *underscore(char* name){
	int x = strlen(name);
        char *str = (char*)malloc(MAX_NAME_LEN);
	int rem = MAX_NAME_LEN - x;
	if(rem%2 ==0){
		int before = rem/2;
	}
	else{
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
	return str;
}



int main(int argc, char* argv[]){
	char* n1;
	char* n2;
	char* n3;
	n1 = underscore(argv[1]);
	n2 = underscore(argv[2]); 
	n3 = underscore(argv[3]);
	printf("1: %s\n",n1);
	printf("2: %s\n",n2);
	printf("3: %s\n",n3);


}
