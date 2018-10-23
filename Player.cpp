#include "Player.h"

/**********************************************************************
Function Name: Player
Purpose: The default constructor for the Player class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) m_name = "Computer"
			2) m_scoure = 0
Assistance Received: none
**********************************************************************/

Player::Player() {
	m_name = "Computer";
	m_score = 0;
}

/**********************************************************************
Function Name: ~Player
Purpose: The default Destructor for the Player class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
			1) m_name.clear()
			2) m_hand.clear()
			3) m_pile.clear()
			4) m_score = 0
			5) movereason.clear()
Assistance Received: none
**********************************************************************/

Player::~Player() {
	m_name.clear();
	m_hand.clear();
	m_pile.clear();
	m_score = 0;
	movereason.clear();
}

/**********************************************************************
Function Name: createBuild
Purpose: Used to create a build
Parameters: Board *a_board
			Card *a_traget
Return Value: true
Local Variables: vector<vector<Card*>> cardlist
				 vector<Card*> c_hand, c_board
				 int Buildset
Algorithm:
			1) get a copy of the hand and board
			2) remove the a_target from the hand
			3) remove your own build from the c_board
			4) call extendBuild to check if you can extend a build
			5) remove oppents builds from the board
			6) for every other card in the hand call r_capture_sets
			7) get the input for buildset
			8) if buildset == -1 return then false
			9) else remove the first card from Player hand
		   10) create a build with the cards for cardlist[buildset]
		   11) delete those cards from the board
		   12) if you can make a multibuild then make a multibuild and push it to the board
		   13) else push the build onto the table
Assistance Received: none
**********************************************************************/

bool Player::createBuild(Board *a_board, Card* a_target) {
	vector<vector<Card*>> cardlist;
	vector<Card*> c_hand = gethand();
	vector<Card*> c_board = a_board->getBoard();
	c_hand = remove(c_hand, a_target);

	removeOwnBuilds(c_board);
	extendBuild(c_board, c_hand, a_target, cardlist);
	removeOppBuilds(c_board);

	for (int i = 0; i < int(c_hand.size()); i++) {
		r_capture_sets(c_board, a_target->getvalue(), vector<Card*>(1, c_hand[i]), cardlist);
	}
	
	int buildset = getInput(cardlist);
	
	if (buildset == -1) {
		return false;
	}

	removeCard(cardlist[buildset][0]);
	Build *m_build1 = new Build(cardlist[buildset], getName());
	for (int i = 0; i < int(cardlist[buildset].size()); i++) {
		a_board->deleteCard(cardlist[buildset][i]->getname());
	}

	if (createMultiBuild(m_build1, a_board)) {
		return true;
	}
	a_board->setCard(m_build1);
	return true;
}

/**********************************************************************
Function Name: extendBuild
Purpose: To extend the one of the opponents build to your own
Parameters: vector<vector<Card*>> &a_cardlist
			vector<Card*> a_board, a_hand
			Card *a_target

Return Value: none
Local Variables: vector<Card*> temp
Algorithm:
			1) loop through the a_board
			2) if the card isnt a build skip it
			3) loop through every card in the hand
			4) if the value of the card on the board + the card in the hand
				is equal to the a_target value
			5) add it to a_cardlist
Assistance Received: none
**********************************************************************/

void Player::extendBuild(vector<Card*> a_board, vector<Card*> a_hand, Card* a_target, vector<vector<Card*>> &a_cardlist) {
	for (int i = 0; i < a_board.size(); i++) {
		if (!a_board[i]->isBuild()) {
			continue;
		}
		for (int j = 0; j < a_hand.size(); j++) {
			if (a_board[i]->getvalue() + a_hand[j]->getvalue() == a_target->getvalue()) {
				vector<Card*> temp = { a_hand[j], a_board[i] };
				a_cardlist.push_back(temp);
			}
		}
	}
}

/**********************************************************************
Function Name: createMultiBuild
Purpose: To extend the one of the opponents build to your own
Parameters: vector<vector<Card*>> &a_cardlist
			vector<Card*> a_board, a_hand
			Card *a_target

Return Value: none
Local Variables: vector<Card*> temp
Algorithm:
			1) loop through the a_board
			2) if the card isnt a build skip it
			3) loop through every card in the hand
			4) if the value of the card on the board + the card in the hand
				is equal to the a_target value
			5) add it to a_cardlist
Assistance Received: none
**********************************************************************/

