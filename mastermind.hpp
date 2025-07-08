#ifndef MASTERMIND_HPP	// check if the compiler does not already recognizes a macro called GUESS_HPP
#define MASTERMIND_HPP	// if it does not already recognize it, then we can define it

// minimize the amount of imports you have here, because this file might be included in a bunch
// of other files that don't need all of the included files for the implementation of this class
#include "game.hpp" 	// the Guess object inherits the Game object, so we need its header file
#include "block.hpp" //should inherit from 


// define some MACROS 
#define GUESS_MIN 1		// mininum of the magic number distribution
#define GUESS_MAX 6		// maximum of the magic number distribution

// create a class Guess that inherits the class Game (so Guess is a type of Game)
class Mastermind : public Game {

private: // these variables and functions are only available to class members (and friends)
	//these are the first blocks in the lists for the cpu and the player.
	Block cpuFirst;
	Block playerBlocksFirst;
	//these are the block trackers for the cpu and the player
	Block* cpuTracker;
	Block* playerBlocksTracker;

	std::string guess; //this is the string used to take input for the user's individual number guesses.
    bool user_guess;    // Becomes true when the user correctly guesses the board.
	int num_guesses;	// the number of guesses the user has attempted

	int board_min;		// minimum incorrect guess
	int board_max;		// maximum incorrect guess

	void updateScoreboard();
	void askPlayAgain();

public: // these functions (usually not variables) are available to anyone
// default constructor
	Mastermind( );
	virtual ~Mastermind() override;

	virtual void resetGame( ) override;
	virtual void drawBoard() override;
	virtual void getInput() override;
	virtual bool addScore( HighScore ) override;
	virtual int  play( const Player& ) override;
}; // make sure you don't forget this semicolon because it can be difficult to find from error messages

#endif