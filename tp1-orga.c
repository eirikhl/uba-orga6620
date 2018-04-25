#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define ERROR -1
#define SALIDA_EXITOSA 0
FILE* validacionDeArchivoEntrada(int argc, char *argv[], bool ingresoGuion){
	FILE *auxi = NULL;
	auxi = fopen( argv[argc - 1], "r" );
	if(auxi == NULL){
		fprintf(stderr, "Error archivo Entrada: %s\n", strerror(errno));
		return NULL;
	}
	return auxi;
}
void guardarMatriz(long long *matrix, int cantColumnas, int cantFilas, FILE *fp){
	int i=0;
	int contadorColumna = 0;
	for (i = 0; i < (cantColumnas*cantFilas); i++){
		if(contadorColumna == cantColumnas){
			fprintf( fp, "\n");
			contadorColumna = 0;
		}
		fprintf( fp, "%lli", matrix[i] );
		contadorColumna++;
		if(contadorColumna != cantColumnas){
			fputc( ' ', fp );
		}
	}
	if ( NULL != fp ) fputc( '\n', fp);
	else puts( "\n" );
}
int trasponer(unsigned int filas, unsigned int columnas, long long *entrada, long long *salida){
	int i = 0;
	int contadorMatrixSalida = 0;
	for(i = 0; i < columnas; i++){
		int j = 0;
		for(j = 0; j < filas; j++){
			salida[contadorMatrixSalida] = entrada[j*columnas+i];
			contadorMatrixSalida++;
		}
	}
	return 1;
}

int llenarFila(char *fila,long long *vectorFila,int *cantColumnas,int contadorFilas){
	int contadorColumna = 0;
	char *auxi = malloc((*cantColumnas)*sizeof(char));
	char *eptr;
	int contadorAuxi = 0;
	int contadorFila = 0;
	int tamanioFile = strlen(fila);
	while(contadorFila <= tamanioFile){
		if(fila[contadorFila] == ' ' || contadorFila == tamanioFile){
			auxi[contadorAuxi] = '\0';
			long long numero = strtoll(auxi, &eptr, 10);
			if (*eptr){
			    printf("Error de conversion en fila: %i ,columna: %i\n",contadorFilas,*cantColumnas);
			    return ERROR;
			}
			if(contadorAuxi > 0){
				vectorFila[contadorColumna] = numero;
				contadorColumna++;
				contadorAuxi = 0;
			}
			if(contadorColumna > (*cantColumnas)){
				free(auxi);
				fprintf(stderr, "Error: exceso de columnas en fila %i\n",contadorFilas);
				return ERROR;
			}
		}else{
			auxi[contadorAuxi] = fila[contadorFila];
			contadorAuxi++;
		}
		contadorFila++;
	}
	if(contadorColumna < (*cantColumnas)){
		free(auxi);
		fprintf(stderr, "Error: faltan columnas en fila %i\n",contadorFilas);
		return ERROR;
	}
	free(auxi);
	return SALIDA_EXITOSA;
}

long long *parsearMatriz(FILE *inputFile, int *cantFilas, int *cantColumnas){
	fscanf(inputFile,"%i %i \n", cantFilas, cantColumnas);
	long long *matrix = malloc(((*cantFilas)*(*cantColumnas))*sizeof(long long));
	int contadorMatrix = 0;
	int contadorFilas = 0;
	char *fila = NULL;
	int contadorCadenaFila = 0;
	char caracter = fgetc(inputFile);
	while (!feof(inputFile)){
		while((!feof(inputFile)) && (caracter!='\n')){
			if(fila == NULL){
				fila = malloc((contadorCadenaFila+1)*sizeof(char));
				fila[contadorCadenaFila] = caracter;
			}else{
				fila = realloc(fila, (contadorCadenaFila+1)* sizeof(char));
				fila[contadorCadenaFila]=caracter;
			}
			contadorCadenaFila++;
			caracter = fgetc(inputFile);
		}
		if(fila != NULL){
			contadorFilas++;
			if(contadorFilas > (*cantFilas)){
				fprintf(stderr, "Error: exceso de filas\n");
				return NULL;
			}

			fila = realloc(fila, (contadorCadenaFila+1)* sizeof(char));
			fila[contadorCadenaFila]='\0';

			long long *vectorFila = malloc((*cantColumnas)*sizeof(long long));
			if(llenarFila(fila,vectorFila,cantColumnas,contadorFilas) == ERROR){
				return NULL;
			}
			int i= 0;
			for(i = 0; i < *cantColumnas;i++){
				matrix[contadorMatrix] = vectorFila[i];
				contadorMatrix++;
			}
			free(vectorFila);
			free(fila);
		}
		fila = NULL;
		contadorCadenaFila = 0;
		if(!feof(inputFile)){
			caracter = fgetc(inputFile);
		}
	}
	if(contadorFilas < (*cantFilas)){
		fprintf(stderr, "Error: faltan filas\n");
		return NULL;
	}
	return matrix;
}

int main(int argc, char *argv[])
{
    int option = 0;
	char *file;
    const char *short_opt = ":o:hV";
    struct option long_opt[] = {
            {"version", no_argument,       NULL, 'V'},
            {"help",    no_argument,       NULL, 'h'},
            {"output",   optional_argument, NULL, 'o'},
            {NULL, 0,                      NULL, 0}
    };
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;
    bool ingresoGuion = false;
    while ((option = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
    	switch (option) {
		case 'V':
			printf("TP #0 de la materia Organizacion de Computadoras \n");
			printf("Alumno: \n");
			printf("	Quino Lopez Julian \n");
			return SALIDA_EXITOSA;
		case 'h':
			printf("Usage: \n");
			printf("	%s -h \n", argv[0]);
			printf("	%s -V \n", argv[0]);
			printf("	%s [options] file\n", argv[0]);
			printf("Options: \n");
			printf("	-V, --version  Print version and quit. \n");
			printf("	-h, --help     Print this information. \n");
			printf("	-o, --output   Path to output file. \n");
			printf("\n Examples: \n");
			printf("	%s - mymatrix \n", argv[0]);
			printf("	%s -o - mymatrix \n", argv[0]);
			return SALIDA_EXITOSA;
		case 'o':
			if(strcmp(optarg, "-") != 0){
				file = optarg;
				outputFile = fopen( file, "w" );
				if (outputFile == NULL) {
				 	fprintf(stderr, "Error archivo Salida: %s\n", strerror(errno));
					return ERROR;
				}
			}
			else{
				ingresoGuion = true;
				printf ("salida por stdout\n");
			}
			break;
		default:
			fprintf(stderr, "Parametro invalido, use el comando -h\n");
			return ERROR;
			break;
        }

    }
    inputFile = validacionDeArchivoEntrada(argc,argv,ingresoGuion);
    if(inputFile==NULL){
    	return ERROR;
    }
    int cantFilas = 0;
    int cantColumnas = 0;
    long long *matrix = parsearMatriz(inputFile,&cantFilas, &cantColumnas);
    if(matrix==NULL){
    	return ERROR;
    }
    long long *matrixSalida = malloc((cantFilas*cantColumnas)*sizeof(long long));

    trasponer(cantFilas, cantColumnas, matrix, matrixSalida);
	
	if ( NULL == outputFile ) outputFile = stdout;
	guardarMatriz(matrixSalida, cantFilas, cantColumnas, outputFile);

	if(outputFile != stdout){
		fclose(outputFile);
	}

	fclose(inputFile);
    free(matrix);
    free(matrixSalida);
    return SALIDA_EXITOSA;
}
