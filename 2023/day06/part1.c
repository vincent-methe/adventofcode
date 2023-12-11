#include <stdio.h>
#include <ctype.h>

int fill_arr(char str[], int arr[]);
int get_number(int *i, char str[]);
int new_records(int time, int record);

int main() {
	int races = 4;

	int result = 1;

	int race_time[races];
	int race_record[races];
	
	// open the input an fill the time and record arrays with it

	FILE *fptr = fopen("input", "r");

	if (fptr == NULL) {
		printf("Error opening file!\n");
	} else {
		char buffer[512];
		fill_arr(fgets(buffer, sizeof(buffer), fptr), race_time);
		fill_arr(fgets(buffer, sizeof(buffer), fptr), race_record);
	}

	fclose(fptr);
	
	// calculate the product of the number of ways each race record could be broken

	for (int i = 0; i < races; i++) {
		result = result *  new_records(race_time[i], race_record[i]);
	}

	printf("The result is %d!\n", result);

	return 0;
}

// fill_arr populates an array with the numbers found within a string

int fill_arr(char str[], int arr[]) {
	int i = 0;
	int x = 0;
	
	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			arr[x] = get_number(&i, str);
			x++;
		} else {
			i++;
		}
	}
	return 0;
}

// get_number returns a number as an int given its first digit in a string

int get_number(int *i, char str[]) {
	int sum = 0;
	int digits = 0;
	int multiply = 1;
	int count = 1;

	while (isdigit(str[*i])) {
		(*i)++;
		digits++;
	}

	while (count <= digits) {
		sum = sum + (str[*i - count] - '0') * multiply;
		multiply = multiply * 10;
		count++;
	}

	return sum;
}

// new_records returns the number of ways in which a given record can be broken

int new_records(int time, int record) {
	int distance = 0;
	int count = 0;

	for (int i = 0; i <= time; i++) {
		distance = (i * 1) * (time - i);
		if (distance > record)
			count++;
	}
	return count;
}
