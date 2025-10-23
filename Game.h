#ifndef GAME_H
#define GAME_H

#include "Board/Board.h"

#include "gameStuff/Player.h"

class Game {

private:
    Board* current_Board = new Board();
    bool turn = true;
    bool game_Running = false;

    Player* white = nullptr;
    Player* black = nullptr;

public:
    void start_Game(){
        white = new Player(true);
        black = new Player(false);

        game_Running = true;

        current_Board->show_Board();

        while(game_Running){
            move(turn);

            turn = !turn;
            current_Board->show_Board();
        }
        

    }

    void move(bool turn){

        string prin;
        Player* pl;

        if(turn){
            prin = "White";
            pl = white; 
        }
        else{
            prin = "Black";
            pl = black;
        }

        while(true){
            cout << prin << "\'s move\n";

            Tile* current = get_Tile(pl, 0);
            Tile* target = get_Tile(pl, 1);

            
            if(current_Board->move_Piece(current, target)){

                Piece* moved = target->get_Piece();
                pair<char, int> position = target->get_Position();
                if(moved->get_Piece_Type() == 'p'){
                    if(position.second == 1 || position.second == 8){
                        promote_Pawn(target);
                    }
                }

                return;
            }
            
            cout << "Invalid move\n";

        }

    }

    void promote_Pawn(Tile* target){

        cout << "Pawn reached end of board\n";
        char s;
        target->remove_Piece();
        while(true){
            cout << "Select piece to promote to (Q, R, B, N): ";
            cin >> s;
            if(s >= 'a') s -= 32;
            switch (s){
                case 'Q': return;
                case 'R': return;
                case 'B': return;
                case 'N': return;
            }
        }

    }

    string parse_Input(string s){

        if(s.size() != 2) return "-1";
        if(s[0] < 'a' || s[0] > 'h') return "-1";
        if(s[1] < '1' || s[1] > '8') return "-1";

        return s;

    }

    pair<int, int> get_Vector_Idxs(string s){

        int j = s[0] - 'a';
        int i = 7 - (s[1] - '1');

        return {i, j};

    }

    Tile* get_Tile(Player* p, bool is_target){

        string s;
        while(true){
            s = parse_Input(p->get_Current());
            if(s == "-1"){
                cout << "Invalid input\n";
                continue;
            }

            pair<int, int> idxs = get_Vector_Idxs(s);
            
            Tile* selected = current_Board->get_Tile(idxs.first, idxs.second);
            Piece* piece = selected->get_Piece();
            if(is_target){
                if(piece == nullptr || piece->get_Color() != p->get_Color()) return selected;
                else{
                    cout << "target is occupied by friendly piece\n";
                }

            }
            else{
                if(piece != nullptr){
                    if(selected->get_Piece_Color() == p->get_Color()) return selected;
                    else cout << "Tile has a piece of the wrong side\n";
                }
                else{
                    cout << "Tile has no piece\n";
                }
            }

        }

    }


};

#endif 