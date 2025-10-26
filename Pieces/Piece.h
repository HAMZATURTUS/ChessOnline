#ifndef PIECE_H
#define PIECE_H



class Tile;

class Piece {

protected:
    bool color; // true = white, false = black
    bool moved = false;
    char rep; // p = pawn, K = king, Q = queen ...
    
public:
    Piece(bool color){
        this->color = color;
    }

    virtual bool valid_move(Tile* current, Tile* target) = 0;
    virtual bool valid_capture(Tile* current, Tile* target) = 0;
    
    virtual bool valid_enpassant(Tile* current, Tile* target){ return false; }
    virtual bool canbe_enpassant_victim(){ return false; }
    virtual void set_enpassant_victimcy(){ return; }
    virtual void rm_enpassant_victimcy(){ return; }

    char get_Representation(){
        if(color){
            return rep - 32;
        }
        return rep;
    }

    void set_moved(){ moved = true; }

    char get_Color(){ return color; }
    bool has_moved(){ return moved; }
    virtual char get_Piece_Type() = 0;

};


#endif 