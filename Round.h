#ifndef ROUND_H
#define ROUND_H
#include "BigIncludeFile.h"
#include "Computer.h"
#include "Player.h"
#include "Board.h"
#include "Files.h"
#include "Human.h"
#include "Deck.h"

class Round
{
public:

	//Constructors and Desturctors
	Round();
	~Round();
	string playRound(Player *a_playerList[2], int a_startpos, Deck *a_deck, Board *a_board, int a_roundcount, Files &a_files);
	void updateDisplay(Player *a_playerList[2], Board *a_board, Deck *a_deck);
	void tableToPile(Board *a_board, Player *a_playerList[2], string capturedLast);
private:
	int turns;
	string capturedLast;
};
#endif // !ROUND_H


