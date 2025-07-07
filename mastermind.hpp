#ifndef MASTERMIND_HPP	// check if the compiler does not already recognizes a macro called GUESS_HPP
#define MASTERMIND_HPP	// if it does not already recognize it, then we can define it

// minimize the amount of imports you have here, because this file might be included in a bunch
// of other files that don't need all of the included files for the implementation of this class
#include "game.hpp" 	// the Guess object inherits the Game object, so we need its header file

// define some MACROS 
#define GUESS_MIN 1		// mininum of the magic number distribution
#define GUESS_MAX 6		// maximum of the magic number distribution

// create a class Guess that inherits the class Game (so Guess is a type of Game)
class Mastermind : public Game {

private: // these variables and functions are only available to class members (and friends)
	struct Cpu {
        int dataCPU; // The data stored in the node
        Cpu* nextCPU; // Pointer to the next node
        Cpu* headCPU = nullptr;
    };
    struct Pu {
        int dataPU;
        Pu* nextPU;
    };

    bool user_guess;    // the user hasn't guessed right yet
	int num_guesses;	// the number of guesses
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