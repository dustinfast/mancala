//////////////////////////////////
// AIPlayer.h: The AI Player, playing as max in the minimax algorithm
//
///Author: Dustin Fast Oct, 2017

#pragma once
#define INT_MAX 2147483647
#define INT_MIN -2147483647

#include <vector>
#include "Gameboard.h"

struct Move
{
	Move() {};
	Move(int heuristic) : nHeuristic(heuristic), nPit(-1) {};
	int nPit;
	int nHeuristic;
};

class AIPlayer
{
public:
	AIPlayer();
	int getMove(GameBoard *board, string player, int maxdepth);

private:
	Move findBestMove(GameBoard *board, string player, int depth, int maxdepth, int alpha, int beta);
	int evalFunction(GameBoard *board, string player);
};

AIPlayer::AIPlayer()
{
}

//Returns the results of recursive function findBestMove()
int AIPlayer::getMove(GameBoard *board, string player, int maxdepth)
{
	int n = findBestMove(board, player, 0, maxdepth, INT_MIN, INT_MAX).nPit;
	if (!board->isMoveValid(player, n))
		cout << "ERROR: An invalid move was generated. " << n;
	return n;
}

//Finds the agent's best move, 
Move AIPlayer::findBestMove(GameBoard *board, string player, int depth, int maxdepth, int alpha, int beta)
{
	//Recursion base case for terminal nodes
	string strWinner = board->getWinner();
	if (strWinner == "SOUTH")
		return Move(INT_MAX);
	else if (strWinner == "NORTH")
		return Move(INT_MIN);
	else if (strWinner == "TIE")
		return Move(0);

	//Ini curr player and vars
	vector<Move> vMoves; //Container to hold moves at current DFS level
	Move mTemp, m;	//Moves objects. 
	int nLimit = 6;
	int nStart = 0;
	string strCurrPlayer = "SOUTH"; //assume max player is curr
	if (player == "NORTH")			//but if min player is curr
	{
		nLimit = 13;
		nStart = 7;
		strCurrPlayer = "NORTH"; 
	}

	//If at max depth, evaluate the board heuristics and make a decision.
	if (depth >= maxdepth)
		return Move(evalFunction(board, strCurrPlayer));

	//For the current simulated player iterate through all pits that have
	// stones in them (i.e. that are valid moves) and push the move to vMoves
	// to be evaluated later for being a "best" move at this depth
	m.nHeuristic = INT_MIN; //assume max player is curr
	if (strCurrPlayer == "NORTH")
		m.nHeuristic = INT_MAX; //but, if min player is curr
	for (int i = nStart; i < nLimit; i++)
	{
		if (board->findPitByID(i)->getNumStones() > 0)
		{
			GameBoard boardTemp(board); //store curr board, to restore later
			mTemp.nPit = i;
			board->doMove(strCurrPlayer, mTemp.nPit); //do the move
			mTemp.nHeuristic = Move(evalFunction(board, strCurrPlayer)).nHeuristic; //get board state heuristic now that the move has been made
			vMoves.push_back(mTemp); //Push move to vector for evaluation later

			//Do recursive call and pruning for next player
			if (strCurrPlayer == "NORTH") //min player
			{
				mTemp.nHeuristic = findBestMove(board, "SOUTH", depth + 1, maxdepth, alpha, m.nHeuristic).nHeuristic;
				if (m.nHeuristic < alpha)  
					break; 
				if (mTemp.nHeuristic < m.nHeuristic) 
					m.nHeuristic = mTemp.nHeuristic; 
			}
			else if (strCurrPlayer == "SOUTH") //max player
			{
				mTemp.nHeuristic = findBestMove(board, "NORTH", depth + 1, maxdepth, m.nHeuristic, beta).nHeuristic;
				if (m.nHeuristic > beta) 
					break; 
				if (mTemp.nHeuristic >= m.nHeuristic) 
					m.nHeuristic = mTemp.nHeuristic;
			}

			//Restore board state to before the "imagined" move
			board->setWinner(boardTemp.getWinner());
			for (int i = 0; i < 14; i++)
				board->findPitByID(i)->setNumStones(boardTemp.findPitByID(i)->getNumStones());
		}
	}
	
	//determine best move in our list of moves at this level via DFS
	int nBestMoveIndex = 0;
	int nBestHeuristic = 0;
	if (strCurrPlayer == "SOUTH") //max player
	{
		nBestHeuristic = INT_MIN; //ini to worst case
		for(unsigned int i = 0; i < vMoves.size(); i++)
			if (vMoves[i].nHeuristic > nBestHeuristic)
			{
				nBestMoveIndex = i;
				nBestHeuristic = vMoves[i].nHeuristic;
			}
	}
	else //Player = minPlayer = NORTH
	{
		nBestHeuristic = INT_MAX;  //ini to worst case
		for (unsigned int i = 0; i < vMoves.size(); i++)
			if (vMoves[i].nHeuristic < nBestHeuristic)
			{
				nBestMoveIndex = i;
				nBestHeuristic = vMoves[i].nHeuristic;
			}
	}

	if (vMoves.size() == 0)
		cout << "ERROR: Move vector is empty.\n";
	return vMoves[nBestMoveIndex];

}

//Determines and returns the board statue heuristic.
//A higher heuristic denotes a more desirable state for max player (SOUTH),
// and vice versa. The goal is to maximize num stones in player goal.
// For the min player we give the negation, because what's good for the min
// player is what's bad for the max player.
int AIPlayer::evalFunction(GameBoard *board, string player)
{
	int nHeuristic = 0;
	int nStonesInNorthGoal = board->findPitByID(13)->getNumStones();
	int nStonesInSouthGoal = board->findPitByID(6)->getNumStones();
	int nEmptyPitsOnSouthSide = board->getEmptyPitCount("SOUTH");
	int nEmptyPitsOnNorthSide = board->getEmptyPitCount("NORTH");
	if (player == "NORTH")
		return -(nStonesInNorthGoal);
	else if (player == "SOUTH")
		return nStonesInSouthGoal;
	return nHeuristic;
}