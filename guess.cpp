// here you can import more things. import everything needed for the implementation of this class.
#include "guess.hpp"		// the class definition
#include "consoledraw.hpp"	// stuff to help with writing to the console

// some generally helpful libraries
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <fstream>

/* High score board and score function: Read from a high score file
* (you are free to choose the specifics of file format, file name, etc.), and make the game read this file
* in its constructor to populate an object representing the high scores. Then, implement the addScore
* function to add scores to the record after each round. A score should only be added if it represents
* top-10 performance. In the case of the Guess game, a lower number of guesses is better. The
* scoreboard is displayed via the main file after each round.
*/

// default constructor
Guess::Guess( ) : Game()
{
	
	std::cout << "Constructor for Guess!" << std::endl;

	// read the old scoreboard file here (NEED TO IMPLEMENT - TODO)
	//create a filestream to read, a string to store lines, and a tracker
	std::fstream fin;
	std::string line;
	int i = 0;

	//open the filestream as input
	fin.open("guess_scores.txt", std::ios::in);



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
Guess::~Guess( )
{
	std::cout << "Destructor for Guess!" << std::endl;
	// nothing to delete
	//when game ends, re-adds records to file.

	//create a filestream to write and string for scores.
	std::fstream fout;

	//open the filestream--trunc erases all its current contents.
	fout.open("guess_scores.txt", std::ofstream::out | std::ofstream::trunc);


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

// reset the game to the initial state
void Guess::resetGame( )
{
	// seed the time to the random library
	std::srand(std::time(nullptr));

	// generate a random distribution
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(GUESS_MIN, GUESS_MAX);
	
	// get a random magic number
	this->magic_number = distribution(gen);

	// reset number of guesses and board min/max
	this->num_guesses = 0;
	this->board_min = GUESS_MIN;
	this->board_max = GUESS_MAX;
}

// draw the board on the screen in its current state
void Guess::drawBoard()
{
    const int width = 60; // total characters for the line
    const std::string RED = "\033[31m";
    const std::string RESET = "\033[0m";

    // Compute the scale factor
    int range = GUESS_MAX - GUESS_MIN;
    if (range <= 0){
        std::cerr << "Invalid range.\n";
        return;
    }

    // Build the number line
    std::string line;
    for (int i = 0; i <= width; ++i){
        int value = GUESS_MIN + (i * range) / width;
        if (value < board_min || value > board_max){
            line += RED + "-" + RESET;
        } else {
            line += "-";
        }
    }

    // Print the line
    std::cout << line << "\n";

    // Create label line
    std::string labels(width + 1, ' ');
    int pos_min = (board_min - GUESS_MIN) * width / range;
    int pos_max = (board_max - GUESS_MIN) * width / range;

    if (pos_min >= 0 && pos_min <= width)
        labels[pos_min] = '|';
    if (pos_max >= 0 && pos_max <= width)
        labels[pos_max] = '|';

    std::cout << labels << "\n";

    // Print the numeric labels
    std::cout << std::setw(pos_min + 1) << board_min;
    std::cout << std::setw(pos_max - pos_min + 1) << board_max << "\n";

	return;
}

// we don't use this one but it's part of the interface so we have to implement it
void Guess::getInput()
{
	return;
}

// needs to be implemented as part of the first task - TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//adds scores after each round. 
bool Guess::addScore( HighScore* newScore )
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

// handles the entire process of playing a single game
int Guess::play( const Player& player )
{
	// make sure everything is initialized
	this->resetGame();
	
	int user_guess = -1;
	while( user_guess != this->magic_number )
	{
		// clear the screen
		resetScreen();
		std::cout << "Guess the magic number!" << std::endl;

		// draw the board on the screen
		this->drawBoard();

		// ask the user for a guess and get it
		std::cout << "Enter your guess (between " << this->board_min << " and " << this->board_max << "): ";
		std::cin >> user_guess;

		// if the guess is too small
		if( user_guess < this->magic_number )
		{
			std::cout << "too small!" << std::endl;

			// if it is the highest low-guess then we can update the board
			if( this->board_min < user_guess )
			{
				this->board_min = user_guess;

				std::cout << "board min: " << this->board_min << std::endl;
			}
		}
		// if the guess is too big
		else if( user_guess > this->magic_number )
		{
			std::cout << "too big!" << std::endl;
			
			// if it is the lowest high-guess then we can update the board
			if( this->board_max > user_guess )
			{
				this->board_max = user_guess;
				
				std::cout << "board max: " << this->board_max << std::endl;
			}
		}

		// increment the number of guesses
		this->num_guesses ++;
	}

	// celebrate and output the amount of guesses required
	std::cout << "Good job! You figured out the magic number after only "
		  << this->num_guesses
		  << " guesses!"
		  << std::endl
	;
	//add the score to the scoreboard
	addScore(new HighScore(player, num_guesses));

	return 0;
}

