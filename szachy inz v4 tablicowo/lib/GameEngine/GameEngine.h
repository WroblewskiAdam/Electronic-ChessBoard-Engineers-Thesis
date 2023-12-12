#pragma once
#include <Arduino.h>
#include <string>
#include <array>
#include <moveSolver.h>

class GameEngine
{
    MoveSolver moveSolver;
    public:
        bool whites_turn = true;
        int checking_figures[8][8] = {{0,0,0,0,0,0,0,0}, // macierz zawierajaca pozycje figur przeciwnika które szachują
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0}}; 
        

        int check_saving_figures[8][8] =   {{0,0,0,0,0,0,0,0}, // pozycje figur gracza ktore moga "zdjac" szacha 
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0}};

        std::string board[8][8] =  {{"0","0","0","0","0","0","0","0"}, // kodaowanie szachowncy male - czarme, duze - biale, dopisek f - figura nie wykonala jeszcze ruchu
                                    {"0","0","0","0","0","0","0","0"},
                                    {"0","0","0","0","0","0","0","0"},
                                    {"0","0","0","0","0","0","0","0"},
                                    {"0","0","0","0","0","0","0","0"},
                                    {"0","0","0","0","0","0","0","0"},
                                    {"0","0","0","0","0","0","0","0"},
                                    {"0","0","0","0","0","0","0","0"}};

        

        
        GameEngine();
        void make_move(int row, int col, int new_row, int new_col);
        void capture_figure(int row, int col, int new_row, int new_col);
        // void evaluate_check();
        // void evaluate_checkmate();
        void get_checking_figures();
        void get_check_saving_figures();
        void init_board(const char (&myArray)[8][8]);
        void print_board(const std::string (&myArray)[8][8], bool compact);
        void print_board(const int (&myArray)[8][8], bool compact);
        std::array<int,2> get_king_cords();
        std::array<int,2> get_only_one_cords(const int (&myArray)[8][8]);
        void change_turn();

    private:
        int sum_array(const int (&myArray)[8][8]);
        void clear_board(std::string (&board)[8][8]);
        void clear_array(int (&myArray)[8][8]);


};