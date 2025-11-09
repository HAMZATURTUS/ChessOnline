#include <iostream>
#include <string>


#include "Game.h"
#include "Board/Board.h"
#include "Board/Tile.h"

using namespace std;

Board* b;
Tile* current;

queue<Tile*> enpassant_pawns;

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
    
    current = b->get_Tile_Coords(start[0], start[1] - '0');
    vector<Tile*> vect = b->get_Available_Moves(current);
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

bool should_Add_Enpassant(Tile* current, Tile* target){
    Piece* p = target->get_Piece();
    if(p->get_Piece_Type() != 'p') return false;

    pair<char, int> current_pos = current->get_Position();
    pair<char, int> target_pos = target->get_Position();

    int y = target_pos.second - current_pos.second;
    if(abs(y) == 2) return true;
    return false;

}

void add_enpassant_pawn(Tile* tile){
    Piece* p = tile->get_Piece();

    if(p == nullptr) return;
    if(p->get_Piece_Type() != 'p') return;

    p->set_enpassant_victimcy();

    enpassant_pawns.push(tile);

}

void clear_enpassant_pawns(){

    while(!enpassant_pawns.empty()){
        Tile* cur = enpassant_pawns.front();
        enpassant_pawns.pop();

        Piece* p = cur->get_Piece();
        if(p == nullptr) continue;
        p->rm_enpassant_victimcy();
    }

}

void makeMove(string end){

    Tile* target = b->get_Tile_Coords(end[0], end[1] - '0');

    b->move_Piece(current, b->get_Tile_Coords(end[0], end[1] - '0'));
    turn = !turn;

    clear_enpassant_pawns();
    if(should_Add_Enpassant(current, target)) add_enpassant_pawn(target);

}

string getPieceType(string label){
    Tile* t = b->get_Tile_Coords(label[0], label[1] - '0');

    string s = "";
    if(t->get_Piece() != nullptr) s.push_back(t->get_Piece_Type());
    else s = "0";

    return s;
}

bool getPieceColor(string label){
    Tile* t = b->get_Tile_Coords(label[0], label[1] - '0');

    return t->get_Piece_Color();
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
    emscripten::function("getPieceType", &getPieceType);
    emscripten::function("getPieceColor", &getPieceColor);
    
    
    emscripten::register_vector<string>("vector<string>");
}
