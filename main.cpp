#include <iostream>
#include <string>

#include "Game.h"
#include "Board/Board.h"

using namespace std;
int main (int argc, char** argv) {
    
    Board* b = new Board();
    b->show_Board();
    cout << "all good\n";
    
    return 0;
}