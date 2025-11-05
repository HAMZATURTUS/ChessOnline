#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"


class Queen : public Piece {

private:

public:
    Queen(bool color) : Piece(color) {
        rep = 'q';
    }

    bool reachable(Tile* current, Tile* target){

        Rook rook(true);
        Bishop bishop(true);

        if(rook.reachable(current, target) || bishop.reachable(current, target)) return true;

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

    char get_Piece_Type(){ return 'q'; }

};


#endif 