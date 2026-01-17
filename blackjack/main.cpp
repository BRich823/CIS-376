#include "deck.h"
#include <iostream>

int main(int argc, char** argv){
	// Create a deck
	Deck deck;
	// Shuffle the deck (notice the static-method call)
	Deck::shuffle(deck);
	// Auto keyword deduces type for us, so we don't have to.  Here
	// it is for creating an iterator.
	for(auto it = deck.begin(); it != deck.end(); ++it){
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
}
