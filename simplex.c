#include <stdio.h>
#include <stdlib.h>
#include "builder.h"

struct LPP
{
  struct Vector *o;		//bjective function vector, in standard simplex form. all coefficients should be positive, with a Maxmiziation problem.
  struct Vector *r;		//esource vector.
  Matrix *c;			//onstraints Matrix
};

int
main (int argc, char **argv)
{
  delimiter = ',';
  EoV = '}';
setDebug(argv[2]);
  Matrix obj = buildMatrix ("obj");
  Matrix resources = buildMatrix ("resources");
  Matrix constraints = buildMatrix ("constraints");
  struct LPP problem;
  printVector(obj.v);
  putchar('\n');
  printMatrix (constraints);
  putchar('\n');
  printVector(getVector(&constraints,1));
  putchar('\n');
  //scaleVector(getVector(constraints,1), -1);
  scaleVector(obj.v, -1);
  putchar('\n');
  printVector(obj.v);
printf("entering column is %d.\n", getMinIndex(obj.v));
printf("with a value of %d", getEntry(obj.v, getMinIndex(obj.v)));
  putchar('\n');
//printVector(getTCol(constraints, 0));//getMinIndex(obj.v)));
  return 0;
}

//returns col index of entry where the minimum is stored. such as finding entering variable from standard form.
int
getMinIndex(struct Vector * v){
int min = 0, i = 0;
for(; i < (*v).n; i++)
if(*((*v).v+i) < *((*v).v+min))
	min = i;
return min;
}
