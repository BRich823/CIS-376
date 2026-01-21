#include "game_loop.h"
#include <iostream>
#include <string>
#include <limits>

GameLoop::GameLoop(){
	this->deck = Deck();
	this->playerHand = Hand();
	this->dealerHand = Hand();
	this->playerScore = 0;
	this->dealerScore = 0;
	this->gameOver = false;
    this->playerturn = true;
    this->bet = 0; 
    this->money = 100; 
}

void GameLoop::playGame(){
    //create deck and hands
	Deck deck;

    // Create the player and dealer's hand
    // The vector, for example, may be < ♦K, ♥9, ♣3, ♠A>
    // The top of the deck, is the back of the vector (♠A)
    Hand playerHand;
    Hand dealerHand;

	// Shuffle the deck (notice the static-method call)
	Deck::shuffle(deck);
    
    // Displays initial amount of money
    std::cout << "Money left: " << money << "\n"; 
    // Handles initial player bets. 
    while (true) {
        std::cout << "Place your bet: "; 
        if (std::cin >> bet) {
            if (bet <= money) {
                money -= bet; 
                break; 
            }else{
                std::cout << "You don't have enough money for that bet.\n"; 
            }
        }else{
            std::cout << "Please enter a proper amount for the bet.\n"; 
            // Clear the error state and discard the invalid input so the
            // next read can proceed normally instead of looping forever.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Deals cards to the player and the dealer
    // Using the above vector, the result should look like so:
    // playerHand = < ♠A, ♥9 >
    // dealerHand = < ♣3, ♦K >
    std::cout << "Dealing...\n\n"; 
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard(false));
    
	// Prints the playerHand and dealerHand using the iterator from
    // the above printing of the deck (given code)
    std::cout << "Your Hand: ";
    for(auto it = playerHand.begin(); it != playerHand.end(); ++it){
        std::cout << *it << "\t";
    }
    std::cout << std::endl;
    playerScore = playerHand.scoreHand();

    std::cout << "Dealer's Hand: ";
    for(auto it = dealerHand.begin(); it != dealerHand.end(); ++it){
        std::cout << *it << "\t";
    }
    std::cout << std::endl;
    dealerScore = dealerHand.scoreHand();
    while (this->playerturn && this->gameOver == false){
        // Player's turn 
        std::cout << "Player's turn. Choose an action (h/s/d): ";
        std::string input;
        std::cin >> input;
        PlayerAction action = parsePlayerAction(input);
        if (action == PlayerAction::Hit){
            playerHand.addCard(deck.dealCard());
        }
        else if (action == PlayerAction::Stand){
            this->playerturn = false;
        }
        else if ((action == PlayerAction::Double) && (bet <= money)){
            money -= bet;
            bet += bet; 
            playerHand.addCard(deck.dealCard());
            this->playerturn = false;
        }
        else {
            std::cout << "Invalid action. Please try again." << std::endl;
        }
        std::cout << "Your Hand: ";
        for(auto it = playerHand.begin(); it != playerHand.end(); ++it){
            std::cout << *it << "\t";
        }
        std::cout << std::endl;
        playerScore = playerHand.scoreHand();
        //handles bust
        if (playerScore > 21){
            std::cout << "Player busts! Dealer wins." << std::endl;
            std::cout << "You lost $" << bet << "\n";
            std::cout << "Money left: " << money << "\n"; 
            gameOver = true;
        }
    }
    
    // Dealer plays if player hasn't busted.
    // First flips the hole card and adds the total. 
    if (!gameOver) { 
        dealerHand[1].reveal();
        for (auto it = dealerHand.begin(); it != dealerHand.end(); ++it) {
            std::cout << *it << "\t"; 
        } 
        // If the score is 17 or less, the dealer takes another card 
        dealerScore = dealerHand.scoreHand();
        while ((dealerScore <= 17) || dealerScore < playerScore) {  
            std::cout << "Dealer Hits...\n"; 
            dealerHand.addCard(deck.dealCard());
            std::cout << "Dealer Hand: "; 
            for (auto it = dealerHand.begin(); it != dealerHand.end(); ++it) {
                std::cout << *it << "\t"; 
            }
            dealerScore = dealerHand.scoreHand(); 
            if (dealerScore > 21) {
                std::cout << "Dealer Busts\n"; 
                break; 
            }
        }
    
        // Compares scores after the dealer's turn. 
        if (playerScore > 21) {
            std::cout << "Dealer Wins!\n";
            std::cout << "You Lost $" << bet << "\n";
            std::cout << "Money Left: " << money << "\n\n";
        }else if (dealerScore > 21) {
            std::cout << "Player Wins!\n"; 
            money += (bet + bet * 2);
            std::cout << "You Won $" << bet * 2 << "\n";
            std::cout << "Money Left: " << money << "\n\n"; 
        }else if (playerScore > dealerScore) {
            std::cout << "Player Wins!\n";
            money += (bet + bet * 2);
            std::cout << "You Won $" << bet * 2 << "\n";
            std::cout << "Money Left: " << money << "\n\n";
        }else if (dealerScore > playerScore) {
            std::cout << "Dealer Wins!\n";
            std::cout << "You Lost $" << bet << "\n";
            std::cout << "Money Left: " << money << "\n\n";
        }else{
            std::cout << "Push!\n"; 
            std::cout << "You get your money back.\n"; 
            money += bet; 
            std::cout << "Money Left: " << money << "\n\n"; 
        }
    }
    
    if (GameLoop::promptPlayAgain(std::cin, std::cout)){
        //play again
        this->gameOver = false;
        this->playerturn = true;
        this->playGame();
    }
    return;
}
// Parse a textual input into a PlayerAction.
// Accepts case-insensitive single-letter commands such as "h", "s", "d",
// or the full words "hit", "stand", "double". Returns `PlayerAction::Invalid`
// for unrecognized input.
PlayerAction GameLoop::parsePlayerAction(const std::string &input){
	PlayerAction action = PlayerAction::Invalid;
	if (input == "h" || input == "hit"){
		action = PlayerAction::Hit;
	}
	else if (input == "s" || input == "stand"){
		action = PlayerAction::Stand;
	}
	else if (input == "d" || input == "double"){
		action = PlayerAction::Double;
	}
	return action;
}
// Prompt the player if they want to play another round. Uses `in`/`out`
// so the function is testable; defaults to `std::cin`/`std::cout`.
// Returns true for yes, false for no.
bool GameLoop::promptPlayAgain(std::istream &in, std::ostream &out){
	out << "Play again? (y/n): ";
	std::string input;
	in >> input;
	if (input == "y" || input == "yes"){
		return true;
	}
	else if (input == "n" || input == "no"){
		return false;
	}
	else {
		out << "Invalid input. Please enter 'y' or 'n'." << std::endl;
		return promptPlayAgain(in, out);
	}
}
