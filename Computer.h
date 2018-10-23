#ifndef COMPUTER_H
#define COMPUTER_H
#include "BigIncludeFile.h"
#include "Player.h"
#include "Card.h"

class Computer : public Player
{
public:
	void play(Board *a_board, string &capturedLast);
	Card* getCard(string a_cardname);
	int getInput(vector<vector<Card*>> cardlist);

private:
};

#endif // !COMPUTER_H
