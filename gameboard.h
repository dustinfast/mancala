//////////////////////////////////
//GameBoard.h:
//A Mancala game board, represented as a circular linked list of pits
//
///Author: Dustin Fast Oct, 2017

#pragma once
#include "pit.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class GameBoard
{
public:
	GameBoard();							
	GameBoard(GameBoard *board);			
	~GameBoard();
	void setupGameBoard();					//Add initial pits/stones to game board
	void addItem(int ID, int numstones);	// Add new item to front of list, replacing head and tail.
	// void displayBoard(string currplayer);
	void displayBoardVerbose(string currplayer); // Output game board
	int getNextByID(int ID);				//gets a ptr to the next pit, given the id of a pit
	bool isMoveValid(string player, int pit); //checks to ensure a given move by player on pit is valid
	bool doMove(string player, int pit);	// returns true iff game should continue. i.e. one player has not ended the game by clearing their own row of stones
	Pit* findPitByID(int id);				//gets a ptr to a pit, given an ID number
	int getEmptyPitCount(string player);	//returns the number of empty pits on given players side
	bool emptyRowExists();					//returns true if an empty row (North or south) exists on the board
	void setWinner();						//sets the game winner, determined by max(stonesInGoalPit)
	void setWinner(string player);			//sets the game winner statically
	string getWinner();						//Returns game winner, or "" if not winner yet

private:
	Pit* m_pHead;           // Pointer to head element
	Pit* m_pLast;			// pointer to the last element};
	string m_strWinner;		// String value of winner. 
							//  Either NORTH, SOUTH, TIE, or "" if in progress
};

//default constructor
GameBoard::GameBoard()
{
	m_pHead = NULL;
	m_strWinner = "";
	setupGameBoard();
}
//Copy constructor. Accepts a ptr to a board and sets 'this' to a copy of
// that board and it's current pits/stones.
GameBoard::GameBoard(GameBoard *board)
{
	m_pHead = NULL;
	m_strWinner = "";
	setupGameBoard();
	for (int i = 0; i < 14; i++)
		this->findPitByID(i)->setNumStones(board->findPitByID(i)->getNumStones());
}

GameBoard::~GameBoard()
{
	Pit *p = m_pHead;
	Pit *pTemp;

	do
	{
		pTemp = p->getNext();
		delete p;
		p = pTemp;
	} while (p != m_pHead);
}

void GameBoard::setupGameBoard()
{
	for (int i = 13; i >= 0; i--)
		if (i == 6 || i == 13)
			this->addItem(i, 0); //add goal pit
		else
			this->addItem(i, 3); //add non-goal pit
	
}
// Adds new Pit with id of ID to the front of list
void GameBoard::addItem(int ID, int numstones)
{
	if (m_pHead == NULL)
	{
		m_pHead = new Pit(ID, NULL, numstones); //New list, make new head
		m_pLast = m_pHead;
		m_pLast->setNext(m_pHead); //Set last item to point back to the first
	}
	else
	{
		Pit *temp = new Pit(ID, m_pHead, numstones); //New item pointing to head
		m_pHead = temp; //Set head to the new item
		m_pLast->setNext(m_pHead); //Set tail to point back to the first
	}
}

//Get the next ID of the item with id of ID
int GameBoard::getNextByID(int ID)
{
	Pit *pTemp = m_pHead;
	do
	{
		if (pTemp->getID() == ID)
		{
			return pTemp->getNext()->getID();
		}
		pTemp = pTemp->getNext();
	} while (pTemp != m_pHead);
	return -1;
}