bool Player::createMultiBuild(Card* a_build1, Board *a_board) {
	for (int i = 0; i < int(a_board->getSize()); i++) {
		if (a_board->getCard(i)->isBuild() && a_board->getCard(i)->getvalue() == a_build1->getvalue()) {
			if (a_board->getCard(i)->isMultiBuild() ) {
				MultiBuild *multiBuild = new MultiBuild((MultiBuild*)a_board->getCard(i), (Build *)a_build1);
				a_board->deleteCard(i);
				a_board->setCard(multiBuild);
				return true;
			}
			else {
				MultiBuild *multiBuild = new MultiBuild((Build *)a_board->getCard(i), (Build *)a_build1);
				a_board->deleteCard(i);
				a_board->setCard(multiBuild);
				return true;
			}

		}
	}
	return false;
}

/**********************************************************************
Function Name: remove
Purpose: remove a card from the list vector passed
Parameters: vector<Card*> a_list
			Card *a_target

Return Value: vector<Card*>
Local Variables: none
Algorithm:
			1) loop throught a_list
			2) if a_list[i] name == a_target name then
			3) remove it from a_list
			4) return a_list
Assistance Received: none
**********************************************************************/

vector<Card*> Player::remove(vector<Card*> a_list, Card* a_target) {
	for (int i = 0; i < a_list.size(); i++) {
		if (a_list[i]->getname() == a_target->getname()) {
			a_list.erase(a_list.begin() + i);
		}
	}
	return a_list;
}

/**********************************************************************
Function Name: extendBuild
Purpose: To extend the one of the opponents build to your own
Parameters: vector<vector<Card*>> &a_cardlist
			vector<Card*> a_board, a_hand
			Card *a_target

Return Value: none
Local Variables: vector<Card*> temp
Algorithm:
			1) loop through the a_board
			2) if the card isnt a build skip it
			3) loop through every card in the hand
			4) if the value of the card on the board + the card in the hand
				is equal to the a_target value
			5) add it to a_cardlist
Assistance Received: none
**********************************************************************/

bool Player::captureSets(Board *a_board, Card* a_playedCard) {
	int totalcapture = 0;

	vector<vector<Card*>> cardlist;
	int input;
	do {
		vector<Card*> board = a_board->getBoard();
		removeOppBuilds(board);
		//this means the card is an Ace so we need to check to see if you make sets with 1 or 14
		if (a_playedCard->getvalue() == 1) {
			r_capture_sets(board, a_playedCard->getvalue() + 13, vector<Card*>(), cardlist);
		}
		else {
			r_capture_sets(board, a_playedCard->getvalue(), vector<Card*>(), cardlist);
		}

		input = getInput(cardlist);
		if (input == -1) {
			break;
		}
		for (int i = 0; i < int(cardlist[input].size()); i++) {
			if (cardlist[input][i]->isBuild()) {
				getBuildCards(cardlist[input][i]);
			}
			else {
				m_pile.push_back(cardlist[input][i]);
			}
			a_board->deleteCard(cardlist[input][i]->getname());
		}
		totalcapture++;
		cardlist.clear();
	} while (!cardlist.empty());

	for (int i = int(a_board->getSize()) - 1; i >= 0; i--) {
		//this ugly if statement checks to see if the values are the same and if its a loose card or it has an owner
		if (a_playedCard->getvalue() == a_board->getCard(i)->getvalue() && (a_board->getCard(i)->getowner() == "none" || a_board->getCard(i)->getowner() == getName())) {
			if (a_board->getCard(i)->isBuild()) {
				getBuildCards(a_board->getCard(i));
			}
			else {
				m_pile.push_back(a_board->getCard(i));
			}
			a_board->deleteCard(i);
			totalcapture++;
			continue;
		}
	}

	if (totalcapture == 0) {
		return false;
	}
	m_pile.push_back(a_playedCard);
	removeCard(a_playedCard);
	return true;
}

/**********************************************************************
Function Name: getBuildCards
Purpose: To extend the one of the opponents build to your own
Parameters: Card *a_build
Return Value: none
Local Variables: vector<Card*> buildcards
Algorithm:
			1) get the cards from Card *build
			2) loop through the buildcards
			3) add those cards to m_pile
Assistance Received: none
**********************************************************************/

void Player::getBuildCards(Card* a_build) {
	vector<Card*> buildcards = a_build->getcards();
	for (int i = 0; i < buildcards.size(); i++) {
		m_pile.push_back(buildcards[i]);
	}
}

/**********************************************************************
Function Name: removeOwnBuilds 
Purpose: To remove all of your builds from the board
Parameters: vector<Card*> &a_board
Return Value: none
Local Variables: none
Algorithm:
			1) loop through a_board
			2) if the card is a build and you are the owner remove it from the board
Assistance Received: none
**********************************************************************/

