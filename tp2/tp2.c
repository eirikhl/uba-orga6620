#include <stdio.h>
#include <stdlib.h>


unsigned int instructions;
unsigned int misses;
unsigned int miss_rate;

typedef struct {
	unsigned char value;
	int index; // Address
	int tag;
	int offset;
} Line; // For memory

typedef struct {
	unsigned char value;
	int offset;
	int tag;
	int lru;
	int dirty;
	int valid;
} Block; // For cache

Line mem[128]; // 4096B/32B
Block cache[16][2]; // 2 ways => 512B*2 => 16 Blocks of 32B
// Necesita un malloc o calloc???


void init()
{
	instructions = 0;
	misses = 0;
	miss_rate = 0;
	
	for ( int i = 0; i < 16; ++i )
	{
		for( int j = 0; j < 2; ++j )
		{
			// Seguro que hay errores
			Block temp;
			temp.value = 0;
			temp.offset = 0;
			temp.tag = j; // ???
			temp.lru = j; // To make a first decision
			temp.dirty = 0;
			temp.valid = 0;
			
			cache[i][j] = temp;
		}
	}

	for ( int i = 0; i < 128; ++i )
	{
		Line temp;
		temp.value= i;
		temp.index = 32*i;
		temp.tag = i%16; // Distribute between the 16 blocks of each way
		temp.offset = i;

		mem[i] = temp;
	}
}


unsigned char read_byte( int address )
{
	int loc;
	loc = address/32;
	
	int pos;
	pos = mem[loc].tag;
	int way;

	int present = 1;
	
	if ( cache[pos][0].offset == mem[loc].offset ) way = 0; 
	else if ( cache[pos][1].offset == mem[loc].offset ) way = 1;
	else
	{
		present = 0;
		way = ( cache[pos][0].lru ) ? 1 : 0; // If way 0 is LRU, use 0
	}
	
	// Used now => is the LRU
	cache[pos][way].lru = 0;
	cache[pos][1-way].lru = 1;

	if ( ( cache[pos][way].valid ) && ( ! cache[pos][way].dirty ) )
	{
		puts("valid and clean");
		return cache[pos][way].value;
	}

	if ( ! cache[pos][way].valid )
	{
		puts("invalid");
		cache[pos][way].value = mem[loc].value;
		cache[pos][way].offset = mem[loc].offset;
		
		cache[pos][way].valid = 1;
		cache[pos][way].dirty = 0;
				
		return -1;
	}

	// Writeback
	puts("dirty");
	
	mem[ cache[pos][way].offset * 32 ].value = cache[pos][way].value;
	cache[pos][way].value = mem[loc].value;
	cache[pos][way].offset = mem[loc].offset;
	
	cache[pos][way].valid = 1;
	cache[pos][way].dirty = 0;
	return -1;
}


unsigned int write_byte( int address, unsigned char value )
{
	int loc;
	loc = address/32;
	mem[loc].value = value; // The value should be written to mem no matter what
	
	int pos;
	pos = mem[loc].tag;
	int way;
	/* way = ( cache[pos][0].lru ) ? 1 : 0; // If way 0 is LRU, use 0 */
	if ( cache[pos][0].offset == mem[loc].offset ) way = 0; 
	else if ( cache[pos][1].offset == mem[loc].offset ) way = 1;
	else return -1;

	// Used now => is the LRU
	cache[pos][way].lru = 0;
	cache[pos][1-way].lru = 1;
	
	cache[pos][way].value = value;
	cache[pos][way].valid = 1;

	puts("written");
    return 0;
}


unsigned int get_miss_rate()
{
	return misses/instructions;
}


int main( int argc, char *argv[] )
{
	FILE *fp;

	if ( 2 != argc )
	{
		printf( "Invalid amount of arguments\n" );
		exit( EXIT_FAILURE );
	}
	
	fp = fopen( argv[1], "r" );
	
	init();
	printf("%d\n", write_byte(96, 11));
	printf("%u\n", read_byte(96));
	
	printf("%d\n", write_byte(96, 69));
	printf("%u\n", read_byte(96));
	
	printf("%u\n", read_byte(3072));

	char * line = NULL;
    size_t len = 0;
    ssize_t read;

    /* fp = fopen("/etc/motd", "r"); */
    if ( fp == NULL )
	{
		printf( "The file does not exist\n" );
		exit( EXIT_FAILURE );
	}

	char cmd;
	int addr;
	int val;
	char temp[12];
	char *ptr;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf( "%s", line );
    }

    fclose( fp );

	if (line)
        free(line);
    	
	exit( EXIT_SUCCESS );
}
