#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int instructions;
unsigned int misses;
float miss_rate;

typedef struct {
	unsigned char value;
	int index; // For finding cache block
	int address;
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


// Change it to use the entire range of numbers
// Then, change read and write to operate on groups of 32 byte
Line mem[128]; // 4096B/32B
Block cache[16][2]; // 2 ways => 512B*2 => 16 Blocks of 32B


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
			temp.offset = 0; // where in cache block to place data
			
			temp.tag = 0; //compare with memory index
			temp.lru = j; // To make a first decision
			
			temp.dirty = 0;
			temp.valid = 0;
			
			cache[i][j] = temp;
		}
	}

	for ( int i = 0; i < 128; ++i )
	{
		Line temp;
		temp.value = 0;
		temp.address = 32*i;
		temp.offset = i;
		temp.index = i%16; // Distribute between the 16 blocks of each way

		mem[i] = temp;
	}
}

int read_byte( int address )
{
	int loc;
	loc = address/32; // translate for mem array

	int offset;
	offset = address%32;

	int pos;
	pos = mem[loc].index; // which cache block should it use

	int way;
	int present;
	present = 1;
	if ( loc == cache[pos][0].tag ) way = 0;
	else if ( loc == cache[pos][1].tag ) way = 1;
	else 
	{
		present = 0;
		way = ( cache[pos][0].lru ) ? 0 : 1; // If way 0 is LRU, use 0
	}
	
	// Used now => the other is the LRU
	cache[pos][way].lru = 0;
	cache[pos][1-way].lru = 1;

	if ( present && (cache[pos][way].valid) && (! cache[pos][way].dirty) )
		return cache[pos][way].value;
	
	if ( ! cache[pos][way].valid )
	{
		cache[pos][way].tag = loc;
		cache[pos][way].offset = offset;
		cache[pos][way].value = mem[loc].value;
		cache[pos][way].valid = 1;
		cache[pos][way].dirty = 0;
	}
	else if ( cache[pos][way].dirty )
	{
		// Write back
		mem[cache[pos][way].tag].value = cache[pos][way].value;

		cache[pos][way].tag = loc;
		cache[pos][way].offset = offset;
		cache[pos][way].value = mem[loc].value;
		cache[pos][way].valid = 1;
		cache[pos][way].dirty = 0;
	}
	
	return -1;
}


unsigned int write_byte( int address, unsigned char value )
{
	int loc;
	loc = address/32; // translate for mem array
	mem[loc].value = value; // The value should be written to mem no matter what

	int offset;
	offset = address%32;

	int pos;
	pos = mem[loc].index; // which cache block should it use

	int way;
	if ( loc == cache[pos][0].tag ) way = 0;
	else if ( loc == cache[pos][1].tag ) way = 1;
	else
	{
		return -1;
	}
	if ( ! cache[pos][way].valid )
		return -1;
	
	cache[pos][way].tag = loc;
	cache[pos][way].value = mem[loc].value;
	cache[pos][way].valid = 1;
	// If it's a different position in memory that's loaded, that makes it dirty for the old
	cache[pos][way].dirty = ( offset == cache[pos][way].offset ) ? 0 : 1;

	cache[pos][way].offset = offset;

	return 0;
}


unsigned int get_miss_rate()
{
	return ((float)misses/(float)instructions)*100;
}

void get_instruction(char *line,char *instruction,int *addr,int *val){
	int x = 0;
	char *token = NULL;
	token = strtok(line, " ");
	if(strcmp(token, "W") == 0){
		instruction[0] = 'W';
		instruction[1] = '\0';
		token = strtok(NULL, ", ");
		*addr = atoi(token);
		token = strtok(NULL, " \n");
		*val = atoi(token);
	}else if(strcmp(token, "R") == 0){
		instruction[0] = 'R';
		instruction[1] = '\0';
		token = strtok(NULL, " \n");
		*addr = atoi(token);
	}else{
		instruction[0] = 'M';
		instruction[1] = 'R';
		instruction[2] = '\0';
	}
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
	/*printf("%d\n", write_byte(96, 11));
	printf("%u\n", read_byte(96));
	
	printf("%d\n", write_byte(96, 69));
	printf("%u\n", read_byte(96));
	
	printf("%u\n", read_byte(3072));
	*/
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
	char tipe_instruction[3] = "--";
	char temp[12];
	char *ptr;
    /*while ((read = getline(&line, &len, fp)) != -1) {
        printf( "%s", line );
    }*/
	getline(&line, &len, fp);
    while (!feof(fp)) {
    	get_instruction(line,tipe_instruction,&addr,&val);

    	if(strcmp(tipe_instruction, "W") == 0){
    		instructions++;
    		if(write_byte(addr,(unsigned char)val) == -1){
    			misses++;
    			printf("miss  \n");
    		}
    		else{
    			printf("0\n");
    		}
    	}else if(strcmp(tipe_instruction, "R") == 0){
    		instructions++;
    		int valor = read_byte( addr );
    		if(valor == -1){
    			misses++;
    			printf("miss  \n");
    		}else{
    			printf("%i\n",valor);
    		}
    	}else if(strcmp(tipe_instruction, "MR") == 0){
    		printf("%i\n", get_miss_rate());
    	}
    	getline(&line, &len, fp);
    }
    fclose( fp );

	if (line)
        free(line);
    	
	exit( EXIT_SUCCESS );
}
