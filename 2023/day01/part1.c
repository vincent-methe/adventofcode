#include <stdio.h>
#include <ctype.h>

int find();

int main() {
	int total = 0;
	char buffer[255];

	FILE* fptr;
	fptr = fopen("input", "r");

	if (fptr == NULL) {
		printf("Error opening file!");
	} else {
	 	while (fgets(buffer, sizeof(buffer), fptr)) {
			total = total + find(buffer);
			printf("Running total: %d,\n", total);
		}
		fclose(fptr);
	}

	printf("\nTotal: %d!\n", total);
}

int find(char str[]) {
	
	int i = 0;
	int num_one;
	int num_two;
	int num;

	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			num_one = str[i];
			break;
		}
		i++;
	}

	i = 0;

	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			num_two = str[i];
		}
		i++;
	}

	num = (num_one - '0') * 10 + (num_two - '0');

	printf("Temporary Result: %d,\n", num);

	return num;
}
