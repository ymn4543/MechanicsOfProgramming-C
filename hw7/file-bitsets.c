// file: file-bitsets.c
// author: Youssef Naguib <ymn4543@rit.edu>
// description: cs243 homework_7 implementation
////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // uint64_t type
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>

//the maximum number of elements in a set
const size_t SETSIZE = sizeof( uint64_t ) << 3 ;
//read up to BUFSIZE bytes at a time.
const size_t BUFSIZE = 256;

/** 
 * Helper function to find the index of a char in a string.
 * param string: a string that contains a char being looked for
 * param c: char being looked for in string
 */
int find_index(char* string, char c){
        int l = strlen(string);
        int x = 0;
        while(x!=l){
                if (string[x] == c){
                        return x;
                }
                else{
                        x++;
                }
        }
        return 64; //if the char isn't in string, return 64
}

/**
 * file_set_encode reads all characters in a file and creates a bit set of type
 * uint64_t.
 * param fp: the file being read.
 */
uint64_t file_set_encode( FILE * fp ){
	char* bit = "6666555555555544444444443333333333222222222211111111110000000000";
        char* pos = "3210987654321098765432109876543210987654321098765432109876543210";
        char* chr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,0123456789";
	uint64_t result = 0;
	char letter[1];
	while(fscanf(fp, "%c", &letter[0])!=EOF){
		int index = find_index(chr,letter[0]);	
		if(index==64){
			continue;
		}
		else{
			uint64_t mask = 0;
                        char b = bit[index];
                        char p = pos[index];
                        char* new = malloc(sizeof(char)*2);
                        new[0] = b;
                        new[1] = p;
                        int shifter = atoi(new);
                        mask = 1L << shifter;
                        result = result | mask;
			free(new);
		}
	}
	return result;
}

/**
 * set_encode converts a string into a bit set of type uint64_t.
 * param st: string to be converted.
 */
uint64_t set_encode( char * st ){
	char* bit = "6666555555555544444444443333333333222222222211111111110000000000";
	char* pos = "3210987654321098765432109876543210987654321098765432109876543210";
	char* chr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,0123456789";
	int l = strlen(st);
	uint64_t result = 0;
	int x = 0;
	while(x!=l){
		int index = find_index(chr,st[x]);
		if(index==64){
			x++;
		}
		else{
			uint64_t mask = 0;
			char b = bit[index];
			char p = pos[index];
			char* new = malloc(sizeof(char)*2);
			new[0] = b;
			new[1] = p;
			int shifter = atoi(new);
			mask = 1L << shifter;
			result = result | mask;
			x++;
			free(new);
		}
	}
	return result;

}

/**
 * set_intersect takes two bit sets and returns their intersection set.
 * param set1: first set.
 * param set2: second set.
 */
uint64_t set_intersect( uint64_t set1, uint64_t set2 ){
	uint64_t result = set1 & set2;
	return result;
}

/**
 * set_union takes two bit sets and returns their union set.
 * param set1: first set.
 * param set2: second set.
 */
uint64_t set_union( uint64_t set1, uint64_t set2 ){
	uint64_t result = set1 | set2;
	return result;

}

/**
 * set_complement takes a bit set and returns it's complement.
 * param set1: set being complemented.
 */
uint64_t set_complement( uint64_t set1 ){
	uint64_t result = ~set1;
	return result;
}

/**
 * set_difference takes two bit sets and returns their difference.
 * param set1: first set.
 * param set2: second set.
 */
uint64_t set_difference( uint64_t set1, uint64_t set2 ){
	uint64_t result = set1 & ~set2;
	return result;

}

/**
 * set_symdifference takes two bit sets and returns their symetric difference.
 * param set1: first set.
 * param set2: second set.
 */
uint64_t set_symdifference( uint64_t set1, uint64_t set2 ){
	uint64_t uni = set_union(set1,set2);
	uint64_t intersect = set_intersect(set1,set2);
	uint64_t result = set_difference(uni,intersect);
	return result;
}

/**
 * set_cardinality returns the cardinality of a bit set.
 * param set: set who's cardinality will be returned.
 */
size_t set_cardinality( uint64_t set ){
	char* chr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,0123456789";
	char* bit = "6666555555555544444444443333333333222222222211111111110000000000";
        char* pos = "3210987654321098765432109876543210987654321098765432109876543210";
	int x = 0;
	uint64_t temp;
	int counter = 0;
	while(x<64){
		temp = 0;
		char c = chr[x];
		char* new = malloc(sizeof(char)*2);
                new[0] = bit[x];
                new[1] = pos[x];
		temp = 1L << atoi(new);
		if(set & temp){
			counter++;
		}
		x++;
		free(new);
	}	
	return counter;
}

