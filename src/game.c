#include "header/game.h"

/* Main game loop. Returns the winning player or NULL if draw. */
Player * playGame(Player * first, Player * second)
{
	/* Board array declared. */
	Cell board[BOARD_WIDTH][BOARD_HEIGHT];
	
	/* Pointers for keeping track of original player numbers. */
	Player * origFirst;
	Player * origSecond;

	/* Boolean variable for ending the game. */
	Boolean endGame = FALSE;
	
	/* Controls whether hints are printed on the board. */
	Boolean showHints = FALSE;
		
	/* Board initialized once. */
	initBoard(board);
	
	/* Initializes players. Ends the game if names are not entered. */
	if (!initFirstPlayer(first))
		return NULL;
	if (!initSecondPlayer(second, otherToken(first->token)))
		return NULL;
	
	/* Board is scanned and scores are set. */
	first->score = gameScore(board, first->token);
	second->score = gameScore(board, second->token);
	
	/* Player pointers are assigned to keep track of player numbers when
 	 * printing scores. ie. first player/second player. */
	origFirst = first;
	origSecond = second;

	/* Red goes first. If Player 1 is not red, Player 2 goes first. */
	if (first->token != RED)
		swapPlayers(&first, &second);

	printf(COLOUR_YELLOW "\nHints are disabled. Enter 'h' to toggle hints.\n"
	COLOUR_RESET);

	/* Checks for valid moves and sets HINT cells (displays all 
 	 * player's valid moves. */
	avaliableMove(board, first->token);
	
	/* Loops while the game hasn't ended. */
	while (!endGame)
	{
		/* Prints the board. Uses the fixed player pointers to ensure
 		 * player 1 is printed first, followed by player 2. */
		displayBoard(board, origFirst, origSecond, &showHints);
		
		/* Prints the current player's turn in the player's 
 		 * token colour. */
		printPlayerTurn(first);

		/* Makes move. If move is not made, game is ended. */
		if (!makeMove(first, board, origFirst,
		origSecond, &showHints))
			return NULL;

		/* Player scores are updated. */
		first->score = gameScore(board, first->token);
		second->score = gameScore(board, second->token);

		/* Ends the game if any player runs outs of tokens. */
		if (first->score == 0 || second->score == 0)
		{
			displayBoard(board, origFirst, origSecond, &showHints);	
			printf("No tokens left!\n");
			endGame = TRUE;
		}
		
		/* Ends the game if the board is full and the game hasn't
 		 * already been ended for another reason. */
		if (boardFull(board) && !endGame)
		{
			displayBoard(board, origFirst, origSecond, &showHints);
			printf("The board is full!\n");
			endGame = TRUE;
		}		

		/* Swaps the players allowing the players to take turns. */
		swapPlayers(&first, &second);

		/* Clears all hint cells from the board. */
		clearHints(board);
		
		/* Checks if there is no avaliable move for the next player
 		 * and that the game hasn't ended. The method avaliableMove sets 
 		 * new hint cells for next player's turn. */
		if (!avaliableMove(board, first->token) && !endGame)
		{	
			/* If valid move not found, player takes another turn. */
			printf("\nValid move not found. Take another turn.\n");
			swapPlayers(&first, &second);
			
			/* Hint cells are cleared from the board. */
			clearHints(board);

			/* Checks if there is an avaliable move for the 
 			 * current player. Sets new hint cells. */		
			if (!avaliableMove(board, first->token))
			{
				/* Displays the updated board. */
				displayBoard(board, origFirst,
				origSecond, &showHints);

				/* Ends the game if a stalemate occures. */
				printf("Valid move not found. Stalemate!\n");
				endGame = TRUE;
			}
		}
	}
	
	/* If the game has ended successfully, a winner is determined. */
	return getWinner(first, second);
}

/* Asks the player for move input. OrigFirst, origSecond and showHints are
 * used for re-printing the board under certain circumstances. */
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH],
Player * origFirst, Player * origSecond, Boolean * showHints)
{
	/* Store the players inputted coordinates. */
	int x, y;

	Boolean validInput = FALSE;

	/* Loops until a valid input is entered. */
	while(!validInput)
	{
		/* Gets the player's input. If no coordinates are
 		 * entered, the program quits. */
		if(!getCoordinates(&y, &x, board, player, origFirst, origSecond,
		showHints))
		{
			printf("\nNo coordinates were entered.\n");
			return FALSE;
		}
		
		/* Move is applied. An error is printed if the input
		 * is not valid indicating no tokens can be taken. */
		if (applyMove(board, y, x, player->token))
		{
			/* Cell at input coordinates is set to the
 			 * players token. */
			board[y][x] = player->token;
			validInput = TRUE;
		}
		else
			printf("Error: Invalid Move: No tokens could be"
			" captured.\n");
	}

	return TRUE;
}

