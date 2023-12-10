#include <stdio.h>
#include <ctype.h>

int points(char str[]);
int winning_numbers(int win[], int lose[]);

// setting the amount of numbers encountered in each category as to avoid errors to to uninitialized elements

int win_length = 10;
int your_length = 25;

int main() {
	int total = 0;

	FILE *fptr = fopen("input", "r");
	
	if (fptr == NULL) {
		printf("Error opening file!\n");
	} else {
		char buffer[512];
		while (fgets(buffer, sizeof(buffer), fptr)) {
			total = total + points(buffer);
		}
	}
	
	printf("Total points: %d\n", total);

	fclose(fptr);

	return 0;
}

// points returns the number of points earned for a given string/card

int points(char str[]) {
	int i = 0;
	int x = 0;

	int win_numbers[win_length];
	int your_numbers[your_length];

	while (str[i] != ':')
		i++;

	// placing the winning numbers in an array

	while (str[i] != '|') {
		if (isdigit(str[i])) {
			if (isdigit(str[i + 1])) {
				win_numbers[x] = 10 * (str[i] - '0') + (str[i + 1] - '0');
				i++;
			} else {
				win_numbers[x] = (str[i] - '0');
			}
			x++;
		}
		i++;
	}
	
	x = 0;

	// placing your numbers in an array

	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			if (isdigit(str[i + 1])) {
				your_numbers[x] = 10 * (str[i] - '0') + (str[i + 1] - '0');
				i++;
			} else {
				your_numbers[x] = (str[i] - '0');
			}
			x++;
		}
		i++;
	}
	
	// calculate the number your numbers that are winning numbers

	int nums = winning_numbers(win_numbers, your_numbers);
	
	// return the appropriate amount of points

	if (nums > 0)
		return (1 << (nums - 1));
	else
		return 0;
}

// winning_numbers returns the amount of your numbers that are part of the set of winning numbers

int winning_numbers(int win[], int your[]) {
	int sum = 0;

	for (int t = 0; t < your_length; t++) {
		for (int s = 0; s < win_length; s++) {
			if (your[t] == win[s]) {
				sum++;
			}
		}
	}
	return sum;
}
