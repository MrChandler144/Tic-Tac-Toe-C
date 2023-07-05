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

// tic tac toe but it's one player and the AI starts
// AI makes random moves
// no secret square ten

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
	
	// set the reference depending on the player
	if (player%2 == 1)
	{
		ref='X';
	} else {
		ref='O';
	}
	
	// check rows
	for (i=0; i<3; i++)
	{
		// count number of valid symbols
		for (j=0; j<3; j++)
		{
			if (ref == smolgrid[i][j])
			{
				count++;
			}
		}
		// and act on that
		if (count==3)
		{
			// a winning row for the player
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
	
	// check diagonals
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
	
	// no winners, return 2
	return 2;
}

int askMoveOrder(void)
{
	char response[5] = "  ";
	scanf("%s", &response);
	if (response[0] == '1' && response[1] == '\0')
	{
		// human goes first
		return 0;
	}
	else if (response[0] == '2' && response[1] == '\0')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int main(void)
{
	srand((int)time(NULL));
	
	char values[99] = "1|2|3\n-+-+-\n4|5|6\n-+-+-\n7|8|9\n  ";
	char move[99] = "  ";
	
	int i;
	int iref = 0;
	int numTurns = 0;
	int validq = 0;
	int gameState;
	int moveInt;
	int player;
	
	// humans play on even numbered moves (counted by the 'player' variable)
	
	// ask for if you want to go second or first
	printf("Would you like to play first (1) or second (2)?\n");
	while (validq != 1)
	{
		player = askMoveOrder();
		if (player == 2)
		{
			validq=0;
		} else {
			validq=1;
		}
	}
	validq=0;
	
	while (numTurns < 9)
	{
		// display the move
		printf("\n%s\n", values);
		
		if (player%2==0)	// human player
		{
			// take in the move and process it
			while (validq!=1)
			{
				// take in a move
				printf("Which square do you want? ");
				scanf("%s", &move);
		
				// process the move
					// is it valid?
						// yes --> put it in array
						// no --> try again
			
				// is it in the array (if we can find it then it hasn't been guessed yet)
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
			}
		}
		else				// computer move
		{
			//it can move randomly for now
			
			validq=0;
			while (validq!=1)
			{
				moveInt = (rand()%9) + 1;
				
				sprintf(move, "%d", moveInt);
				
				// is it like in the array
				for (i=0; i<31; i++)
				{
					if (move[0]==values[i])
					{
						validq=1;
						iref=i;
					}
				}
			}
			
			// all good
			
			printf("Computer playing square %c\n", move[0]);
		}
		
		// so now we have a valid move
		// play it on the board
		
		if ((player%2)==1)
		{
			values[iref] = 'X';
		}
		else
		{
			//player 2
			values[iref] = 'O';
		}
		
		// check for a win
			// when yes, make the numTurns big
			// if no, set up for the next move
		
		gameState = checkWin(values, player);
		if (gameState == 1)
		{
			// ai win
			numTurns=101;
		} else if (gameState==0)
		{
			// human win
			numTurns=102;
		} else if (numTurns==8)
		{	
			// draw
			numTurns=103;
		} else
		{
			// change player, reset for next round, etc...
			validq = 0;
			player++;
			numTurns++;
			// beware that numTurns is increased here
		}
	}
	
	// game has been won or drawn
	
	// print the board
	printf("\n%s\n", values);
	// and final message
	if (numTurns==101)
	{
		printf("the ai won. maybe you need to hit the books a bit");
	}
	if (numTurns==102)
	{
		printf("hmm maybe the AI revolution is still a few ways away yet");
	}
	if (numTurns==103)
	{
		printf("noone won. y'all drew. make it more exciting next time please");
	}
	
	
	return 0;
}