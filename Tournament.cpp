#include "Tournament.h"

/**********************************************************************
Function Name: Tournament
Purpose: Constructor to initilize the Tournament class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) set m_roundcount = 0
			2) startpos = 0
Assistance Received: none
**********************************************************************/

Tournament::Tournament()
{
	m_roundCount = 0;
	startpos = 0;
}

/**********************************************************************
Function Name: ~Tournament
Purpose: Destructor to initilize the Round class
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
**********************************************************************/

Tournament::~Tournament()
{
}

/**********************************************************************
Function Name: setupGame
Purpose: to set up the Tournament and start playing
Parameters: none
Return Value: none
Local Variables: string nextPlayer, input
				 Files m_files
				 Human *m_human
				 Computer *m_computer
				 Deck *m_deck
				 Board *m_board
				 Round *m_Round
Algorithm:
			1) if the user wants to load a file then
			2) call openfile and loadGame function
			3) else call setupNewGame function
			4) while m_human or m_computer score is less then 21
			5) create a new round and call playRound function
Assistance Received: none
**********************************************************************/

void Tournament::setupGame()
{
	string nextPlayer, input;

	Files m_files;
	Human* m_human = new Human();
	Computer* m_computer = new Computer();
	Deck *m_deck = new Deck();
	Board *m_board = new Board();

	cout << "Welcome to Casino!  A card game of skill and luck!" << endl;
	do{
		cout << "Would you like to load in a file (Y/N): ";
		cin >> input;
	} while (input != "Y" && input != "N");
	if ("Y" == input) {
		if (!m_files.openfile()) {
			exit(1);
		}
		do {
			cout << "Would you like to load a save game or a deck: (S/D) ";
			cin >> input;
		} while (input != "S" && input != "D");
		if (input == "S") {
			m_files.loadGame(m_human, m_computer, m_deck, m_board, startpos, m_roundCount);
		} 
		else{
			m_files.loadDeck(m_deck);
			setupNewGame(m_human, m_computer, m_deck, m_board);
		}
	}
	else{
		if (!coinflip()) {
			startpos = 1;
		}
		setupNewGame(m_human, m_computer, m_deck, m_board);
	}

	//populating the Player array
	m_playerList[0] = m_human;
	m_playerList[1] = m_computer;

	do{
		Round* m_Round = new Round();
		nextPlayer = m_Round->playRound(m_playerList, startpos, m_deck, m_board, m_roundCount, m_files);
		m_roundCount++;

		if (nextPlayer == "Human") {
			startpos = 0;
		}
		else {
			startpos = 1;
		}

		m_deck->resetDeck();
		calculatePoints();
		setupNewGame(m_human, m_computer, m_deck, m_board);

	} while (m_human->getScore() < 21 && m_computer->getScore() < 21);

	if (m_playerList[0]->getScore() >= 21 && m_playerList[1]->getScore() >= 21) {
		cout << m_playerList[0]->getName() << " has tied with " << m_playerList[1]->getName() << "!";
	}
	else if (m_playerList[0]->getScore() >= 21) {
		cout << m_playerList[0]->getName() << " has WON!";
	}
	else {
		cout << m_playerList[1]->getName() << " has WON!";
	}
}

/**********************************************************************
Function Name: setupNewGame
Purpose: To set up a new game that isnt loaded from a file
Parameters: Player *a_human
			Player *a_computer
			Deck *a_deck
			Board *a_board
Return Value: none
Local Variables: none
Algorithm: 
			1) clear both m_human's and m_computer's pile
			2) set the human hand with 4 cards from the deck
			3) set the computer hand with 4 cards from the deck
			4) set the users board with 4 cards from the deck
Assistance Received: none
**********************************************************************/

void Tournament::setupNewGame(Player *a_human, Player *a_computer, Deck *a_deck, Board *a_board) {

	a_human->clearPile();
	a_computer->clearPile();
	a_human->setHand(a_deck->dealCards());
	a_computer->setHand(a_deck->dealCards());
	a_board->setBoard(a_deck->dealCards());
}

/**********************************************************************
Function Name: coinflip
Purpose: to decide who goes first or second
Parameters: none
Return Value: bool
Local Variables:
				string coinFlip
				int x
Algorithm:
			1) prompt the user for an input
			2) if the user enters H or T then
			3) if H and 0 or T and 1 then
			4) return true
			5) else return false
			6) else prompt the user again
Assistance Received: none
**********************************************************************/

