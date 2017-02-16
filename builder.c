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

int d1, d2, d3;

struct Vector {
	int n;			//# of columns/width
	int *v;			//a malloc(n*sizeof(int))'d              int pointer to the vector
};

typedef struct {
	int m;			//# of rows/height:
	struct Vector *v;	//a malloc(m*sizeof(struct Vector))'d vector pointer to a vector
} Matrix;
/*

Matrix m;
[[1,2,3,4,5],
 [6,7,8,9,0],
 [1,3,5,7,9],
 [2,4,6,8,0]]

m.m == 4;
m.n == 5;
m.v == memoryaddr;

*(m)  => struct Vector;
**(m) => int;

*(m.v)  			== [ 1, 2, 3, 4, 5];
**(m.v) 			== 1;
**(m.v+4)			== 2;

*(m.v+sizeof(struct Vector)) 	== [ 6, 7, 8, 9, 0]

*/

void printMatrix(Matrix m);
struct Vector buildVector(char *buffer)
{				//this takes in input after readline from file.

	//#INIT VECTOR:
	struct Vector row;
	row.n = 0;
	row.v = malloc(sizeof(int));
	//INIT CSTR
	char * token = malloc(1);
	int counter = 0;
if(d1)
	printf("building vector from buffer: %s\n", buffer);

	while (*(++buffer)) {	//preincrement due to starting char will be opening character following matrix convention.
		if (*buffer == delimiter || *buffer == EoV) {
			*(row.v + (row.n)) = atoi(token);
			row.n++;
			if (d2)
				printf("cstring rep. of #: %s. int %d added. size of row: %d\nsizeof(row.v) = %lu\n", token, *(row.v + row.n - 1), row.n, sizeof(row.v));
			row.v = realloc(row.v, ((row.n + 1) * 8));
			free(token);
			counter = 0;
			token = malloc(1);
		}
		if (*buffer == EoV)
			break;
		if ((48 <= *buffer) && (*buffer <= 57)) {
			if (d2)
				printf("char: \'%c\', addr: %p\n", *buffer, buffer);
			*(token + counter) = *buffer;
			token = realloc(token, (counter + 1));
			*(token + counter + 1) = '\0';
			counter++;
		}

	}

	return row;
}

Matrix buildMatrix(char *buf)
{	
	//this takes in file name as cstring

	//#INIT MATRIX:
	Matrix matrix;
	matrix.m = 0;
	matrix.v = malloc(sizeof(struct Vector));

	FILE *mfile;
	mfile = fopen(buf, "r");
	if (mfile == NULL) {
		printf("File doesn't exist: %s\n", buf);
		return matrix;
	}
//static allocation: eww. todo
	char * storage = malloc(100);//todo: make dynamic read in if possible? maybe pass in buffer size, run tests, derive best?

	while (fgets(storage, 100, (FILE *) mfile)) {
		//INIT TEMP VECTOR
		struct Vector r;
		r = buildVector(storage);
		*( matrix.v + matrix.m ) = r;
		if(d1){
			int i;
			printf("printing vector contents for row %d:\n", r.n);
			printf("\n[ ");
			for (i = 0; i < r.n-1; i++)
				printf("%d, ", *(r.v+i));
			printf("%d ]\n", *(r.v+r.n-1));
		}
		if(d1){
			int i;
			printf("printing vector contents for m.%d:\n", matrix.m);
			printf("theres %d elements\n", (*(matrix.v)).n);
			for (i = 0; i < (*(matrix.v)).n - 1 ; i++)
				printf("%d, ", *((*(matrix.v+matrix.m)).v+i));
			printf("%d ]\n", *((*(matrix.v+matrix.m)).v+(*(matrix.v+matrix.m)).n-1));
		}
if(d2)
		printf("sizeof(struct Vector *) == %lu;\nsizeof(struct Vector) == %lu;\nr.n = %d;\nsizeof(int) == %lu\n addr: %p\n", 
				sizeof(struct Vector *), 
				sizeof(struct Vector), 
				r.n, 
				sizeof(int),
				( matrix.v + (matrix.m * sizeof(struct Vector *))));
if(d1)
		printf("total mem for Vector %d: %lu\n\n", matrix.m, (sizeof(struct Vector *) + sizeof(struct Vector) + (r.n * sizeof(int))));
		matrix.m++;
		matrix.v = realloc(matrix.v, ((matrix.m + 1) * sizeof(struct Vector)));
	}
	fclose(mfile);
	return matrix;

}

void printMatrix(Matrix m){

	int i, j;
printf("[[");
	for(j = 0; j < m.m; j++){
		for(i = 0; i < (*(m.v)).n -1; i++)
			printf(" %d, ", *((*(m.v+j)).v+i));
		printf("%d ]\n [", *((*(m.v+j)).v+(*(m.v+j)).n-1));
	}
	printf("end]\n");

}

int main(int argc, char *argv[])
{
	d1,d2 = 0;
if(argc == 3)
	switch(atoi(argv[2])){
	case 2: d2 = 1;	
	case 1: d1 = 1;
	default: break;}

	printf("building matrix in %s\n", argv[1]);

	Matrix m = buildMatrix(argv[1]);
	printf("m.m == %d;\n", m.m);

	printMatrix(m);
//only receiving one line from input currently.
//refactor to call new helper function buildVector() in buildMatrix(string file). move all file io inside build matrix master call.

	return 0;

}
