#ifndef HUMAN_H
#define HUMAN_H
#include "BigIncludeFile.h"
#include "Player.h"
#include "Build.h"
#include "Board.h"
#include "Card.h"

class Human: public Player
{
public:
	Human();
	~Human();
	void play(Board *a_board, string &capturedLast);
	int selectCard();
	int inHand(string cardname);
	int getInput(vector<vector<Card*>> cardlist);
	bool Build(Board *a_board);
	bool Capture(Board *a_board);
	bool Trail(Board *a_board);
	void Help(Board *a_board);
private:
};
#endif // !HUMAN_H