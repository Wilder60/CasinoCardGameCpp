#include "Build.h"

/**********************************************************************
Function Name: Build
Purpose: The default constructor for the Build class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) m_cardname = "NULL"
			2) m_value = 0
			3) m_owner = "NULL"
Assistance Received: none
**********************************************************************/

Build::Build()
{
	m_cardname = "NULL";
	m_value = 0;
	m_owner = "NULL";
}

/**********************************************************************
Function Name: ~Build
Purpose: The Destructor for the Build class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) m_cardname.clear()
			2) m_cardList.clear()
			3) m_value = 0
			4) m_owner.clear()
Assistance Received: none
**********************************************************************/

Build::~Build()
{
	m_cardname.clear();
	m_cardList.clear();
	m_value = 0;
	m_owner.clear();
}

/**********************************************************************
Function Name: Build
Purpose: The constructor to create a build or extend a build
Parameters: vector<Card*> a_buildCards
			string a_owner
Return Value: none
Local Variables: string buildName, name
				 vector<Card*> temp
				 int total
Algorithm:
			1) loop through a_buildCards
			2) if card at i is a build then
			3) remove the first and last character
			4) add the name to buildname
			5) add the value to the total
			6) loop through the a_buildCards vector and the cards to m_cardList
			7) else add card name to buildname
			8) add the value of the card to total
			9) add the card to m_cardList
		   10) setname, value and total
Assistance Received: none
**********************************************************************/

Build::Build(vector<Card*> a_buildCards, string a_owner) {
	string buildName = "[";
	int total = 0;
	for (int i = 0; i < int(a_buildCards.size()); i++) {
		if (a_buildCards[i]->isBuild()) {
			string name = a_buildCards[i]->getname();
			name = name.erase(0, 1);
			name.pop_back();
			buildName += name + " ";
			total += a_buildCards[i]->getvalue();
			vector<Card*> temp = a_buildCards[i]->getcards();
			for (int j = 0; j < temp.size(); j++) {
				m_cardList.push_back(temp[j]);
			}
		}
		else {
			buildName += a_buildCards[i]->getname() + " ";
			total += a_buildCards[i]->getvalue();
			m_cardList.push_back(a_buildCards[i]);
		}
	}
	buildName.erase(buildName.size() - 1);
	buildName += "]";
	setname(buildName);
	setvalue(total);
	m_owner = a_owner;
}

vector<Card*> Build::getcards() const{
	return m_cardList;
}

bool Build::isBuild() const{
	return true;
}

int Build::buildSize() const {
	return m_cardList.size();
}

Card* Build::getCard(int pos) const {
	return m_cardList[pos];
}

void Build::setCards(vector<Card*> cardlist) {
	m_cardList = cardlist;
}

bool Build::isMultiBuild() const {
	return false;
}