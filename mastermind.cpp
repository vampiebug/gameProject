#include "mastermind.hpp"		// the class definition
#include "consoledraw.hpp"	// stuff to help with writing to the console

// some generally helpful libraries
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <fstream>

// default constructor
Mastermind::Mastermind( ) : Game()
{
	
	std::cout << "Constructor for Hangman!" << std::endl;

	// read the old scoreboard file here (NEED TO IMPLEMENT - TODO)
	//create a filestream to read, a string to store lines, and a tracker
	std::fstream fin;
	std::string line;
	int i = 0;

	//open the filestream as input
	fin.open("mastermind_scores.txt", std::ios::in);



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
Mastermind::~Mastermind( )
{
	std::cout << "Destructor for Mastermind!" << std::endl;
	// nothing to delete
	//when game ends, re-adds records to file.

	//create a filestream to write and string for scores.
	std::fstream fout;

	//open the filestream--trunc erases all its current contents.
	fout.open("mastermind_scores.txt", std::ofstream::out | std::ofstream::trunc);


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
void Mastermind::resetGame( )
{
	// seed the time to the random library
	std::srand(std::time(nullptr));

	// reset number of guesses and board min/max
	this->num_guesses = 0;
	this->board_min = GUESS_MIN;
	this->board_max = GUESS_MAX_MIND;

    //reset the flag for the user's guess
    user_guess = false;

    // Initialize the head of the list
    //Cpu* headCPU = nullptr;
    // Create new nodes and add them to the list
    //again, I think this would be easily scalable.


    //I think this should do the same as your for-loop below. Also, the game seems very scalable--maybe we can do that if we have time?
    //create a new block with a random data value as the first in the list.
    cpuTower = Tower(rand() %5+1);
    //assign the tracker to the address of the first (REMOVED)
    //cpuTracker = &cpuFirst;
    //assign the next ones
    for (int i = 0; i<2; i++){
        cpuTower.addToEnd(new Block(rand() %5+1));
    }


     
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
bool Mastermind::addScore( HighScore* newScore )
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
int Mastermind::play( const Player& player )
{
	// make sure everything is initialized
	this->resetGame();
	std::cout << "Welcome to Mastermind! Guess the combination of 3 digits (may repeat) between 1 - 6" << std::endl;
	while( user_guess != true )
	{
		// clear the screen --note: this causes some issues, as it hides the previous guess before it can be seen
		//resetScreen();
		std::cout << "Guess the number combination!" << std::endl;

		// draw the board on the screen
		//this->drawBoard();
        user_guess = false;

		// ask the user for a guess and get it
		std::cout << "Enter your guess (between " << this->board_min << " and " << this->board_max << "): ";
		



        //basically works the same as in the reset except takes user input. Need to clean this to make sure it's an int.
        std::cin >> guess;
        playerTower = Tower(stoi(guess));
        //assign the tracker to the address of the first REMOVED
        //playerBlocksTracker = &playerBlocksFirst;
        for (int i = 0; i < 2; i++){
            // ask the user for a guess and get it
		    std::cout << "Enter your guess (between " << this->board_min << " and " << this->board_max << "): ";
            std::cin >> guess;
            //implement getInput and checking to make sure the input is in fact an int within range here
            playerTower.addToEnd(new Block(stoi(guess)));
        }
        // std::cout<<cpuTower.startBlock->data<<std::endl;
        // std::cout<<cpuTower.startBlock->traverseDown()->data<<std::endl;
        // std::cout<<cpuTower.startBlock->traverseDown()->traverseDown()->data<<std::endl;
        // std::cout<<playerTower.startBlock->data<<std::endl;
        // std::cout<<playerTower.startBlock->traverseDown()->data<<std::endl;
        // std::cout<<playerTower.startBlock->traverseDown()->traverseDown()->data<<std::endl;

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
        //probably need to reset both trackers back to the head. REMOVED
        // playerBlocksTracker = &playerBlocksFirst;
        // cpuTracker = &cpuFirst;

    //need to reset the trackers before looping. See if there's a better way to do this. Maybe make the trackers part of the towers?
    playerTracker = playerTower.startBlock;
    cpuTracker = cpuTower.startBlock;

    //On the last loop, playerBlocksTracker will be set equal to the next block for the last block in the list, which is nullptr.
    while (playerTracker != nullptr){
        if (playerTracker->data == cpuTracker->data){
            std::cout << cpuTracker->data;
            ++correct_guesses;
            //break out of this iteration and update if reach print
            playerTracker = playerTracker->traverseDown();
            cpuTracker = cpuTracker->traverseDown();
            continue;
        }
        //otherwise:
        //if the previous cpu data is safe to access and its data matches the current player guess, output an asterisk.
        if (playerTracker->traverseUp() != nullptr){
            if (playerTracker->data == cpuTracker->traverseUp()->data){
                std::cout<<"*";
                //break out of this iteration and update if reach print
                playerTracker = playerTracker->traverseDown();
                cpuTracker = cpuTracker->traverseDown(); 
                continue;
            }
        }
        //if the prior cpu data is safe to access and its data matches the current player guess, output an asterisk.
        //will have ended the iteration if already printed, so can use if instead of else if.
        if (playerTracker->traverseDown() != nullptr){
            if (playerTracker->data == cpuTracker->traverseDown()->data){
                std::cout<<"*";
                //break out of this iteration and update if reach print
                playerTracker = playerTracker->traverseDown();
                cpuTracker = cpuTracker->traverseDown(); 
                continue;
            }
        }
        //if it's still in the loop, there is no match. Print x and increment.
        std::cout << "X";
        playerTracker = playerTracker->traverseDown();
        cpuTracker = cpuTracker->traverseDown(); 
    }
    std::cout << std::endl;
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

    }
    	// celebrate and output the amount of guesses required
	std::cout << "Good job! You figured out the combination after only "
		  << this->num_guesses
		  << " guesses!"
		  << std::endl
        ;
    addScore(new HighScore(player, num_guesses));

	return 0;
}

// we don't use this one but it's part of the interface so we have to implement it
//I mean we could just use it in play?
void Mastermind::getInput()
{
	return;
}

// needs to be implemented as part of the first task - TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// handles the entire process of playing a single game
int Mastermind::play( const Player& player )
{
	// make sure everything is initialized
	this->resetGame();
	std::cout << "Welcome to Mastermind! You need to guess the combination of 3 digits (may repeat) between 1 - 6" << std::endl;
    std::cout << "Guesses that earn a 'X' mean the guess is completely wrong. An '*' means the guess is not in the right spot.";
    std::cout << "Seeing the guessed number means it is correct and in the correct spot!" << std::endl;

	while( user_guess != true )
	{
		// clear the screen --note: this causes some issues, as it hides the previous guess before it can be seen
		//resetScreen();
		//std::cout << "Guess the number combination!" << std::endl; dont need this since we shouldnt reset the screen

        //basically works the same as in the reset except takes user input. Need to clean this to make sure it's an int.
        std::cout << "Enter your guess (between " << this->board_min << " and " << this->board_max << "): ";
        std::cin >> guess;
        playerTower = Tower(stoi(guess));

        //assign the tracker to the address of the first REMOVED
        //playerBlocksTracker = &playerBlocksFirst;

        for (int i = 0; i < 2; i++){
            // ask the user for a guess and get it
		    std::cout << "Enter your guess (between " << this->board_min << " and " << this->board_max << "): ";
            std::cin >> guess;
            //implement getInput and checking to make sure the input is in fact an int within range here
            playerTower.addToEnd(new Block(stoi(guess)));
        }

        //std::cout << cpuTower.startBlock->data << std::endl;
        //std::cout << cpuTower.startBlock->traverseDown()->data << std::endl;
        //std::cout << cpuTower.startBlock->traverseDown()->traverseDown()->data << std::endl;
        //std::cout << playerTower.startBlock->data << std::endl;
        //std::cout << playerTower.startBlock->traverseDown()->data << std::endl;
        //std::cout << playerTower.startBlock->traverseDown()->traverseDown()->data << std::endl;

        // draw the board on the screen (the combination hints)
		this->drawBoard();


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

        // increment the number of guesses
	    this->num_guesses ++;

    }

	// celebrate and output the amount of guesses required
	std::cout << "Good job! You figured out the combination after only "
		  << this->num_guesses
		  << " guesses!"
		  << std::endl
        ;
    addScore(new HighScore(player, num_guesses));

	return 0;
}