#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("TODO: write a main function\n");
	//Declare Variables
	//_____________________________________
	FILE *in_file;
	char *line = NULL;
	size_t len = 0;
	//_____________________________________

	//Read the input file
	in_file = fopen(argv[1], "r");

	//If there is no in_file
	if (in_file == NULL) {
		// (Can't open file)
		printf("oh no");
		exit(1);
	}
	//
	else {
		while (getline(&line, &len, in_file) != -1) {
			printf("%s", line);
		}
	}

	fclose(in_file);
	free(line); // Deallocate the ptr in memory 
		
	return 0;
}