bool Tournament::coinflip() {

	srand(int(time(NULL)));
	string coinFlip;
	int x = rand() % 2;

	cout << "Enter H for heads and T for tails: ";
	do {
		cin >> coinFlip;
		if (coinFlip != "H" && coinFlip != "T") {
			cout << "Enter H for heads, T for tails: ";
		}
	} while (coinFlip != "H" && coinFlip != "T");

	if (coinFlip == "H" && x == 0 || coinFlip == "T" && x == 1) {
		return true;
	}
	return false;
}

/**********************************************************************
Function Name: calculatePoints
Purpose: To calculate the points that each player has
Parameters: none
Return Value: none
Local Variables: vector<Card*> pilevector
				 int numberOfSpades[2]
Algorithm:
			1) if m_playerList[0] pile size is greater then m_playerList[1] pile size then
			2) increase m_playerList[0] score by 3
			3) else if m_playerList[0] size is less then m_playerList[1] pile size then
			4) increase m_playerList[1] score by 3
			5) loop throught m_playerList
			6) loop throught each m_playerlist pile
			7) if card in the pile == S then increase numberOfSpades[i]++
			8) if card in the pile == A then increase m_playerList[i] score by 1
			9) if card in the pile == DX then increase m_playerList[i] score by 2
		   10) if card in the pile == S2 then increase m_playerList[i] score by 1
		   11) if numberOfSpades[0] pile size is greater then numberOfSpades[1] pile size then
		   12) increase numberOfSpades[0] score by 3
		   13) else if numberOfSpades[0] size is less then numberOfSpades[1] pile size then
		   14) increase numberOfSpades[1] score by 3
Assistance Received: none
**********************************************************************/
void Tournament::calculatePoints() {
	if (m_playerList[0]->getPileSize() > m_playerList[1]->getPileSize()) {
		m_playerList[0]->increaseScore(3);
	}
	else if (m_playerList[0]->getPileSize() < m_playerList[1]->getPileSize()) {
		m_playerList[1]->increaseScore(3);
	}

	int numberOfSpades[2] = {0, 0};
	vector<Card*> pilevector;
	for (int i = 0; i < 2; i++) {
		pilevector = m_playerList[i]->getPile();
		for (int j = 0; j < pilevector.size(); j++) {
			if (pilevector[j]->getname().substr(0, 1) == "S") {
				numberOfSpades[i]++;
			}
			if (pilevector[j]->getname().substr(1, 1) == "A") {
				m_playerList[i]->increaseScore(1);
			}
			else if (pilevector[j]->getname() == "DX") {
				m_playerList[i]->increaseScore(2);
			}
			else if (pilevector[j]->getname() == "S2") {
				m_playerList[i]->increaseScore(1);
			}
		}
	}
	
	if (numberOfSpades[0] > numberOfSpades[1]) {
		m_playerList[0]->increaseScore(1);
	}
	else if (numberOfSpades[0] < numberOfSpades[1]) {
		m_playerList[1]->increaseScore(1);
	}
	postGameStats(numberOfSpades);
}

/**********************************************************************
Function Name: postGameStats
Purpose: To print the piles and the scores of both players
Parameters: int numberOfSpades[2]
Return Value: none
Local Variables: none
Algorithm:
			1) clear the screen
			2) display the round count
			3) display the human score and the pile
			4) display the computer score and the pile
Assistance Received: none
**********************************************************************/

void Tournament::postGameStats(int numberOfSpades[2]) {
	system("cls");
	cout << "END OF ROUND: " << m_roundCount << endl;
	cout << m_playerList[0]->getName() << "'s score is : " << m_playerList[0]->getScore() << endl;
	cout << m_playerList[0]->getName() << "'s pile: ";
	m_playerList[0]->displayPile();
	cout << "\nNumber of Spades is: " << numberOfSpades[0] << endl;
	cout << "\n\n\n";
	cout << m_playerList[1]->getName() << "'s score is : " << m_playerList[1]->getScore() << endl;
	cout << m_playerList[1]->getName() << "'s pile: ";
	m_playerList[1]->displayPile();
	cout << "\nNumber of Spades is: " << numberOfSpades[1] << endl;
	cout << "\n";
	system("pause");
}
