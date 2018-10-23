#ifndef DECK_H
#define DECK_H

#include "BigIncludeFile.h"
#include "Player.h"
#include "Board.h"
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();
	void createDeck();
	//uses <algorthim> random_shuffle to randomize the deck
	void shuffleDeck();
	vector<Card*> dealCards();
	void resetDeck();
	//checking to see if the deck is empty meaning the round ends
	bool emptyDeck();
	void setDeck(vector<Card*> a_deck);
	vector<Card*> getDeck() const;

private:
	//vector of Card* to hold the deck
	vector<Card*> m_deck;
	//The list of all the card names in a deck
	vector<string> m_mastercardlist = {
		"C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CX", "CJ", "CQ", "CK", "CA",
		"S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "SX", "SJ", "SQ", "SK", "SA",
		"D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DX", "DJ", "DQ", "DK", "DA",
		"H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "HX", "HJ", "HQ", "HK", "HA"
	};
	//map to convert the card name to the value
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

#endif // !