#ifndef PLAYER_H
#define PLAYER_H

#include "utility.h"

/* Hint cell was added to show possble moves for each player.
 * It is treated as a blank cell for most methods. */
typedef enum cell
{
    BLANK, RED, CYAN, HINT
} Cell;

/* Color codes required to display the tokens on the board. */
#define COLOUR_RED    "\33[31m"
#define COLOUR_CYAN   "\33[36m"
#define COLOUR_RESET  "\33[0m"
#define COLOUR_YELLOW "\33[33m"


/* The maximum length of a player name. */
#define NAMELEN 20

typedef struct player
{
    char name[NAMELEN + NULL_SPACE];
    Cell token;
    unsigned score;
} Player;

Boolean initFirstPlayer(Player * player);
Boolean initSecondPlayer(Player * player, Cell token);
Boolean getPlayerName(Player * player, int playerNumer);

void copyArray(char input[], char output[], int outputArraySize);
void printPlayerTurn(Player * player);
void printTokenColour(Cell token);

Cell otherToken(Cell token);

#endif
