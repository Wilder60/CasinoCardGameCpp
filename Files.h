#ifndef FILES_H
#define FILES_H
#include "BigIncludeFile.h"
#include "MultiBuild.h"
#include "Player.h"
#include "Build.h"
#include "Deck.h"
#include "Card.h"

class Files
{
public:
	Files();
	~Files();
	bool openfile();
	void populateRound(string a_round);
	void populateComputer(ifstream &a_myFile);
	void populateHuman(ifstream &a_myFile);
	void populateBoard(string a_boardline);
	void createBuild(string a_line);
	void createDeck(string a_line);
	void loadDeck(Deck *a_deck);
	void loadGame(Player *m_human, Player *m_computer, Deck *m_deck, Board *m_board, int &startpos, int &m_roundCount);
	void saveGame(Player *a_playerList[2], int a_turns, Deck *a_deck, Board *a_board, int a_roundcount);
private:
	int m_Roundcount;
	//-------------------------------------------------------------------------
	int m_humanScore;
	vector<Card*> m_humanHand;
	vector<Card*> m_humanPile;
	//-------------------------------------------------------------------------
	int m_computerScore;
	vector<Card*> m_computerHand;
	vector<Card*> m_computerPile;
	//-------------------------------------------------------------------------
	vector<Card*> m_board;
	vector<Card*> m_buildList;
	//-------------------------------------------------------------------------
	vector<Card*> m_deck;
	int m_nextplayer;
	//-------------------------------------------------------------------------
	map<string, int> m_cardvalue = {
	{"A", 1},
	{"2", 2},
	{"3", 3},
	{"4", 4},
	{"5", 5},
	{"6", 6},
	{"7", 7},
	{"8", 8},
	{"9", 9},
	{"X", 10},
	{"J", 11},
	{"Q", 12},
	{"K", 13}
	};

};

#endif // !FILES_H