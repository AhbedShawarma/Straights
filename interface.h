#ifndef INTERFACE_H
#define INTERFACE_H

#include "observer.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

class Card;
class StraightsModel;

class Interface : public Observer {
	std::shared_ptr<StraightsModel> model;
	std::map<int, char>	displayRanks;
	std::map<char, int>	storeRanks;

	void print(const std::vector<Card> &cards) const;

public:
	Interface(std::shared_ptr<StraightsModel> model);
	~Interface();
	void computerTurn();
	int humanTurn();
	void gameLoop();
	void outputDeck() const;
	void outputTable() const;
	void update() override;
};

#endif
