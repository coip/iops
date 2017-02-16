#ifndef BUILDER_H_
#define BUILDER_H_

char delimiter;
char EoV;

int d1, d2, d3;

typedef struct
{
  int m;			//# of rows/height:
  struct Vector *v;		//a malloc(m*sizeof(struct Vector))'d vector pointer to a vector
} Matrix;

struct Vector
{
  int n;			//# of columns/width todo kind of redundant. #onthetable
  int *v;			//a malloc(n*sizeof(int))'d              int pointer to the vector
};

void setDebug(char*);

Matrix buildMatrix(char *buf);

void printMatrix(Matrix);

#endif
