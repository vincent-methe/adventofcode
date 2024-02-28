#include <stdio.h>
#include <ctype.h>

int check();

int main() {
	int id = 1;
	int total = 0;

	char buffer[512];

	FILE* fptr;
	fptr = fopen("input", "r");

	if (fptr == NULL) {
		printf("Error opening file!\n");
	} else {
	 	while (fgets(buffer, sizeof(buffer), fptr)) {
			if (check(buffer)) {
				total = total + id;
				printf("[x] Game %d\n", id);
			} else {
				printf("[ ] Game %d\n", id);
			}
			id++;
		}
		fclose(fptr);
	}

	printf("\nTotal: %d\n", total);
}

int check(char str[]) {
	
	int i = 0;
	int temp;

	while (str[i] != ':') {	
		i++;
	}

	while (str[i] != '\0') {
		if (isdigit(str[i])) {
			if (isdigit(str[i + 1])) {
				temp = ((str[i] - '0') * 10) + (str[i + 1] - '0');
				i++;
			} else {
				temp = str[i] - '0';
			}
			switch (str[i + 2]) {
				case 'r':
					if (temp > 12) {
						return 0;
						}
					break;
				case 'g':
					if (temp > 13) {
						return 0;
						}
					break;
				case 'b':
					if (temp > 14) {
						return 0;
						}
					break;
				default:
					printf("Unexpected behaviour! (no matching color found)");
			}
		}
		i++;
	}
	return 1;
}
