#ifndef BOARD_H
#define BOARD_H

#include "BigIncludeFile.h"
#include "Card.h"

class Board
{
public:
	//sets the card a user plays on to the board
	Board();
	~Board();
	void clearboard();
	void deleteCard(int a_pos);
	void deleteCard(string a_cardname);
	string stringifyBoard();
	//Getters and Setters
	vector<Card*> getBoard() const;
	string getCardname(int a_pos) const;
	Card* getCard(int a_pos) const;
	int getSize() const;
	void setCard(Card *a_card);
	void setBoard(vector<Card*> a_board);
private:
	vector<Card*> m_Board;
};

#endif // ! BOARD_H