#include "hangman.hpp"
#include "consoledraw.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <random>
#include <vector>
#include <iterator>

Hangman::Hangman( ) : Game( ){

    std::cout << "Constructor for Hangman!" << std::endl;

    // read the old scoreboard file here (NEED TO IMPLEMENT - TODO same as in guess.cpp)
	// populate the game's scoreboard object
    

}

// destructor
Hangman::~Hangman( )
{
	std::cout << "Destructor for Hangman!" << std::endl;
	// nothing to delete
}

// we don't use this one but it's part of the interface so we have to implement it
void Hangman::getInput()
{
	return;
}

// needs to be implemented as part of the first task - TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// add scores to the record after each round. A score should only be added if it represents top-10 performance. 
// In the case of the Guess game, a lower number of guesses is better
bool Hangman::addScore( HighScore newScore )
{

	return false;
}

// reset the game to the initial state
void Hangman::resetGame( ){
	// seed the time to the random library
	std::srand(std::time(nullptr));
	
    //Randomly pick a word from the word list and set it as the magic word
    srand ( time(NULL) ); //creates seed https://cplusplus.com/forum/beginner/26611/ 
    int RandIndex = rand() % 10; //generates a random number between 0 and 9

    this->magic_word = word_list[RandIndex];

	// reset number of guesses and board min/max
	this->num_guesses = 0;
    this->guess_total=0;

    for(size_t i = 0; i < this->magic_word.size(); i++){
        guesses[i] = "_";
    }
}

// draw the board on the screen in its current state
void Hangman::drawBoard(){
    
    const std::string ORN = "\x1b[38;5;202m";
    const std::string RESET = "\033[0m";

    // Build the gallow
    if (this->num_guesses == 0){ // To initialize the gallow
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |      O      " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    
    //Update gallow to add sequential limb
    else if(this->num_guesses == 1){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)      " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(this->num_guesses == 2){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(this->num_guesses == 3){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|      " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(this->num_guesses == 4){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|>     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(this->num_guesses == 5){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|>     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |     /       " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(this->num_guesses == GUESS_MAX_HANG){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|>     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |     / |     " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;

    }

    // need to reset if the guess was correct this time
    int correct_guess = 0;
    
    // Check if any letters have been correctly guessed and print out word line
    for (size_t i = 0; i < this->magic_word.size(); ++i) {
        char letter = magic_word[i];
        char guess_letter = user_guess[0];
        if (letter == guess_letter){
            guesses[i] = letter;
            correct_guess = correct_guess+1;
            correct_letter = correct_letter+1;
            
        }
        
    }

    // outputs all of the correct letters and placeholders for letters to be guessed
    for(size_t i=0; i<this->magic_word.size(); ++i){
        std::cout<< guesses[i];
    }
    std::cout<< std::endl;

    // counts if an incorrect guess was made, since no correct guess was made
    if( correct_guess == 0){
        this->num_guesses = this->num_guesses+1;
    }

    // assembles a string word from the deque storing all the user's guesses
    guesses_string = "";
    for (size_t i =0; i < guesses.size(); i++){
        guesses_string += guesses[i];
    }

}

// handles the entire process of playing a single game
int Hangman::play( const Player& player )
{
	// make sure everything is initialized
	this->resetGame();

	while( this->magic_word != guesses_string ) // While the player has made an incorrect guess, update board and continue playing
	{
		// clear the screen
		resetScreen();
		std::cout << "Guess one letter to get the correct word! Type 'done' when you've guessed each letter and finished the word!" << std::endl;

		// draw the board on the screen
		this->drawBoard();

        // Checks if the user hit their max amount of guesses
        if( num_guesses == GUESS_MAX_HANG){
            guesses_string = this->magic_word;
        }


        user_guess = ""; // reset the storage for the user's guess
		// ask the user for a guess and get it
		std::cout << "Enter your guess (between A - Z): "; //Should we give vowels to the player when they start playing?
		std::cin >> user_guess;

        // counts the total number of guesses made overall in the game
        guess_total = guess_total+1;

        // Checks if the player guessed all of the letters in the magic word correctly, ends the game if so
        if( static_cast<size_t>(correct_letter) == this->magic_word.size()){
            guesses_string = this->magic_word;
        }

    }

    if( num_guesses < GUESS_MAX_HANG){
        // celebration and output the amount of guesses required
	std::cout << "Good job! You guessed the word after only "
		  << (guess_total)
		  << " guesses!"
		  << std::endl
	;
    } else {
        // Sadness and output the amount of guesses required
	    std::cout << "Too bad  :(  You finished after "
		      << (guess_total)
		      << " guesses!"
		      << std::endl
	    ;
    }

    // message outputting the total number of incorrect guesses made in one game
    std::cout << "The answer was: " << this->magic_word << std::endl;
    std::cout << "Total incorrect guesses: " << num_guesses - 1 << std::endl;

    return 0;

}
