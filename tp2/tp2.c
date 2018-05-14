#include <stdio.h>
#include <stdlib.h>


unsigned int miss_rate;

typedef struct {
	unsigned char value;
	int tag;
	int dirty;
} Block;


void init()
{
	miss_rate = 0;
}


unsigned char read_byte( int address )
{
	
}


int write_byte( int address, unsigned char value )
{
	return -1;
}


unsigned int get_miss_rate()
{

}


int main( int argc, char *argv[] )
{
	FILE *fp;

	if ( 2 != argc )
	{
		printf( "Invalid amount of arguments\n" );
		return EXIT_FAILURE;
	}
	fp = fopen( argv[1] );
	if ( NULL == fp )
	{
		printf( "The file does not exist\n" );
		return EXIT_FAILURE;
	}
	
	init();

	fclose( fp );
	return EXIT_SUCCESS;
}
