#ifndef STRAIGHTSMODEL_H
#define STRAIGHTSMODEL_H

#include <vector>
#include <string>
#include "playerdata.h"
#include "subject.h"
#include "card.h"
#include <memory>

class StraightsModel : public Subject {
	// stores a list of the players
	PlayerData players[4];
	// stores whether each player is human or a computer
	char playerType[4];
	// stores the integer for the current player
	int currPlayer;
	
	std::vector<Card> deck{};
	
	// constants that decide the starting card and the score that will end the game
	const Card startCard = { 7, 'S' };
	const int endThreshold = 80;

	// vector of the 4 piles on the table
	std::vector<Card> clubs{};
	std::vector<Card> diamonds{};
	std::vector<Card> hearts{};
	std::vector<Card> spades{};

	// stores the seed
	unsigned seed;

	// removes the given card from currPlayer's hand
	void removeCard(Card card);

public:
	StraightsModel(unsigned seed);
	~StraightsModel() override;

	// accessor methods
	int getCurrPlayer() const;
	std::vector<Card> getClubs() const;
	std::vector<Card> getDiamonds() const;
	std::vector<Card> getHearts() const;
	std::vector<Card> getSpades() const;
	std::vector<Card> getDeck() const;
	std::vector<Card> getPlayerHand() const;
	std::vector<Card> getPlayerDiscards(int player) const;
	int getPlayerOldScore(int player) const;
	int getPlayerNewScore(int player) const;
	
	// sets currPlayer to a computer
	void setComputer(int player);
	// increments currPlayer
	void nextPlayer();
	// returns true if currPlayer is human
	bool isHuman() const;
	// returs true if currPlayer can play the given card
	bool legalPlay(Card card) const;
	// returns true if currPlayer can discard the given card
	bool legalDiscard(Card card) const;

	// currPlayer plays the given card. The card is removed from their hand and added to
	// the pile on the table associated with card's suit. Calls notifyObservers()
	void playCard(Card card);
	// currPlayer plays the given card. The card is removed from their hand and added to
        // the currPlayer's discardPile. Calls notifyObservers()
	void discardCard(Card card);

	// returns a vector of validMoves that the currPlayer can make
	std::vector<Card> validMoves() const;
	
	// calls functions from the Computer Class
	Card computerMove();
	// turns the currPlayer to a computer
	void rageQuit();

	// returns true if the round is over, so when all player hands are empty
	bool isRoundOver() const;
	// returns true if the endThreshold has been met or exceeded by at least one player's score
	bool isGameOver() const;
	// returns a vector of ints associated with the players that won (multiple players win if
	// they tie for the lowest score total
	std::vector<int> playersWon() const;
	
	// shuffles the deck
	void shuffleDeck();
	// deals the deck out to each player
	void deal();
	// sets currPlayer to whoever has the startingCard
	void startingPlayer();
	// clears the piles on the table, player hands and discardPiles, and player scores for the round
	void resetRoundData();
};

#endif
