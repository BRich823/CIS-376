#include "deck.h"
#include <algorithm>
#include <random>
#include <string>

// Simple set the values to the ones passed in. Not the safest thing to do,
// but this is just for demo purposes anyway.
Card::Card(Suit suit, int number){
	this->suit = suit;
	this->number = number;
	this->hole = false;
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

Card Deck::dealCard(bool show){
    Card top = cards.back();
    if (!show){
        top.hole = true;
    }
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

// Get the Card at the given location (if valid)
Card& Hand::operator[](size_t index){
    if(index < 0 || index > 52){
        throw std::out_of_range("That isn't a valid deck index.");
    }
    return cards[index]; 
}

// Adds a card to the hand
void Hand::addCard(const Card& card){
    cards.push_back(card); 
}

// Score the hand
//Aces can be 1 or 11, so we'll count them as 11 and subtract later if needed.
int Hand::scoreHand(){
	int score = 0;
	int aces = 0;
	bool hole = false;
	for(auto it = cards.begin(); it != cards.end(); ++it){
		if (it->getHole()){ //if the card is a hole, skip it
			hole = true;
			continue;
		}
		int num = it->getNumber(); //get the number of the card
		if(num == 1){
			num = 11;
			aces += 1;
		}
		else if(num > 10){
			num = 10;
		}
		score += num;
	}
	while ((score > 21) && (aces > 0)){
			score -= 10;
			aces -= 1;
		}
	std::cout << "Score: " << score;
	if (hole){
		std::cout << " + ??";
	}
	std::cout << std::endl;
	return score;
}

// Print out a representation of a Card
std::ostream& operator<<(std::ostream& os, const Card& card){
	if (card.hole){
		os << "??";
		return os;
	}
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
