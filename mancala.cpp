//////////////////////////////////
// Human vs. Computer Manacala - an adversarial AI demonstration.
// - Minimax algorithm with Alpha Beta Pruning implemented a Mancala player
//
// main.cpp
//
///Author: Dustin Fast Oct, 2017
///Email: dustin.fast@hotmail.com

#include <iostream>
#include <cctype>
#include <string>
#include <ctime>
#include "gameboard.h"
#include "ai_player.h"

using namespace std;

// Default max depth. See readme for details.
int MAX_SEARCH_DEPTH = 8; 

string getWhoMovesFirst();
bool getHumanPlayerMove(GameBoard *gameboard);			//gets player move
bool getAIPlayerMove(GameBoard *gameboard);				//gets computer move
bool getRandomPlayerMoveHuman(GameBoard *gameboard);	//gets a random (but valid) player move. Returns true. For testing purposes.
bool getSmartPlayerMoveHuman(GameBoard *gameboard);		//Simulates a player move by generating an AI move. For testing purposes.

int nTurnNumber = 0; 

int main(int argc, char *argv[])
{
	//Setup the game board
	GameBoard gameboard;
	bool gameEnded = false;

	//Get search depth from command args (or use default)
	if(argc == 2)
		MAX_SEARCH_DEPTH = atoi(argv[1]);
	cout << "Using MAX_SEARCH_DEPTH = " << MAX_SEARCH_DEPTH << endl;

	//Prompt for first player
	string strPlayerTurn = getWhoMovesFirst();

	//While game is not won, accept moves.
	while (!gameEnded) 
	{
		gameboard.displayBoardVerbose(strPlayerTurn);

		int nMove = -1;
		bool bEndState = false;
		//If player turn is human
		if (strPlayerTurn == "NORTH")
		{
			if (!getHumanPlayerMove(&gameboard)) //RELEASE
			//if (!getSmartPlayerMoveHuman(&gameboard)) //DEBUG
				bEndState = true;
			else
				strPlayerTurn = "SOUTH";
		}
		//If player turn is computer
		else if (strPlayerTurn == "SOUTH")
		{
			if (!getAIPlayerMove(&gameboard)) //RELEASE
				bEndState = true;
			else
				strPlayerTurn = "NORTH";
		}

		//If game has been ended. 
		if (bEndState)
		{
			gameboard.displayBoardVerbose("");
			cout << "Game was ended by " << strPlayerTurn << ". Winner is " << gameboard.getWinner() << endl;
			gameEnded = true;
		}
	}
	system("pause");
}

//Prompts for first player
string getWhoMovesFirst()
{
	string strInput = "";
	while (strInput != "1" && strInput != "2")
	{
		cout << "Which Player will go first (Enter a 1 for Human or 2 for Computer)? ";
		cin >> strInput;
	}
	if (strInput == "1")
		return "NORTH";
	else
		return "SOUTH";
}

//Gets human player move from console. Returns true iff game will continue
bool getHumanPlayerMove(GameBoard *gameboard)
{
	nTurnNumber++;
	int nMove = -1;
	string strTemp = "";
	while (!gameboard->isMoveValid("NORTH", nMove))
	{
		if (nMove != -1)
			cout << "Invalid move: Enter a non-empty cell # (viewed L to R) 12, 11, 10, 9, 8, or 7\n";
		cout << nTurnNumber << ": Human player (NORTH), enter your move: ";
		cin >> strTemp;
		if (strTemp != "12" && strTemp != "11" && strTemp != "10" && strTemp != "9" && strTemp != "8" &&strTemp != "7")
			nMove = -2;
		else
			nMove = atoi(strTemp.c_str());
	}
	if (!gameboard->doMove("NORTH", nMove))
		return false;

	return true;
}

//Gets computer's move. Returns true iff game will continue
bool getAIPlayerMove(GameBoard *gameboard)
{
	nTurnNumber++;
	AIPlayer ai;
	cout << "Move " << nTurnNumber << ": Computer player (SOUTH) chooses move: ";
	int nMove = ai.getMove(gameboard, "SOUTH", MAX_SEARCH_DEPTH); 
	int nAltMove = -1;
	/*if (nMove == 0)
		nAltMove = */
	cout << nMove << endl;
	//system("pause");
	if (gameboard->doMove("SOUTH", nMove))
		return true;
	return false;
}

//Substitutes a random (but valid) move for the human player. For testing convenience.
bool getRandomPlayerMoveHuman(GameBoard *gameboard)
{
	nTurnNumber++;
	int nMove = -1;
	string strTemp = "";
	srand(time(NULL));
	cout << "Move " << nTurnNumber << ": Human player (NORTH), enter your move: ";
	while (!gameboard->isMoveValid("NORTH", nMove))
		nMove = (rand() % (13 - 7)) + 7;
	cout << nMove << endl;
	if (!gameboard->doMove("NORTH", nMove))
		return false;
	return true;
}

//Substitues an AI move for the human player. For testing convenience.
bool getSmartPlayerMoveHuman(GameBoard *gameboard)
{
	nTurnNumber++;
	AIPlayer ai;
	cout << "Move " << nTurnNumber << ": Human player (NORTH) chooses move: ";
	int nMove = ai.getMove(gameboard, "NORTH", MAX_SEARCH_DEPTH);
	int nAltMove = -1;
	cout << nMove << endl;
	if (gameboard->doMove("NORTH", nMove))
		return true;
	return false;
}