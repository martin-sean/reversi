#ifndef GAME_H
#define GAME_H

#include "gameboard.h"

/* Defines the maximum number of coordinates that can be changed
 * when a token is placed. This program keeps track of tokens to be changed
 * by storing the coordinates as integers in an array. */
#define LINE_MAX 12
#define BOARD_MAX LINE_MAX + LINE_MAX + LINE_MAX
/* Line Max Explained:
 *  - A valid move must have a friendly token at the end of a line.
 *  - An space must be avaliable for a token to be placed
 *  - The maximum straight line on a board is 8 cells. 8 - 1 - 1 = 6
 *  - Therefore, at most, 6 tokens can be captured in a single line. 
 *  - 2 coordinates per cell. 2 * 6 = 12 coordinates.
 *  - Therefore, an array of size 12 is required for each line to
 *    hold the information for 6 board cell changes
 *
 * Board Max explained:
 *  - To maximise the number of token captures, same player tokens need
 *    to be minimised. A capture in the middle of the board requires tokens
 *    on each side for valid captures. Maximum token captures occurs when
 *    a token is placed in a corner.
 *  - eg. Top left corner.
 *  	- Same player tokens in top right, bottom left, bottom right.
 *  	- up to 3 lines of capture pathways (EAST, SOUTH EAST, SOUTH)
 *	- 3 * LINE_MAX = A maximum of 36 coordinates required to store
 *	  this information. */

Player * playGame(Player * first, Player * second);
Boolean makeMove(Player * player, Cell board[BOARD_HEIGHT][BOARD_WIDTH],
	Player * origFirst, Player * origSecond, Boolean * showHints);
Boolean getCoordinates(int * y, int * x, Cell board[BOARD_HEIGHT][BOARD_WIDTH],
	Player * first, Player * origFirst, Player * origSecond,
	Boolean * showHints);
Boolean applyMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
	int y, int x, Cell token);
Boolean checkDirection(int y, int x, int b, int a,
	Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token, 
	int cellsToChange[], int line[], int * index);

Boolean isBlank(int y, int x, Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
Boolean validCell(int y, int x);
void copyCoordinates(int line[], int cellsToChange[], int lineArraySize, 
	int * index);

Boolean avaliableMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token);
Boolean checkValidMove(Cell board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x,
	Cell token);
Boolean checkValidDirection(int y, int x, int i, int j,
	Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token);

unsigned gameScore(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Cell token);
void swapPlayers(Player ** first, Player ** second);
Player * getWinner(Player * first, Player * second);

#endif