// // Output entire list with stone count arranged as A Mancala board.
// //if currplayer is are populated, those elements are highlighted.
// void GameBoard::displayBoard(string currplayer)
// {
// 	HANDLE hConsole;
// 	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// 	//output human, aka NORTH pits, in green.
// 	SetConsoleTextAttribute(hConsole, 10);
// 	cout << "\n      NORTH";
// 	if (currplayer == "NORTH")
// 		cout << "*";
// 	cout << "\n\n  ";
// 	cout << findPitByID(12)->getNumStones() << " ";
// 	cout << findPitByID(11)->getNumStones() << " ";
// 	cout << findPitByID(10)->getNumStones() << " ";
// 	cout << findPitByID(9)->getNumStones() << " ";
// 	cout << findPitByID(8)->getNumStones() << " ";
// 	cout << findPitByID(7)->getNumStones() << endl;

// 	//output computer, AKA SOUTH's goal pit, then NORTH's
// 	SetConsoleTextAttribute(hConsole, 10);
// 	cout << findPitByID(13)->getNumStones();
// 	cout << "             "; //spacer
// 	SetConsoleTextAttribute(hConsole, 12);
// 	cout << findPitByID(6)->getNumStones() << endl;

// 	//output computer, AKA SOUTH's pits, in red.
// 	SetConsoleTextAttribute(hConsole, 12);
// 	cout << "  ";
// 	cout << findPitByID(0)->getNumStones() << " ";
// 	cout << findPitByID(1)->getNumStones() << " ";
// 	cout << findPitByID(2)->getNumStones() << " ";
// 	cout << findPitByID(3)->getNumStones() << " ";
// 	cout << findPitByID(4)->getNumStones() << " ";
// 	cout << findPitByID(5)->getNumStones() << endl;
// 	cout << "\n      SOUTH";
// 	if (currplayer == "SOUTH")
// 		cout << "*";
// 	cout << endl << endl;

// 	//restore console text default color
// 	SetConsoleTextAttribute(hConsole, 7); 
// }

// Output entire list with stone count arranged as A Mancala board.
//if currplayer is are populated, those elements are highlighted.
//This function differs from displayBoard() in that it also displays pit ID #'s
//for the users convenience
void GameBoard::displayBoardVerbose(string currplayer)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//output human, aka NORTH pits, in green.
	SetConsoleTextAttribute(hConsole, 10);
	cout << "\n      NORTH";
	if (currplayer == "NORTH")
		cout << "*";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "\n\n  12  11  10  9   8   7\n  ";
	SetConsoleTextAttribute(hConsole, 10);

	cout << findPitByID(12)->getNumStones() << "   ";
	cout << findPitByID(11)->getNumStones() << "   ";
	cout << findPitByID(10)->getNumStones() << "   ";
	cout << findPitByID(9)->getNumStones() << "   ";
	cout << findPitByID(8)->getNumStones() << "   ";
	cout << findPitByID(7)->getNumStones() << endl;

	//output computer, AKA SOUTH's goal pit, then NORTH's
	SetConsoleTextAttribute(hConsole, 10);
	cout << findPitByID(13)->getNumStones();
	cout << "                       "; //spacer
	SetConsoleTextAttribute(hConsole, 12);
	cout << findPitByID(6)->getNumStones() << endl;

	//output computer, AKA SOUTH's pits, in red.
	SetConsoleTextAttribute(hConsole, 12);
	cout << "  ";
	cout << findPitByID(0)->getNumStones() << "   ";
	cout << findPitByID(1)->getNumStones() << "   ";
	cout << findPitByID(2)->getNumStones() << "   ";
	cout << findPitByID(3)->getNumStones() << "   ";
	cout << findPitByID(4)->getNumStones() << "   ";
	cout << findPitByID(5)->getNumStones() << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "  0   1   2   3   4   5\n  ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n      SOUTH";
	if (currplayer == "SOUTH")
		cout << "*";
	cout << endl << endl;

	//restore console text default color
	SetConsoleTextAttribute(hConsole, 7);
}

