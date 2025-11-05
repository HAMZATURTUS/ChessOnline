#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"



class Bishop : public Piece {

private:
    
public:
    Bishop(bool color) : Piece(color) {
        rep = 'b';
    }

    bool reachable(Tile* current, Tile* target){

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        int one = (target_pos.first - current_pos.first);
        int two = (target_pos.second - current_pos.second);

        if(abs(one) != abs(two) || one == 0){
            return false;
        }

        return true;
    }

    bool valid_move(Tile* current, Tile* target){
        if(target->get_Piece() != nullptr) return false;

        return reachable(current, target);
    }

    bool valid_capture(Tile* current, Tile* target){
        if(target->get_Piece() == nullptr) return false;

        return reachable(current, target);

    }

    char get_Piece_Type(){ return 'b'; }

};


#endif 