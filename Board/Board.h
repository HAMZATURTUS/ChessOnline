#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Tile.h"
#include "../Pieces/Piece.h"
#include "../Pieces/Pawn.h"


class Board {

private:
    int length = 8;
    int width = 8;

    vector<vector<Tile*>> board;

public:
    Board(){
        build_Board();
        place_Pieces();
    }
    
    void build_Board(){
        bool current = true;

        for(int i = 0; i < length; i++){
            vector<Tile*> v;
            for(int j = 0; j < width; j++){
                bool color = current;
                pair<char, int> position = {i + 'a', 8 - j};

                v.push_back(new Tile(color, position));

                current = !current;
            }
            board.push_back(v);
        }
    }

    void place_Pieces(){
        bool color;
        for(int i = 0; i < length; i++){
            for(int j = 0; j < width; j++){
                if(i <= 1) color = false;
                else if(i >= 6) color = true;
                else continue;

                Piece* add;
                if(i == 1 || i == 6){
                    add = new Pawn(color);
                }
                else continue;
                board[i][j]->place_Piece(new Pawn(color));
            }
        }
    }

    bool move_Piece(Tile* current, Tile* target){
        if(current->get_Piece() == nullptr) return false;
        Piece* p = current->get_Piece();
        if(target->get_Piece() == nullptr){
            if(p->valid_move(current, target)){
                current->remove_Piece();
                target->place_Piece(p);
                return true;
            }
        }
        else{
            if(p->valid_capture(current, target)){
                target->remove_Piece();
                current->remove_Piece();
                target->place_Piece(p);
                return true;
            }
        }
        return false;
    }

    void SetColor(const std::string& color) {
        std::cout << color;
    }
    void show_Board(){
        for(int i = 0; i < length; i++){
            cout << length - i << " ";
            for(int j = 0; j < width; j++){
                Piece* p = board[i][j]->get_Piece();
                if(p == nullptr){
                    cout << ".";
                }
                else cout << p->get_Representation();
                cout << " ";
            }
            cout << "\n";
        }
        cout << "  ";
        SetColor("\033[32m");
        for(char i = 'a'; i <= 'h'; i++){
            cout << i << " ";
        }
        SetColor("\033[0m"); 
        cout << "\n";
    }

};


#endif 