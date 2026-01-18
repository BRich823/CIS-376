#include "deck.h"
#include <iostream>

int main(int argc, char** argv){
	// Creates a deck
	Deck deck;

    // Create the player and dealer's hand
    // The vector, for example, may be < ♦K, ♥9, ♣3, ♠A>
    // The top of the deck, is the back of the vector (♠A)
    Hand playerHand;
    Hand dealerHand;

	// Shuffle the deck (notice the static-method call)
	Deck::shuffle(deck);
    std::cout << "Deck after shuffle:" << std::endl;
    for(auto it = deck.begin(); it != deck.end(); ++it){
        std::cout << *it << "\t"; 
    }
    std::cout << std::endl;

    // Deals cards to the player and the dealer
    // Using the above vector, the result should look like so:
    // playerHand = < ♠A, ♥9 >
    // dealerHand = < ♣3, ♦K >
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());
    
	// Prints the playerHand and dealerHand using the iterator from
    // the above printing of the deck (given code)
	std::cout << "PlayerHand";
    for(auto it = playerHand.begin(); it != playerHand.end(); ++it){
        std::cout << *it << "\t";
    }
    std::cout << std::endl;
   
    std::cout << "DealerHand";
    for(auto it = dealerHand.begin(); it != dealerHand.end(); ++it){
        std::cout << *it << "\t";
    }
    std::cout << std::endl;
}
