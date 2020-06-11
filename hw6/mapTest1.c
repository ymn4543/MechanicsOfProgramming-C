///
/// Description:  test driver for the MapADT module
///
/// This test program creates three maps (one using int keys, 
/// one using unsigned int keys, and one using C String keys),
/// inserts a number of long values into each map, and then
/// removes and prints them.
///
/// @author ckd 
/// @author wrc
///

// need setvbuf() declaration
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "mapADT.h"

///
/// Sequence of test values to be inserted and removed
///
long int testData[] = { 42, 17, -12, 9982, 476, 2912, -22, 3291213, 7782 };
int numData = sizeof(testData) / sizeof(long int);

///
/// Comparison function for integer keys
///
/// @param a first value to compare
/// @param b second value to compare
/// @return integer indicating the relationship between a and b
///
int compare_int( const void *a, const void *b ) {
    int na = *(int*)a;
    int nb = *(int*)b;

    return( na - nb );
}

///
/// Comparison function for unsigned integer keys
///
/// @param a first value to compare
/// @param b second value to compare
/// @return integer indicating the relationship between a and b
///
int compare_uint( const void *a, const void *b ) {
    unsigned int na = *(unsigned int*)a;
    unsigned int nb = *(unsigned int*)b;

    return( na < nb ? -1 : (na == nb ? 0 : 1) );
}

///
/// Comparison function for C string keys
///
/// @param a first value to compare
/// @param b second value to compare
/// @return integer indicating the relationship between a and b
///
int compare_str( const void *a, const void *b ) {
    char *key1, *key2;
    
    key1 = (char*)a;
    key2 = (char*)b;

    return( strcmp(key1, key2) );
}

///
/// Process insertions/removals using a specific map
///
/// @param map the MapADT to use for the tests
///
void process_int( MapADT map) {
    int i;
    int *key;
    long int *value;
    int testKey;

    // load data into the Map

    fputs( "Inserting: ", stdout );
    for( i = 0; i < numData; ++i ) {
        key = (int*)malloc(sizeof(int));
        assert( NULL != key );
        *key = i;
        value = (long int*)malloc(sizeof(long int));
        assert( NULL != value );
        *value = testData[i];
        printf( "[%d, %ld] ", *key, *value );
        map_put( map, (void*)key, (void *)value );
    }

    // begin the tests

    fputs( "\nTesting contents:", stdout );
    testKey = 4;
        printf( "\n   Contains 4: %s",
            map_contains( map, (void*)&testKey ) ? "true" : "false");
    testKey = 22;
    printf( "\n   Contains 22: %s",
            map_contains( map, (void*)&testKey ) ? "true" : "false");
    testKey = 1000000;
    printf( "\n   Contains 1000000: %s",
            map_contains( map, (void*)&testKey ) ? "true" : "false");

    fputs( "\nGetting:  ", stdout );
    for( i = numData-1; i >= 0; --i ) {
        value = (long int*) map_get( map, (void*)&i );
        assert( NULL != value );
        printf( " %ld", *value );
    }

    fputs( "\nRemoving:  ", stdout );
    for( i = numData-1; i >= 0; --i ) {
        value = (long int*) map_delete( map, (void*)&i );
        printf( " %ld", *value );
        free(value);
    }
    putchar( '\n' );
}


///
/// Process insertions/removals using a specific map
///
/// @param map the MapADT to use for the tests
///
void process_uint( MapADT map) {
    int i;
    unsigned int *key;
    long int *value;
    unsigned int testKey;

    // load data into the map

    fputs( "Inserting: ", stdout );
    for( i = 0; i < numData; ++i ) {
        key = (unsigned int*)malloc(sizeof(int));
        assert( NULL != key );
        *key = i*1000;
        value = (long int*)malloc(sizeof(long int));
        assert( NULL != value );
        *value = testData[i];
        printf( "[%d, %ld] ", *key, *value );
        map_put( map, (void*)key, (void *)value );
    }

    // begin testing

    fputs( "\nTesting contents:", stdout );
    testKey = 4000;
        printf( "\n   Contains %u: %s", testKey,
            map_contains( map, (void*)&testKey ) ? "true" : "false");
    testKey = 22000;
    printf( "\n   Contains %u: %s", testKey,
            map_contains( map, (void*)&testKey ) ? "true" : "false");
    testKey = 1000000;
    printf( "\n   Contains %u: %s", testKey,
            map_contains( map, (void*)&testKey ) ? "true" : "false");

    fputs( "\nGetting:  ", stdout );
    for( i = numData-1; i >= 0; --i ) {
        testKey = i*1000;
        value = (long int*) map_get( map, (void*)&testKey );
        assert( NULL != value );
        printf( " %ld", *value );
    }

    fputs( "\nRemoving:  ", stdout );
    for( i = numData-1; i >= 0; --i ) {
        testKey = i*1000;
        value = (long int*) map_delete( map, (void*)&testKey );
        printf( " %ld", *value );
        free(value);
    }
    putchar( '\n' );
}

