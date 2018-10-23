#include "Files.h"

/**********************************************************************
Function Name: Files
Purpose: Constructor for the Files class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:	none
Assistance Received: none
**********************************************************************/

Files::Files()
{
}

/*********************************************************************
Function Name: ~Files
Purpose: Destructor for the Files class
Parameters: none
Return Value: none
Local Variables: none
Algorithm:	none
Assistance Received: none
**********************************************************************/

Files::~Files()
{
}

/**********************************************************************
Function Name: openfile
Purpose: opens the save file that is entered by the user
Parameters: none
Return Value: true if the file was successfully opened, else false
Local Variables: string fileName, line, command
				 ifstream myfile
				 stringstream ss
Algorithm:
			1) Open the file
			2) Read in a line
			3) If the line has a keyword in the first word
			4) call the appropiate function
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

bool Files::openfile() {
	string fileName;
	ifstream myfile;
	cout << "Enter the file location" << endl;
	cin >> fileName;
	myfile.open(fileName.c_str());

	if (!myfile.is_open()) {
		cout << "File cannot be open" << endl;
		return false;
	}

	string line;
	while (getline(myfile, line)) {
		stringstream ss(line);
		string command;
		while (ss >> command) {
			if (command == "Round:") {
				ss >> line;
				populateRound(line);
			}
			else if (command == "Computer:") {
				populateComputer(myfile);
			}
			else if (command == "Human:") {
				populateHuman(myfile);
			}
			else if (command == "Table:") {
				populateBoard(line);
			}
			else if (command == "Build") {
				createBuild(line);
			}
			else if (command == "Deck:") {
				createDeck(line);
			}
			else if (command == "Next") {
				ss >> line;
				ss >> line;
				if (line == "Computer") {
					m_nextplayer = 1;
				}
				else {
					m_nextplayer = 0;
				}
			}
		}
	}
	myfile.close();
	return true;
}

/**********************************************************************
Function Name: populateRound
Purpose: To load in the current round count from the number
Parameters: string a_round
Return Value: none
Local Variables: stringstream ss
				 string num
Algorithm:
			1) get the round number as a string from a_round
			2) convert that string to a number
			3) assign that number to m_Roundcount
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::populateRound(string a_round) {
	stringstream ss(a_round);
	string num = a_round;
	m_Roundcount = stoi(num);
}

/**********************************************************************
Function Name: populateBoard
Purpose: To load in the board from the save file
Parameters: string a_boardstring

Return Value: none
Local Variables: string board
				 stringstream ss
				 string cardname
				 Card *name
				 int inBuild
Algorithm:
			1) remove spaces and the Table: from the board string
			2) while inBuild == 0 we know were not in a build
			3) grab 2 chars and make them into a card
			4) add that card to m_board
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::populateBoard(string a_boardstring) {
	string board;
	stringstream ss(a_boardstring);
	ss >> a_boardstring;
	while (ss >> a_boardstring) {
		board += a_boardstring;
	}

	int inBuild = 0;
	for (int i = 0; i < board.size()-1; i++) {
		if (board[i] == '[' || board[i] == '{') {
			inBuild++;
		}
		else if (board[i] == ']' || board[i] == '}') {
			inBuild--;
		}
		else if (0 == inBuild) {
			string cardname = board.substr(i, 2);
			Card *name = new Card(cardname, m_cardvalue[cardname.substr(1,1)]);
			m_board.push_back(name);
			i++;
		}
	}
}

/**********************************************************************
Function Name: populateComputer
Purpose: To load in all the information that the Computer needs from the 
		 save file
Parameters: ifstream &a_myFile
Return Value: none
Local Variables: string line
				 stringstream ss
				Card *temp
Algorithm:
			1) grab the next three lines from the file
			2) if the first word of the line is "Score:" then
			3) parse the line into the score
			4) if the first word of the line is "Hand:" then
			5) loop through the line and for each substring create a card and add it to m_computerHand
			6) if the first word of the line is "Pile:" then
			7) loop through the line and for each substring create a card and add it to m_computerPile
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::populateComputer(ifstream &a_myFile) {
	string line;
	for (int i = 0; i < 3; i++) {
		getline(a_myFile, line);
		stringstream ss(line);
		while (ss >> line) {
			if (line == "Score:") {
				ss >> line;
				m_computerScore = stoi(line);
			}
			else if (line == "Hand:") {
				while (ss >> line) {
					Card *temp = new Card(line, m_cardvalue[line.substr(1, 1)]);
					m_computerHand.push_back(temp);
				}
			}
			else if (line == "Pile:") {
				while (ss >> line) {
					Card *temp = new Card(line, m_cardvalue[line.substr(1, 1)]);
					m_computerPile.push_back(temp);
				}
			}
		}
	}
}

/**********************************************************************
Function Name: populateHuman
Purpose: To load in all the information that the Human needs from the
		 save file
Parameters: ifstream &a_myFile
Return Value: none
Local Variables: string line
				 stringstream ss
				 Card *temp
Algorithm:
			1) grab the next three lines from the file
			2) if the first word of the line is "Score:" then
			3) parse the line into the score
			4) if the first word of the line is "Hand:" then
			5) loop through the line and for each substring create a card and add it to m_humanHand
			6) if the first word of the line is "Pile:" then
			7) loop through the line and for each substring create a card and add it to m_humanPile
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::populateHuman(ifstream &a_myFile) {
	string line;
	for (int i = 0; i < 3; i++) {
		getline(a_myFile, line);
		stringstream ss(line);
		while (ss >> line) {
			if (line == "Score:") {
				ss >> line;
				m_humanScore = stoi(line);
			}
			else if (line == "Hand:") {
				while (ss >> line) {
					Card *temp = new Card(line, m_cardvalue[line.substr(1, 1)]);
					m_humanHand.push_back(temp);
				}
			}
			else if (line == "Pile:") {
				while (ss >> line) {
					Card *temp = new Card(line, m_cardvalue[line.substr(1, 1)]);
					m_humanPile.push_back(temp);
				}
			}
		}
	}
}

/**********************************************************************
Function Name: createBuild
Purpose: To load in a build or multibuild from the save file
Parameters: string a_line
Return Value: none
Local Variables: stringstream ss
				 string build, owner, cardname
				 vector<Card*> build, singlebuild, buildcards
				 Build *build
				 MutliBuild *mbuild
Algorithm:
			1) remove the first two words and all the spaces from a_line
			2) Check to see if the owner is Human or Computer but check the
				end of the string
			3) loop through the string starting at pos 1 until the end of the string
			4) if you run into a '[' youre in a sub-build then
			5) take two chars to make a card and add it to buildcards
				until == ']'
			6) take those cards and make a build and add it to builds
			7) once you finish making all the builds convert them into a multibuild
			8) add the multibuild to the m_board
			9) if no '[' grab the next two chars and make them a card until you the
				end of the string
		   10) take those cards, create a build and add them to m_board
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::createBuild(string a_line) {
	stringstream ss(a_line);
	ss >> a_line;
	ss >> a_line;
	string build, owner;
	while (ss >> a_line) {
		build += a_line;
	}
	if(build.substr(build.size() - 5, 5) == "Human") {
		owner = "Human";
		build.erase(build.size() - 5, 5);
	}
	else {
		owner = "Computer";
		build.erase(build.size() - 8, 8);
	}

	vector<Card*> builds;
	vector<Card*> singlebuildcards;
	for (int i = 1; i < build.size() -1; i++) {
		if (build[i] == '[') {
			int j = i + 1;
			vector<Card*> buildcards;
			while (build[j] != ']') {
				string cardname = build.substr(j, 2);
				Card * card = new Card(cardname, m_cardvalue[cardname.substr(1, 1)]);
				j += 2;
				buildcards.push_back(card);
			}
			Build *build = new Build(buildcards, owner);
			builds.push_back(build);
			i = j;
		}
		else {
			string cardname = build.substr(i, 2);
			Card * card = new Card(cardname, m_cardvalue[cardname.substr(1, 1)]);
			i += 1;
			singlebuildcards.push_back(card);
		}
	}
	if (singlebuildcards.size() != 0) {
		Build *build = new Build(singlebuildcards, owner);
		m_board.push_back(build);
	}
	if (builds.size() != 0) {
		MultiBuild *mbuild = new MultiBuild(builds);
		m_board.push_back(mbuild);
	}
}

/**********************************************************************
Function Name: createDeck
Purpose: To load in all the information that the Computer needs from the
		 save file
Parameters: ifstream &a_myFile
Return Value: none
Local Variables: string line
				 stringstream ss
				 Card *temp
Algorithm:
			1) grab the next three lines from the file
			2) if the first word of the line is "Score:" then
			3) parse the line into the score
			4) if the first word of the line is "Hand:" then
			5) loop through the line and for each substring create a card and add it to m_computerHand
			6) if the first word of the line is "Pile:" then
			7) loop through the line and for each substring create a card and add it to m_computerPile
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::createDeck(string a_line) {
	stringstream meme(a_line);
	meme >> a_line;
	//this will create the deck
	while (meme >> a_line) {
		Card *temp = new Card(a_line, m_cardvalue[a_line.substr(1, 1)]);
		m_deck.push_back(temp);
	}
}

/**********************************************************************
Function Name: loadGame
Purpose: To load in all the information that the Computer needs from the
		 save file
Parameters: ifstream &a_myFile
Return Value: none
Local Variables: string line
				 stringstream ss
				Card *temp
Algorithm:
			1) grab the next three lines from the file
			2) if the first word of the line is "Score:" then
			3) parse the line into the score
			4) if the first word of the line is "Hand:" then
			5) loop through the line and for each substring create a card and add it to m_computerHand
			6) if the first word of the line is "Pile:" then
			7) loop through the line and for each substring create a card and add it to m_computerPile
Assistance Received: stackoverflow for file and stringstream
**********************************************************************/

