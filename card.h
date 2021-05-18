#ifndef CARD_H
#define CARD_H

class Card {

public:
	int rank;
	char suit;
	Card(int rank, char suit);
};

bool operator==(const Card &lhs, const Card &rhs);
bool operator!=(const Card &lhs, const Card &rhs);
bool operator<(const Card &lhs, const Card &rhs);
bool operator>(const Card &lhs, const Card &rhs);
bool operator<=(const Card &lhs, const Card &rhs);
bool operator>=(const Card &lhs, const Card &rhs);

Card operator+(const Card &lhs,  const int & rhs);
Card operator-(const Card &lhs, const int &rhs);

#endif
