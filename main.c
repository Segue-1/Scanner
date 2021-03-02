#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "scanner.h"


void print_usage();
static char * read_stdin();
static char *load_file(char const * path);

int main (int argc, char* argv[]) {

	

	// Check number of arguments
	if (argc > 2) {
		printf("Too many arguments\n");
		print_usage();
		exit(0);
	}	
	else if (argc == 2) {
		// File was passed, check if it exists
		if (access(argv[1], F_OK) == 0) {
			printf("File exists, continuing...\n");
		}
		else {
			printf("File doesn't exist, exiting...\n");
			exit(0);
		}
		
		//FILE *fp;
		//FILE fopen(argv[1], r);
		char *input = load_file(argv[1]);

		parse(input);
		

		exit(0);
	}
	else if (argc == 1) {


		printf("Getting input from stdin...\n");
		printf("Simulate EOF by entering 0 \n");


		char *input = read_stdin(); 	 // Read from STDIN


		parse(input);

		exit(0);
	}
	else {
		// Shouldn't be possible... 0 args
		printf("How did you do that?\n");
		print_usage();
		exit(0);
	}


	return 0;
}


void print_usage(){

	printf("---Usage---\n");
	printf("Enter './main' to test keyboard\n");
	printf("Enter './main < FILENAME' to test keyboard input from some file\n");
	printf("Enter './main FILENAME' to read from a file\n");

}

static char * read_stdin(){


	size_t capacity = 4096, offset = 0;  // Set size of buffer and offset.
	char *buffer = malloc(capacity * sizeof (char));
	int c; 

	// Read until EOF
	while ((c = fgetc(stdin)) != '0' && !feof(stdin)) {
				
		
		buffer[offset] = c;	
		if (++offset == capacity) {
			buffer = realloc(buffer, (capacity *= 2) * sizeof (char));
		}
			

	}

	// Trim and pad
	buffer = realloc(buffer, (offset + 1) * sizeof (char));
	buffer[offset] = '\0';

	return buffer;
}


static char* load_file(char const* path)
{
    	char* buffer = 0;
    	long length;
    	FILE * f = fopen (path, "rb"); 

	if(f) {
		fseek (f, 0, SEEK_END);
      		length = ftell (f);
      		fseek (f, 0, SEEK_SET);
      		buffer = (char*)malloc ((length+1)*sizeof(char));
      	if (buffer) {
        	fread (buffer, sizeof(char), length, f);
      	}

	fclose (f);

	}
	
	// Pad will null terminator
	buffer[length] = '\0';

    	return buffer;
}