void Files::loadGame(Player *a_human, Player *a_computer, Deck *a_deck, Board *a_board, int &a_startpos, int &a_roundCount) {
	a_human->setScore(m_humanScore);
	a_human->setHand(m_humanHand);
	a_human->setPile(m_humanPile);
	a_computer->setScore(m_computerScore);
	a_computer->setHand(m_computerHand);
	a_computer->setPile(m_computerPile);
	a_deck->setDeck(m_deck);
	a_board->setBoard(m_board);
	a_startpos = m_nextplayer;
	a_roundCount = m_Roundcount;
}

/**********************************************************************
Function Name: saveGame
Purpose: used to save the game state and exit the program
Parameters: Player *a_playerList[2]
			int a_turns
			Deck *a_deck
			Board *a_board
			int a_roundcount

Return Value: void
Local Variables: const char *saveState
				 vector<Card*> tempvector
				 ofstream file
Algorithm:
			1) create the text file
			2) write a_roundcount to the file
			3) write the info of the computer to the file
			3) write the info of the human to the file
			4) write the table to the file
			5) loop the table and write the builds to the file
			6) write the deck to the file
			7) write the next person to the file
Assistance Received: none
**********************************************************************/

void Files::saveGame(Player *a_playerList[2], int a_turns, Deck *a_deck, Board *a_board, int a_roundcount) {
	const char* saveState = "SavedGame.txt";
	vector<Card*> tempvector;
	ofstream file(saveState);

	file << "Round: " << a_roundcount << endl << endl;
	for (int i = 1; i > -1; i--) {
		if (1 == i) {
			file << "Computer: " << endl;
		}
		else {
			file << "Human: " << endl;
		}
		file << "\tScore: " << a_playerList[i]->getScore() << endl;
		file << "\tHand: ";
		tempvector = a_playerList[i]->gethand();
		for (int j = 0; j < tempvector.size(); j++) {
			file << tempvector[j]->getname() << " ";
		}
		file << endl;

		file << "\tPile: ";
		tempvector = a_playerList[i]->getPile();
		for (int j = 0; j < tempvector.size(); j++) {
			file << tempvector[j]->getname() << " ";
		}
		file << endl << endl;

	}

	file << "Table: ";
	tempvector = a_board->getBoard();
	for (int i = 0; i < tempvector.size(); i++) {
		file << tempvector[i]->getname() << " ";
	}
	file << endl << endl;

	for (int i = 0; i < tempvector.size(); i++) {
		if (tempvector[i]->isBuild()) {
			file << "Build Owner: " << tempvector[i]->getname() << " " << tempvector[i]->getowner() << endl << endl;
		}
	}

	file << endl;

	file << "Deck: ";
	tempvector = a_deck->getDeck();
	for (int i = 0; i < tempvector.size(); i++) {
		file << tempvector[i]->getname() << " ";
	}
	file << endl << endl;

	file << "Next Player: ";
	if (0 == a_turns) {
		file << "Human";
	}
	else {
		file << "Computer";
	}

	exit(0);
}

void Files::loadDeck(Deck *a_deck) {
	a_deck->setDeck(m_deck);
}