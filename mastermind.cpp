#include "mastermind.hpp"		// the class definition
#include "consoledraw.hpp"	// stuff to help with writing to the console

// some generally helpful libraries
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

// default constructor
Mastermind::Mastermind( ) : Game()
{
	
	std::cout << "Constructor for Mastermind!" << std::endl;

	// read the old scoreboard file here (NEED TO IMPLEMENT - TODO)
	// populate the game's scoreboard object

    //probably just run the reset command. It should define everything as needed.

}

// destructor
Mastermind::~Mastermind( )
{
	std::cout << "Destructor for Mastermind!" << std::endl;
	// nothing to delete
}

// reset the game to the initial state
void Mastermind::resetGame( )
{
	// seed the time to the random library
	std::srand(std::time(nullptr));

	// reset number of guesses and board min/max
	this->num_guesses = 0;
	this->board_min = GUESS_MIN;
	this->board_max = GUESS_MAX;

    // Initialize the head of the list
    //Cpu* headCPU = nullptr;
    // Create new nodes and add them to the list
    //again, I think this would be easily scalable.


    //I think this should do the same as your for-loop below. Also, the game seems very scalable--maybe we can do that if we have time?
    //create a new block with a random data value as the first in the list.
    cpuFirst = Block(rand() %5+1);
    //assign the tracker to the address of the first
    cpuTracker = &cpuFirst;
    //assign the next ones
    for (int i = 0; i<2; i++){
        //Assign the next pointer of the tracker block to a new block with a random data value (use the tracker to access). Also set the tracker to the new block.
        cpuTracker->nextBlock = new Block(rand() %5+1);
        //reassign the tracker to the block just defined
        cpuTracker = cpuTracker->nextBlock;
    }
    //probably need to reset cpuTracker.
     
    // for (int i = 1; i <= 3; i++) {
    //     Cpu* newNodeCPU = new Cpu();
    //     newNodeCPU->dataCPU = rand() %5+1; // Choses random number from 1-6, can be repeated numbers
    //     newNodeCPU->nextCPU = nullptr;

    //     // Link the nodes
    //     if (newNodeCPU->headCPU == nullptr) {
    //         // The list is empty, so the new node is the
    //         // head of the list
    //         newNodeCPU->headCPU = newNodeCPU;
    //     }
    //     else {
    //         // The list is not empty, traverse the list to find the last node
    //         Cpu* temp = newNodeCPU->headCPU;
    //         while (temp->nextCPU != nullptr) {
    //             temp = temp->nextCPU;
    //         }
    //         // Now temp points to the last node, link the new node
    //         temp->nextCPU = newNodeCPU;
    //     }

    // }
}

// draw the board on the screen in its current state
void Mastermind::drawBoard() //May not be in use~~~~~~~~
{
    const std::string RED = "\033[31m";

    // Build the number line
    std::string line;
    for (int i = 0; i <3; ++i){
        line += RED + "X";
    }
    // Print the line
    std::cout << line << "\n";

}

// we don't use this one but it's part of the interface so we have to implement it
//I mean we could just use it in play?
void Mastermind::getInput()
{
	return;
}

// needs to be implemented as part of the first task - TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Mastermind::addScore( HighScore newScore )
{
	return false;
}

// handles the entire process of playing a single game
int Mastermind::play( const Player& player )
{
	// make sure everything is initialized
	this->resetGame();
	std::cout << "Welcome to Mastermind! Guess the combination of 3 digits (may repeat) between 1 - 6" << std::endl;
	while( user_guess != true )
	{
		// clear the screen
		resetScreen();
		std::cout << "Guess the number combination!" << std::endl;

		// draw the board on the screen
		//this->drawBoard();
        user_guess = false;

		// ask the user for a guess and get it
		std::cout << "Enter your guess (between " << this->board_min << " and " << this->board_max << "): ";
		



        //basically works the same as in the reset except takes user input
        std::cin >> guess;
        playerBlocksFirst = Block(stoi(guess));
        //assign the tracker to the address of the first
        playerBlocksTracker = &playerBlocksFirst;
        for (int i = 0; i < 2; i++){
            std::cin >> guess;
            //implement getInput and checking to make sure the input is in fact an int within range here
            playerBlocksTracker->nextBlock = new Block(std::stoi(guess));
            playerBlocksTracker = playerBlocksTracker->nextBlock;
        }
        

        // // Initialize the head of the list
        // Pu* headPU = nullptr;
        // // Create new nodes and add them to the list
        // for (int i = 1; i <= 3; i++) {
        //     Pu* newNodePU = new Pu();
        //     std::cin >> newNodePU->dataPU; // Player choses number from 1-6, can be repeated numbers
        //     newNodePU->nextPU = nullptr;
        
        //     // Link the nodes
        //     if (headPU == nullptr) {
        //         headPU = newNodePU;
        //     }
        //     else {
        //         // The list is not empty, traverse the list to find the last node
        //         Pu* tempP = headPU;
        //         while (tempP->nextPU != nullptr) {
        //             tempP = tempP->nextPU;
        //         }
        //         tempP->nextPU = newNodePU;
        //     }
        // }
        
        int correct_guesses = 0;
        //probably need to reset both trackers back to the head.
        playerBlocksTracker = &playerBlocksFirst;
        cpuTracker = &cpuFirst;

        //On the last loop, playerBlocksTracker will be set equal to the next block for the last block in the list, which is nullptr.
        while (playerBlocksTracker != nullptr){
            if (playerBlocksTracker->data == cpuTracker->data){
                std::cout << cpuTracker->data << std::endl;
                ++correct_guesses;
            }
            else if (playerBlocksTracker->data == cpuTracker->data){
                std::cout << "X";
            }
        }
        //Check if a node matches, will print out their response if so. If doesnt match, prints an 'X'
        // for(int i=0; i<3; ++i){
        //     if (headCPU->dataCPU != headPU->dataPU){
        //         std::cout << "X";
        //     }
        //     else if(headCPU->dataCPU == headPU->dataPU){
        //         std::cout << headCPU->dataCPU << std::endl;
        //         ++correct_guesses;
        //     }
        // }
        
        if(correct_guesses == 3){
            user_guess = true;
        }

		// increment the number of guesses
		this->num_guesses ++;
	}

	// celebrate and output the amount of guesses required
	std::cout << "Good job! You figured out the combination after only "
		  << this->num_guesses
		  << " guesses!"
		  << std::endl
        ;

	return 0;
}