//returns true iff move is valid
bool GameBoard::isMoveValid(string player, int pit)
{
	//if player is properly formatted
	if (!(player == "NORTH" || player == "SOUTH"))
		return false;
	//if move is out of bounds or is a goal pit
	if (pit < 0 || pit > 13 || pit == 6 || pit == 13)
		return false;
	//if move is on the wrong side of the board for curr player
	if (player == "SOUTH" && !(pit >= 0 && pit <= 5))
		return false;
	if (player == "NORTH" && !(pit >= 7 && pit <= 12))
		return false; 
	//if chosen pit has no stones in it
	if (findPitByID(pit)->getNumStones() == 0)
		return false;

	return true;
}

// Returns true iff game should continue. i.e. if one player has not ended the 
// game by clearing their own row of stones
// Will throw an exception if given move is not valid - Validate the move first
// with isMoveValid() to avoid.
bool GameBoard::doMove(string player, int pit)
{
	//ensure move is valid before attempting
	if (!isMoveValid(player, pit))
		cout << "An invalid move was attempted on pit # " + to_string(pit) + " by player " + player;

	//ensure move is not being performed on a board with a winner
	if (emptyRowExists())
		cout << "A move was attempted on a board that has already been won.";

	Pit *pMoveFrom = findPitByID(pit);
	int nStonesInHand = pMoveFrom->getNumStones();
	pMoveFrom->setNumStones(0);

	while (nStonesInHand > 0)
	{
		pMoveFrom = pMoveFrom->getNext();
		//If on any pit except opposing player goal, drop a stone in it from stonesInHand
		if (!(player == "NORTH" && pMoveFrom->getID() == 6) && !(player == "SOUTH" && pMoveFrom->getID() == 13)) 
		{
			pMoveFrom->setNumStones(pMoveFrom->getNumStones() + 1);
			nStonesInHand--;
		}
	}

	//If we dropped the last stone on the moving players non-goal pit and 
	// there's only one stone in the pit, capture the adjacent cell's stones.
	int nID = pMoveFrom->getID();
	if (pMoveFrom->getNumStones() == 1 && nID != 13 && nID != 6 && ((player == "SOUTH" && nID >= 0 && nID <= 5) || (player == "NORTH" && nID >= 7 && nID <= 12)))
	{
		int nTakeFromID = abs(nID - 12);
		int nCaptured = findPitByID(nTakeFromID)->getNumStones();
		findPitByID(nTakeFromID)->setNumStones(0);
		if (player == "SOUTH")
			findPitByID(6)->setNumStones(findPitByID(6)->getNumStones() + nCaptured);
		else
			findPitByID(13)->setNumStones(findPitByID(13)->getNumStones() + nCaptured);
	}

	//Check if there exists an empty row. 
	if (emptyRowExists())
	{
		//If NORTH Cleared their board. Get all of SOUTH's stones and put them into SOUTH's goal
		if (player == "NORTH" && getEmptyPitCount("NORTH") == 6)
		{
			findPitByID(6)->setNumStones(findPitByID(6)->getNumStones()
				+ findPitByID(0)->getNumStones()
				+ findPitByID(1)->getNumStones()
				+ findPitByID(2)->getNumStones()
				+ findPitByID(3)->getNumStones()
				+ findPitByID(4)->getNumStones()
				+ findPitByID(5)->getNumStones());
			findPitByID(0)->setNumStones(0);
			findPitByID(1)->setNumStones(0);
			findPitByID(2)->setNumStones(0);
			findPitByID(3)->setNumStones(0);
			findPitByID(4)->setNumStones(0);
			findPitByID(5)->setNumStones(0);
		}
		//If NORTH Cleared SOUTH's board. Get all of NORTH's stones and put them into NORTH's goal
		else if (player == "NORTH" && getEmptyPitCount("SOUTH") == 6)
		{
			findPitByID(13)->setNumStones(findPitByID(13)->getNumStones()
				+ findPitByID(12)->getNumStones()
				+ findPitByID(11)->getNumStones()
				+ findPitByID(10)->getNumStones()
				+ findPitByID(9)->getNumStones()
				+ findPitByID(8)->getNumStones()
				+ findPitByID(7)->getNumStones());
			findPitByID(12)->setNumStones(0);
			findPitByID(11)->setNumStones(0);
			findPitByID(10)->setNumStones(0);
			findPitByID(9)->setNumStones(0);
			findPitByID(8)->setNumStones(0);
			findPitByID(7)->setNumStones(0);
		}
		//If SOUTH Cleared their board. Get all of NORTH's stones and put them into NORTH's goal
		else if (player == "SOUTH" && getEmptyPitCount("SOUTH") == 6)
		{
			findPitByID(13)->setNumStones(findPitByID(13)->getNumStones()
				+ findPitByID(12)->getNumStones()
				+ findPitByID(11)->getNumStones()
				+ findPitByID(10)->getNumStones()
				+ findPitByID(9)->getNumStones()
				+ findPitByID(8)->getNumStones()
				+ findPitByID(7)->getNumStones());
			findPitByID(12)->setNumStones(0);
			findPitByID(11)->setNumStones(0);
			findPitByID(10)->setNumStones(0);
			findPitByID(9)->setNumStones(0);
			findPitByID(8)->setNumStones(0);
			findPitByID(7)->setNumStones(0);
		}
		//If SOUTH Cleared NORTH's board. Get all of SOUTH's stones and put them into SOUTH's goal
		else if (player == "SOUTH" && getEmptyPitCount("NORTH") == 6)
		{
			findPitByID(6)->setNumStones(findPitByID(6)->getNumStones()
				+ findPitByID(0)->getNumStones()
				+ findPitByID(1)->getNumStones()
				+ findPitByID(2)->getNumStones()
				+ findPitByID(3)->getNumStones()
				+ findPitByID(4)->getNumStones()
				+ findPitByID(5)->getNumStones());
			findPitByID(0)->setNumStones(0);
			findPitByID(1)->setNumStones(0);
			findPitByID(2)->setNumStones(0);
			findPitByID(3)->setNumStones(0);
			findPitByID(4)->setNumStones(0);
			findPitByID(5)->setNumStones(0);
		}
		
		setWinner(); //Empty rowfound, so determine winner.
		return false;
	}

	return true;
}

