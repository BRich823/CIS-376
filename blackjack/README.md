# Blackjack Game (C++)
### Designed by Colin Nagley and Brody Richards 
Blackjack is a widely-known and popular game. We are creating a very simple, ASCII game that allows users to play a single-player game against the dealer (computer). 

## Download and Run 
1. Download the blackjack folder onto your device.
2. Run ```g++ main.cpp game_loop.cpp deck.cpp -o myGame``` then ```./myGame```.

## Rules
Now you have the game file on your computer and have begun to play the game. Here are the basic rules to blackjack: 
* You start with $100, displayed as (Money Left: $100).
* You place a bet, either less than or equal to the amount of money you have left. If you win the hand you will get your money back, plus double your bet (i.e., if you started with $100, bet $100, and win the hand, you will have $300). If you lose the bet, you lose that money.
* The dealer gives you two cards, and themself two cards (one faceup, one facedown--the hole card).
* You now select to either hit, stand, or double down (Type ```h``` or ```hit``` for hit, ```s``` or ```stand``` for stand, ```d``` or ```double``` for double down).
* If you hit, you get another card dealt to you. If the total of your hand is >21, you lose bust and lose the round. If you double down, you get exactly one more card and you double your bet. If you stand, your turn is over.
* Once your turn is over, the dealer goes. The dealer reveals the hole card, and then, if their hand is less than the player hand or less than 17 they must hit.
* After the dealer goes, both hands are compared. If the dealer's hand is > 21, you win. If your hand is greater than the dealer's hand, you win. If the hands are tied, the bet pushes, and you get your money back.
* After the round, assuming you still have money left, you will receive a prompt to either play again or walk away. Enter ```y``` to play again or ```n``` to exit.

## FAQs
* If you are having trouble with input try entering only one character or key and then enter. (```h``` for hit, ```s``` for stand, ```d``` for double down; and ```y``` for play again and ```n``` for leave the table).
* Aces have a value of 1 and 11. The value is automatically calculated by having the Ace count as 11 until the player would bust. Then, the Ace counts for 1.
* Double Down is not broken. If you started the round with $100 and bet $75, you cannot double down your bet since you would have to give the dealer $150 if you lost, which exceeds your money ($100).
* If you are familiar with blackjack you are probably wondering where the split feature is. Maybe one day... 
