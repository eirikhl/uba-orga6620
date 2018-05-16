#include <stdio.h>
#include <stdlib.h>


unsigned int miss_rate;

typedef struct {
	unsigned char V;
	int index; // Address
	int tag;
	int offset;
} Line; // For memory

typedef struct {
	unsigned char V;
	int tag;
	int dirty;
} Block; // For cache

Line mem[128]; // 4096B/32B
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
			temp.V = 0;
			temp.tag = j; // ???
			temp.dirty = 1;
			cache[i][j] = temp;
		}
	}

	for( int i = 0; i < 128; ++i )
	{
		Line temp;
		temp.V = i;
		temp.index = 32*i;
		temp.tag = i%16; // Distribute between the 16 blocks of each way
		temp.offset = 0; // ???
		mem[i] = temp;
	}
}


unsigned char read_byte( int address )
{
	
	return mem[address/32].V;
}


int write_byte( int address, unsigned char value )
{
	return -1;
}


unsigned int get_miss_rate()
{
	return miss_rate;
}


int main( int argc, char *argv[] )
{
	FILE *fp;

	if ( 2 != argc )
	{
		printf( "Invalid amount of arguments\n" );
		return EXIT_FAILURE;
	}
	fp = fopen( argv[1], "r" );
	if ( NULL == fp )
	{
		printf( "The file does not exist\n" );
		return EXIT_FAILURE;
	}
	
	init();
	printf("%u\n", read_byte(32));
	printf("%u\n", read_byte(3072));

	
	fclose( fp );
	return EXIT_SUCCESS;
}
