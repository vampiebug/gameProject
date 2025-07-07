#include "consoledraw.hpp"
#include "factory.hpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	// clear the screen
	resetScreen();
	std::cout << BYEL << "ARCADE MACHINE" << KNRM << std::endl;

	// figure out who's playing
	std::string player_name;
	std::cout << "Enter your name: ";
	cin >> player_name;
	Player player(player_name);
	std::cout << player.getName() << std::endl;

	// create a game instance and run the factory function
	Game* game = pickGame();
	while ( NULL != game )
	{
		bool player_wants_to_play = true;
		while( player_wants_to_play )
		{
			// play the game once with player
			game->play( player );
			
			// show the scoreboard after each game
			game->showScoreBoard();

			// see if the user wants to play again
			char c = 'z';
			while( 'n' != c && 'y' != c )
			{
				std::cout << "Would you like to play again? (y/n): " << std::endl;
				std::cin >> c; 
			}
			if( 'n' == c )
			{
				player_wants_to_play = false;
			}
			resetScreen();
			game->resetGame();
		}

		// get rid of the game before starting a new one
		delete game;
		game = NULL;
		game = pickGame();
	}
	
	std::cout << BYEL << "Bleep bloop bleep bloop bleep bloop, shutting down the machine!" << std::endl << KNRM;
	
	return 0;
}
