#pragma once
#include "BigIncludeFile.h"

using namespace std;

class Card
{
public:
	Card(string a_name = "NULL", int a_value = -1);
	Card(Card* a_card);
	virtual bool isBuild() const;
	virtual vector<Card*> getcards() const;
	virtual int buildSize() const;
	virtual Card* getCard(int pos) const;
	virtual bool isMultiBuild() const;
	string getname() const;
	int getvalue() const;
	string getowner() const;
	void setname(string a_name);
	void setvalue(int a_value);
	void setowner(string a_owner);

protected:
	string m_cardname;
	int m_value;
	string m_owner;
};