//Returns a ptr to a pit, given that pits ID number
Pit* GameBoard::findPitByID(int id)
{
	//find the node with the given id
	Pit *pTemp = m_pHead;
	do
	{
		if (pTemp->getID() == id)
			return pTemp;
		pTemp = pTemp->getNext();
	} while (pTemp != m_pHead);
	return nullptr;
}

//Returns the number of empty pits for the specified player
int GameBoard::getEmptyPitCount(string player)
{
	int nCount = 0;
	if (player == "NORTH")
	{
		for (int i = 7; i < 13; i++)
		{
			if (findPitByID(i)->getNumStones() == 0)
				nCount++;
		}
	}
	else if (player == "SOUTH")
	{
		for (int i = 0; i < 6; i++)
		{
			if (findPitByID(i)->getNumStones() == 0)
				nCount++;
		}
	}
	return nCount;
}

//Returns true iff all north sides pits are empty 
// OR all south side's pits are empty.
bool GameBoard::emptyRowExists()
{
	//Check north side
	int nCount = 0;
	for (int i = 7; i < 13; i++)
	{
		if (findPitByID(i)->getNumStones() == 0)
			nCount++;
	}
	if (nCount == 6)
		return true;

	//Check south side
	nCount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (findPitByID(i)->getNumStones() == 0)
			nCount++;
	}
	if (nCount == 6)
		return true;

	return false;
}

//Set a winner based on max(playergoalstonecount)
void GameBoard::setWinner()
{
	if (findPitByID(6)->getNumStones() > findPitByID(13)->getNumStones())
		m_strWinner = "SOUTH";
	else if (findPitByID(13)->getNumStones() > findPitByID(6)->getNumStones())
		m_strWinner = "NORTH";
	else
		m_strWinner = "TIE";
}

void GameBoard::setWinner(string player)
{
	m_strWinner = player;
}

string GameBoard::getWinner()
{
	return m_strWinner;
}