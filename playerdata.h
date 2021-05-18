#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <vector>
#include <string>

class Card;

struct PlayerData {
	int totalScore = 0;
	int roundScore = 0;
	std::vector<Card> hand;
	std::vector<Card> discardPile;
};

#endif
