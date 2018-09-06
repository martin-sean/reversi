#ifndef REVERSI_H
#define REVERSI_H

#include "game.h"

#define BUFFER_OVERFLOW '0'
#define START_GAME '1'
#define QUIT_GAME '2'
#define OTHER_OPTION -1

void printMenu();
void menu();
char getMenuInput();
void startGame();

#endif
