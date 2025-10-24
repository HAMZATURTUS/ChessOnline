#ifndef PIECE_H
#define PIECE_H



class Tile;

class Piece {

protected:
    bool color; // true = white, false = black
    char rep; // p = pawn, K = king, Q = queen ...
    
public:

    Piece(bool color){
        this->color = color;
    }

    virtual bool valid_move(Tile* current, Tile* target) = 0;
    virtual bool valid_capture(Tile* current, Tile* target) = 0;

    char get_Representation(){
        if(color){
            return rep - 32;
        }
        return rep;
    }
    char get_Color(){ return color; }
    virtual char get_Piece_Type() = 0;
};


#endif 