#include <stdio.h>

int cards_on_hand = 5;

enum CardType
{
	FIVE_OF_A_KIND,
	FOUR_OF_A_KIND,
	FULL_HOUSE,
	THREE_OF_A_KIND,
	TWO_PAIR,
	PAIR,
	HIGH_CARD
};

struct Hand
{
	// the cards per hand has to be set manually in this instance

	char card[5];
	int bid;
	int rank;
	enum CardType type;
};

int determine_type(char str[]);

int main()
{
	// open the file for reading

	FILE *fptr = fopen("test", "r");

	if (fptr == NULL)
	{
		printf("An error occured while opening file!\n");
	}
	else
	{
		// scan every line of the file

		char buffer[256];
		while (fgets(buffer, sizeof(buffer), fptr))
		{
			printf("%s", buffer);
		}
	}

	fclose(fptr);

	return 0;
}
