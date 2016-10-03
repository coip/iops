#include <stdio.h>
#include <stdlib.h>
int* buildVector(char buffer[]){
	
}

char* trim(char * buffer){	//rel:b) ascii 48 - 57 is 0-9
	int counter = 0;
	char * result;
	char * iterator;
	char * temp = buffer;	//rel:a) input needs a { at the start
	
	result = malloc(1);
	iterator = result;

	while(*temp++ != '}'){	//rel:a) because of this in initial iteration, ignores first char.
	
		if( *temp == 44 || (48 <= *temp) && (*temp <= 57)){ //rel:b) logic for [0-9]
			result = realloc(result, (counter+1));
			*iterator = *temp;
			counter++;
			printf("char: %c, addr: %u", *iterator, iterator);
			iterator++;
		}
		
	}
	iterator = result;	
	for(int i = 0; i < counter; i++, iterator++)
		printf("\n %c", *iterator);

	return result;
}

int main(int* argc, char* argv[]){

	printf("argc: %d; argv[]: %s", argc, argv[1]);

	FILE *obj, *con, *res;

	char buffer[100];

	obj = fopen(argv[1], "r");
	con = fopen("con", "r");
	res = fopen("res", "r");

	fgets(buffer, 100, (FILE *)obj);


	printf("\nsizeof(buffer): %d, contents: %s", sizeof(buffer), buffer);

	trim(buffer);

	fclose(con);
	fclose(res);
	fclose(obj);

	return 0;

}
