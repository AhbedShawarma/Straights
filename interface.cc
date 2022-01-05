#include "interface.h"
#include "card.h"
#include "straightsmodel.h"
#include <iostream>
#include <string>
#include <stdexcept>

Interface::Interface(std::shared_ptr<StraightsModel> model) : model{ model } {
	displayRanks[1] = 'A';
	displayRanks[2] = '2';
	displayRanks[3] = '3';
	displayRanks[4] = '4';
	displayRanks[5] = '5';
	displayRanks[6] = '6';
	displayRanks[7] = '7';
	displayRanks[8] = '8';
	displayRanks[9] = '9';
	displayRanks[10] = 'T';
	displayRanks[11] = 'J';
	displayRanks[12] = 'Q';
	displayRanks[13] = 'K';

	storeRanks['A'] = 1;
	storeRanks['2'] = 2;
	storeRanks['3'] = 3;
	storeRanks['4'] = 4;
	storeRanks['5'] = 5;
	storeRanks['6'] = 6;
	storeRanks['7'] = 7;
	storeRanks['8'] = 8;
	storeRanks['9'] = 9;
	storeRanks['T'] = 10;
	storeRanks['J'] = 11;
	storeRanks['Q'] = 12;
	storeRanks['K'] = 13;

	model->attach(this);
	gameLoop();
}

Interface::~Interface() {}

void Interface::print(const std::vector<Card> &cards) const {
	int len = cards.size();
	for (int i = 0; i < len; i++) {
		std::cout << " " << displayRanks.at(cards[i].rank) << cards[i].suit;
	}
	std::cout << std::endl;
}

void Interface::outputTable() const {
	std::cout << "Cards on the table" << std::endl;
	std::cout << "Clubs:";
	print(model->getClubs());

	std::cout << "Diamonds:";
	print(model->getDiamonds());

	std::cout << "Hearts:";
	print(model->getHearts());

	std::cout << "Spades:";
	print(model->getSpades());
}

void Interface::outputDeck() const {
	int len = model->getDeck().size();
	for (int i = 0; i < 13; i++) {
		std::cout << displayRanks.at(model->getDeck()[i].rank) << model->getDeck()[i].suit << " ";
	}
	std::cout << std::endl;
	for (int i = 13; i < 26; i++) {
		std::cout << displayRanks.at(model->getDeck()[i].rank) << model->getDeck()[i].suit << " ";
	}
	std::cout << std::endl;
	for (int i = 26; i < 39; i++) {
		std::cout << displayRanks.at(model->getDeck()[i].rank) << model->getDeck()[i].suit << " ";
	}
	std::cout << std::endl;
	for (int i = 39; i < 52; i++) {
		std::cout << displayRanks.at(model->getDeck()[i].rank) << model->getDeck()[i].suit << " ";
	}
	std::cout << std::endl;
}

void Interface::update() {}

void Interface::gameLoop() {
	char input;
	for (int i = 1; i < 5; i++) {
		try {

			std::cout << "Is Player" << i << " a human (h) or computer (c)?" << std::endl;
			std::cout << ">";
			std::cin >> input;
			if (input == 'c') model->setComputer(i - 1);
		}
		catch(std::invalid_argument& e) {}
	}
	while (!model->isGameOver()) {
		model->shuffleDeck();
		model->deal();
		model->startingPlayer();
		std::cout << "A new round begins. It's Player" << model->getCurrPlayer() + 1 << "'s turn to Play." << std::endl;
		while (!model->isRoundOver()) {
			if (model->isHuman()) {
				outputTable();
				std::cout << "Your hand:";
				print(model->getPlayerHand());
				std::cout << "Legal plays:";
				print(model->validMoves());
				int retVal = humanTurn();
				if (retVal == 1) return;
			}
			else {
				computerTurn();
			}
			model->nextPlayer();
		}
		for (int i = 1; i < 5; i++) {
			std::cout << "Player" << i << "'s discards:";
			print(model->getPlayerDiscards(i - 1));
			std::cout << "Player" << i << "'s score: " << model->getPlayerOldScore(i - 1) << " + " << model->getPlayerNewScore(i - 1) 
				<< " = " << model->getPlayerOldScore(i - 1) + model->getPlayerNewScore(i - 1) << std::endl;
		}
		model->resetRoundData();
	}
	std::vector<int> winningPlayers = model->playersWon();
	for (int i = 0; i < winningPlayers.size(); i++) {
		std::cout << "Player" << winningPlayers[i] + 1 << " wins!" << std::endl;
	}
	
}

void Interface::computerTurn() {
	Card chosen = model->computerMove();
	if (model->validMoves().empty()) {
		std::cout << "Player" << model->getCurrPlayer() + 1 << " discards " << displayRanks[chosen.rank] << chosen.suit << "." << std::endl;
		model->discardCard(chosen);
	}
	else {
		std::cout << "Player" << model->getCurrPlayer() + 1 << " plays " << displayRanks[chosen.rank] << chosen.suit << "." << std::endl;
		model->playCard(chosen);
	}
}

int Interface::humanTurn() {
	std::string cmd;
	std::cout << ">";
	try {

		while (std::cin >> cmd) {
		
			if (cmd == "play") {
				char rank;
				char suit;
				std::cin >> rank;
				std::cin >> suit;
				Card played = { storeRanks[rank], suit };
				if (!model->legalPlay(played)) {
					std::cout << "This is not a legal play." << std::endl;
				}
				else {
					std::cout << "Player" << model->getCurrPlayer() + 1 << " plays " << rank << suit << "." << std::endl;
					model->playCard(played);
					return 0;
				}
			}
			else if (cmd == "discard") {
				char rank;
				char suit;
				std::cin >> rank;
				std::cin >> suit;
				Card discarded = { storeRanks[rank], suit };
				if (!model->legalDiscard(discarded)) {
					std::cout << "You have a legal play. You may not discard." << std::endl;
				}
				else {
					std::cout << "Player" << model->getCurrPlayer() + 1 << " discards " << rank << suit << "." << std::endl;
					model->discardCard(discarded);
					return 0;
				}
			}
			else if (cmd == "deck") {
				outputDeck();
			}
			else if (cmd == "ragequit") {
				model->rageQuit();
				computerTurn();
				return 0;
			}
			else if (cmd == "quit") {
				return 1;
			}
			else {
				std::cout << "Invalid command." << std::endl;
			}
			std::cout << ">";
		}
	}
	catch(std::ios::failure&) {}
	
}
