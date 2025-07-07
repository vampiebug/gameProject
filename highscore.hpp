#ifndef CLASS_HIGHSCORE
#define CLASS_HIGHSCORE

#include "player.hpp"
#include <string>

class HighScore
{

private:
	Player p;
	int score;

public:
	HighScore();
	HighScore( Player _p, int _score );
	std::string toStr();
};

#endif
