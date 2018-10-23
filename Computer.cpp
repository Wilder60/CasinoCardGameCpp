#include "Computer.h"

/**********************************************************************
Function Name: play
Purpose: Makes the move that was decided by the AI
Parameters: Board *a_board
			string &capturedLast
Return Value: none
Local Variables: string recommendmove, reasonwhy, nextmove, move
Algorithm:
			1) get the result of generateMove
			2) get the move from getreason
			3) if nextmove == "BUILD" then
			4) call createBuild
			5) else if nextmove == "CAPTURE" then
			6) call captureSets
			7) set capturedLast to getName
			8) else if nextmove == "TRAIL" then
			9) call trailCard
		   10) call an error
		   11) set movereason to move
Assistance Received: none
**********************************************************************/

void Computer::play(Board *a_board, string &capturedLast) {

	string recommendmove, reasonwhy;
	string nextmove = generateMove(a_board->getBoard(), gethand(), recommendmove, reasonwhy);
	string move = getreason(nextmove, recommendmove, reasonwhy);

	if (nextmove == "BUILD") {
		createBuild(a_board, getCard(recommendmove));
	}
	else if (nextmove == "CAPTURE") {
		captureSets(a_board, getCard(recommendmove));
		capturedLast = getName();
	}
	else if (nextmove == "TRAIL") {
		trailCard(a_board, getCard(recommendmove));
	}
	else {
		cerr << "You shouldn't be here" << endl;
	}
	movereason = move;
}

/**********************************************************************
Function Name: getCard
Purpose: loop through the hand and return the card if it exists in the hand
			of exit the program with 1
Parameters: string a_cardname
Return Value: none
Local Variables: none
Algorithm:
			1) loop the hand and if you find a card equal to the card name then
			2) return that card
			3) else exit(1)
Assistance Received: none
**********************************************************************/

Card* Computer::getCard(string a_cardname) {
	for (int i = 0; i < m_hand.size(); i++) {
		if (m_hand[i]->getname() == a_cardname) {
			return m_hand[i];
		}
	}
	exit(1);
}

/**********************************************************************
Function Name: play
Purpose: Makes the move that was decided by the AI
Parameters: Board *a_board
			string &capturedLast
Return Value: none
Local Variables: string recommendmove, reasonwhy, nextmove, move
Algorithm:
			1) get the result of generateMove
			2) get the move from getreason
			3) if nextmove == "BUILD" then
			4) call createBuild
			5) else if nextmove == "CAPTURE" then
			6) call captureSets
			7) set capturedLast to getName
			8) else if nextmove == "TRAIL" then
			9) call trailCard
		   10) call an error
		   11) set movereason to move
Assistance Received: none
**********************************************************************/

int Computer::getInput(vector<vector<Card*>> cardlist) {
	return 0;
}