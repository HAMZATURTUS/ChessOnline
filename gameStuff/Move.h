#ifndef MOVE_H
#define MOVE_H

#include "../Board/Tile.h"

class Move {

private:
    
    Tile* current = nullptr;
    Tile* target = nullptr;

public:
    
    void set_Move(Tile* current, Tile* target){
        this->current = current;
        this->target = target;
    }

    void get_Current(){ return current; }
    void get_Target(){ return target; }

};

#endif 