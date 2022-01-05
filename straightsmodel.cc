#include "straightsmodel.h"
#include <algorithm>
#include <random>
#include <iostream>
#include "computer.h"

StraightsModel::StraightsModel(unsigned seed) : seed{ seed }, playerType{ 'h', 'h', 'h', 'h' }, currPlayer{ 0 } {
	for (int i = 1; i < 14; i++) {
		deck.emplace_back(i, 'C');
	}
	for (int i = 1; i < 14; i++) {
		deck.emplace_back(i, 'D');
	}
	for (int i = 1; i < 14; i++) {
		deck.emplace_back(i, 'H');
	}
	for (int i = 1; i < 14; i++) {
		deck.emplace_back(i, 'S');
	}
}

StraightsModel::~StraightsModel() {}

int StraightsModel::getCurrPlayer() const {
	return currPlayer;
}

void StraightsModel::nextPlayer() {
	currPlayer++;
	if (currPlayer == 4) currPlayer = 0;
}

std::vector<Card> StraightsModel::getClubs() const {
	return clubs;
}
std::vector<Card> StraightsModel::getDiamonds() const {
	return diamonds;
}
std::vector<Card> StraightsModel::getHearts() const {
	return hearts;
}
std::vector<Card> StraightsModel::getSpades() const {
	return spades;
}
std::vector<Card> StraightsModel::getDeck() const {
	return deck;
}

std::vector<Card> StraightsModel::getPlayerHand() const {
	return players[currPlayer].hand;
}

std::vector<Card> StraightsModel::getPlayerDiscards(int player) const {
	return players[player].discardPile;
}

int StraightsModel::getPlayerOldScore(int player) const {
	return players[player].totalScore - players[player].roundScore;
}

int StraightsModel::getPlayerNewScore(int player) const {
	return players[player].roundScore;
}

void StraightsModel::setComputer(int player) {
	playerType[player] = 'c';
}

bool StraightsModel::isHuman() const {
	if (playerType[currPlayer] == 'h') return true;
	return false;
}


void StraightsModel::removeCard(Card card) {
	int player = currPlayer;
	std::vector<Card>::iterator cbegin = players[player].hand.begin();
	std::vector<Card>::iterator cend = players[player].hand.end();
	std::vector<Card> tempCards;
	cend = std::remove(cbegin, cend, card);

	for (std::vector<Card>::iterator c = cbegin; c != cend; ++c) {
		tempCards.emplace_back(*c);
	}
	int tempSize = tempCards.size();
	players[player].hand.clear();
	for (int i = 0; i < tempSize; i++) {
		players[player].hand.emplace_back(tempCards[i]);
	}
	
}

bool StraightsModel::legalPlay(Card card) const {
	if (find(players[currPlayer].hand.begin(), players[currPlayer].hand.end(), startCard) != players[currPlayer].hand.end()) {
		if (card == startCard) return true;
		else return false;
	}
	if (card.rank == 7) return true;
	if ((card.suit == 'C') && (!clubs.empty()) && (card >= (clubs.front() - 1)) && (card <= (clubs.back() + 1))) return true;
	else if ((card.suit == 'D') && (!diamonds.empty()) && (card >= (diamonds.front() - 1)) && (card <= (diamonds.back() + 1))) return true;
	else if ((card.suit == 'H') && (!hearts.empty()) && (card >= (hearts.front() - 1)) && (card <= (hearts.back() + 1))) return true;
	else if ((card.suit == 'S') && (!spades.empty()) && (card >= (spades.front() - 1)) && (card <= (spades.back() + 1))) return true;
	else return false;
}

bool StraightsModel::legalDiscard(Card card) const {
	if (validMoves().empty()) return true;
	return false;
}

std::vector<Card> StraightsModel::validMoves() const {
	int player = currPlayer;
	int handLen = players[player].hand.size();
	std::vector<Card> moves;
	for (int i = 0; i < handLen; i++) {
		if (legalPlay(players[player].hand[i])) moves.emplace_back(players[player].hand[i]);
	}
	return moves;
}

void StraightsModel::playCard(Card card) {
	// removes the played card from player's hand
	removeCard(card);

	// adds the card to the suit's pile and sorts the pile
	if (card.suit == 'C') {
		clubs.emplace_back(card);
		std::sort(clubs.begin(), clubs.end());
	}
	else if (card.suit == 'D') {
		diamonds.emplace_back(card);
		std::sort(diamonds.begin(), diamonds.end());
	}
	else if (card.suit == 'H') {
		hearts.emplace_back(card);
		std::sort(hearts.begin(), hearts.end());
	}
	else {
		spades.emplace_back(card);
		std::sort(spades.begin(), spades.end());
	}
	
	notifyObservers();
}

void StraightsModel::discardCard(Card card) {	
	removeCard(card);
	players[currPlayer].discardPile.emplace_back(card);
	players[currPlayer].roundScore += card.rank;
	players[currPlayer].totalScore += card.rank;
	
	notifyObservers();
}

Card StraightsModel::computerMove() {
	Computer c;
	std::vector<Card> moves = validMoves();
	if (moves.empty()) {
		return c.cardToDiscard(players[currPlayer]);
	}
	else {
		return c.cardToPlay(players[currPlayer], moves);
	}
}

void StraightsModel::rageQuit() {
	playerType[currPlayer] = 'c';
}

void StraightsModel::deal() {
	for (int i = 0; i < 13; i++) {
		players[0].hand.emplace_back(deck[i]);
	}
	for (int i = 13; i < 26; i++) {
		players[1].hand.emplace_back(deck[i]);
	}
	for (int i = 26; i < 39; i++) {
		players[2].hand.emplace_back(deck[i]);
	}
	for (int i = 39; i < 52; i++) {
		players[3].hand.emplace_back(deck[i]);
	}
}

void StraightsModel::startingPlayer() {
	if (find(players[0].hand.begin(), players[0].hand.end(), startCard) != players[0].hand.end()) currPlayer = 0;
	else if (find(players[1].hand.begin(), players[1].hand.end(), startCard) != players[1].hand.end()) currPlayer = 1;
	else if (find(players[2].hand.begin(), players[2].hand.end(), startCard) != players[2].hand.end()) currPlayer = 2;
	else currPlayer = 3;
}

void StraightsModel::shuffleDeck() {
	std::default_random_engine rng{ seed };
	std::shuffle(deck.begin(), deck.end(), rng);
}

void StraightsModel::resetRoundData() {
	for (int i = 0; i < 4; i++) {
		players[i].discardPile.clear();
		players[i].hand.clear();
		players[i].roundScore = 0;
	}
	clubs.clear();
	diamonds.clear();
	hearts.clear();
	spades.clear();
}


bool StraightsModel::isRoundOver() const {
	for (int i = 0; i < 4; i++) {
		if (!players[i].hand.empty()) return false;
	}
	return true;
}


bool StraightsModel::isGameOver() const {
	for (int i = 0; i < 4; i++) {
		if (players[i].totalScore >= endThreshold) return true;
	}
	return false;
}

std::vector<int> StraightsModel::playersWon() const {
	std::vector<int> won;
	won.emplace_back(0);
	
	for (int i = 1; i < 4; i++) {
		if (players[i].totalScore < players[won[0]].totalScore) {
			won.clear();
			won.emplace_back(i);
		} 
		else if (players[i].totalScore == players[won[0]].totalScore) {
			won.emplace_back(i);
		}
	}
	return won;
}
