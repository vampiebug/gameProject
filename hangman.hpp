#ifndef HANGMAN_HPP	// check if the compiler does not already recognizes a macro called GUESS_HPP
#define HANGMAN_HPP	// if it does not already recognize it, then we can define it

#define GUESS_MIN 1		// mininum of the magic number distribution
#define GUESS_MAX_HANG 6 // for the total limbs that the hanged man has

#include "game.hpp"
#include <deque>

// create a class Guess that inherits the class Game (so Guess is a type of Game)
class Hangman : public Game {

private: // these variables and functions are only available to class members (and friends)
	std::string magic_word;	// the word to guess
	std::string user_guess; // the user's guessed letter
	int num_guesses;	// the number of incorrect guesses
	int board_min;		// minimum incorrect guess
	int board_max;		// maximum incorrect guess
    std::string word_list[10] = {"EXTRAORDINARY", "DISAPPOINTMENT", "CAFFEINE", "MICHIGAN", "WOLVERINE", "DETROIT",
         "SIGMA", "INTELLECTUAL", "ROBOTICS", "GRASS"}; // an assortment of words to guess from
	std::deque<std::string> guesses; // Stores all the correctly guessed letters and placeholders from the game
	std::string guesses_string; // is a string of the the deque (all the letters are in one string)
	int correct_letter; // counter for correct letters guessed throughout one full game
	int guess_total; // counts number of all guesses (correct or not)
	void updateScoreboard();
	void askPlayAgain();

public: // these functions (usually not variables) are available to anyone
// default constructor
	Hangman( );
	virtual ~Hangman() override;

	virtual void resetGame( ) override;
	virtual void drawBoard() override;
	virtual void getInput() override;
	virtual bool addScore( HighScore ) override;
	virtual int  play( const Player& ) override;
};


#endif