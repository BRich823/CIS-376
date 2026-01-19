/* gameloop.h
 * Blackjack game loop interface
 *
 * This header exposes a small, documented API to run an interactive
 * Blackjack play loop. Implementations should use the existing
 * `Deck` and `Hand` types defined in `deck.h`.
 *
 * Features expected from the implementation:
 *  - Prompt the player for actions: Hit (h), Stand (s), Double (d).
 *  - Execute the dealer behavior (hit while dealer total < 17).
 *  - Resolve the round (bust, compare totals, push) and
 *    support a simple betting/bankroll model.
 *
 * Notes on `double` semantics: minimal behavior is "draw one card then
 * stand". If you add betting, double should also double the wager.
 */

#ifndef H_GAMELOOP
#define H_GAMELOOP

#include "deck.h"
#include <string>
#include <iostream>

// Represents the player's chosen action during their turn.
enum class PlayerAction {
    Hit,
    Stand,
    Double,
    Invalid
};

class GameLoop{
    private:
        Deck deck;
        Hand playerHand;
        Hand dealerHand;
        int playerScore;
        int dealerScore;
        bool gameOver;
        bool playerturn;
    public:
        GameLoop();
        void playGame();
        PlayerAction parsePlayerAction(const std::string &input);
        bool promptPlayAgain(std::istream &in = std::cin, std::ostream &out = std::cout);
};



// Runs the interactive game loop. This function is blocking and will handle
// dealing, asking the player for actions, running the dealer logic, resolving
// the round, and repeating until the player quits.
//
// Implementation notes:
//  - Use `Deck::dealCard()` and `Hand::addCard()` to manage cards.
//  - Use a `Hand::value()` helper to compute


#endif // H_GAMELOOP
