#include "Round.h"

/**********************************************************************
Function Name: Round
Purpose: Constructor to initilize the Round class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) set turns = 0
			2) clear the capturedLast Variable
Assistance Received: none
**********************************************************************/

Round::Round()
{
	turns = 0;
	capturedLast.clear();
}

/**********************************************************************
Function Name: ~Round
Purpose: destructor to initilize the Deck class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) capturedLast.clear
			2) resized capturedLast to 0
Assistance Received: none
**********************************************************************/

Round::~Round()
{
	capturedLast.clear();
	capturedLast.resize(0);
}

/**********************************************************************
Function Name: playRound
Purpose: Plays a round of Casino game until both the deck and hand is empty
Parameters: Player *a_playerList[2]
			int a_startpos
			Deck *a_deck
			Board *a_board

Return Value: string
Local Variables: string input
Algorithm:
			1) add a_startpos to turns
			2) call updateDisplay to initize the display
			3) Ask the user if they want to save
			3) while the hands are not empty each person make a move one
				after another
			4) if the deck is not empty, refill the hands and repeat step 3
			5) if the deck is empty return name of the person last captured
Assistance Received: none
**********************************************************************/

string Round::playRound(Player *a_playerList[2], int a_startpos, Deck *a_deck, Board *a_board, int a_roundcount, Files &a_files) {

	turns += a_startpos;
	updateDisplay(a_playerList, a_board, a_deck);
	string input;

	do{	
		do{
			cout << "Would you like to save the game state (Y/N) :";
			cin >> input;
			if ("Y" == input) {
				a_files.saveGame(a_playerList, turns, a_deck, a_board, a_roundcount);
			}
			a_playerList[turns % 2]->play(a_board, capturedLast);
			turns++;
			updateDisplay(a_playerList, a_board, a_deck);
		} while (!a_playerList[0]->emptyHand() || !a_playerList[1]->emptyHand());

		if (!a_deck->emptyDeck()) {
			a_playerList[0]->setHand(a_deck->dealCards());
			a_playerList[1]->setHand(a_deck->dealCards());
			updateDisplay(a_playerList, a_board, a_deck);
		}

	} while(!a_playerList[0]->emptyHand() || !a_playerList[1]->emptyHand());

	cout << "Ending the Round" << endl;
	tableToPile(a_board, a_playerList, capturedLast);
	system("pause");
	return capturedLast;
}

/**********************************************************************
Function Name: updateDisplay
Purpose: to update the display that is should in the command line
Parameters: Player *a_playerList[2], Board *a_board, Deck *a_deck
Return Value: none
Local Variables: string board
Algorithm:
			1) get a string version of the board
			2) clear the current screen
			3) print the players hands, piles, board and the deck
			4) if turns % 2 == 0 print the reason
Assistance Received: none
**********************************************************************/

void Round::updateDisplay(Player *a_playerList[2], Board *a_board, Deck *a_deck) {

	string board = a_board->stringifyBoard();


	system("cls");
	cout << a_playerList[0]->getName() << ": " << a_playerList[0]->getScore() << "\t" << a_playerList[1]->getName() << ": " << a_playerList[1]->getScore() << endl;
	cout << a_playerList[0]->getName() << " Pile is: ";
	a_playerList[0]->displayPile();
	cout << "\n" << endl;
	cout << a_playerList[0]->getName() << " Hand is: " << endl;

	a_playerList[0]->showHand();
	cout << endl;
	//displaying the board with a nice box around it
	cout << char(218) << string(int(board.size()), '-') << char(191) << endl;
	cout << "|" << string(int(board.size()), ' ') << "|" << endl;
	cout << "|" << board << "|" << endl;
	cout << "|" << string(int(board.size()), ' ') << "|" << endl;
	cout << char(192) << string(int(board.size()), '-') << char(217) << endl;

	a_playerList[1]->showHand();
	cout << "\n"<<a_playerList[1]->getName() << " Hand is: \n" << endl;
	cout << a_playerList[1]->getName() << " Pile is: ";
	a_playerList[1]->displayPile();
	cout << endl;
	vector<Card*> deck = a_deck->getDeck();
	cout << "Deck: ";
	for (int i = 0; i < deck.size(); i++) {
		cout << deck[i]->getname() << " ";
	}
	cout << endl;
	cout << "Next player is: " << a_playerList[(turns + 1) % 2]->getName() << endl;
	if (turns  % 2 == 0) {
		cout << a_playerList[(turns + 1) % 2]->getReason() << endl;
	}
}

/**********************************************************************
Function Name: tableToPile
Purpose: move all the leftover cards from the board to the player who captured last
Parameters: Board *a_board
			Player *a_playerList[2]
			string capturedLast

Return Value: none
Local Variables: string board
Algorithm:
			1) get a string version of the board
			2) clear the current screen
			3) print the players hands, piles, and board
			4) if turns % 2 == 0 print the reason
Assistance Received: none
**********************************************************************/

void Round::tableToPile(Board *a_board, Player *a_playerList[2], string capturedLast) {
	int pos = 0;
	if (capturedLast == "Computer") {
		pos = 1;
	}
	a_playerList[pos]->addToPile(a_board->getBoard());
	a_board->clearboard();
}