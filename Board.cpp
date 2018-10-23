#include "Board.h"

/**********************************************************************
Function Name: Board
Purpose: Constructor to initilize the Board class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) clear the board
			2) resize the board to zero
Assistance Received: none
**********************************************************************/

Board::Board() {
	m_Board.clear();
	m_Board.resize(0);
}

Board::~Board() {

}

/**********************************************************************
Function Name: stringifyBoard
Purpose: returns a string of all the cards on the board
Parameters: none
Return Value: string
Local Variables: string board
Algorithm:
			1) look through the board and add the name of the card and a space
			2) return board string
Assistance Received: none
**********************************************************************/

string Board::stringifyBoard() {
	string board = " ";
	for (int i = 0; i < int(m_Board.size()); i++) {
		board += m_Board[i]->getname() + " ";
	}
	
	return board;
}

/**********************************************************************
Function Name: deleteCard
Purpose: removing a card from the board that has the same name
Parameters: string a_name
Return Value: none
Local Variables: none
Algorithm:
			1) loop through the board
			2) if the card at i's name is equal to a_cardname delete that card
			3) return
Assistance Received: none
**********************************************************************/

void Board::deleteCard(string a_cardname) {
	for (int i = 0; i < int(m_Board.size()); i++) {
		if (a_cardname == m_Board[i]->getname()) {
			m_Board.erase(m_Board.begin() + i);
			return;
		}
	}
}

void Board::clearboard() {
	m_Board.clear();
}

void Board::deleteCard(int a_pos) {
	m_Board.erase(m_Board.begin() + a_pos);
}

void Board::setCard(Card *a_card) {
	m_Board.push_back(a_card);
}

void Board::setBoard(vector<Card*> a_Board){
	m_Board = a_Board;
}

string Board::getCardname(int a_pos) const {
	return m_Board[a_pos]->getname();
}

Card* Board::getCard(int a_pos) const {
	return m_Board[a_pos];
}

vector<Card*> Board::getBoard() const {
	return m_Board;
}

int Board::getSize() const {
	return m_Board.size();
}