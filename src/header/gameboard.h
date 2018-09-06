#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "player.h"

#define BOARD_HEIGHT 8
#define BOARD_WIDTH BOARD_HEIGHT

/* Define the boundries of the board for validation. */
#define MIN_COLUMN 0
#define MAX_COLUMN 7
#define MIN_ROW MIN_COLUMN
#define MAX_ROW MAX_COLUMN

/* Define lengths of graphical lines */
#define LONG_LINE 36

void initBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], 
Player * first, Player * second, Boolean * showHints);

void displayDetails(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
Player * first, Player * second);
void displayPlayerDetails(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player);
void printChar(char charToPrint, int timesToPrint, Boolean newLine);

Boolean boardFull(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);
void clearHints(Cell board[BOARD_HEIGHT][BOARD_WIDTH]);

#endif
