#include <iostream>
#include <string>

#include "Game.h"
#include "Board/Board.h"

using namespace std;
int main (int argc, char** argv) {
    
    Game* g = new Game();
    
    g->start_Game();
    
    return 0;
}