#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

private:
    
public:
    King(bool color) : Piece(color) {
        rep = 'k';
    }

    bool reachable(Tile* current, Tile* target){

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();


        int one = abs(current_pos.first - target_pos.first);
        int two = abs(current_pos.second - target_pos.second);

        if(one <= 1 && two <= 1){
            return true;
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

    char get_Piece_Type(){ return 'k'; }

};


#endif 