void Player::removeOwnBuilds(vector<Card*> &a_board)
{
	for (int i = 0; i < a_board.size(); i++) {
		if (a_board[i]->isBuild() && a_board[i]->getowner() == getName()) {
			a_board.erase(a_board.begin() + i);
		}
	}
}

/**********************************************************************
Function Name: removeOppBuilds
Purpose: To remove all of your opponents builds from the board
Parameters: vector<Card*> &a_board
Return Value: none
Local Variables: none
Algorithm:
			1) loop through a_board
			2) if the card is a build and you are not the owner remove it from the board
Assistance Received: none
**********************************************************************/

void Player::removeOppBuilds(vector<Card*> &a_board)
{
	for (int i = 0; i < a_board.size(); i++) {
		if (a_board[i]->isBuild() && a_board[i]->getowner() != getName()) {
			a_board.erase(a_board.begin() + i);
		}
	}
}

/**********************************************************************
Function Name: trailCard
Purpose: To trail a card
Parameters: Board *a_board
			Card *a_playedCard

Return Value: bool
Local Variables: none
Algorithm:
			1) set the card on the board
			2) remove the card from the hand
			3) return true
Assistance Received: none
**********************************************************************/

bool Player::trailCard(Board *a_board, Card *a_playedCard) {
	a_board->setCard(a_playedCard);
	removeCard(a_playedCard);
	return true;
}

int Player::getInput(vector<vector<Card*>>) {
	return 0;
}

/**********************************************************************
Function Name: r_capture_sets
Purpose: recurive function to find all sets
Parameters: vector<vector<Card*>> &a_cardlist
			vector<Card*> a_board, a_partial
			int a_target
Return Value: none
Local Variables: Card *temp, *n
				 int sum = 0
				 vector<Card*> partical_rec, remaining
Algorithm:
			1) find the sum of all the cards in a_partial
			2) if sum == a_target then push_back a_partial into a_cardlist
			3) if sum >= a_target return
			4) loop through the a_board
			5) loop throught every card after the position of the first loop
			6) push those cards into remaining
			7) add the card at the first loop into the partial vector
			8) call r_capture_sets
Assistance Received: stackoverflow
**********************************************************************/

void Player::r_capture_sets(std::vector<Card*> a_board, int a_target, std::vector<Card*> a_partial, vector<vector<Card*>> &a_cardist)
{
	//declaring the sum of the a_partial list of cards
	int sum = 0;
	for (std::vector<Card*>::const_iterator cit = a_partial.begin(); cit != a_partial.end(); cit++) {
		Card *temp = *cit;
		sum += temp->getvalue();
	}

	if (sum == a_target) {
		a_cardist.push_back(a_partial);
	}

	if (sum >= a_target) {
		return;
	}

	for (std::vector<Card*>::const_iterator ai = a_board.begin(); ai != a_board.end(); ai++) {
		Card *n = *ai;

		std::vector<Card*> remaining;
		for (std::vector<Card*>::const_iterator aj = ai; aj != a_board.end(); aj++){
			Card *temp = *aj;
			if (aj == ai) {
				continue;
			}
			remaining.push_back(*aj);
		}
		std::vector<Card*> partial_rec = a_partial;
		partial_rec.push_back(n);
		r_capture_sets(remaining, a_target, partial_rec, a_cardist);
	}
}

/**********************************************************************
Function Name: ownBuild
Purpose: To check to see if you own a build
Parameters: Board *a_board 
Return Value: bool
Local Variables: none
Algorithm:
			1) loop through the board
			2) if card at board i owner is equal to getName() then return true
			3) return false
Assistance Received: none
**********************************************************************/

bool Player::ownBuild(Board *a_board) {
	for (int i = 0; i < a_board->getSize(); i++) {
		if (a_board->getCard(i)->getowner() == getName()) {
			return true;
		}
	}
	return false;
}

void Player::play(Board *a_board, string &a_playedLast) {
	cout << "You shouldn't be seeing this" << endl;
}

/**********************************************************************
Function Name: showHand
Purpose: To show the hand of the player
Parameters: none

Return Value: none
Local Variables: none
Algorithm:
			1) loop through the hand
			2) print the name of each card plus a space
Assistance Received: none
**********************************************************************/

void Player::showHand() {
	for (int i = 0; i < int(m_hand.size()); i++) {
		cout << m_hand[i]->getname() << " ";
	}
}

bool Player::emptyHand() {
	return m_hand.empty();
}

void Player::removeCard(int a_pos) {
	m_hand.erase(m_hand.begin() + a_pos);
}

