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


    char get_Representation(){
        return rep;
    }
};


#endif 