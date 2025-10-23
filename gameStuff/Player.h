#ifndef PLAYER_H
#define PLAYER_H

#include "Board/Board.h"
#include <string>

class Player {

private:

public:

    string get_Current(){

        string in;

        cout << "Select a tile in chess format (a8, b3): ";
        cin >> in;

        return in;
    }

    string get_Target(){
        string out;

        cout << "Select the target tile in chess format (a8, b3): ";
        cin >> out;

        return out;
    }

};

#endif 