/**
 * set_members takes a bit set and returns a string containing the characters
 * that are members of that bit set..
 * param set: set who's members will be put into a string and returned.
 */
char * set_members( uint64_t set ){
	char *string = malloc(sizeof(char)*BUFSIZE);
	char* chr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,0123456789";
        char* bit = "6666555555555544444444443333333333222222222211111111110000000000";
        char* pos = "3210987654321098765432109876543210987654321098765432109876543210";
        int x = 0;
	int index = 0;
        uint64_t temp;
        while(x<64){
                temp = 0;
                char c = chr[x];
                char* new = malloc(sizeof(char)*2);
                new[0] = bit[x];
                new[1] = pos[x];
                temp = 1L << atoi(new);
                if(set & temp){
                        string[index] = c;
			index++;
                }
                x++;
		free(new);
        }
	string[index] = '\0';
	return string;
}


/**
 * - main function.
 * - takes in two arguments, can be strings or filenames.
 * - returns an error if file can't be opened o if there are less than two or
 *   more than two command line arguments.
 * - both strings are encoded into bit sets.
 * - program outputs: the sets, their intersection, their union,
 *   			their complements, their difference and symetric
 *   			difference, cardinalities, and set members.
 * - program terminates.
 */
int main(int argc, char *argv[]){
	 uint64_t string1, string2;
	if(argc>3||argc==1){
		printf("Usage: ./file-bitsets string1 string2\n");
	}
	else{
		int file1 = access(argv[1],F_OK);
		int file2 = access(argv[2],F_OK);
		if(file1==0){
			int readable = access(argv[1],R_OK);
			if(readable == 1){
				perror("file unreadable\n");
				return EXIT_FAILURE;	
			}
			printf("string 1:\t\t%s\tEncoding the file:\t%s\n",argv[1],argv[1]);
			FILE* file = fopen(argv[1],"r");
	//		string1 = file_set_encode(file);
		}
		else{
			printf("string 1:\t\t%s\tEncoding the string:\t%s\n",argv[1],argv[1]);	
			string1 = set_encode(argv[1]);
		}


		if(file2==0){
			int readable = access(argv[2],R_OK);
                        if(readable == 1){
                                perror("file unreadable\n");
                                return EXIT_FAILURE;
                        }
			printf("string 2:\t\t%s\tEncoding the file:\t%s\n",argv[2],argv[2]);
			FILE* file = fopen(argv[2],"r");
         //               string2 = file_set_encode(file);
		}

		else{
			printf("string 2:\t\t%s\tEncoding the string:\t%s\n",argv[2],argv[2]);
			string2 = set_encode(argv[2]);
		}
		
	}
	//print sets
	printf("\nset1:\t%#018lx\n",string1);
	printf("set2:\t%#018lx\n",string2);

	//print set intersection
	uint64_t intersection = set_intersect(string1,string2);
	printf("\nset_intersect:\t%#018lx\n",intersection);

	//print set union
	uint64_t uni = set_union(string1,string2);
	printf("set_union:\t%#018lx\n",uni);

	//print compliments
	uint64_t comp1 = set_complement(string1);
	uint64_t comp2 = set_complement(string2);	
	printf("\nset1 set_compliment:\t%#018lx\n",comp1);
	printf("set2 set_compliment:\t%#018lx\n",comp2);
	
	//print difference and symetric difference
	uint64_t diff = set_difference(string1,string2);
	uint64_t symdiff = set_symdifference(string1,string2);
	printf("\nset_difference:\t\t%#018lx\n",diff);
	printf("set_symdifference:\t%#018lx\n",symdiff);

	//print cardinalities
	int card1 =  set_cardinality(string1);
	int card2 =  set_cardinality(string2);
	printf("\nset1 set_cardinality:\t%d\n",card1);
	printf("set2 set_cardinality:\t%d\n",card2);

	//print members of sets
	char* members1 = set_members(string1);
	char* members2 = set_members(string2);
	printf("\nmembers of set1:\t'%s'\n",members1);
	printf("members of set2:\t'%s'\n",members2);
	free(members1);
	free(members2);

	return 0;
}
