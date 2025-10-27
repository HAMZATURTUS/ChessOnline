#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

private:
    
public:
    Knight(bool color) : Piece(color) {
        rep = 'n';
    }

    bool reachable(Tile* current, Tile* target){

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        //cout << (char)current_pos.first << current_pos.second << " " << target_pos.first << target_pos.second << ": ";

        int one = abs(current_pos.first - target_pos.first);
        int two = abs(current_pos.second - target_pos.second);

        if((one == 2 && two == 1) || (one == 1 && two == 2)){
            //cout << "\n";
            return true;
        }

        //cout << "false\n";

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

    char get_Piece_Type(){ return 'n'; }

};


#endif 