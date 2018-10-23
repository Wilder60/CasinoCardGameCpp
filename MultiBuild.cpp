#include "MultiBuild.h"

/**********************************************************************
Function Name: MultiBuild
Purpose: The default constructor for the MultiBuild class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) m_cardname = "NULL"
			2) m_value = 0
			3) m_owner = "NULL"
			4) m_cardList
Assistance Received: none
**********************************************************************/

MultiBuild::MultiBuild()
{
	m_cardname = "NULL";
	m_value = 0;
	m_owner = "NULL";
	m_cardList;
}

/**********************************************************************
Function Name: !MultiBuild
Purpose: The default destructor for the MultiBuild class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) m_cardname.clear
			2) m_value = 0
			3) m_owner.clear
			4) m_cardList.clear
Assistance Received: none
**********************************************************************/

MultiBuild::~MultiBuild()
{
	m_cardname.clear();
	m_value = 0;
	m_owner.clear();
	m_cardList.clear();
}

/**********************************************************************
Function Name: MultiBuild
Purpose: A constructor for adding to a Multibuild
Parameters: MultiBuild *a_Multibuild
			Build *a_build
Return Value: none
Local Variables: vector<Card*> cards
				 vector<Card*> build
Algorithm:
			1) set the name to be the name of the multibuild and the build + ]
			2) set the value to the value of a multibuild
			3) set the owner to the owner of the multibuild
			4) set build to a_Multibuild->getcards
			5) insert build to card vector
			6) repeat 4, 5 with a_build->getcards
Assistance Received: none
**********************************************************************/

MultiBuild::MultiBuild(MultiBuild *a_Multibuild, Build *a_build) {
	setname(a_Multibuild->getname().substr(0, a_Multibuild->getname().size() - 1) + a_build->getname() + " ]");
	setvalue(a_Multibuild->getvalue());
	setowner(a_Multibuild->getowner());
	vector<Card*> cards;
	vector<Card*> build = a_Multibuild->getcards();
	cards.insert(cards.end(), build.begin(), build.end());
	build = a_build->getcards();
	cards.insert(cards.end(), build.begin(), build.end());
	setCards(cards);

}

/**********************************************************************
Function Name: MultiBuild
Purpose: For creating a MultiBuild
Parameters: Build *a_build1, *a_build2
Return Value: none
Local Variables: vector<Card*> cards
				 vector<Card*> build
Algorithm:
			1) set the name to be the name of [ + build1 and build2 + ]
			2) set the value to the value of a build1
			3) set the owner to the owner of the build1
			4) set build to a_build1->getcards
			5) insert build to card vector
			6) repeat 4, 5 with a_build2->getcards
Assistance Received: none
**********************************************************************/

MultiBuild::MultiBuild(Build *a_build1, Build *a_build2) {
	setname("[" + a_build1->getname() + a_build2->getname() + "]");
	setvalue(a_build1->getvalue());
	setowner(a_build1->getowner());
	vector<Card*> cards;
	vector<Card*> build = a_build1->getcards();
	cards.insert(cards.end(), build.begin(), build.end());
	build = a_build2->getcards();
	cards.insert(cards.end(), build.begin(), build.end());
	setCards(cards);
}

/**********************************************************************
Function Name: MultiBuild
Purpose: The constructor for a multiBuild from a vector of builds for a file
Parameters: vector<Card*> a_buildlist
Return Value: none
Local Variables: string name
				 vector<Card*> buildcards, cardlist
Algorithm:
			1) for all the builds in a_buildlist
			2) add a_buildlist[i] name to name string
			3) set value to buildlist[0] value
			4) for all the builds in a_buildlist
			5) set cardlist to a_buildlist[i]
			6) insert cardlist into buildcards
			7) setcards to buildcards
			8) setowner to a_buildlist[0] owner
Assistance Received: none
**********************************************************************/

MultiBuild::MultiBuild(vector<Card*> a_buildlist) {
	string name = "[ ";
	for (int i = 0; i < a_buildlist.size(); i++) {
		name += a_buildlist[i]->getname() + " ";
	}
	name += "]";
	setname(name);
	setvalue(a_buildlist[0]->getvalue());
	vector<Card*> buildcards;
	for (int i = 0; i < a_buildlist.size(); i++) {
		vector<Card*> cardlist = a_buildlist[i]->getcards();
		buildcards.insert(buildcards.end(), cardlist.begin(), cardlist.end());
	}
	setCards(buildcards);
	setowner(a_buildlist[0]->getowner());
}

bool MultiBuild::isMultiBuild() const {
	return true;
}