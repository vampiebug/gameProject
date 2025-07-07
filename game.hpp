#include "highscore.hpp"
#include "player.hpp"
#ifndef CLASS_GAME
#define CLASS_GAME

class Game {
private:
	const static int boardsize = 10;
	HighScore top10list[boardsize];

public:
	// Vars
	std::string lastInput;
	// Functions
	virtual void drawBoard() = 0;
	virtual void getInput() = 0;
	/* returns true if in top 10 */
	virtual bool addScore( HighScore newScore ) = 0;
	virtual int play(const Player&) = 0;
	virtual void resetGame() = 0;
	void showScoreBoard();
	// ctor / dtor
	Game();
	virtual ~Game() = 0;
};

#endif
