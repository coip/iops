/* builder.c is the parsing workhorse. exhumes vectors, value by value
 *
 *
 *
 * Copyright Mon, Oct 03, 2016 6:49:45 PM 
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include "builder.h"

struct Vector
buildVector (char *buffer)
{				//this takes in input after readline from file.

  //#INIT VECTOR:
  struct Vector row;
  row.n = 0;
  row.v = malloc (sizeof (int));
  //INIT CSTR
  char *token = malloc (1);	//todo memory could likely be much less granular.
  int counter = 0;
  if (d1)
    printf ("building vector from buffer: %s\n", buffer);

  while (*(++buffer))
    {				//preincrement due to starting char will be opening character following matrix convention.
      if (*buffer == delimiter || *buffer == EoV)
	{
	  *(row.v + (row.n)) = atoi (token);
	  row.n++;
	  if (d2)
	    printf
	      ("cstring rep. of #: %s. int %d added.",
	       token, *(row.v + row.n - 1));
	  row.v = realloc (row.v, ((row.n + 1) * 8));
	  free (token);
	  counter = 0;
	  token = malloc (1);
	}
      if (*buffer == EoV)
	break;
      if ((48 <= *buffer) && (*buffer <= 57))
	{
	  if (d2)
	    printf ("char: \'%c\', addr: %p\n", *buffer, buffer);
	  *(token + counter) = *buffer;
	  token = realloc (token, (counter + 1));
	  *(token + counter + 1) = '\0';
	  counter++;
	}

    }

  if (d1)
    {
      int i;
      printf ("printing vector contents for row %d:\n", row.n);
      printf ("\n[ ");
      for (i = 0; i < row.n - 1; i++)
	printf ("%d, ", *(row.v + i));
      printf ("%d ]\n", *(row.v + row.n - 1));
    }

  return row;
}

Matrix
buildMatrix (char *buf)
{
  //this takes in file name as cstring
  if (d1)
    printf ("building matrix in file %s", buf);
  //#INIT MATRIX:
  Matrix matrix;
  matrix.m = 0;
  matrix.v = malloc (sizeof (struct Vector));

  FILE *mfile;
  mfile = fopen (buf, "r");
  if (mfile == NULL)
    {
      printf ("File doesn't exist: %s\n", buf);
      return matrix;
    }
//static allocation: eww. todo
  char *storage = malloc (100);	//todo: make dynamic read in if possible? maybe pass in buffer size, run tests, derive best?

  while (fgets (storage, 100, (FILE *) mfile))
    {
      //INIT TEMP VECTOR
      struct Vector r;
      r = buildVector (storage);
      *(matrix.v + matrix.m) = r;
      if (d1)
	{
	  printMatrix (matrix);
	}
      if (d2)
	printf
	  ("sizeof(struct Vector *) == %lu;\nsizeof(struct Vector) == %lu;\nr.n = %d;\nsizeof(int) == %lu\n addr: %p\n",
	   sizeof (struct Vector *), sizeof (struct Vector), r.n,
	   sizeof (int), (matrix.v + (matrix.m * sizeof (struct Vector *))));
      matrix.m++;
      matrix.v =
	realloc (matrix.v, ((matrix.m + 1) * sizeof (struct Vector)));
    }
  fclose (mfile);
  return matrix;

}

void
printMatrix (Matrix m)
{

  int i, j;
  printf ("{");
  for (j = 0; j < m.m; j++)
    {
      printf("[");
      for (i = 0; i < (*(m.v)).n - 1; i++)
	printf (" %d, ", *((*(m.v + j)).v + i));
      printf ("%d ]", *((*(m.v + j)).v + (*(m.v + j)).n - 1));
	if(!(j+1==m.m))
		printf("\n");
    }
  printf ("}\n");

}

void
printVector(struct Vector * v){

}
void
setDebug (char *arg)
{

  d1, d2, d3 = 0;
  switch (atoi (arg))
    {
    case 3:
      d3 = 1;
    case 2:
      d2 = 1;
    case 1:
      d1 = 1;
    default:
      break;
    }
}

/*int
main (int argc, char *argv[])
{
  if (argc == 3)
    setDebug (argv[2]);
delimiter = ',';
EoV = '}';
  Matrix m = buildMatrix (argv[1]);

  printMatrix (m);

  return 0;

}*/