/**********************************************************************
Function Name: removeCard
Purpose: remove the card from the hand by the name
Parameters: Card *a_buildCard
Return Value: none
Local Variables: none
Algorithm:
			1) loop through the m_hand
			2) if the card at i name is equal to a_buildCard name then
			3) call removeCard
Assistance Received: none
**********************************************************************/

void Player::removeCard(Card* a_buildCard) {
	for (int i = 0; i < int(m_hand.size()); i++) {
		if (m_hand[i]->getname() == a_buildCard->getname()) {
			removeCard(i);
		}
	}
}

void Player::displayPile() {
	for (int i = 0; i < int(m_pile.size()); i++) {
		cout << m_pile[i]->getname() << " ";
	}
}

/**********************************************************************
Function Name: generateMove
Purpose: Generate the next move for the AI/Computer
Parameters: vector<Card*> a_board, a_hand
			string &recommendmove, &reasonwhy
Return Value: string
Local Variables: none
Algorithm:
			1) if canBuild return true then return BUILD
			2) if canCapture returns true then return CAPTURE
			3) recommendedmove to the most left card
			4) reasonwhy to "The Computer wants you to trail a Card
			5) return TRAIL
Assistance Received: none
**********************************************************************/

string Player::generateMove(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy) {

	if (canBuild(a_board, a_hand, recommendmove, reasonwhy)) {
		return "BUILD";
	}
	if (canCapture(a_board, a_hand, recommendmove, reasonwhy)) {
		return "CAPTURE";
	}
	recommendmove += m_hand[0]->getname();
	reasonwhy = "The Computer wants you to trail a Card";
	return "TRAIL";
}

/**********************************************************************
Function Name: canBuild
Purpose: To extend the one of the opponents build to your own
Parameters: vector<Card*> a_board, a_hand
			string &recommendmove, &reasonwhy
Return Value: bool
Local Variables: vector<vector<Card*>> cardlist
				 vector<Card*> buildlist, reservedcards

Algorithm:
			1) loop through the board and push any builds that are yours into buildlist
			2) call pruneHand
			3) if hand.size < 2 return false
			4) if buildlist is not empty then
			5) for each build loop through the hand
			6) call r_capture_sets
			7) if cardlist is not empty return true
			8) loop through the hand to see if you can make the build
			9) if you can return true
Assistance Received: none
**********************************************************************/

bool Player::canBuild(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy) {
	vector<vector<Card*>> cardlist;
	vector<Card*> buildlist;
	vector<Card*> reservedcards;
	//getting the builds that are yours
	for (int i = 0; i < int(a_board.size()); i++) {
		if (a_board[i]->getowner() == getName()) {
			buildlist.push_back(a_board[i]);
		}
	}
	
	pruneHand(buildlist, a_hand, reservedcards);

	if (a_hand.size() < 2) {
		return false;
	}

	//checking to see if you can make a build that will convert into a multibuild
	if (!buildlist.empty()) {
		for (int i = 0; i < int(buildlist.size()); i++) {
			for (int j = 0; j < int(a_hand.size()); j++) {
				r_capture_sets(a_board, buildlist[i]->getvalue(), vector<Card*>(1, a_hand[j]), cardlist);
				if (!cardlist.empty()) {
					recommendmove = reservedsearch(buildlist[i]->getvalue(), reservedcards);
					reasonwhy = "The Computer wants to make a mulibuild.";
					return true;
				}
			}
		}
	}

	for (int i = 0; i < int(a_hand.size()); i++) {
		for (int j = 0; j < int(a_hand.size()); j++) {
			if (i == j) {
				continue;
			}
			r_capture_sets(a_board, a_hand[i]->getvalue(), vector<Card*>(1, a_hand[j]), cardlist);
			if (!cardlist.empty()) {
				recommendmove += a_hand[i]->getname();
				reasonwhy = "The Computer wants to make a build.";
				return true;
			}
		}
	}
	return false;
}

/**********************************************************************
Function Name: pruneHand
Purpose: To remove cards that equal the builds
Parameters: vector<Card*> a_builds, &a_hand, &a_reservedcards
Return Value: none
Local Variables: none
Algorithm:
			1) loop through the a_builds
			2) loop through the a_hand
			3) if a_builds at i value is equal to a_hand j vale
			4) add the card to a_reservedcards
			5) remove the card from a_hand
			6) break
Assistance Received: none
**********************************************************************/

void Player::pruneHand(vector<Card*> a_builds, vector<Card*> &a_hand, vector<Card*> &a_reservedcards) 
{
	for (int i = 0; i < a_builds.size(); i++) {
		for (int j = 0; j < a_hand.size(); j++) {
			if (a_builds[i]->getvalue() == a_hand[j]->getvalue()) {
				a_reservedcards.push_back(a_hand[j]);
				a_hand.erase(a_hand.begin() + j);
				break;
			}
		}
	}
}

