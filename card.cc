#include "card.h"
#include <algorithm>

Card::Card(int rank, char suit) : rank{ rank }, suit{ suit } {}

bool operator==(const Card &lhs, const Card &rhs) {
	return lhs.rank == rhs.rank && lhs.suit == rhs.suit;
}
bool operator!=(const Card &lhs, const Card &rhs) {
	return !(lhs == rhs);
}
bool operator<(const Card &lhs, const Card &rhs) {
	return lhs.rank < rhs.rank;
}
bool operator>(const Card &lhs, const Card &rhs) {
	return rhs.rank < lhs.rank;
}
bool operator<=(const Card &lhs, const Card &rhs) {
	return !(lhs.rank > rhs.rank);
}
bool operator>=(const Card &lhs, const Card &rhs) {
	return !(lhs.rank < rhs.rank);
}

Card operator+(const Card &lhs, const int &rhs) {
	return { lhs.rank + rhs, lhs.suit };
}

Card operator-(const Card &lhs, const int &rhs) {
	return { lhs.rank - rhs, lhs.suit };
}
