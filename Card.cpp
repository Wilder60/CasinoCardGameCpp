#include "Card.h"

/**********************************************************************
Function Name: Card
Purpose: Constructor to initilize the Card  class
Parameters: string a_name, int a_value
Return Value: none
Local Variables: none
Algorithm:
			1) assign m_cardname to a_name
			2) assign m_value to a_value
			3) assign owner to none
Assistance Received: none
**********************************************************************/

Card::Card(string a_name, int a_value)
{
	m_cardname = a_name;
	m_value = a_value;
	m_owner = "none";
}

/**********************************************************************
Function Name: Card
Purpose: Constructor to initilize the Card class
Parameters: Card* a_card
Return Value: none
Local Variables: none
Algorithm:
			1) assign m_cardname to a_card->getname()
			2) assign m_value to a_card->getvalue()
			3) assign owner to a_card->getowner()
Assistance Received: none
**********************************************************************/

Card::Card(Card *a_card) {
	m_cardname = a_card->getname();
	m_value = a_card->getvalue();
	m_owner = a_card->getowner();
}

/**********************************************************************
Function Name: isBuild
Purpose: virtual function for the build class
Parameters: Card* a_card
Return Value: bool false
Local Variables: none
Algorithm:
			1) return false
Assistance Received: none
**********************************************************************/

bool Card::isBuild() const{
	return false;
}

//Getters and Setters are below
vector<Card*> Card::getcards() const {
	return vector<Card*>();
}

int Card::buildSize() const {
	return 0;
}

Card* Card::getCard(int pos) const {
	Card* temp = new Card();
	return temp;
}

string Card::getname() const{
	return m_cardname;
}

int Card::getvalue() const {
	return m_value;
}

string Card::getowner() const {
	return m_owner;
}

void Card::setname(string a_name) {
	m_cardname = a_name;
}

void Card::setvalue(int a_value) {
	m_value = a_value;
}

void Card::setowner(string a_owner) {
	m_owner = a_owner;
}

bool Card::isMultiBuild() const {
	return false;
}