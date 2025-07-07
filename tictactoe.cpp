#include "tictactoe.hpp"
using namespace std;

/* TicTacToe is a two player game, where players take turn */ 

// default constructor
TicTacToe::TicTacToe() : Game()
{
    this->pToken[0] = 'X';
    this->pToken[1] = 'O';

    cout << "We are not reading the scoreboard because we don't have a score for tic tac toe!" << endl;

    // initialize the board
    this->resetGame();
}

TicTacToe::~TicTacToe()
{
    cout << "TTT destructor " << endl;
    //Game::~Game();
}

bool TicTacToe::isFree( int cell )
{
	// ceck range
	if (cell < 0 || cell > 8)
	{
		return false;
	}
	if (this->board[cell] == this->pToken[0] ||
		this->board[cell] == this->pToken[1] )
	{
		return false;
	}
	return true;
}
// finds the first free cell, returns -1 if none is found
int TicTacToe::findFirstFreeCell( )
{
	for (int i=0; i<9; ++i)
	{
		if( TicTacToe::isFree( i ) )
		{
			return i;
		}
	}
	return -1;
} 

void TicTacToe::resetGame()
{
    for (int i=0; i<9; ++i)
    {
        board[i] = i+0x30;
    }
    this->winner = false;
    this->numMoves = 0;
    // inti to 'O' start as play() starts by flipping it
    this->currentToken = 1;
}

void TicTacToe::drawBoard()
{
    cout << ORNG;
    cout << "\t --- --- --- " << endl;
    cout << KNRM;
    int cell=0;
    while (cell < 9)
    {
        cout << ORNG;
        cout << "\t| ";
        cout << KNRM;
        for (int col=0; col < 3; ++col)
	{
            cout << board[cell];
            cout << ORNG << " | " << KNRM;
            cell++;
        }
        cout << ORNG;
        cout << endl << "\t --- --- --- " << endl;
        cout << KNRM;
    }

}

void TicTacToe::getInput()
{
    string in;
    cout << "Current turn is " << this->pToken[this->currentToken] << endl;
    cout << "Please pick a free cell by enterin its number (1-9)" << endl;
    cout << "NOT! If input is not the number of a free cell (or invalid)" << endl; 
    cout << "the first available cell will be played for you" << endl;
    cout << "What cell do you play? ";
    cin >> in;

    //cout << "New input is: " << in << endl;
    //cout << "Last input was: " << this->lastInput << endl;
    this->lastInput = in;
}

bool TicTacToe::addScore( HighScore newScore )
{
    cout << "adding score .. not supported for TicTacToe !" << endl;
    return false;
}

void TicTacToe::checkForWinner()
{
    // We need to check if X or Y has winning conditions ..
    // that is 3 in a row in any row, column or diagonal
    // Check rows
    for (int i=0; i<9; i=i+3)
    {
        if (this->board[0+i] == this->board[1+i] &&
            this->board[0+i] == this->board[2+i])
	{
            // all celles in this row are the same so we have a winner
            this->winner = true;
            return;
        }
    } // end for rows
    for (int i=0; i<3; ++i)
    {
        if ( this->board[i] == this->board[i+3] &&
                this->board[i] == this->board[i+6] )
	{
            // all cells of this column are the same so we have a winner
            this->winner = true;
            return;
        }
    }// end for columns
    // check the diagonals
    if ( this->board[0] == this->board[4] &&
            this->board[0] == this->board[8] )
    {
        this->winner = true;
        return;
    } else if ( this->board[2] == this->board[4] &&
                this->board[2] == this->board[6] )
    {
        this->winner = true;
        return;
    }
    cout << " ############################# " << endl;
    cout << "--> No winner yet, game on! <-- " << endl;
}

int TicTacToe::play( const Player& player )
{
    while (! this->winner && this->numMoves < 9)
    {
        resetScreen();
        cout << "Move " << this->numMoves << endl;
        // change who's turn it is
        this->currentToken = !this->currentToken;
        // draw the board
        drawBoard();
        // get move 
        getInput();
        // update gameboard
        int selection = stoi( this->lastInput );
        if ( ! this->isFree( selection ) )
	{
            selection = this->findFirstFreeCell();
        }
        this->board[selection] = this->pToken[currentToken];
        // check for winner 
        checkForWinner();
        // loop until we have a winner 
        // OR we run out of moves
        this->numMoves++;
    }
    if (this->winner)
    {
        cout << KGRN << BLNK_ON;
        cout << "We have a winner!!!" << endl;
        cout << KNRM;
        cout << "The winner is " << this->pToken[this->currentToken] << endl;
    }
    else
    {
        cout << "No cells left, so we have a draw :(" << endl;
    }
    // draw the board on last time
    drawBoard();
    return this->numMoves;
} // end of play()
