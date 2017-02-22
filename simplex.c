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
  Matrix obj = buildMatrix ("obj");
  Matrix resources = buildMatrix ("resources");
  Matrix constraints = buildMatrix ("constraints");
  struct LPP problem;
  printMatrix (obj);
  printf ("\n");
  printMatrix (resources);
  printf ("\n");
  printMatrix (constraints);
  return 0;
}
