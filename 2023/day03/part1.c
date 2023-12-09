#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 142 // assuming 140 characters followed by a newline and null character

int part_number_sum(char prev[], char curr[], char next[]);
void init_array(char arr[]);

int main() {
	// declaring and defining arrays for temporary line storage

	char prev_line[LINE_LENGTH];
	char curr_line[LINE_LENGTH];
	char next_line[LINE_LENGTH];
	
	// initializing the arrays

	init_array(prev_line);
	init_array(curr_line);
	init_array(next_line);

	// loading the input file into memory

	FILE *fptr = fopen("input", "r");
	
	// if the file was loaded successfully, processing begins

	if (fptr == NULL) {
		printf("Error: opening the file failed");
	} else {
		char buffer[LINE_LENGTH];
		while (fgets(buffer, sizeof(buffer), fptr)) {
			memcpy(next_line, buffer, sizeof(buffer));
			part_number_sum(prev_line, curr_line, next_line);
			memcpy(prev_line, curr_line, sizeof(curr_line));
			memcpy(curr_line, next_line, sizeof(next_line));
		}

		init_array(next_line);
		part_number_sum(prev_line, curr_line, next_line);
	}
	
	// closes the file stream

	fclose(fptr);

	return 0;
}

// part_number_sum return the sum of all numbers in a string that are part numbers

int part_number_sum (char prev[], char curr[], char next[]) {
	printf("PREV: %s", prev);
	printf("CURR: %s", curr);
	printf("NEXT: %s", next);
	printf("\n");
	return 0;
}

// init_array takes an array of characters and initializes all elements to '.'. The last two elements are replaced by the newline and null characters.

void init_array(char arr[]) {
	for (int i = 0; i < LINE_LENGTH; i++) {
		arr[i] = '.';
	}
	
	// strings in C end with a null character \0 optionally preceded by a newline character '\n'.

	arr[LINE_LENGTH - 2] = '\n';
	arr[LINE_LENGTH - 1] = '\0';
}
