#include "hangman.hpp"
#include "consoledraw.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <random>
#include <deque>
#include <algorithm>
#include <iterator>

Hangman::Hangman( ) : Game( ){
	
	std::cout << "Constructor for Hangman!" << std::endl;

	// read the old scoreboard file here
	//create a filestream to read, a string to store lines, and a tracker
	std::fstream fin;
	std::string line;
	int i = 0;

	//open the filestream as input
	fin.open("hangman_scores.txt", std::ios::in);



	while (getline(fin, line) && i < 10){
		//make sure this isn't a double delete
		delete top10list[i];
		//assign the value to the HighScore in the file converted to a HighScore object.
		top10list[i] = new HighScore(Player(line.substr(0, line.find("\t"))), stoi(line.substr(line.find("\t")+1, std::string::npos)));
		//incrementing is kind of important you know
		i++;
	}
	//if that doesn't work:

	//use a for loop going through the top10List
	//use getline to read out the lines. look at project 1.
	//assign these to the scoreboard starting at beginning
	//if there are less than 10, initialize the rest to empty highscores. try not doing this and see what happens.

	//close the filestream
	fin.close();
}

// destructor
Hangman::~Hangman( )
{
	std::cout << "Destructor for Hangman!" << std::endl;
	// nothing to delete
	//when game ends, re-adds records to file.

	//create a filestream to write and string for scores.
	std::fstream fout;

	//open the filestream--trunc erases all its current contents.
	fout.open("hangman_scores.txt", std::ofstream::out | std::ofstream::trunc);


	//for each in the top10list, write to the file. do this from best to worst score.
	for (HighScore* score : top10list){
		//write to file as toStr
		//get the str of the score with toStr. Add an endline so getline can break it up.
		fout<<score->toStr()<<std::endl;
		//deallocate the object--this is actually done in game.
		//delete score;
	}

	//close the filstream
	fout.close();
}

// Gets the input (guessed letter) and checks if it is valid.
// Input and output is nothing
void Hangman::getInput()
{
    //reset guess to be empty
    user_guess = "";
    bool isValid = false;
    //take input until guess is within the correct range. Must check that guess is an alphabetic letter.
    while (!isValid){
        std::cin >> user_guess;

        //truncates to only be the first value. Works bc max length is one digit.
        if (!isdigit(user_guess[0])){
            if (isalpha(user_guess[0])){
                isValid = true;
                // Changes lower case letters to upper case
                char guess_letter = user_guess[0];
                if( islower(guess_letter) ){
                    transform(user_guess.begin(), user_guess.end(), user_guess.begin(), ::toupper);
                }
                continue;
            }
        }
        std::cout << "Input must be a letter." << std::endl;
    }
    
    return;
}

// needs to be implemented as part of the first task
// add scores to the record after each round. A score should only be added if it represents top-10 performance. 
// In the case of the Guess game, a lower number of guesses is better
bool Hangman::addScore( HighScore* newScore )
{
//from toStr, get the score itself (the part after the tab)
	//take the toStr of newScore. find the tab. One place forward will be the first digit. from there till the end will be the number. Convert that to an int.
	
	int score = stoi(newScore->toStr().substr(newScore->toStr().find('\t')+1, std::string::npos));

	//check that the newScore can at least work at the end of the list.
	if (stoi(top10list[9]->toStr().substr(top10list[9]->toStr().find('\t')+1, std::string::npos)) < score && stoi(top10list[9]->toStr().substr(top10list[9]->toStr().find('\t')+1, std::string::npos)) != 0){
		//is not in top 10 as score is greater than the tenth position and the tenth position is not 0 (default).
		std::cout<<"Not in the top 10. Keep trying!"<<std::endl;
		return false;
	}
	
	//if the new score is in the top 10, its value can be safely deleted. This is the only value that should be deleted: the rest will just be "passed back"
	delete top10list[9];
	//set the tracker
	int i = 9;	
	//starting at the end, check if that digit is greater than score. If it is, take the value of the prior value in the list.

	while (i > 0){
		//if the value is equal to 0 or greater than the value, just reassign and increment, then continue.

		if (stoi(top10list[i-1]->toStr().substr(top10list[i-1]->toStr().find('\t')+1, std::string::npos)) == 0 || stoi(top10list[i-1]->toStr().substr(top10list[i-1]->toStr().find('\t')+1, std::string::npos)) > score){
			//in the case of the end of the list, it will go from empty to the value of top10list[8]. Everything else just shifts over.
			top10list[i] = top10list[i - 1];
			//decrement and break out of the current iteration
			i--;
			continue;
		}
		else{
			break;
		}
	}
	// i should now be the correct position to add the score
	top10list[i] = newScore;
	return true;
}

