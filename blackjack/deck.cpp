#include "deck.h"
#include <algorithm>
#include <random>
#include <string>

// Simple set the values to the ones passed in. Not the safest thing to do,
// but this is just for demo purposes anyway.
Card::Card(Suit suit, int number){
	this->suit = suit;
	this->number = number;
}

// Create a new Deck by instantiating each Card.
Deck::Deck(){
	for(int i=0; i<4; ++i){
		for(int j=1; j<14; ++j){
			// Casting from 0, 1, 2, 3 to the proper suit.
			cards.push_back(Card(static_cast<Suit>(i), j));
		}
	}
}


// "Shuffle" the deck by using the C++ standard library shuffle.
void Deck::shuffle(Deck& deck){
	// First need a random device.
	std::random_device rd;
	// Then we need an engine.
	std::mt19937 gen(rd());
	// Shuffle from the beginning to the end, using the engine.
	std::shuffle(deck.cards.begin(), deck.cards.end(), gen);
}

Card Deck::dealCard(){
    Card top = cards.back();
    std::cout << "Dealing: " << cards.back() << '\n';
    std::cout << std::endl;
    cards.pop_back();
    return top; 
}

// Get the Card at the given location (if valid)
Card& Deck::operator[](size_t index){
	if(index < 0 || index > 52){
		throw std::out_of_range("That isn't a valid deck index.");
	}
	return cards[index];
}

// Adds a card to the hand
void Hand::addCard(const Card& card){
    cards.push_back(card); 
}

// Print out a representation of a Card
std::ostream& operator<<(std::ostream& os, const Card& card){
	std::string suit = "♠";
	if(card.suit == HEART){
		suit = "♥";
	} else if (card.suit == DIAMOND){
		suit = "♦";
	} else if (card.suit == CLUB){
		suit = "♣";
	}
	
	os << suit;
	std::string number = "A";
	if(card.number > 1 && card.number < 11){
		number = std::to_string(card.number);
	} else if(card.number == 11){
		number = "J";
	} else if(card.number == 12){
		number = "Q";
	} else if(card.number == 13){
		number = "K";
	}
	os << number;

	return os;
}

// Expose the cards iterator.
std::vector<Card>::iterator Deck::begin(){
	return cards.begin();
}

std::vector<Card>::iterator Deck::end(){
	return cards.end();
}

std::vector<Card>::iterator Hand::begin(){
    return cards.begin();
}

std::vector<Card>::iterator Hand::end(){
    return cards.end();
}

