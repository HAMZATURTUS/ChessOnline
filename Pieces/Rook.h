#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"



class Rook : public Piece {

private:
    
public:
    Rook(bool color) : Piece(color) {
        rep = 'r';
    }

    bool reachable(Tile* current, Tile* target){

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        int one = (target_pos.first - current_pos.first);
        int two = (target_pos.second - current_pos.second);

        if(one == 0 || two == 0){
            if(one != 0 || two != 0) return true;
        }

        return false;
    }

    bool valid_move(Tile* current, Tile* target){
        if(target->get_Piece() != nullptr) return false;

        return reachable(current, target);
    }

    bool valid_capture(Tile* current, Tile* target){
        if(target->get_Piece() == nullptr) return false;

        return reachable(current, target);

    }

    char get_Piece_Type(){ return 'r'; }

};


#endif 