#include "header/utility.h"

/* Clears buffer and resets the error status of the stream. */
void readRestOfLine()
{
	int ch;
	while(ch = getc(stdin), ch != EOF && ch != '\n');
	clearerr(stdin);
}

/* Returns true if a new line character is found in a character array.
 * This is used for determining if buffer overflow has occured. */
Boolean searchNewLine(char string[], int arraySize)
{
	int i;
	for (i = 0; i < arraySize; i++)
	{
		/* If new line found, return true. */
		if (string[i] == '\n')
			return TRUE;
	}
	return FALSE;
} 

/* Replaces new line characters in a string with null terminators. 
 * This is used for removing '\n' before copying string to player name. */
void stripNewLine(char string[], int arraySize)
{
	int i;
	for (i = 0; i < arraySize; i++)
	{
		if (string[i] == '\n')
			string[i] = '\0';
	}
}

/* Replaces all characters in a string with null terminators.
 * Used for clearing junk data from a char array before use. */
void clearCharArray(char string[], int arraySize)
{
	int i;
	for (i = 0; i < arraySize; i++)
		string[i] = '\0';
}

/* Replaces all characters in an int array with 0's. Used for clearing junk
 * data from an int array before use. */
void clearIntArray(int array[], int arraySize)
{
	int i;
	for (i = 0; i < arraySize; i++)
		array[i] = 0;
}
