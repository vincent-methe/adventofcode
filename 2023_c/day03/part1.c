#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 142 // assuming 140 characters followed by a newline and null character

int part_number_sum(char prev[], char curr[], char next[]);
int has_symbol(int i, char prev[], char curr[], char next[]);
int is_symbol(char c);
void init_array(char arr[]);

int main() {
	int total = 0;

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
			total = total + part_number_sum(prev_line, curr_line, next_line);
			memcpy(prev_line, curr_line, sizeof(curr_line));
			memcpy(curr_line, next_line, sizeof(next_line));
		}

		init_array(next_line);
		total = total + part_number_sum(prev_line, curr_line, next_line);

		printf("Total: %d\n", total);
	}
	
	// closes the file stream

	fclose(fptr);

	return 0;
}

// part_number_sum return the sum of all numbers in a string that are part numbers

int part_number_sum (char prev[], char curr[], char next[]) {
	/*
	printf("PREV: %s", prev);
	printf("CURR: %s", curr);
	printf("NEXT: %s", next);
	printf("\n");
	*/
	int sum = 0;

	int i = 0;

	while (curr[i] != '\n') {

		// condition checks if an element of the string is a digit and if it is next to a symbol

		if (isdigit(curr[i]) && has_symbol(i, prev, curr, next)) {
		
			// the loop advances to the last digit of the number as to avoid duplicates

			while (isdigit(curr[i+1])) {
				i++;
			}

			// adding up digits

			if (isdigit(curr[i - 1])) {
				if (isdigit(curr[i - 2])) {
					sum = sum + 100 * (curr[i - 2] - '0') + 10 * (curr[i - 1] - '0') + (curr[i] - '0');
				} else {
					sum = sum + 10 * (curr[i - 1] - '0') + (curr[i] - '0');
				}
			} else {
				sum = sum + (curr[i] - '0');
			}
		}
		i++;
	}
	
	return sum;
}

// has_symbol checks if an element is adjacent to a symbol

int has_symbol (int i, char prev[], char curr[], char next[]) {
	if (
		is_symbol(prev[i - 1]) ||
		is_symbol(prev[i]) ||
		is_symbol(prev[i + 1]) ||
		is_symbol(curr[i - 1]) ||
		is_symbol(curr[i + 1]) ||
		is_symbol(next[i - 1]) ||
		is_symbol(next[i]) ||
		is_symbol(next[i + 1])
	) {
		return 1;
	} else {
		return 0;
	}
}

// is_symbol checks if a character counts as a symbol

int is_symbol (char c) {
	if (c == '.' || c == '\0' || c == '\n' || isdigit(c))
		return 0;
	else
		return 1;
}

// init_array takes an array of characters and initializes all elements to '.'. The last two elements are replaced by the newline and null characters.

void init_array (char arr[]) {
	for (int i = 0; i < LINE_LENGTH; i++) {
		arr[i] = '.';
	}
	
	// strings in C end with a null character \0 optionally preceded by a newline character '\n'.

	arr[LINE_LENGTH - 2] = '\n';
	arr[LINE_LENGTH - 1] = '\0';
}
