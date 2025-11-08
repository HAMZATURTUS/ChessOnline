#include <iostream>
#include <string>


#include "Game.h"
#include "Board/Board.h"
#include "Board/Tile.h"

using namespace std;

Board* b;
Tile* first;

bool turn = true;

void makeBoard(){
    b = new Board();
}

bool getTurn(){
    return turn;
}

int hasPiece(string tile){

    Tile* t = b->get_Tile_Coords(tile[0], tile[1] - '0');
    if(t->get_Piece() == nullptr) return -1;

    else return t->get_Piece_Color();

}

vector<string> getAvailableMoves(string start){
    
    first = b->get_Tile_Coords(start[0], start[1] - '0');
    vector<Tile*> vect = b->get_Available_Moves(first);
    vector<string> ret;
    
    for(Tile* x : vect){
        string add = "";
        pair<char, int> pos = x->get_Position();
        add.push_back((pos.first));
        add.push_back(char(pos.second + int('0')));

        int piece = 0;
        if(x->get_Piece() != nullptr) piece = 1;

        ret.push_back(char(piece + '0') + add);
    }
    
    return ret;
    
}

void makeMove(string end){
    b->move_Piece(first, b->get_Tile_Coords(end[0], end[1] - '0'));
    turn = !turn;
}

int main (int argc, char** argv) {
    
    return 0;
}


#include <emscripten/emscripten.h>
#include <emscripten/bind.h>


EMSCRIPTEN_BINDINGS(module) {
    
    emscripten::function("makeBoard", &makeBoard);
    emscripten::function("getTurn", &getTurn);
    emscripten::function("hasPiece", &hasPiece);
    emscripten::function("getAvailableMoves", &getAvailableMoves);
    emscripten::function("makeMove", &makeMove);
    
    
    emscripten::register_vector<string>("vector<string>");
}