/**********************************************************************
Function Name: reservedsearch
Purpose: return the name of the card in the reserved list
Parameters: vector<Card*> reservedcards
			int a_target
Return Value: string
Local Variables: none
Algorithm:
			1) loop through the reserved cards vector
			2) if reservedcards value is equal to a_target
			3) then return the cards name
			4) return "NULL"
Assistance Received: none
**********************************************************************/

string Player::reservedsearch(int a_target, vector<Card*> reservedcards) {
	for (int i = 0; i < int(reservedcards.size()); i++) {
		if (reservedcards[i]->getvalue() == a_target) {
			return reservedcards[i]->getname();
		}
	}
	return "NULL";
}

/**********************************************************************
Function Name: canCapture
Purpose: Check to see if you can capture with any cards
Parameters: vector<Card*> a_board, a_hand
			string &recommendmove, &reasonwhy
Return Value: bool
Local Variables: vector<vector<Card*>> cardlist
				 int maxpairs = 0
				 int cardPos = -1
				 int samevalue = 0
Algorithm:
			1) loop through the hand 
			2) for every card loop the board
			3) if value of the hand card and the board card are the same then increase samevalue
			4) if a_hand[i] value == 1 then call r_capture_sets with value + 13
			5) else call r_capture_sets with value
			6) if cardlist size + same value > maxpairs then cardPos = i and maxpairs = cardlist.size()
			7) if cardpos = 0 then return -1
			8) recommendmove = a_hand[cardpos]
			9) return true
Assistance Received: none
**********************************************************************/

bool Player::canCapture(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy) {
	vector<vector<Card*>> cardlist;
	int maxpairs = 0;
	int cardPos = -1;

	for (int i = 0; i < int(a_hand.size()); i++) {
		int samevalue = 0;
		for (int j = 0; j < int(a_board.size()); j++) {
			if (a_board[j]->getowner() == getName() && a_board[j]->getvalue() == a_hand[i]->getvalue()) {
				samevalue++;
			}
		}
		if (a_hand[i]->getvalue() == 1) {
			r_capture_sets(a_board, a_hand[i]->getvalue() + 13, vector<Card*>(), cardlist);
		}
		else {
			r_capture_sets(a_board, a_hand[i]->getvalue(), vector<Card*>(), cardlist);
		}

		if (int(cardlist.size()) + samevalue > maxpairs) {
			cardPos = i;
			maxpairs = cardlist.size();
		}
		cardlist.clear();
	}

	if (cardPos == -1) {
		return false;
	}

	recommendmove = a_hand[cardPos]->getname();
	reasonwhy = "The Computer wants to maximize capture sets.";
	return true;
}

string Player::getreason(string a_move, string a_cardname, string a_reasonwhy) {
	return "The Computer played " + a_move + " with " + a_cardname + "\n" + a_reasonwhy;
}

/**********************************************************************
Function Name: addToPile
Purpose: add the cards from a_excessCards to m_pile
Parameters: vector<Card*> a_excessCards
Return Value: none
Local Variables: none
Algorithm:
			1) loop through a_excessCards
			2) add each card to the m_pile
Assistance Received: none
**********************************************************************/

void Player::addToPile(vector<Card*> a_excessCards) {
	for (int i = 0; i < int(a_excessCards.size()); i++) {
		m_pile.push_back(a_excessCards[i]);
	}
}

string Player::getName() const{
	return m_name;
}

int Player::getScore() const{
	return m_score;
}

int Player::getPileSize() const{
	return m_pile.size();
}

 Card* Player::getCard(int a_pos) const{
	if (a_pos < int(m_hand.size())) {
		return m_hand[a_pos];
	}
	cerr << "Invaild entry for hand size" << endl;
	exit(1);
}

 vector<Card*> Player::gethand() const {
	 return m_hand;
 }

 string Player::getReason() const {
	 return movereason;
 }

 vector<Card*> Player::getPile() const {
	 return m_pile;
 }

 void Player::setHand(vector<Card*> a_cards) {
	 m_hand = a_cards;
 }

void Player::setHandCard(Card* a_card) {
	m_hand.push_back(a_card);
}

void Player::setScore(int a_points) {
	m_score = a_points;
}

void Player::setName(string a_name) {
	m_name = a_name;
}

void Player::setPile(vector<Card*> a_pile) {
	m_pile = a_pile;
}

void Player::increaseScore(int a_score) {
	m_score = m_score + a_score;
}

void Player::clearPile() {
	m_pile.clear();
	m_pile.resize(0);
}