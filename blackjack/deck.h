/* deck.h
 * MrW 2026
 * A simple set of classes for a deck of cards.  ASCII-based images for suits.
 *
 * First - include guards to ensure we don't import code more than once.
 */

#ifndef		__H__DECK__
#define		__H__DECK__

/* We are referring to the ostream and vector classes in this file, so we have to
 * include them so the compiler knows what we are talking about.
 */

#include <iostream>
#include <vector>

/* I don't want to refer to the suits as numbers.  Checking things later, it would be
 * easier if my code looked like `if(card.suit == HEART)` rather than
 * `if(card.suit == 0)`.  Enums let us create a new type that is really just
 * numbers under the hood.  So below, SPADE = 0, HEART = 1, etc.
 */

enum Suit { SPADE, HEART, DIAMOND, CLUB };

/* A Card is two pieces of data - a suit and a number. */
class Card {
	// Data or methods we don't want other classes to be able to change directly
	private:
		Suit suit;
		int number;

	// Data or methods that can be used by other classes
	public:
		// Two constructors.  If we had not created the second constructor,
		// (the one that takes the two parameters), we wouldn't need to specify
		// the default constructor as C++ would have made one.  But once you
		// make a constructor on your own, C++ no longer makes the default one
		// unless you tell it to.
		Card() = default;
		Card(Suit suit, int number);
		
		// Getter
		Suit getSuit();
		int getNumber();

		// I want the Deck class to be able to access the Card data without
		// needing the getters.  I'm going to make it a friend class so that
		// it has access to my private information.
		friend class Deck;

		// When you print something in C++, we send it to the standard output stream
		// (std::cout).  Every type of data (ints, floats, strings, your own data types)
		// must have an operator<< function that tells std::cout how to print that
		// data type (if we want to send it to the ostream that is).  
		// This function *lives in the global namespace*.  Since this function is not
		// part of the Card class, we are marking it a friend here so it can access
		// Card data without a getter.
		friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

// Also need a Deck class
class Deck {
	private:
		// A Deck holds cards.  We could have been (possibly) more efficient
		// by using a fixed-size array since we are only ever going to have
		// 52 cards, but vector is very efficient, and we need to learn how
		// to use them, so here we are!
		std::vector<Card> cards;

	public:
		// Constructor
		Deck();
		// I want to access cards by indexing the Deck.  operator[] let's us 
		// do that.  Remember, we are taking a size_t (an unsigned long) since
		// we don't need negative values for an index.
		Card& operator[](size_t index);
		
		// Shuffle a deck.  This function is static (belongs to the class not
		// objects).  We could have also (probably better to have) had a non-static
		// method for this, but I wanted to show how to use static methods and illustrate
		// passing a Deck around by reference.  Try changing it to pass by copy instead
		// and see what happens!
		static void shuffle(Deck& deck);

		// Really, we want to iterate over the vector of cards.  But it would be
		// nice if we could just call myDeck.begin() and myDeck.end() instead of
		// myDeck.cards.begin(), etc.  These two lines allow us to expose that iterator.
		std::vector<Card>::iterator begin();
		std::vector<Card>::iterator end();
		
};

#endif
