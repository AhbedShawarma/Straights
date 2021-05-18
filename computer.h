#ifndef COMPUTER_H
#define COMPUTER_H

#include "card.h"
#include "playerdata.h"
#include <vector>

class Computer {
public:
	Card cardToPlay(const PlayerData player, const std::vector<Card> validMoves) const;
	Card cardToDiscard(const PlayerData player) const;
};

#endif
