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
int debug;

struct Vector {
	int n;			//# of columns/width
	int *v;			//a malloc(n*sizeof(int))'d int pointer to the vector
};

typedef struct {
	int m;			//# of rows/height:
	int n;			//# of columns/width
	struct Vector *v;
} Matrix;

struct Vector buildVector(char *buffer)
{				//this takes in input after readline from file.

	//#INIT VECTOR:
	struct Vector row;
	row.n = 0;
	row.v = malloc(sizeof(int));
	//INIT CSTR
	char *token = malloc(1);
	int counter = 0;

	while (*(++buffer)) {	//preincrement due to starting char will be opening character following matrix convention.
		if (*buffer == delimiter || *buffer == EoV) {
			*(row.v + (row.n)) = atoi(token);
			row.n++;
			if (debug)
				printf("cstring rep. of #: %s. int %d added. size of row: %d\n\n", token, *(row.v + row.n - 1), row.n);
			row.v = realloc(row.v, ((row.n + 1) * 8));
			free(token);
			counter = 0;
			token = malloc(1);
		}
		if (*buffer == EoV)
			break;
		if ((48 <= *buffer) && (*buffer <= 57)) {
			if (debug)
				printf("char: \'%c\', int: %d, addr: %p\n", *buffer, *buffer, buffer);
			*(token + counter) = *buffer;
			token = realloc(token, (counter + 1));
			*(token + counter + 1) = '\0';
			counter++;
		}

	}

return row;
}

Matrix buildMatrix(char *buf)
{				//this takes in file name as cstring

	//#INIT MATRIX:
	Matrix matrix;
	matrix.m = 0;
	matrix.n = 0;
	matrix.v = malloc(sizeof(struct Vector *));
	
	FILE *mfile;
	mfile = fopen(buf, "r");
	if (mfile == NULL) {
		printf("File doesn't exist: %s", buf);
		fclose(mfile);
		return matrix;
	}
//static allocation: eww. todo
	char storage[100];
	
while(fgets(storage, 100, (FILE *) mfile)){
	//INIT TEMP VECTOR
	struct Vector r;
	r = buildVector(storage);
printf("sizeof(vector *) == %lu", sizeof(struct Vector *));
	matrix.v(matrix.m * 8) = &r;//malloc( (r.n + 1) * sizeof(int) ); //vector elements are n - many, with +1 for the counter itself.
	matrix.m++;
}
	fclose(mfile);
	return matrix;

}

int main(int argc, char *argv[])
{
	debug = 0;
	if (argc == 3)
		debug = 1;

	printf("building matrix in %s\n", argv[1]);

	buildMatrix(argv[1]);
//only receiving one line from input currently.
//refactor to call new helper function buildVector() in buildMatrix(string file). move all file io inside build matrix master call.

	return 0;

}
