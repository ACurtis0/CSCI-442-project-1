#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Creates struct node for linked list:
Holds the next pointer and string data 
*/
struct node
{
	char *str;
	struct node *next;
};

/*
Function: printReverseList
Description: Recursively prints (in reverse) linked list with head input;
Free line(strdup) memory and node(malloc) memory.
*/
void printReverseList(struct node *head, FILE *outFile);
void printReverseList(struct node *head, FILE *outFile)
{
	if (head == NULL) {
		return;
	}

	printReverseList(head->next, outFile);
	fprintf(outFile, "%s", head->str);
	char *line = head->str;
	free(line);
	struct node* freeNode;
	freeNode = head;
	free(freeNode);
};

int main(int argc, char *argv[])
{
	//Check incorrect number of arguments passed to program
	if(argc < 2 || argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	

	FILE *out_file;


	/*
	1) Check if there is an output file, if there is open the file
	2) Check if input file is the same as the output file (prints error if it is)
	3) Check if output file can be open (prints error if it cannot)
	*/
	if (argv[2] != NULL) {
		if (strcmp(argv[1], argv[2]) == 0) {
			fprintf(stderr, "error: input and output file must differ\n");
			exit(1);
		}
		out_file = fopen(argv[2], "w");
		if (out_file == NULL) {
			fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
			exit(1);
		}
	} else {
		out_file = stdout;
	}

	
	//Declare Variables
	FILE *in_file;
	char *line = NULL;
	size_t len = 0;
	int count = 0;

	struct node *head = NULL;
	struct node *newNode = NULL;
	struct node *current = NULL;

	
	/*
	Reads input file 
	Check if input file can be open (prints error if it cannot)
	*/
	in_file = fopen(argv[1], "r");
	if (in_file == NULL) {
		fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
		exit(1);
	}

	
	//Reads each line in the file and stores it into a linked list structure
	while (getline(&line, &len, in_file) != -1) {
		count += 1;
		newNode = (struct node *)malloc(sizeof(struct node));

		//Check for System Call Failure (print error if fails)
		if (newNode == NULL) {
			fprintf(stderr, "error: malloc failed\n");
			exit(1);
		}
		
		newNode->str = strdup(line);

		//Check for System Call Failure (print error if fails)
		if (newNode->str == NULL) {
			fprintf(stderr, "error: strdup failed\n");
		}

		newNode->next = NULL;

		/*
		Checks for first node and makes it the head;
		Else links the node to the end of the previous node
		*/
		if (count == 1) {
			head = newNode;
			current = newNode;
		} else { 
			count = 2; 		//Limits the count variable from being large
			current->next = newNode;
			current= newNode;
		}
	}

	//Recursively print the reverse file
	current = head;
	printReverseList(current, out_file);

	//Close files and frees line ptr memory
	fclose(in_file);
	fclose(out_file);
	free(line); 

	return 0;
}

