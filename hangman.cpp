#include "hangman.hpp"
#include "consoledraw.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <random>

Hangman::Hangman( ) : Game( ){
	
	std::cout << "Constructor for Hangman!" << std::endl;

	// read the old scoreboard file here (NEED TO IMPLEMENT - TODO)
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

// we don't use this one but it's part of the interface so we have to implement it
void Hangman::getInput()
{
	return;
}

// needs to be implemented as part of the first task - TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// add scores to the record after each round. A score should only be added if it represents top-10 performance. 
// In the case of the Guess game, a lower number of guesses is better

//this isn't actually in play yet. Just going to test on guess.
bool Hangman::addScore( HighScore* newScore )
{
	//from toStr, get the score itself (the part after the tab)
	//header.push_back(line.substr(0, line.find(',')));
	//take the toStr of newScore. find the tab. One place forward will be the first digit. from there till the end will be the number. Convert that to an int.
	
	//std::cout<<"entered addScore"<<std::endl;
	//std::cout<<"score: "<<newScore->toStr().substr(newScore->toStr().find('\t')+1, std::string::npos)<<std::endl;
	int score = stoi(newScore->toStr().substr(newScore->toStr().find('\t')+1, std::string::npos));

	//check that the newScore can at least work at the end of the list.
	if (stoi(top10list[9]->toStr().substr(top10list[9]->toStr().find('\t')+1, std::string::npos)) < score && stoi(top10list[9]->toStr().substr(top10list[9]->toStr().find('\t')+1, std::string::npos)) != 0){
		//is not in top 10 as score is greater than the tenth position and the tenth position is not 0 (default).
		std::cout<<"Not in the top 10. Keep trying!"<<std::endl;
		return false;
	}
	//std::cout<<"checked last score"<<std::endl;
	
	//if the new score is in the top 10, its value can be safely deleted. This is the only value that should be deleted: the rest will just be "passed back"
	delete top10list[9];
	//set the tracker
	int i = 9;	
	//starting at the end, check if that digit is greater than score. If it is, take the value of the prior value in the list.

	while (i > 0){
		//if the value is equal to 0 or greater than the value, just reassign and increment, then continue.

		//std::cout<<i<<std::endl;
		if (stoi(top10list[i-1]->toStr().substr(top10list[i-1]->toStr().find('\t')+1, std::string::npos)) == 0 || stoi(top10list[i-1]->toStr().substr(top10list[i-1]->toStr().find('\t')+1, std::string::npos)) > score){
			//in the case of the end of the list, it will go from empty to the value of top10list[8]. Everything else just shifts over.
			top10list[i] = top10list[i - 1];
			//decrement and break out of the current iteration
			i--;
			continue;
		}
		else{
			//std::cout<<"breaking out at position"<<i<<std::endl;
			break;
		}
	}
	//std::cout<<"iterated to position "<<i<<std::endl;
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
    int RandIndex = rand() % 10; //generates a random number between 0 and 9

    this->magic_word = word_list[RandIndex];

	// reset number of guesses and board min/max
	this->num_guesses = 0;

}

// draw the board on the screen in its current state
void Hangman::drawBoard(){
    const int width = 60; // total characters for the line
    const std::string ORN = "\x1b[38;5;202m";
    const std::string RESET = "\033[0m";

    // Compute the scale factor
    int range = GUESS_MAX - GUESS_MIN;
    if (range <= 0){
        std::cerr << "Invalid range.\n";
        return;
    }

    // Build the gallow
    if (num_guesses == 0){ // To initialize the gallow
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
    else if(num_guesses == 1){
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
    else if(num_guesses == 2){
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
    else if(num_guesses == 3){
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
    else if(num_guesses == 4){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|\     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(num_guesses == 5){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|\     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |     /       " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;
    }
    else if(num_guesses == 6){
        //print out gallow with new body part
        std::cout << "####################" << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "      _______       " << std::endl;
        std::cout << "      |/     |      " << std::endl;
        std::cout << "      |     (_)     " << std::endl;
        std::cout << "      |     /|\     " << std::endl;
        std::cout << "      |      |      " << std::endl;
        std::cout << "      |     / \     " << std::endl;
        std::cout << "      |             " << std::endl;
        std::cout << "    __|___          " << std::endl;
        std::cout << "                    " << std::endl;
        std::cout << "####################" << std::endl;

    }

    // Check if any letters have been correctly guessed and print out word line
    for (int i = 0; i < magic_word.length(); ++i) {
        char letter = magic_word[i];
        char guess_letter = user_guess[i];
        if (letter == guess_letter){
            std::cout << letter;
        }
        else{
            std::cout << "_";
        }
    }
    std::cout << std::endl;

}

// handles the entire process of playing a single game
int Hangman::play( const Player& player )
{
	// make sure everything is initialized
	this->resetGame();

	user_guess = "";
	while( user_guess != this->magic_word ) // While the player has made an incorrect guess, update board and continue playing
	{
		// clear the screen
		resetScreen();
		std::cout << "Guess a letter to get the correct word!" << std::endl;

		// draw the board on the screen
		this->drawBoard();

        //test comments:

        std::cout<<this->magic_word<<std::endl;
        std::cout<<this->user_guess<<std::endl;
		// ask the user for a guess and get it
		std::cout << "Enter your guess (between A - Z): "; //Should we give vowels to the player when they start playing?
		std::cin >> user_guess;

    }

    // celebrate and output the amount of guesses required
	std::cout << "Good job! You figured out the word after only "
		  << this->num_guesses
		  << " guesses!"
		  << std::endl
	;
    addScore(new HighScore(player, num_guesses));

    return 0;

}
