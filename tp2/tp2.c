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


Line mem[4096];
Block cache[512][2];


void init()
{
	instructions = 0;
	misses = 0;
	miss_rate = 0;
	
	for ( int i = 0; i < 512; ++i )
	{
		for( int j = 0; j < 2; ++j )
		{
			Block temp;
			temp.value = -1;
			temp.offset = 0; // Where in cache block to place data
			
			temp.tag = 0; // To compare with memory index
			temp.lru = j; // To make a first decision
			
			temp.dirty = 0;
			temp.valid = 0;
			
			cache[i][j] = temp;
		}
	}

	for ( int i = 0; i < 4096; ++i )
	{
		Line temp;
		temp.value = -1;
		temp.address = i;
		temp.offset = i;
		temp.index = i%16; // Distribute between the 16 blocks of each way

		mem[i] = temp;
	}
}


int read_byte( int address )
{
	int offset;
	offset = address%32;

	int loc;
	loc = address - offset; // Translate for mem array

	int pos;
	pos = (mem[loc].index)*32; // Start position for which cache block should it use

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

	if ( present && (cache[pos][way].valid) )
		return cache[pos+offset][way].value;

	for ( int i = 0; i < 32; ++i )
	{
		cache[pos+i][way].tag = loc;
		cache[pos+i][way].offset = offset;
		cache[pos+offset+i][way].value = mem[loc+i].value;
		cache[pos+i][way].valid = 1;
		cache[pos+i][way].dirty = 0;
	}
	
	return -1;
}


unsigned int write_byte( int address, unsigned char value )
{
	int offset;
	offset = address%32;

	int loc;
	loc = address - offset; // Translate for mem array
	mem[address].value = value; // The value should be written to mem no matter what

	int pos;
	pos = (mem[loc].index)*32; // Which cache block should it use

	int way;
	if ( loc == cache[pos][0].tag ) way = 0;
	else if ( loc == cache[pos][1].tag ) way = 1;
	else
		return -1;

	if ( ! cache[pos][way].valid )
		return -1;
	
	cache[pos][way].tag = loc;
	cache[pos+offset][way].value = value;
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
	
	char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if ( fp == NULL )
	{
		printf( "The file does not exist\n" );
		exit( EXIT_FAILURE );
	}

	char cmd;
	int addr;
	int val;
	char tipe_instruction[3] = "--";
	
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
