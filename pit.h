//////////////////////////////////
// pit.h: Representation of a pit on a Mancala board.
//
///Author: Dustin Fast Oct, 2017

#pragma once

using namespace std;

class Pit
{
private:
	int m_nID;
	int m_nStones;
	Pit* m_pNext;
public:
	Pit();
	Pit(int m_nID, Pit* m_pNext, int numstones);
	int getID();
	void setID(int m_nID);
	Pit* getNext();
	void setNext(Pit *m_pNext);
	int getNumStones();
	void setNumStones(int numstones);
};

Pit::Pit() : m_nID(-1), m_pNext(NULL)
{
}

Pit::Pit(int ID, Pit* next, int numstones) : m_nID(ID), m_pNext(next), m_nStones(numstones)
{
}

int Pit::getID()
{
	return m_nID;
}
void Pit::setID(int ID)
{
	m_nID = ID;
}
Pit* Pit::getNext()
{
	return m_pNext;
}
void Pit::setNext(Pit *next)
{
	m_pNext = next;
}
int Pit::getNumStones()
{
	return m_nStones;
}
void Pit::setNumStones(int numstones)
{
	m_nStones = numstones;
}