#include <stdio.h>
#include <ctype.h>

int find();

int main() {
	int total;

	FILE* fptr;
	fptr = fopen("input2", "r");

	if (fptr = NULL)
		printf("Error opening file!");

 	char buffer[100];
	while (fgets(buffer, sizeof(buffer), fptr)) {
		printf("%s", buffer);
	}
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

	printf("Number: %d\n", num);

	return num;
}