// reset the game to the initial state
void Hangman::resetGame( ){
    // seed the time to the random library
    std::srand(std::time(nullptr));

    //Randomly pick a word from the word list and set it as the magic word
    srand ( time(NULL) ); //creates seed https://cplusplus.com/forum/beginner/26611/ 
    int RandIndex = rand() % 17; //generates a random number between 0 and 16

    this->magic_word = word_list[RandIndex];

    // reset number of guesses and board min/max
    //setting this to -1 means that when the loop is run for the first time, and no value is found because it's just drawing the gallows, it will automatically show first state.
    this->num_guesses = -1;
    this->guess_total = 0;
    this->user_guess = "";
    this->guesses_string = "";
    this->correct_letter = 0;
    this->guess_total = 0;

    // Initialize deque with placeholders for user to know how many letters are in the word
    std::cout << guesses.size() << std::endl;
    for(auto i = 0; i < this->magic_word.length(); i++){
        guesses.push_back("_");
        
    }


}

// draw the board on the screen in its current state
void Hangman::drawBoard(){

    // need to reset if the guess was correct this time
    bool correct_guess = false;

    // Check if any letters have been correctly guessed and print out word line
    for (size_t i = 0; i < this->magic_word.size(); ++i) {
        char letter = magic_word[i];
        char guess_letter = user_guess[0];
        if (letter == guess_letter){
            guesses[i] = letter;
            correct_guess = true;
            correct_letter = correct_letter+1;
        }

    }

    // outputs all of the correct letters and placeholders for letters to be guessed
    for(size_t i=0; i<this->magic_word.size(); ++i){
        std::cout<< guesses[i];
    }
    std::cout<< std::endl;

    // counts if an incorrect guess was made, since no correct guess was made
    if(!correct_guess){
       this->num_guesses = this->num_guesses+1;
    }

    // assembles a string word from the deque storing all the user's guesses
    guesses_string = "";
    for (size_t i =0; i < guesses.size(); i++){
        guesses_string += guesses[i];
    }
    // Build the gallow
    //don't you usually only add a body part for an incorrect guess?
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

        // ask the user for a guess and get it
        std::cout << "Enter your guess (between A - Z): "; //Should we give vowels to the player when they start playing?
        getInput();

        // counts the total number of guesses made overall in the game
        guess_total = guess_total+1;

        // Checks if the player guessed all of the letters in the magic word correctly, ends the game if so
        if( static_cast<size_t>(correct_letter) == this->magic_word.size()){
            guesses_string = this->magic_word;
        }

        // Checks if the user hit their max amount of guesses
        if( num_guesses == GUESS_MAX_HANG){
            guesses_string = this->magic_word;
        }

    }

    if( num_guesses < GUESS_MAX_HANG){
        // celebration and output the amount of guesses required
        std::cout << "Good job! You guessed the word after only "
        << (guess_total-1)
        << " guesses!"
        << std::endl
        ;
        //do the addscore--only adds if get it right/win
        addScore(new HighScore(player, num_guesses));
        std::cout << "Total incorrect guesses: " << num_guesses << std::endl;

    } else {
        // Sadness and output the amount of guesses required
        std::cout << "Too bad  :(  You finished after "
        << (guess_total-1)
        << " guesses!"
        << std::endl
        ;
        std::cout << "Total incorrect guesses: " << num_guesses << std::endl;
    }

    // message outputting the total number of incorrect guesses made in one game
    std::cout << "The answer was: " << this->magic_word << std::endl;

    // Clear the guessed word deque for the next game
    while (!guesses.empty())
    {
        guesses.pop_back();
    }


    return 0;

}