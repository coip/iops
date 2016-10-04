/* builder.c is the parsing workhorse. exhumes vectors, value by value
 *
 *
 *
 * Copyright Mon, Oct 03, 2016 6:49:45 PM 
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

const char delimiter = ',';
const char EoV = '}';







struct Vector {
	int n; 	//# of columns/width
	int *v; //a malloc(n*sizeof(int))'d int pointer to the vector
};

typedef struct {
	//# of rows/height:
	int m;
	//# of columns/width
	int n;
	struct Vector *vector;
} Matrix;







Matrix buildMatrix(char * buf){
	
	//#INIT VECTOR:
	struct Vector row;
	row.v = malloc(sizeof(int));
	row.n = 0;

	//#INIT MATRIX:
	Matrix matrix;
	matrix.m = 0;
	matrix.n = 0; 

	//INIT CSTR
	char * token = malloc(1);
	int counter = 0;

	while( *++buf ){
		if(*buf == delimiter || *buf == EoV){
			*(row.v+(row.n)) = atoi(token);
			row.n++;
			//printf("cstring rep. of #: %s. int %d added. size of row: %d // free(token) && malloc(1)", *token, *(row.v), row.n);
			row.v = realloc(row.v, ((row.n+1) * 8)); 
			free(token);
			counter = 0;
			token = malloc(1);
		}
		if(*buf == EoV)
			break;
		if((48 <= *buf) && (*buf <= 57)){
				printf("char: \'%c\', int: %d, addr: %u\n", *buf, *buf, buf);
			*(token+counter) = *buf;
			token = realloc(token, (counter+1));
			*(token+counter+1) = NULL;
			counter++;
		}
		
	}
	printf("row.n: %d", row.n);
	for(int i = 0; i < row.n; i++)
		printf("row[%d]: %d\n", i, row.v[i]);
	return matrix;

}


int main(int argc, char* argv[]){


	printf("building matrix in %s", argv[1]);
	

	FILE *matrix;

	matrix = fopen(argv[1], "r");
	if(matrix == NULL){
		printf("File doesn't exist: %s", argv[1]);
		fclose(matrix);
		return -1;
	}

	char buffer[100];
	fgets(buffer, 100, (FILE *)matrix);

	printf("\nsizeof(buffer): %d, contents: %s", sizeof(buffer), buffer);
	
	buildMatrix(buffer);

	fclose(matrix);

	return 0;

}
