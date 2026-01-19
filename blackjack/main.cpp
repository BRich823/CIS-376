#include "deck.h"
#include <iostream>
#include "game_loop.h"
// On Windows the console code page may not be UTF-8 by default which causes
// Unicode suit symbols (♠♥♦♣) to render incorrectly. Enable UTF-8 when
// compiling/running on Windows so those characters print properly.

int main(int argc, char** argv){

    //start the game loop
    GameLoop game = GameLoop();
    game.playGame();
}