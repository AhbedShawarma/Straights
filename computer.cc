#include "computer.h"

Card Computer::cardToPlay(const PlayerData player, const std::vector<Card> validMoves) const {
	return validMoves[0];
}

Card Computer::cardToDiscard(const PlayerData player) const {
	return player.hand[0];
}
