#include "header/player.h"

/* Initializes the structure of the first player.
 * Return type was changed to allow for exiting the method when a player
 * name is not entered. */
Boolean initFirstPlayer(Player * player)
{	
	/* Creates an integer for random number generation */
	int random;

	/* Sets the player's score. */
	player->score = 0;
	
	/* Seeds rand() based on time for random number generation. */
	srand(time(NULL));

	/* Generates a random number. If even, random = 0.
 	 * If odd, random = 1. */
	random = rand() % 2;
	
	/* Sets the players token. */
	if (random == 0)
		player->token = RED;
	else
		player->token = CYAN;

	/* Gets player name input. Returns false if no name is inputted. */
	if (!getPlayerName(player, 1))
		return FALSE;
	return TRUE;
}

/* Initializes the structure of the second player.
 * Return type was changed to allow for handling when names are not entered. */
Boolean initSecondPlayer(Player * player, Cell token)
{
	/* Score is set. */
	player->score = 0;

	/* Token is set from parameter. */
	player->token = token;

	/* Gets name input. Returns false if no name is inputted. */
	if (!getPlayerName(player, 2))
		return FALSE;
	return TRUE;
}

/* Gets the player's name. Returns false if no name is inputted. */
Boolean getPlayerName(Player * player, int playerNumber)
{
	/* Creates a char array for storing the name input. */
	char name[NAMELEN + EXTRA_SPACES]; 
	
	/* Loops until a valid name is inputted. */
	Boolean validInput = FALSE;
	while (!validInput)
	{
		/* Initializes the array for storing the name by setting
 		 * all indexes to '\0'. */
		clearCharArray(name, sizeof name);
		
		/* Displays the colour of the first player's token. */
		printTokenColour(player->token);
		printf("%s%d%s", "Enter Player ", playerNumber, " Name: ");
		printf(COLOUR_RESET);
		
		/* Returns false if fgets returns NULL (ctrl+d). Gets
 		 * the player's name. */
		if(fgets(name, NAMELEN + EXTRA_SPACES, stdin) == NULL)
		{	
			printf("\nNo name was entered, returning to menu.\n");
			return FALSE;
		}
		
		/* Checks if player did not enter a name. */
		if (name[0] == '\n')
		{
			printf("\nNo name was entered, returning to menu.\n");
			return FALSE;
		}	
		
		/* Searches for '\n' indicating valid input.
 		 * Checks for buffer overflow. */
		if (searchNewLine(name, sizeof name))
		{
			/* Removes new line character from name[] so it fits
 			 * in the player structure. */
			stripNewLine(name, sizeof name);
			
			/* Copies input name to player struct. */
			copyArray(name, player->name, sizeof player->name);
			validInput = TRUE;
		}
		else
		{
			/* Clears the buffer when new line not found. */
			printf("Error! Buffer Overflow. Please enter a name");
			printf(" less than 20 characters\n");
			readRestOfLine();
		}
	}
	return TRUE;
}

/* Copies characters between char arrays. Used for copying player name to
 * struct after new line char is removed. */
void copyArray(char input[], char output[], int outputArraySize)
{
	int i;
	for (i = 0; i < outputArraySize; i++)
		output[i] = input[i];
}

/* Returns token of other colour. */
Cell otherToken(Cell token)
{
	if (token == CYAN)
		return RED;
	else
		return CYAN;	
}

/* Prints the current player's turn. */
void printPlayerTurn(Player * player)
{
	/* Prints the current player's token colour. */
	printTokenColour(player->token);	
		
	/* Prints the current player's turn. */
	printf("%s%s", "It's ", player->name);
	printf("%s%s","'s turn.\n", COLOUR_RESET);
}

/* Prints the string colour of the supplied token parameter. */
void printTokenColour(Cell token)
{
	if (token == CYAN)
		printf(COLOUR_CYAN);
	else
		printf(COLOUR_RED);
}	
