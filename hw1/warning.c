/// file: warning.c
/// description: faulty code example that needs repair.
/// @author RIT CS Dept.

#include <stdio.h>

#define SIZE 1               ///< size of the array

/// compute first calculates the year representing the current millenium
/// using the century parameter as a factor. Next, compute uses the
/// millenium value to calculate the year of the last presidential election.
/// @param century integer number of the current century AD
/// @return year of the last presidential election

int compute( int century ) {
    int b = century * 4;
	int mill = 100 * century;
	int year = mill - b;
        
    return year;
}

/// main computes and prints the year of the next presidential election.
/// The function should have no parameters and uses compute for its job.
/// @return 0 to tell the OS that the process ran to a success conclusion

int main( ) {
   
    int y = compute( 21 );

    printf( "%d\n",y+4);

    if ( y > 1000 ){
    return 1;}
    else{
	    return 0;
    }
}

