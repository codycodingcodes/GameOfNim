// GameOfNim.cpp :
// 2 players
// A pile of marbles of size between 10-100
// random generated # to determine intelligence of bot
// 
// smart mode: computer takes enough marbles to make size of pile a power of 2
// 2^n - 1  : 2^2-1 = 3 ; 2^3-1 = 7 ; 2^4-1 = 15 ; 2^5-1 = 31 ... ;
// 
// stupid mode: computer takes a random value of marbles between 1 and pilesize/2
// 
// 3.14.2021
// Cody McKinney
//

#include <iostream>
#include <cstdlib>
#include <time.h>

#define MAX 100
#define MIN 10

using namespace std;

/*
* humanTurn() - takes the pile as input and outputs the amount of marbles taken from the pile
*			    after user input
*			  = returns user input amount taken
*/
int humanTurn(int pile)
{
	int take;
	cout << "\n  Player's Turn " << endl;
	cout << "------------------" << endl;

	if (pile > 1)
	{
		cout << "How many marbles do you wish to take? (between 1 - " << pile / 2 << ") ";
		cin >> take;
	
		while (take <=0 || take > pile / 2)
		{
			cout << "Not a valid amount to take. Please re enter value: ";
			cin >> take;
		}
	}
	else
	{
		cout << "Only 1 marble left. You lose.\n";
		take = 1;
	}
	

	return take;
}

/*
* skill() - randomly generates a 0 or 1 to determine computers skill
*			smart or stupid
*		  = returns 0 or 1
*/
int skill()
{
	srand(time(NULL));
	int difficulty = rand() % 2;
	if (difficulty == 0)
	{
		cout << "Computer is playing in stupid mode." << endl;
	}
	else
	{
		cout << "Computer is playing in smart mode." << endl;
	}
	cout << "Computer Difficulty: " << difficulty << "\n\n";

	return difficulty;
}

/*
* computerTurn() - takes difficulty and pile as input
*				   if difficulty is 0, computer randomly selects an amount to take
*				   if difficulty is 1, computer makes size of the pile a power of 2 minus 1
*				 = returns value of generated computer selection
*/
int computerTurn(int difficulty, int pile)
{
	int newPile = 0;
	int take = 0;

	cout << "\n  Computer's Turn" << endl;
	cout << "-------------------" << endl;
	if (difficulty == 0 && pile != 1)
	{
		// stupid mode - computer picks random legal number
		srand(time(NULL));
		take = rand() % (pile / 2) + 1;
	}
	if (difficulty == 1 && pile != 1)
	{
		// smart mode - computer picks value to make the pile a power of 2 minus 1
		if (pile >= 64)
		{
			newPile = 63; // 2^6 - 1
		}
		if (pile >= 32 && pile <= 63)
		{
			newPile = 31; // 2^5 - 1
		}
		if (pile >= 16 && pile <= 31)
		{
			newPile = 15; // 2^4 - 1
		}
		if (pile >= 8 && pile <= 15)
		{
			newPile = 7; // 2^3 - 1
		}
		if (pile >= 4 && pile <= 7)
		{
			newPile = 3; // 2^2 - 1
		}
		if (pile == 2)
		{
			newPile = 1;
		}

		take = pile - newPile;
		if (take > pile / 2)
		{
			srand(time(NULL));
			take = rand() % (pile / 2) + 1;
		}
	}
	if (pile == 1)
	{
		take = 1;
	}

	return take;
}

/*
* playGame() - takes a turn, difficulty, and pile integer to process the game
*			   this is the main game function
*			   turn chooses who goes first, difficulty chooses computer mode, pile is size of the stack
*/
void playGame(int turn, int difficulty, int pile)
{
	int take;

	// if turn = 0 the User goes first
	if (turn == 0)
	{
		while (pile != 0)
		{
			take = humanTurn(pile); // user takes this many marbles
			cout << "User takes: " << take << endl; 
			pile = pile - take; // new size of pile after turn
			cout << "\nNew pile size after user turn: " << pile << "\n\n";

			if (pile == 0) // player took the last marble and therefore loses
			{
				cout << "\n\nCOMPUTER IS THE WINNER!\n\n";
				break;
			}

			take = computerTurn(difficulty, pile); // computer takes this many marbles
			cout << "Computer takes: " << take << endl;
			pile = pile - take;
			cout << "\nNew pile size after computer turn: " << pile << endl;

			if (pile == 0) // computer took the last marble and therefore loses
			{
				cout << "\n\nPLAYER IS THE WINNER!\n\n";
				break;
			}
		}
	}

	// if turn = 1 the Computer goes first
	if (turn == 1)
	{
		while (pile != 0)
		{
			take = computerTurn(difficulty, pile);
			cout << "Computer takes: " << take << endl;
			pile = pile - take;
			cout << "\nNew pile size after computer turn: " << pile << endl;

			if (pile == 0)
			{
				cout << "\n\nPLAYER IS THE WINNER!\n\n";
				break;
			}

			take = humanTurn(pile);
			cout << "User takes: " << take << endl;
			pile = pile - take;
			cout << "\nNew pile size after user turn: " << pile << "\n\n";

			if (pile == 0)
			{
				cout << "\n\nCOMPUTER IS THE WINNER!\n\n";
				break;
			}
		}
	}
}

int main()
{

	cout << "          The Game of Nim." << endl;
	cout << "Two players alternately take marbles from a pile." << endl;
	cout << "In each move, a player chooses how many marbles to take." << endl;
	cout << "The player must take at least one but at most half of the marbles." << endl;
	cout << "Then the other player takes a turn. The player who takes the last marble loses.\n" << endl;

	// randomize digits for pile size
	srand(time(NULL));
	int pile = rand() % (MAX - MIN + 1) + MIN;
	cout << "Starting Marbles: " << pile << endl;

	int difficulty = skill();

	// randomize digits for who starts first: 0 for User, 1 for Computer
	int turn = rand() % 2;
	if (turn == 0)
	{
		cout << "User goes first!" << endl;
	}
	else
	{
		cout << "Computer goes first!" << endl;
	}

	playGame(turn, difficulty, pile);

	system("pause");
	return 0;
}
