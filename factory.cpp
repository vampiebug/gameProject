#include "factory.hpp"
#include "consoledraw.hpp"
#include "guess.hpp"
#include "tictactoe.hpp"
#include "hangman.hpp"
#include "mastermind.hpp"

using namespace std;

// This is a "factory" function.
// It is used for creating new game objects dynamically
Game* pickGame()
{
	// we will return a pointer to a Game*
	Game* result = NULL;

	// we need to get the user's choice of game
	int choice = -1;
	while( -1 == choice )
	{
		resetScreen();

		cout // We need to add two options for the two new games here - TODO
			<< "We have the following options available:" << endl
			<< "0: Quit" << endl
			<< "1: Tic Tac Toe - a classic" << endl
			<< "2: Guess! - guess the number between 1 and 100" << endl
			<< "3: Hangman - guess each letter of a word or a man is hanged" << endl
			<< "4: Mastermind - guess a series of numbers until yours matches the secret combo!" << endl
		;
		cout << "Enter your choice here: ";
		if( cin >> choice ) // if the choice is valid
		{
			// handle the choice
			switch( choice )
			{
				case 0:
					break;
				case 1:
					result = new TicTacToe();
					break;
				case 2:
					result = new Guess();
					break;
				case 3:
					result = new Hangman();
					break;
				case 4:
					result = new Mastermind();
					break;
				default:
					cout << "choice not recognized! choose again!" << endl;
					choice = -1;
					break;
			}
		}
		else // if the choice is invalid, cin goes into a failed state and evaluates to false
		{
			//std::cout << std::cin.rdbuf();
			// clear the errors, set choice to the default value
			cin.clear();	// clear the errors
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// flush the buffer (or else we read infinitely)
			choice = -1;	// keep the loop condition going
			//std::cout << std::cin.rdbuf();

			//int i;
			//cin >> i;
		}
	}

	return result;
}
