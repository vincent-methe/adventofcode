#include <stdio.h>
#include <ctype.h>

int set_input(char str[], long int input[]);
int scan(char str[], long int input[], int conv[]);
long int number_conversion(int *i, char str[]);

int input_size = 20;

int main() {
	long int input[input_size];
	int check_conversion[input_size];

	// open a file stream

	FILE *fptr = fopen("input", "r");
	
	if (fptr == NULL) {
		printf("Error opening File!\n");
	} else {
		char buffer[512];

		int check_input = 0; // used to check if an input was set

		while (fgets(buffer, sizeof(buffer), fptr)) {
			if (check_input == 0) {
				set_input(buffer, input);
				check_input = 1;
			} else {
				scan(buffer, input, check_conversion);
			}
		}
	}

	// close the file stream

	fclose(fptr);

	// calculate the lowest location number of the result set

	int lowest_location = input[0];

	for (int i = 0; i < input_size; i++) {
		if (input[i] < lowest_location)
			lowest_location = input[i];
	}

	printf("The lowest location number is %ld!\n", lowest_location);

	return 0;
}

// set_input assigns the numbers found in a given string to a given input array

int set_input(char str[], long int input[]) {
	int i = 0;
	int c = 0;
	
	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			input[c] = number_conversion(&i, str);
			c++;
		} else {
			i++;
		}
	}

	return 0;
}

// scan checks if any element of a given input should be converted by the given string

int scan(char str[], long int input[], int conv[]) {
	int i = 0;
	long int map[3] = {-1, -1, -1};
	int c = 0;

	// check the string for maps or changes in them
	
	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			map[c] = number_conversion(&i, str);
			c++;
		} else if (str[i] == ':') {
			for (int i = 0; i < input_size; i++) {
				conv[i] = 0;
			}
			i++;
		} else {
			i++;
		}
	}

	// convert the input according to the given map

	for (int x = 0; x < input_size; x++) {
		if (map[1] <= input[x] && input[x] < (map[1] + map[2]) && conv[x] == 0) {
			input[x] = map[0] + (input[x] - map[1]);
			conv[x] = 1;
		}
	}
		
	return 0;
}

// number_conversion extracts numbers from a string using its first digit

long int number_conversion(int *i, char str[]) {
	long int sum = 0;
	
	// proceed to the last digit of the number while counting up

	int x = 0;

	while (isdigit(str[*i])) {
		(*i)++;
		x++;
	}

	// convert all digits to decimal

	long int m = 1;
	int c = 1;

	while (c <= x) {
		sum = sum + (str[*i - c] - '0') * m;
		m = m * 10;
		c++;
	}

	return sum;
}