/* Asks user for coordinates and validates input. */
Boolean getCoordinates(int * y, int * x, Cell board[BOARD_HEIGHT][BOARD_WIDTH],
Player * player, Player * origFirst, Player * origSecond, Boolean * showHints)
{
	/* Declares character array for storing move input. */		
	char move[MOVELEN + EXTRA_SPACES];	
	char * endptr;
		
	/* Loops until a valid move is made. */
	Boolean validMove = FALSE;
	while (!validMove)
	{
		/* Clear all data from input array. */
		clearCharArray(move, sizeof move);
		printf("\nEnter cordinates separated by a comma" 
		" (column,row): ");

		/* Reads input and stores in the char array move[].
		 * Exits if fgets returns NULL (ctrl+d entered). */
		if(fgets(move, MOVELEN + EXTRA_SPACES, stdin) == NULL)
		{
			printf("\n");
			return FALSE;
		}
			
		/* Exits if the user doesn't input anything. */
		if (move[0] == '\n')
			return FALSE;

		/* Searches for new line character to check for overflow. */
		if (!searchNewLine(move, sizeof move))
		{
			printf("Error: Buffer Overflow! Please only enter two"
			" numbers separated by a comma.\n");
			readRestOfLine();
		}
		/* Determines if a single 'h' is entered and toggles hints. */
		else if ((move[0] == 'h' || move[0] == 'H') && move[1] == '\n')
		{
			/* Variable showHints pointer dereferenced and is set
 			 * to its opposite. */
			*showHints = !(*showHints);
			
			/* Board is printed. */
			displayBoard(board, origFirst, origSecond, showHints);
			
			/* Current player's turn is printed. */
			printPlayerTurn(player);

			/* Displays message confirming showHints was changed. */
			printf(COLOUR_YELLOW "Hints were turned ");
			if (*showHints)
				printf("on.");
			else
				printf("off.");
			printf(COLOUR_RESET);
		}
		/* Checks that a comma is in the first index of move[]. */
		else if (move[COMMA_POSITION] != ',')
		{
			printf("Error: Invalid input, middle character was"
			" not a comma.\n");
		}
		else
		{
			/* Sets y to the value before the delimiter (",") and
 			 * sets x to the value after. The values are converted
 			 * to coordinates for the array by subtracting one. */
			*y = strtol(strtok(move, DELIMITER), &endptr, 10) - 1;
			*x = strtol(strtok(NULL, EMPTY_STRING), &endptr, 10) - 1;
			
			/* x or y will be -1 if a non-numeric character is
			 * entered. The program asks the user for input again. */
			if (*x == -1 || *y == -1)
			{
				printf("Error: Non numeric character was"
				" entered.\n");
				continue;
			}

			/* Ensures the coordinates are within the bounds of
			 * the board. */
			if(!validCell(*y, *x))
				printf("Error: Please only enter numbers between"
				" 1 and 8.\n");
			else
			/* Move is a valid coordinate */
				validMove = TRUE;
		}
	}
	return TRUE;
}

/* Validates the coordinates will capture opponents pieces and applys 
 * the move to the board. */
Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
int y, int x, Cell token)
{
	Boolean validMove = FALSE;
	
	/* If a move is valid, coordinates are added to cellsToChange[]
 	 * for updating the board. The index variable is the next blank 
 	 * space in the array to store the next set of coordinate to
 	 * change. */
	int i, j, index = 0;

	/* CellsToChange[] stores all coordinates that require updating
 	 * when a valid move is made. The first number is the column, the
 	 * second number is the row. Line[] is reused and stores the 
 	 * coordinates that require changing in a single direction from the
 	 * player's input. The data is discarded if no pieces can be captured
 	 * in that direction.
 	 *
 	 * Coordinates are stored as ints 1 - 8 to differentiate from null ('0')
 	 * characters in the array.
 	 *
 	 * (PLEASE SEE GAME.H FOR EXPLAINATION OF ARRAY SIZE DECLARATION. */
	int cellsToChange[BOARD_MAX], line[LINE_MAX];

	/* Arrays are set to NULL values to remove junk data. */
	clearIntArray(cellsToChange, BOARD_MAX);
	clearIntArray(line, LINE_MAX);
	
	/* Returns an error if the players input points to a cell containing a
 	 * token. Move is not valid. */
	if (!isBlank(y, x, board))
	{
		printf("Error: You can not place a token on another.\n");
		return FALSE;
	}

	/* Checks if tokens can be captured in any direction.
	 * i and j are directional constants and represent the 
	 * direction from the player's input.
  	 * ie. [-1,-1] = North West, [1,1] = South East. */
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			/* Clears line[] array between each direction */
			clearIntArray(line, LINE_MAX);
		
			/* Checks in a direction, if a token can be
 			 * captured, the move is valid. */
			if(checkDirection(y, x, i, j, board, token,
			cellsToChange, line, &index))
				validMove = TRUE;
		}	
	}
	
	/* For each pair of coordinates in cellsToChange[], the board is
	 * updated. */	
	for (i = 0; i < BOARD_MAX; i += 2)
	{
		/* Loop stops when there are no more coordinates. */
		if (cellsToChange[i] == 0)
			break;
	
		/* Board is updated. The first number in cellsToChange[]
 		 * is the column, the number directly after is the row.
 		 * 1 is subtracted from the numbers so the correct positions 
 		 * in the board array are updated. */
		board[cellsToChange[i] - 1]
		[cellsToChange[i + 1] - 1] = token;
	}
	return validMove;
}

