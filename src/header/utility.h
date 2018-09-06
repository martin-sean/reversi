#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <assert.h>

/* Boolean definition. */
typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

/* Defines extra spaces for '\0' and '\n' outputted by fgets(). */
#define NEW_LINE_SPACE 1
#define NULL_SPACE 1
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

/* Characters surrounding coordinates from player input. */
#define DELIMITER ","
#define EMPTY_STRING ""

/* The input length of menu selection. */
#define INPUTLEN 1
#define MOVELEN 3
#define COMMA_POSITION 1
 
void readRestOfLine();
Boolean searchNewLine(char string[], int arraySize);
void stripNewLine(char string[], int arraySize);
void clearCharArray(char string[], int arraySize);
void clearIntArray(int array[], int arraySize);

#endif
