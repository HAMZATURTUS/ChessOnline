#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {

private:
    bool last_move_was_double = false;
    
public:
    Pawn(bool color) : Piece(color) {
        rep = 'p';
    }

    bool valid_move(Tile* current, Tile* target){
        if(target->get_Piece() != nullptr) return false;

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        if(current_pos.first != target_pos.first) return false;
        int y_target = -1;
        int y_second = -2;
        if(this->color == true){
            y_target = 1;
            y_second = 2;
        }

        if(target_pos.second - current_pos.second == y_target) return true;
        else if(target_pos.second - current_pos.second == y_second){
            if(this->color == true){
                if(current_pos.second == 2) return true;
            }
            else{
                if(current_pos.second == 7) return true;
            }
        }

        return false;
    }

    bool valid_capture(Tile* current, Tile* target){
        if(target->get_Piece() == nullptr) return false; //come back to this for en passant;

        Piece* enemy = target->get_Piece();
        if(enemy->get_Color() == this->color) return false;

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        int y_target = -1;
        if(this->color == true){
            y_target = 1;
        }
        if(target_pos.second - current_pos.first == y_target){
            if(abs(target_pos.second - current_pos.first) == 1) return true;
        }

        return false;

    }

    bool canbe_enpassant_victim(){
        return last_move_was_double;
    }

};


#endif 