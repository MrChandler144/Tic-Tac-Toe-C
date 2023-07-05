#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

/*
	1|2|3
	-+-+-
	4|5|6
	-+-+-
	7|8|9
	*/

int checkWin(char *values, int player)
{
	// condense the 5x5 into a 3x3
	char smolgrid[3][3];
	int i, j;
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			smolgrid[i][j]=values[12*i+2*j];
		}
	}
	
	// so now we have the grid
	// we have to check the three rows, three columns, and two diagonals for a win
	
	char ref;
	int count = 0;
	
	// set the refernece depending on the player
	if (player%2 == 1)
	{
		ref='X';
	} else {
		ref='O';
	}
	
	// check rows
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (ref == smolgrid[i][j])
			{
				count++;
			}
		}
		if (count==3)
		{
			// a winning row for player 1
			return player%2;
		} else {
			// no match
			count=0;
		}
	}
	
	// check columns
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (ref == smolgrid[j][i])
			{
				count++;
			}
		}
		if (count==3)
		{
			// a winning row for player 1
			return player%2;
		} else {
			// no match
			count=0;
		}
	}
	
	// check diagonals I guess
	// \ diagonal
	if ((smolgrid[0][0]==ref) && (smolgrid[1][1]==smolgrid[0][0]) && (smolgrid[2][2]==smolgrid[1][1]))
	{
		return player%2;
	}
	// / diagonal
	if ((smolgrid[0][2]==ref) && (smolgrid[1][1]==smolgrid[0][2]) && (smolgrid[2][0]==smolgrid[1][1]))
	{
		return player%2;
	}
	
	// and check square ten
	// 8 9 10
	if ((smolgrid[2][1]==ref) && (smolgrid[2][2]==ref) && (values[30]==ref))
	{
		return player%2;
	}
	// 2 6 10
	if ((smolgrid[0][1]==ref) && (smolgrid[1][2]==ref) && (values[30]==ref))
	{
		return player%2;
	}
	
	// if you get here there are no winners, return 2
	return 2;
}

int main(void)
{
	char values[99] =
	"1|2|3\n"
	"-+-+-\n"
	"4|5|6\n"
	"-+-+-\n"
	"7|8|9   \n";
	
	int i;
	int iref = 0;
	int numTurns = 0;
	int validq = 0;
	int player = 1;
	int wasTenPlayed=0;
	int gameState;
	
	while (numTurns < 20)	// when a win/draw condition is hit we artificially increase numTurns over this limit
	{
		// display the move
		printf("\n%s\n", values);
		
		// take in the move and process it
		while (validq!=1)
		{
			// take in a move
			char move[1998];
			printf("Which square do you want? ");
			scanf("%s", &move);
		
			// process the move
				// is it valid?
					// yes --> put it in array
					// no --> try again
			// surely I just check through to see if there's a similar tile
			
			// is it like in the array
			for (i=0; i<31; i++)
			{
				if (move[0]==values[i])
				{
					validq=1;
					iref=i;
				}
			}
			
			// make sure it's a digit that has been sent through, otherwise could overwrite non-digits
			if (!(move[0] >='1' && move[0]<='9'))
			{
				// not valid
				validq=0;
			}
			
			// is it ten
			if ((move[0]=='1') && (move[1]=='0') && (move[2]=='\0'))
			{
				wasTenPlayed=1;
				iref=30;
				values[29]='|';
				if (values[30]==' ')
				{
					// we haven't placed a ten yet, this is a valid move
					validq=1;
				}
			}
		}
		
		// so now we have a valid move
		// replace it
		if ((player%2)==1)
		{
			values[iref] = 'X';
		} else {
			//player 2
			values[iref] = 'O';
		}
		
		// check for a win
			// when yes, make the numTurns big
			// and we can handle the celebrations after this loop
		
		gameState = checkWin(values, player);
		if (gameState == 1)
		{
			// player 1 win
			numTurns=101;
		} else if (gameState==0)
		{
			// player 2 win
			numTurns=102;
		} else if (numTurns==8+wasTenPlayed)
		{	
			// draw
			numTurns=103;
		}
		
		// change player, reset for next round
		player++;
		numTurns++;
		validq = 0;
		// beware that numTurns is increased here
	}
	
	// undo the final increase in numTurns before exiting the while loop
	numTurns=numTurns-1;
	
	// game has been won or drawn
	// act accordingly
	
	// print the board
	printf("\n%s\n", values);
	if (numTurns==101)
	{
		printf("player 1 won nice work bro");
	}
	if (numTurns==102)
	{
		printf("player 2 won nice work bro");
	}
	if (numTurns==103)
	{
		printf("noone won. y'all drew. make it more exciting next time please");
	}
	
	return 0;
}