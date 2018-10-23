#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include "BigIncludeFile.h"
#include "Computer.h"
#include "Player.h"
#include "Files.h"
#include "Human.h"
#include "Round.h"
#include "Deck.h"

class Tournament
{
public:
	Tournament();
	~Tournament();
	void setupGame();
	void setupNewGame(Player *a_human, Player *a_computer, Deck *a_deck, Board *a_board);
	bool coinflip();
	void calculatePoints();
	void postGameStats(int numberOfSpades[2]);
private:
	Player* m_playerList[2];
	int m_roundCount;
	int startpos;
};

#endif // !TOURNAMENT_H