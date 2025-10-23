#ifndef PIECE_H
#define PIECE_H

//#include "../Board/Tile.h"

class Piece {

protected:
    bool color; // true = white, false = black
    char rep; // p = pawn, K = king, Q = queen ...
    
public:

    Piece(bool color){
        this->color = color;
    }

    char get_Representation(){
        return rep;
    }
};


#endif 