#ifndef BUILD_H
#define BUILD_H
#include "BigIncludeFile.h"
#include "Board.h"
#include "Card.h"

class Build : public Card
{
public:
	Build();
	Build(vector<Card*> a_buildCards, string a_owner);
	~Build();
	virtual bool isMultiBuild() const;
	int buildSize() const;
	Card* getCard(int pos) const;
	vector<Card*> getcards() const;
	bool isBuild() const;
	void setCards(vector<Card*> cardlist);

protected:
	vector<Card*> m_cardList;
};


#endif // !BUILD_H