#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
	char *str;
	struct node *next;
};

void printReverseList(struct node *head, FILE *outFile);

void printReverseList(struct node *head, FILE *outFile)
{
	if (head == NULL) {
		return;
	}

	printReverseList(head->next, outFile);
	//Output to file
	fprintf(outFile, "%s", head->str);
	//Free line memory
	char *line = head->str;
	free(line);
	//Free node memory
	struct node* freeNode;
	freeNode = head;
	free(freeNode);
};

int main(int argc, char *argv[])
{
	//Check incorrect number of arguments passed to program
	if(argc < 2 || argc > 3) {
		fprintf(stderr, "usuage: reverse <input> <output> \n");
		exit(1);
	}

	FILE *out_file;

	//If there is an output file create variable file
	if (argv[2] != NULL) {
		//Check if input file is the same as the output file
		if (strcmp(argv[1], argv[2]) == 0) {
			fprintf(stderr, "error: input and output file must differ \n");
			exit(1);
		}
		//Open output file
		out_file = fopen(argv[2], "w");
		//Check if output file can be open
		if (out_file == NULL) {
			fprintf(stderr, "error: cannot open file %s \n", argv[2]);
			exit(1);
	}
	}
	else {
		out_file = stdout;
	}

	
	

	//Declare Variables
	//_____________________________________
	FILE *in_file;
	char *line = NULL;
	size_t len = 0;
	int count = 0;

	struct node *head = NULL;
	struct node *newNode = NULL;
	struct node *current = NULL;

	//_____________________________________
	
	
	

	//Read the input file
	in_file = fopen(argv[1], "r");

	//If in_file can't open -> stderr
	if (in_file == NULL) {
		fprintf(stderr, "error: cannot open file %s \n", argv[1]);
		exit(1);
	}

	
	
	while (getline(&line, &len, in_file) != -1) {
		//printf("%s", line);
		count += 1;

		// Create new Node with data
		newNode = (struct node *)malloc(sizeof(struct node));
		//Check for System Call Failure
		if (newNode == NULL) {
			fprintf(stderr, "error: malloc failed");
			exit(1);
		}
		
		
		newNode->str = strdup(line); // YAY
		if (newNode->str == NULL) {
			fprintf(stderr, "error: strdup failed");
		}
		newNode->next = NULL;

		//if count == 1; (The node is the head)
		if (count == 1) {
			head = newNode;
			current = newNode;
		}
		//Else link the previous node to the newnode and make the current node into the newnode
		else {
			count = 2; //Limits the count variable from being large
			current->next = newNode;
			current= newNode;
		}
	}

	current = head;
	printReverseList(current, out_file);


	
	fclose(in_file);
	fclose(out_file);
	free(line); // Deallocate the ptr in memory 

	return 0;
}



