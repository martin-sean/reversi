#include "header/gameboard.h"

/* Runs at the start of each game to set up the board. */
void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i, j;

	/* All cells in board[][] are set to BLANK. */
	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
			board[i][j] = BLANK;
	}

	/* Center squares are set to tokens. */
	board[3][3] = RED;
	board[4][4] = RED;
	board[3][4] = CYAN;
	board[4][3] = CYAN;
}

/* Prints the supplied character the specified amount of times. */
void printChar(char charToPrint, int timesToPrint, Boolean newLine)
{
	int i;

	/* Prints character. */
	for (i = 0; i < timesToPrint; i++)
		printf("%c", charToPrint);

	/* Prints a new line if specifed in the parameters. */
	if (newLine)
		printf("\n");
}

/* Displays the information of the players before the board it printed. */
void displayDetails(Cell board[BOARD_HEIGHT][BOARD_WIDTH], 
Player * first, Player * second)
{
	printf("\n");
	printChar('=', LONG_LINE, TRUE);

	/* Prints first player's details. */	
	printf("Player One's Details\n");
	displayPlayerDetails(board, first);
	
	/* Prints second player's details. */
	printf("Player Two's Details\n");
	displayPlayerDetails(board, second);
}

/* Displays the information of the specified player. */
void displayPlayerDetails(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
	printChar('-', LONG_LINE, TRUE);

	/* Prints player's name. */
	printf("%s%s\n","Name: ", player->name);

	/* Prints player's score. */
	printf("%s%d\n", "Score: ", player->score);
	
	/* Prints player's coloured token. */
	printf("Token: ");
	printTokenColour(player->token);
	printf("%c%s\n", 'O', COLOUR_RESET);

	printChar('-', LONG_LINE, TRUE);
}

/* Prints the board. */
void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
Player * first, Player * second, Boolean * showHints)
{
	int i, j;
	
	/* Displays players details. */
	displayDetails(board, first, second);
	
	/* Prints horizontal board bar and column numbers. */
	printChar(' ', 5, FALSE);
	for (i = 1; i < 9; i++)
		printf("%d%s", i, "   ");
	printf("\n");
	printChar('=', LONG_LINE, TRUE);
	
	/* Prints board row by row. */
	for (i = 0; i < BOARD_HEIGHT; i++)
	{	
		/* Prints the vertical row numbers. */
		printf(" ");
		printf("%d", i + 1);
		printf(" |");
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			/* Prints token contained in each cell. */
			if (board[j][i] == BLANK)
				printf("  ");
			else if (board[j][i] == HINT)
			{
				/* If showHints is set to TRUE, hint tokens 
 				 * are printed, otherwise a blank space
 				 * is displayed. */
				if (*showHints)
					printf(COLOUR_YELLOW " ?" COLOUR_RESET);
				else
					printf("  ");
			}
			else if (board[j][i] == RED)
				printf(COLOUR_RED " O" COLOUR_RESET);
			else
				printf(COLOUR_CYAN " O" COLOUR_RESET);
			printf(" |");
		}
		printf("\n");
		
		/* Prints the row lines. Prints a double line at the end. */
		if (i != BOARD_HEIGHT - 1)
			printChar('-', LONG_LINE, TRUE);
		else
			printChar('=', LONG_LINE, TRUE);
	}
}

/* Returns TRUE if the board is full. */
Boolean boardFull(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i, j;

	/* Checks each cell in board[][]. */
	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			/* If any blank/hint cell is found, the board 
 			 * is not full. */
			if (board[i][j] == BLANK || board[i][j] == HINT)
				return FALSE;
		}	
	}
	return TRUE;
}

/* Sets all hint cells on the board to blank. */
void clearHints(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i, j;
	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			/* If cell is HINT, it is set to BLANK. */
			if (board[i][j] == HINT)
				board[i][j] = BLANK;
		}
	}
}