/* Checks if a token can be captured in the specified direction. The integers
 * b and a are numbers between -1 and 1 that represent a direction away from
 * the users inputted coordinate. */
Boolean checkDirection(int y, int x, int b, int a,
Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token,
int cellsToChange[], int line[], int * index)
{
	/* x and y store the original coordinates and tmpX and tmpY are
 	 * updated and determine if the move captures tokens. Counter is
 	 * incremented when coordinates are added to line[] and keeps track
 	 * of the next empty index to write to. */
	int tmpX = x, tmpY = y, counter = 0;

	/* Move is not valid if the cell being checked in not on the board or
 	 * the cell is not an opponents token. */
	if (!validCell(y, x) && board[y + b][x + a] != otherToken(token))
		return FALSE;

	/* Loops until pieces are captured or the direction is found to be
 	 * invalid */
	while(TRUE)
	{
		/* Incrememnts to the next coordinates to check (The directional 
 		 * constants are added to the current coordinates). */
		tmpY += b;
		tmpX += a;
		
		/* Move is not valid if the cell is blank/hint or the
 		 * coordinates are not on the board. */
		if (board[tmpY][tmpX] == BLANK || board[tmpY][tmpX] == HINT ||
		!validCell(tmpY, tmpX))
			return FALSE;
		/* Checks if the token is the current player's */
		else if (board[tmpY][tmpX] == token)
		{
			/* Checks if it's not the first loop when b/a has only
 			 * been added once to tmpY/X and the current player's
 			 * piece is immediately adjacent to the input. */
			if (!(tmpY == y + b && tmpX == x + a))
			{
				/* The coordinates in line[] are copied to
 		 		 * cellsToChange[] so the board can be
 		 		 * updated. */
				copyCoordinates(line, cellsToChange, 
				LINE_MAX, index);
				
				return TRUE;
			}
			/* No tokens can be captured and the move is not
 			 * valid. */
			else
				return FALSE;
		}
		
		/* Checks if the number of cells to change is at the maximum
 		 * for a single direction. Prevents buffer overflow when
 		 * placing a token in a corner and counting seven opponents
 		 * tokens in a row (See reversi.h for further explaination). */
		if (counter == LINE_MAX)
			/* Skips adding coordinates to line[] since no pieces
 			 * can possibly be captured in this direction. */
			continue;
		
		/* If the next token is the opponents, the cell's
 		 * coordinates are added to line[]. 1 is added to the
 	 	 * values to differentiate from the 0's it is filled
 		 * with. */
		line[counter] = tmpY + 1;
		line[counter + 1] = tmpX + 1;

		/* Counter is increased by two since there are two numbers 
 		 * per set of coordinates that were stored in line[] */
		counter += 2;
	}
	
}

/* Checks if the cell at a set of coordinates is blank. */
Boolean isBlank(int y, int x, Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	/* Returns true if the cell is blank. */
	if (board[y][x] == BLANK || board[y][x] == HINT)
		return TRUE;
	return FALSE;
}

/* Checks if a set of coordinates lies in the range of the board. */
Boolean validCell(int y, int x)
{	
	/* Returns true if coordinates are in the range. */
	return y >= MIN_ROW && y <= MAX_ROW &&
	x >= MIN_COLUMN && x <= MAX_COLUMN;
}

/* Copies the coordinates from line[] to cellsToChange[]. Index keeps track
 * of the next empty space in line[] to copy to as tokens that are captured 
 * in each direction are added. */
