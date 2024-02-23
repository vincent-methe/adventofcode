#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int no_nodes = 702;

int scan(char str[], char arr[][3][3], int x);
int process_instructions(char str[], char arr[][3][3], int *current, int *steps);
int find_node(char arr[][3][3], int current, int side);
int is_zzz(char arr[][3][3], int current);
int find_aaa(char arr[][3][3]);

int main()
{
	char instructions[512];

	char nodes[no_nodes][3][3];

	// start reading the file

	FILE *fptr = fopen("input", "r");

	if (fptr == NULL)
	{
		printf("An error occured opening the file!\n");

		return 1;
	}
	else
	{
		char buffer[512];

		int id = 0;
		
		// copy the first string of the file to the instructions string

		fgets(buffer, sizeof(buffer), fptr);
		strcpy(instructions, buffer);

		// skip the second line

		fgets(buffer, sizeof(buffer), fptr);

		// since all other lines contain nodes, convert them using scan

		while (fgets(buffer, sizeof(buffer), fptr))
		{
			scan(buffer, nodes, id);
			id++;
		}
	}

	fclose(fptr);
	
	// process the data starting at 'AAA'
		
	int current_node = find_aaa(nodes);
	int steps = 0;

	// repeat the instructions until 'ZZZ' is reached

	while(process_instructions(instructions, nodes, &current_node, &steps));

	printf("It took %d steps!\n", steps);

	return 0;
}

// scan is used to fill a three dimensional array using lines that contain nodes

int scan(char str[], char arr[][3][3], int x)
{
	// x is the line, y the triplet and z the according character

	int i = 0;

	int y = 0;
	
	while (str[i] != '\n' && str[i] != '\0')
	{
		int z = 0;

		while (isalpha(str[i]))
		{
			arr[x][y][z] = str[i];
			z++;
			i++;
		}
		
		if (str[i] == '=' || str[i] == ',')
			y++;

		i++;
	}
}

// process_instructions goes through the steps stored in a string until the current node is 'ZZZ'

int process_instructions(char str[], char arr[][3][3], int *current, int *steps)
{
	int i = 0;

	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] == 'L')
		{
			*current = find_node(arr, *current, 1);
		}
		else if (str[i] == 'R')
		{
			*current = find_node(arr, *current, 2);
		}
		else
		{
			printf("Input error! Expected 'L' or 'R'!\n");

			return 0;
		}

		(*steps)++;
		
		if (is_zzz(arr, *current))
			return 0;

		i++;
	}
	
	return 1;
}

// find_node returns the index of the node that is found on either the left or right side of the current node

int find_node(char arr[][3][3], int current, int side)
{
	for (int i = 0; i < no_nodes; i++)
	{
		if (arr[i][0][0] == arr[current][side][0] && arr[i][0][1] == arr[current][side][1] && arr[i][0][2] == arr[current][side][2])
		{
			return i;
		}
	}

	printf("Error: did not find a matching node. Returning 0!\n");

	return 0;
}

// is_zzz checks if the current node is 'ZZZ'

int is_zzz(char arr[][3][3], int current)
{
	if (arr[current][0][0] == 'Z' && arr[current][0][1] == 'Z' && arr[current][0][2] == 'Z')
		return 1;
	else
		return 0;
}

// find_aaa returns the index of the node for 'AAA'

int find_aaa(char arr[][3][3])
{
	for (int i = 0; i < no_nodes; i++)
	{
		if (arr[i][0][0] == 'A' && arr[i][0][1] == 'A' && arr[i][0][2] == 'A')
			return i;
		
		i++;
	}

	printf("Error: Did not find 'AAA'!\n");

	return 0;
}
