#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Tile.h"
#include "../Pieces/Piece.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/King.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Queen.h"


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
                pair<char, int> position = {j + 'a', 8 - i};

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

                Piece* add = nullptr;
                if(i == 1 || i == 6){
                    add = new Pawn(color);
                }
                else{
                    switch(j){
                        case 0: case 7: add = new Rook(color); break;
                        case 1: case 6: add = new Knight(color); break;
                        case 2: case 5: add = new Bishop(color); break;
                        case 3: add = new Queen(color); break;
                        case 4: add = new King(color); break;
                    }
                }
                if(add != nullptr) board[i][j]->place_Piece(add);
            }
        }
    }

    bool check_clear_path(Tile* current, Tile* target){

        
        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        //cout << (char)current_pos.first << current_pos.second << " " << target_pos.first << target_pos.second << ": ";

        if(current->get_Piece_Color() == target->get_Piece_Color() && target->get_Piece() != nullptr){
            return false;
        }
        if(current->get_Piece_Type() == 'n'){
            return true;
        }
        //cout << current->get_Piece_Type() << "\n";
        
        int x = target_pos.first - current_pos.first;
        int y = target_pos.second - current_pos.second;
        
        if(abs(x) == 1 || abs(y) == 1) return true;

        int xx = 0, yy = 0;
        if(x < 0) xx = -1;
        else if(x > 0) xx = 1;
        
        if(y < 0) yy = -1;
        else if(y > 0) yy = 1;

        x = current_pos.first;
        y = current_pos.second;
        x += xx; y += yy;

        
        while(x != target_pos.first || y != target_pos.second){

            Tile* mid = get_Tile_Coords(x, y);
            if(mid->get_Piece() != nullptr) return false;

            x += xx; y += yy;
        }


        return true;

    }
    

    bool move_Piece(Tile* current, Tile* target){
        if(current->get_Piece() == nullptr) return false;
        Piece* p = current->get_Piece();
        if(target->get_Piece() == nullptr){

            if(p->valid_move(current, target)){

                if(check_clear_path(current, target)){

                    current->remove_Piece();
                    target->place_Piece(p);

                    p->set_moved();
                    
                    return true;
                }
            }
            else if(p->get_Piece_Type() == 'p'){
                pair<char, int> current_pos = current->get_Position();
                pair<char, int> target_pos = target->get_Position();

                int x = target_pos.first - current_pos.first;
                int y = target_pos.second - current_pos.second;

                if(abs(x) == 1 && abs(y) == 1){
                    Tile* mid = get_Tile_Coords(target_pos.first, current_pos.second);
                    if(p->valid_enpassant(current, mid)){
                        mid->remove_Piece();
                        current->remove_Piece();
                        target->place_Piece(p);

                        p->set_moved();

                        return true;
                    }
                }
            }
            else if(p->get_Piece_Type() == 'k' && p->has_moved() == false){
                pair<char, int> current_pos = current->get_Position();
                pair<char, int> target_pos = target->get_Position();

                int x = target_pos.first - current_pos.first;
                int y = target_pos.second - current_pos.second;

                if(y == 0 && abs(x) == 2){

                    bool right = true;
                    if(x == -2) right = false;

                    bool color = p->get_Color();

                    Tile* other = this->get_Tile_Coords(right ? 'h' : 'a', target_pos.second);
                    int add = right ? -1 : 1;

                    Piece* rook = other->get_Piece();
                    if(rook->has_moved() == false && rook->get_Color() == p->get_Color()){
                        p->set_moved();
                        rook->set_moved();

                        current->remove_Piece();
                        target->place_Piece(p);

                        other->remove_Piece();
                        Tile* rooks_tile = this->get_Tile_Coords(target_pos.first + add, target_pos.second);
                        rooks_tile->place_Piece(rook);
                        return true;
                    }

                }

            }
        }
        else{

            if(p->valid_capture(current, target)){

                if(check_clear_path(current, target)){

                    target->remove_Piece();
                    current->remove_Piece();
                    target->place_Piece(p);

                    p->set_moved();
                    
                    return true;
                }
            }
        }
        return false;
    }

    void SetColor(const std::string& color) {
        std::cout << color;
    }
    void show_Board(){
        cout << "\n\n";
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
    void show_Board(bool color){
        cout << "\n\n";
        
        if(color == 0){
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
        }
        else{
            for(int i = length - 1; i >= 0; i--){
                cout << length - i << " ";
                for(int j = width - 1; j >= 0; j--){
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
            for(char i = 'h'; i >= 'a'; i--){
                cout << i << " ";
            }
            SetColor("\033[0m"); 
        }
            cout << "\n";
    }

    vector<Tile*> get_Available_Moves(Tile* current){
        vector<Tile*> ret;

        Piece* p = current->get_Piece();

        for(int i = 0; i < length; i++){
            for(int j = 0; j < width; j++){
                Tile* target = this->get_Tile(i, j);
                if(target == current) continue;
                if((p->valid_move(current, target) || p->valid_capture(current, target)) && (check_clear_path(current, target))){
                    ret.push_back(target); continue;
                }
                else if(p->get_Piece_Type() == 'p' && p->valid_enpassant(current, target)){
                    pair<char, int> target_pos = target->get_Position();
                    int add = 1;
                    if(p->get_Color() == false) add = -1;
                    ret.push_back(this->get_Tile_Coords(target_pos.first, target_pos.second + add)); continue;
                }
                else if(p->get_Piece_Type() == 'k' && p->has_moved() == false){
                    pair<char, int> current_pos = current->get_Position();
                    pair<char, int> target_pos = target->get_Position();

                    int x = target_pos.first - current_pos.first;
                    int y = target_pos.second - current_pos.second;

                    if(y == 0 && abs(x) == 2){

                        bool right = true;
                        if(x == -2) right = false;

                        bool color = p->get_Color();

                        Tile* other = this->get_Tile_Coords(right ? 'h' : 'a', target_pos.second);
                        int add = right ? -1 : 1;

                        Piece* rook = other->get_Piece();
                        if(rook->has_moved() == false && rook->get_Color() == p->get_Color()){
                            ret.push_back(target); continue;
                        }

                    }
                }
            }
        }
        return ret;
    }

    Tile* get_Tile(int i, int j){
        
        if(i < 0 || i > 7 || j < 0 || j > 7){
            cout << i << " " << j << " is out of bounds\n";
            return nullptr;
        }

        return board[i][j];
    }

    Tile* get_Tile_Coords(char a, int n){

        if(a > 'h' || a < 'a' || n < 1 || n > 8){
            cout << char(a) << n << " is out of bounds\n";
            return nullptr;
        }

        int i = 8 - n;
        int j = a - 'a';
        return board[i][j];
    }

};


#endif 