#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <limits.h>

void
print_help()
{
	printf( "Usage:\n" );
    printf( "\ttp0 -h\n" );
    printf( "\ttp0 -V\n" );
    printf( "\ttp0 [options] file\n" );
    printf( "Options:\n" );
    printf( "\t-V, --version\tPrint version and quit.\n" );
    printf( "\t-h, --help\tPrint this information.\n" );
	printf( "\t-l, --words\tPrint number of lines in file.\n" );
	printf( "\t-w, --words\tPrint number of words in file.\n" );
	printf( "\t-c, --words\tPrint number of characters in file.\n" );
	printf( "\t-i, --input\tPath to input file.\n" );
    printf( "Examples:\n" );
    printf( "\ttp0 -w -i input.txt\n\n" );
	exit( 0 );
}

void print_version()
{
	printf( "tp0 1.0\n" );
    printf( "Copyright © 2017 FIUBA.\n" );
	printf( "This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.\n" );
	printf( "Written by Eirik Harald Lund\n\n" );
	exit( 0 );
}

void
count ( FILE* fp, int line, int word, int character )
{
	int nl; // counter for lines
	nl = 0;
	int nw; // counter for words
	nw = 0;
	int nc; // counter for characters
	nc = 0;
    
	int c; // Working byte/character
	int co; // Previous character
	co = -1; // To avoid using unassigned variable

	c = fgetc( fp );
	while ( ! feof ( fp ) )
	{		
		if ( '\n' == c )
			++nl;
		if ( !isspace( co ) && isspace( c ) )
			++nw;
		++nc;
		
		co = c;
		c = fgetc( fp );
	}

	if ( line ) printf( " %i", nl );
	if ( word ) printf( " %i", nw );
	if ( character ) printf( " %i", nc );
}

int
main ( int argc, char *argv[] )
{
	FILE *fp;
	fp = NULL;
	char *file;
	
	// Values for determining whether to print number of lines, words and characters
	int l = 0, w = 0, c = 0;
	
	static struct option long_options[] = {
        {"version", no_argument, 0, 'V'},
        {"help", no_argument, 0, 'h'},
		{"words", no_argument, 0, 'x'},
		{NULL, 0, NULL, 0}
	};
	int opt;
	int option_index;
	option_index = 0;
	while ((opt = getopt_long (argc, argv, "Vhlwci:", long_options, &option_index )) != -1)
	{
		switch (opt)
		{
		case 'V':
			print_version();
			break;
		case 'h':
			print_help();
			break;
		case 'l':
			l = 1;
			break;
		case 'w':
			w = 1;
			break;
		case 'c':
			c = 1;
			break;
		case 'x':
			l = 1;
			w = 1;
			c = 1;
			break;
		case 'i':
			fp = fopen( optarg, "r" );
			if ( NULL == fp )
			{
				printf( "Invalid file name\nAborting\n" );
				return EXIT_FAILURE;
			}
			file = optarg;
			break;
		}
	}
	
	if ( NULL == fp )
		fp = stdin;
	
	count( fp, l, w, c );
	fclose( fp );
	if ( stdin == fp ) printf( "\n" ); // Can't print a non-existant file name
	else printf( " %s\n", file );

	return EXIT_SUCCESS;
}