///
/// Process insertions/removals using a specific map
///
/// @param map the MapADT to use for the tests
///
void process_string( MapADT map) {
    int i;
    char *key;
    long int *value;
    char testKey[20];
        char *keys[] = {"apple", "banana", "cat", "dog", "red", "blue",
           "green", "water", "table"};

    // load data into the map

    fputs( "Inserting: ", stdout );
    for( i = 0; i < numData; ++i ) {
        key = (char*)malloc(strlen(keys[i])+1);
        assert( NULL != key );
        strncpy( key, keys[i], strlen(keys[i])+1);    
        value = (long int*)malloc(sizeof(long int));
        assert( NULL != value );
        *value = testData[i];
        printf( "[%s, %ld] ", key, *value );
        map_put( map, (void*)key, (void *)value );
    }

    // begin the tests

    fputs( "\nTesting contents:", stdout );
    strncpy(testKey, "apple", sizeof(testKey));
        printf( "\n   Contains %s: %s", testKey,
            map_contains( map, (void*)testKey ) ? "true" : "false");
    strncpy(testKey, "dog", sizeof(testKey));
    printf( "\n   Contains %s: %s", testKey,
            map_contains( map, (void*)testKey ) ? "true" : "false");
    strncpy(testKey, "cow", sizeof(testKey));
    printf( "\n   Contains %s: %s", testKey,
            map_contains( map, (void*)testKey ) ? "true" : "false");

    fputs( "\nGetting:  ", stdout );
    for( i = numData-1; i >= 0; --i ) {
        strncpy(testKey, keys[i], sizeof(testKey));
        value = (long int*) map_get( map, (void*)testKey );
        assert( NULL != value );
        printf( " %ld", *value );
    }

    fputs( "\nRemoving:  ", stdout );
    for( i = numData-1; i >= 0; --i ) {
        strncpy(testKey, keys[i], sizeof(testKey));
        value = (long int*) map_delete( map, (void*)testKey );
        printf( " %ld", *value );
        free(value);
    }
    putchar( '\n' );
}

///
/// main routine - initiate all the tests
///
int main( void ) {
    MapADT keyInt, keyUint, keyStr;

    //
    // to aid in debugging, we reset stdout to be line buffered
    // so that we don't lose any output if an assertion fails
    // even if stdout is redirected into a file
    //
    setvbuf( stdout, NULL, _IOLBF, BUFSIZ );

    keyInt = map_create( compare_int );
    if( keyInt == NULL ) {
        fputs( "Cannot create map with int keys\n", stderr );
        exit( EXIT_FAILURE );
    }

    puts( "\nTesting the [int, long int] map" );
    process_int( keyInt );
    map_destroy( keyInt );

    keyUint = map_create( compare_uint );
    if( keyUint == NULL ) {
        fputs( "Cannot create map with unsigned int keys\n", stderr );
        exit( EXIT_FAILURE );
    }
    puts( "\nTesting the [unsigned int, long int] map" );
    process_uint( keyUint );
    map_destroy( keyUint );

    keyStr = map_create( compare_str );
    if( keyStr == NULL ) {
        fputs( "Cannot create map with C string keys\n", stderr );
        exit( EXIT_FAILURE );
    }
    puts( "\nTesting the [C string, long int] map" );
    process_string( keyStr );
    map_destroy( keyStr );


    return 0;
}
