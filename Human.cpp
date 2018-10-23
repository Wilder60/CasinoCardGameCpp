#include "Human.h"

/**********************************************************************
Function Name: Human
Purpose: default constructor of the Human class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) set m_name = Human
Assistance Received: none
**********************************************************************/

Human::Human() {
	m_name = "Human";
}

/**********************************************************************
Function Name: ~Human
Purpose: Destructor of the Human class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) clear the m_name
			2) resize the m_name to zero
Assistance Received: none
**********************************************************************/

Human::~Human() {
	m_name.clear();
	m_name.resize(0);
}


/**********************************************************************
Function Name: play
Purpose: prompts the user for a move to make
Parameters: Board *a_board
			string &capturedLast
Return Value: none
Local Variables: int move
				 bool success = false
Algorithm:
			1) prompt the user for an input 0 - 3
			2) if prompt not 0 - 3 then goto 1)
			3) while success == false
			4) if move == 0 then call Build function
			5) if move == 1 then call Capture function and set capturedLast to getname
			6) if move == 2 then call Trail function
			7) if move == 3 then call Help function
Assistance Received: none
**********************************************************************/

void Human::play(Board *a_board, string &capturedLast) {
	int move;
	bool success = false;
	do {
		cout << "Would you like to:\n0.BUILD\n1.CAPTURE\n2.TRAIL\n3.HELP: ";
		cin >> move;
		if (move == 0) {
			success = Build(a_board);
		}

		else if (move == 1) {
			success = Capture(a_board);
			capturedLast = getName();
		}

		else if (move == 2) {
			success = Trail(a_board);
		}

		else if (move == 3) {
			Help(a_board);
		}

		else {
			cout << "Invalid Command" << endl;
		}
	} while (success == false);
}

/**********************************************************************
Function Name: Build
Purpose: the starting function for creating a build or Multibuild
Parameters: Board *a_board
Return Value: bool
Local Variables: int cardPos
Algorithm:
			1) if the m_hand size is less then 2 then return false
			2) call the selectCard function
			3) call the createBuild function with the board and the card
				from the hand
Assistance Received: none
**********************************************************************/

bool Human::Build(Board *a_board) 
{
	if (m_hand.size() < 2) {
		cout << "You can't create a build with less them two cards" << endl;
		return false;
	}

	cout << "\nEnter the number of the card you want to BUILD with" << endl;
	int cardPos = selectCard();

	return createBuild(a_board, m_hand[cardPos]);
}

/**********************************************************************
Function Name: Capture
Purpose: prompts the user for a move to make
Parameters: Board *a_board
			string &capturedLast
Return Value: none
Local Variables: int move
				 bool success = false
Algorithm:
			1) call selectCard function
			2) return captureSets with the board and the card from the hand
Assistance Received: none
**********************************************************************/

bool Human::Capture(Board *a_board) 
{
	cout << "\nEnter the number of the card you want to CAPTURE with" << endl;
	int cardPos = selectCard();
	return captureSets(a_board, m_hand[cardPos]);
}

/**********************************************************************
Function Name: Trail
Purpose: prompts the user for a move to make
Parameters: Board *a_board
			string &capturedLast
Return Value: none
Local Variables: int move
				 bool success = false
Algorithm:
			1) if the user owns a build then return false
			2) call selectCard function
			3) call trailCard function with board and hand
			4) return true
Assistance Received: none
**********************************************************************/

bool Human::Trail(Board *a_board) 
{
	if (ownBuild(a_board)) {
		cout << "You cannot trail a card if you own a build" << endl;
		return false;
	}


	cout << "Enter the card that you want to TRAIL with" << endl;
	int cardPos = selectCard();
	trailCard(a_board, m_hand[cardPos]);
	return true;
}

/**********************************************************************
Function Name: Help
Purpose: gets a recommend move from the AI
Parameters: Board *a_board
Return Value: none
Local Variables: string cardname, reasonwhy
Algorithm:
			1) print the result of generateMove and the cardname and the reasonwhy
Assistance Received: none
**********************************************************************/

void Human::Help(Board *a_board) {
	string cardname, reasonwhy;
	cout << "The computer recommends to " << generateMove(a_board->getBoard(), gethand(), cardname, reasonwhy) <<
		" with " << cardname << "\n" << reasonwhy << endl;
}

/**********************************************************************
Function Name: getInput
Purpose: gets the users input on a set of cards
Parameters: vector<vector<Card*>> cardlist
Return Value: int
Local Variables: int input
Algorithm:
			1) if the cardlist is empty then return -1
			2) dispaly each cardlist and the number pos corrisponding to it
			3) prompt the user for an number from -1 to cardlist size
			4) if input < -1 or input > cardlist size GOTO 3
			5) return input
Assistance Received: none
**********************************************************************/

int Human::getInput(vector<vector<Card*>> cardlist) {

	if (cardlist.empty()) {
		return -1;
	}

	for (int i = 0; i < int(cardlist.size()); i++) {
		cout << i << ". ";
		for (int j = 0; j < int(cardlist[i].size()); j++) {
			cout << cardlist[i][j]->getname() << " ";
		}
		cout << endl;
	}

	int input;
	cout << "Enter the number next to the set of cards you want to take or press -1 to cancel: ";

	do {
		cin >> input;
	} while (input < -2 && input > int(cardlist.size()));

	return input;
}

/**********************************************************************
Function Name: selectCard
Purpose: prompts the user to select a cardpos from the hand
Parameters: none
Return Value: int 
Local Variables: int cardPos
Algorithm:
			1) display all the cards in the hand and their corrisponding position
			2) prompt the user for a number from 0 to m_hand size -1
			3) if cardPos < 0 or cardPos > m_hand size GOTO 2
			4) return cardPosS
Assistance Received: none
**********************************************************************/

int Human::selectCard() {
	int cardPos;
	for (int i = 0; i < int(m_hand.size()); i++) {
		cout << i << ". " << m_hand[i]->getname() << "\t";
	}
	cout << endl;
	do {
		cout << "Enter here: ";
		cin >> cardPos;
	} while (cardPos >= int(m_hand.size()));

	return cardPos;
}

/**********************************************************************
Function Name: inHand
Purpose: gets the card from the users hand or return -1 if not in hand
Parameters: string a_cardname
Return Value: none
Local Variables: none
Algorithm:
			1) loop through hand
			2) if card in hand name == a_cardname then return i
			3) return -1
Assistance Received: none
**********************************************************************/

int Human::inHand(string a_cardname) {
	for (int i = 0; i < int(m_hand.size()); i++) {
		if (m_hand[i]->getname() == a_cardname) {
			return i;
		}
	}
	return -1;
}
