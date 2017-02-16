#include <stdio.h>
#include <stdlib.h>
#include "builder.h"

int
main(int argc, char** argv)
{
delimiter = ',';
EoV = '}';
Matrix obj 		= buildMatrix("obj");
Matrix resources 	= buildMatrix("resources");
Matrix constraints 	= buildMatrix("constraints");
printMatrix(obj);
printf("\n");
printMatrix(resources);
printf("\n");
printMatrix(constraints);
return 0;
}