void copyCoordinates(int line[], int cellsToChange[], int lineArraySize, 
int * index)
{
	int i;
	/* Loops through for each index in line[]. */
	for (i = 0; i < lineArraySize; i++)
	{
		/* Stops copying once 0 is reached (when there are no
 		 * more coordiantes. */
		if(line[i] == 0)
			break;
		/* Copies the coordinate from line[] to the the index of the
 		 * address index in pasteArray. */
		cellsToChange[*index] = line[i];
		(*index)++;
	}
}

/* avaliableMove, checkValidMove and checkValidDirection follow the same logic
 * as makeMove, applyMove and checkDirection respectively. I separated the
 * methods for easier understanding at the cost of file size. These methods
 * are used for checking if there are any moves for a player to make to allow
 * skipping of turns and handling stalemates. These methods do not apply
 * tokens to the board but do apply HINT cells. */

/* Returns true if there is any valid move for the current player. */
Boolean avaliableMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	int x, y;
	Boolean avaliableMove = FALSE;	
	
	/* Loops through board array. */
	for (y = 0; y < BOARD_HEIGHT; y++)
	{
		for (x = 0; x < BOARD_HEIGHT; x++)
		{
			/* If a cell is BLANK and the move is valid, the cell
 			 * is set to hint. */
			if ((board[y][x] == BLANK || board[y][x] == HINT) &&
			checkValidMove(board, y, x, token))
			{
				/* Cell is set to hint since there is an
 				 * avaliable move. */
				board[y][x] = HINT;
				avaliableMove = TRUE;
			}
		}
	}
	return avaliableMove;
}

/* Returns true for a coordinate that is a valid move for a token. */
Boolean checkValidMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x,
Cell token)
{
	/* Directional constants from the coordinate being checked. */
	int a, b;
	for (b = -1; b < 2; b++)
	{
		for (a = -1; a < 2; a++)
		{
			/* Returns true if tokens can be captured in any 
 			 * direction from the coordinate. */
			if(checkValidDirection(y, x, b, a, board, token))
				return TRUE;
		}	
	}
	return FALSE;
}

/* Checks if a direction from a coordinate captures any pieces. */
Boolean checkValidDirection(int y, int x, int b, int a,
Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	/* x and y are the original coordianate, tmpY, tmpX is a coordinate
 	 * in a straight line in a certain direction from y,x. */
	int tmpX = x, tmpY = y;
	
	/* Direction does not capture a piece if the coordinate is  not on the 
 	 * board or is not the other players token. */
	if (!validCell(y, x) && board[y + b][x + a] != otherToken(token))
		return FALSE;

	/* Loops until the move validity is determinued. */
	while(TRUE)
	{
		/* Looks at the next coordinate in the directon. */
		tmpY += b;
		tmpX += a;
		
		/* The direciton is not valid if the next coordinate is BLANK,
 		 * HINT or off the board. */
		if (board[tmpY][tmpX] == BLANK || board[tmpY][tmpX] == HINT ||
		!validCell(tmpY, tmpX))
			return FALSE;
		/* The move may be valid if the next token is the
 		 *  current players. */
		else if (board[tmpY][tmpX] == token)
		{
			/* The direction is valid as long as there is at least
 			 * one opponents token before reaching the current
 			 * players token. (ie. coordinate tmpY has been added
 			 * to b more than once. */
			if (!(tmpY == y + b && tmpX == x + a))
				return TRUE;
			/* If tmpY and tmpX have only been increased once,
 			 * this means the adjacent token is the current players
 			 * and the direction is not valid. */
			else 
				return FALSE;
		}
	}
}

/* Returns the number of the specified token on the board. */
unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token)
{
	int i, j;
	unsigned int score = 0;

	/* Loops through every index of the board array. */
	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			/* If the cell is the specified token,
 			 * score is increased. */
			if (board[i][j] == token)
				score++;
		}
	}
	return score;
}

/* Swaps the player struc pointers allowing turns to occur. */
void swapPlayers(Player ** first, Player ** second)
{
	/* Temporary pointer created to store the address of first. */
	Player * tmp = *first;
	/* The address of first is set to the address of second. */
	*first = *second;
	/* The address of second is set to the address of first
 	 * that was stored in the pointed tmp. */
	*second = tmp;
}

/* Determines winner from scores. */
Player * getWinner(Player * first, Player * second)
{
	/* Player 1 wins when score is greater. */
	if (first->score > second->score)
		return first;
	/* Player 2 wins when score is greater. */
	else if (first->score < second->score)
		return second;
	/* Game is a draw if scores are equal. */
	else
		return NULL;
}
