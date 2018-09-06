/* SKELETON CODE PROVIDED BY RMIT UNIVERSITY. */
#include "header/reversi.h"

/* Main method */
int main(void)
{
	menu();
	printf("Goodbye. \n\n");
	return EXIT_SUCCESS;
}

/* Main menu. */
void menu()
{
	/* Stores user's input. */
	char input;

	/* Menu runs when input is not valid and game hasn't ended. */
	Boolean endGame = FALSE;
	Boolean validInput = FALSE;
	while(!validInput || !endGame) {
		
		/* Prints menu. */
		printMenu();
		
		/* Gets user input. */
		input = getMenuInput();
		printf("\n");
		
		/* Starts game. */
		if (input == START_GAME)
		{
			startGame();
			validInput = TRUE;
		}
		/* Ends game. */
		else if (input == QUIT_GAME)
		{
			endGame = TRUE;
			validInput = TRUE;
		}
		/* If getMenuInput() returns 0, buffer overflow has occured. */
		else if (input == BUFFER_OVERFLOW)
			printf("Error: Buffer Overflow! Enter a "
			"valid option.\n");
		/* Valid input is not set to true if the user enters
		 * something else. */
		else
			printf("Error: Enter a valid option.\n");
	}
}

/* Prints the menu. */
void printMenu()
{
	printf("\nWelcome to Reversi!\n"
	"==================\n"
	"Select an Option:\n"
	"1. Play a game\n"
	"2. Quit the program\n"
	"Please enter your choice: ");
}

/* Gets users selection for stating/quiting the game. */
char getMenuInput()
{
	/* Declares character array for storing menu selection */
	char input[INPUTLEN + EXTRA_SPACES];

	/* Gets input and stores in char array input[]
 	 * Returns -1 if fgets returns NULL. */
	if(fgets(input, INPUTLEN + EXTRA_SPACES, stdin) == NULL)
	{	
		printf("\n");
		return OTHER_OPTION;
	}

	/* Returns character inputted. Checks for buffer overflow. */	
	if (searchNewLine(input, sizeof input))
		 return input[0];
	else
	{
		/* Clears the buffer when new line not found. */
		readRestOfLine();
		return BUFFER_OVERFLOW;
	}
}

/* Starts the game. */
void startGame()
{
	/* Creates the player structures. */
	Player first;
	Player second;
	
	/* Begins the gameloop. playGame() returns a pointer to the winner. */
	Player * winner = playGame(&first, &second);
	
	/* The game is a draw if no winner is returned, otherwise
	 * the winner is printed. */
	if (winner == NULL)
		printf("\nThe game was a draw.\n");
	else
	{
		printTokenColour(winner->token);
		printf("\n%s%s%s\n", "The winner is ", winner->name, 
		"." COLOUR_RESET);
		
	}
}
