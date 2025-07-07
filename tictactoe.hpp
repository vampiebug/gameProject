#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "game.hpp"
#include "consoledraw.hpp"

/* TicTacToe is a two player game, where players take turns */ 
class TicTacToe : public Game
{
private:
	char board[9];
	char pToken[2];
	int currentToken;
	int numMoves;
	bool winner;

	bool isFree( int cell );
	// finds the first free cell, returns -1 if none is found
	int findFirstFreeCell( );
	void checkForWinner( );

public:
	// default constructor
	TicTacToe( );
	virtual ~TicTacToe() override;

	virtual void resetGame( ) override;
	virtual void drawBoard() override;
	virtual void getInput() override;
	virtual bool addScore( HighScore newScore ) override;
	virtual int  play( const Player& ) override;
};

#endif
