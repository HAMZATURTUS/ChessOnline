#ifndef GAME_H
#define GAME_H

#include<queue>

#include "Board/Board.h"

#include "gameStuff/Player.h"

class Game {

private:
    Board* current_Board = new Board();
    bool turn = true;
    bool game_Running = false;

    queue<Tile*> enpassant_pawns;

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

        cout << "Game Over\n";
        

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

            Tile* current = nullptr;
            while(true){
                current = get_Tile(pl, 0);

                vector<Tile*> available = current_Board->get_Available_Moves(current);

                if(available.size() == 0){
                    cout << "No available moves, pick another piece\n";
                    continue;
                }

                cout << "Available moves: ";
                for(Tile* x : available){
                    pair<char, int> pos = x->get_Position();
                    cout << (char)pos.first << pos.second << " ";
                }
                cout << "\n";
                break;
            }

            Tile* target = get_Tile(pl, 1);

            bool king_on_target = false;
            if(target->get_Piece_Type() == 'k') king_on_target = true;
            
            if(current_Board->move_Piece(current, target)){

                if(king_on_target){
                    game_Running = false;
                    return;
                }

                clear_enpassant_pawns();

                Piece* moved = target->get_Piece();
                if(moved->get_Piece_Type() == 'p'){
                    if(should_Promote(current, target)){
                        promote_Pawn(target);
                    }
                    else if(should_Add_Enpassant(current, target)){
                        add_enpassant_pawn(target);
                    }
                }

                return;
            }
            
            cout << "Invalid move\n";

        }

    }

    bool should_Promote(Tile* current, Tile* target){
        Piece* p = target->get_Piece();
        if(p->get_Piece_Type() != 'p') return false;


        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        if(target_pos.second == 8 || target_pos.second == 1) return true;
        return false;
    }

    bool should_Add_Enpassant(Tile* current, Tile* target){
        Piece* p = target->get_Piece();
        if(p->get_Piece_Type() != 'p') return false;

        pair<char, int> current_pos = current->get_Position();
        pair<char, int> target_pos = target->get_Position();

        int y = target_pos.second - current_pos.second;
        if(abs(y) == 2) return true;
        return false;

    }

    void add_enpassant_pawn(Tile* tile){
        Piece* p = tile->get_Piece();

        if(p == nullptr) return;
        if(p->get_Piece_Type() != 'p') return;

        p->set_enpassant_victimcy();

        enpassant_pawns.push(tile);

    }

    void clear_enpassant_pawns(){

        while(!enpassant_pawns.empty()){
            Tile* cur = enpassant_pawns.front();
            enpassant_pawns.pop();

            Piece* p = cur->get_Piece();
            if(p == nullptr) continue;
            p->rm_enpassant_victimcy();
        }

    }

    void promote_Pawn(Tile* target){

        cout << "Pawn reached end of board\n";
        char s;
        bool color = target->get_Piece_Color();
        target->remove_Piece();
        while(true){
            cout << "Select piece to promote to (Q, R, B, N): ";
            cin >> s;
            if(s >= 'a') s -= 32;
            switch (s){
                case 'Q': target->place_Piece(new Queen(color)); return;
                case 'R': target->place_Piece(new Rook(color)); return;
                case 'B': target->place_Piece(new Bishop(color)); return;
                case 'N': target->place_Piece(new Knight(color)); return;
            }
            cout << "invalid input\n";
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