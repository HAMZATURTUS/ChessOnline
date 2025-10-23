#ifndef GAME_H
#define GAME_H

#include "Board/Board.h"

class Game {

private:
    Board* current_Board = new Board();
    bool turn = true;

public:
    void start_Game(){
        //Player* white = new Player();
        //Player* black = new Player();

        current_Board->show_Board();

    }


};

#endif 