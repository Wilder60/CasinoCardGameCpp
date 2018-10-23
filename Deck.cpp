
#include "Deck.h"

/**********************************************************************
Function Name: Deck
Purpose: Constructor to initilize the Deck class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) populate m_deck using the createDeck function
			2) shuffle m_deck using the shuffleDeck function
Assistance Received: none
**********************************************************************/

Deck::Deck()
{
	createDeck();
	shuffleDeck();
}

/**********************************************************************
Function Name: Deck
Purpose:
			Constructor to initilize the Deck class with a deck loaded in 
			from a file
Parameters: 
			vector<Card*> a_deck is the deck loaded in from the file
			from the file class
Return Value: none
Local Variables: none
Algorithm:
			1) assign m_deck = a_deck
Assistance Received: none
**********************************************************************/

Deck::~Deck() {
	m_deck.clear();
	m_deck.resize(0);
}

/**********************************************************************
Function Name: shuffleDeck
Purpose:
		To shuffle the m_deck vector to ensure a random draw
Parameters: none
Return Value: none
Local Variables: rand
Algorithm:
			1) seed the rand to the time
			2) call std::random_shuffle on the m_deck vector
Assistance Received: none
**********************************************************************/

void Deck::shuffleDeck() 
{
	srand(int(time(NULL)));
	random_shuffle(m_deck.begin(), m_deck.end());
}

/**********************************************************************
Function Name: createDeck
Purpose:
		To populate the m_deck vector with Card* for ever string in m_mastercardlist
Parameters: none
Return Value: none
Local Variables: Card* card
Algorithm:
			1) loop through the m_mastercardlist vector
			2) for every item create a card with the name of the item and the value being
			   the map look up
Assistance Received: none
**********************************************************************/

void Deck::createDeck()
{
	for (int i = 0; i < int(m_mastercardlist.size()); i++) {
		//creating a new card with the name begin the string at i and the value being
		//the result of a map look up
		Card *card = new Card(m_mastercardlist[i], m_cardvalue[m_mastercardlist[i].substr(1, 1)]);
		m_deck.push_back(card);
	}
}

/**********************************************************************
Function Name: emptyDeck
Purpose:
		To check to see if the deck is empty
Parameters: none
Return Value: true if m_deck is empty, else false
Local Variables: none
Algorithm:
			1) check to see if m_deck is empty
			2) return true if empty, false if not
Assistance Received: none
**********************************************************************/

bool Deck::emptyDeck()
{
	return m_deck.empty();
}

/**********************************************************************
Function Name: dealCards
Purpose:
		To deal 4 cards from the top of the deck and return them 
Parameters: none
Return Value: vector<Card*>
Local Variables: vector<Card*> cardSet
Algorithm:
			1) create the substring cardSet from m_deck 
			2) remove the first 4 cards from m_deck
			3) return cardSet 
Assistance Received: none
**********************************************************************/

vector<Card*> Deck::dealCards() 
{
	//creating the sub-vector with the first 4 cards
	vector<Card*> cardSet(m_deck.begin(), m_deck.begin() + 4);
	m_deck.erase(m_deck.begin(), m_deck.begin() + 4);
	return cardSet;
}

/**********************************************************************
Function Name: resetDeck
Purpose:
		to reset the deck for the next round
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) populate m_deck using the createDeck function
			2) shuffle m_deck using the shuffleDeck function
Assistance Received: none
**********************************************************************/

void Deck::resetDeck() 
{
	createDeck();
	shuffleDeck();
}

/**********************************************************************
Function Name: setDeck
Purpose:
		to import a deck from a save file
Parameters: vector<card*> a_deck
Return Value: none
Local Variables: none
Algorithm:
			1) copy a_deck to m_deck
Assistance Received: none
**********************************************************************/

void Deck::setDeck(vector<Card*> a_deck) {
	m_deck = a_deck;
}

/**********************************************************************
Function Name: getDeck
Purpose: return the deck for the save file
Parameters: none
Return Value: vector<Card*>
Local Variables: none
Algorithm:
			1) return m_deck
Assistance Received: none
**********************************************************************/

vector<Card*> Deck::getDeck() const{
	return m_deck;
}