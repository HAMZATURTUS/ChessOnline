#ifndef PLAYER_H
#define PLAYER_H


#include <string>

class Player {

private:
    bool color = false;
public:
    Player(bool color){
        this->color = color;
    }

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

    bool get_Color(){ return color; }

};

#endif 