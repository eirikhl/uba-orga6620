#include <stdio.h>
#include <stdlib.h>


unsigned int miss_rate;

typedef struct {
	unsigned char value;
	int tag;
	int dirty;
} Block;


Block cache[16][2]; // 2 ways => 512B*2 => 16 Blocks of 32B
// Necesita un malloc o calloc???

void init()
{
	miss_rate = 0;
	for( int i = 0; i < 16; ++i )
	{
		for( int j = 0; j < 2; ++j )
		{
			// Seguro que hay errores
			Block temp;
			temp.value = 0;
			temp.tag = j; // ???
			temp.dirty = 0;
			cache[i][j] = temp;
		}
	}
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
