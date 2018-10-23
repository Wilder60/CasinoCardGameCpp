#ifndef PLAYER_H
#define PLAYER_H

#include "BigIncludeFile.h"
#include "Card.h"
#include "Board.h"
#include "Build.h"
#include "MultiBuild.h"

class Player
{
public:
	Player();
	~Player();
	virtual void play(Board *a_board, string &a_playedLast);
	//-------------------BUILD-FUNCTIONS---------------------------------------
	bool createBuild(Board *a_board, Card* a_target);
	void extendBuild(vector<Card*> a_board,vector<Card*> a_hand, Card* a_target, vector<vector<Card*>> &a_cardlist);
	bool createMultiBuild(Card *a_build1, Board *a_board);
	void removeOppBuilds(vector<Card*> &a_board);
	//-------------------CAPTURE-FUNCTIONS-------------------------------------
	bool captureSets(Board *a_board, Card* a_playedCard);
	//-------------------TRAIL FUNCTIONS---------------------------------------
	bool trailCard(Board *a_board, Card* a_playedCard);
	//------------------FUNCTIONS USED IN MULTIPLE STEPS-----------------------
	virtual int getInput(vector<vector<Card*>> cardlist);
	void r_capture_sets(vector<Card*> a_board, int a_target, vector<Card*> a_partial, vector<vector<Card*>> &a_cardist);
	void removeOwnBuilds(vector<Card*> &a_board);
	//-------------------------------------------------------------------------
	bool emptyHand();
	bool ownBuild(Board *a_board);
	void removeCard(int a_pos);
	void removeCard(Card* a_buildCard);
	vector<Card*> remove(vector<Card*> a_list, Card* a_target);
	void showHand();
	void displayPile();
	void addToPile(vector<Card*> a_excessCards);
	void getBuildCards(Card* a_build);

	//Setters and Getters go here
	string getName() const;
	int getScore() const;
	int getPileSize() const;
	vector<Card*> getPile() const;
	Card* getCard(int a_pos) const;
	vector<Card*> gethand() const;
	string getReason() const;
	void setName(string a_name);
	void setScore(int a_points);
	void setHandCard(Card* a_card);
	void setHand(vector<Card*> a_cards);
	void setPile(vector<Card*> a_pile);
	void increaseScore(int a_score);
	void clearPile();

	//AI stuff here
	string generateMove(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy);
	bool canBuild(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy);
	void pruneHand(vector<Card*> a_builds, vector<Card*> &a_hand, vector<Card*> &reservedcards);
	string reservedsearch(int a_target, vector<Card*> reservedcards);
	bool canCapture(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy);
	//bool canTrail(vector<Card*> a_board, vector<Card*> a_hand, string &recommendmove, string &reasonwhy);
	string getreason(string a_move, string a_cardname, string a_reasonwhy);

protected:
	string m_name;
	vector<Card*> m_hand;
	vector<Card*> m_pile;
	int m_score = 0;
	string movereason = " ";
};

#endif // !PLAYER_H
