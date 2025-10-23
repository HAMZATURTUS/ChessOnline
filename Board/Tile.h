#ifndef TILE_H
#define TILE_H

#include <utility>

#include "../Pieces/Piece.h"

using namespace std;
class Tile {
private:
    bool color;
    pair<char, int> position;

    Piece* current_Piece = nullptr;

public:
    Tile(char color, pair<char, int> position){
        this->color = color;
        this->position = position;
    }
    Tile(char color, pair<char, int> position, Piece* piece){
        this->color = color;
        this->position = position;
        this->current_Piece = piece;
    }

    void place_Piece(Piece* piece){
        this->current_Piece = piece;
    }
    void remove_Piece(){
        this->current_Piece = nullptr;
    }

    Piece* get_Piece(){ return current_Piece; }
    bool get_Piece_Color(){
        if(current_Piece == nullptr) return false;
        return current_Piece->get_Color();
    }
    char get_Piece_Type(){
        if(current_Piece == nullptr) return '0';
        else return current_Piece->get_Piece_Type();
    }
    pair<char, int> get_Position(){ return position; }

};


#endif 