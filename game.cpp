#include "game.hpp"

#include <sstream>
#include <iostream>
#include <iostream>

Game::Game()
{
    this->lastInput = "";
}

Game::~Game()
{
    std::cout << "Game destuctor" << std::endl;
    this->lastInput = "";
}

void Game::showScoreBoard ()
{
	std::cout << "# Player ################## Score  #" << std::endl;
	std::cout << "####################################" << std::endl;
	for (int i=0; i<this->boardsize; ++i)
	{
		std::cout << "# " << top10list[i].toStr() << std::endl;
	}
	std::cout << "####################################" << std::endl;
}
