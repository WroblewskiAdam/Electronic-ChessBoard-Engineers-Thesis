#pragma once
#include <Arduino.h>
#include <string>
#include <array>
#include <MoveSolver.h>

class GameEngine
{
    public:
        std::array<std::array<int, 8>, 8> checking_figures = {{{0,0,0,0,0,0,0,0}, // macierz zawierajaca pozycje figur przeciwnika które szachują
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0}}}; 
        

        std::array<std::array<int, 8>, 8> check_saving_figures = {{{0,0,0,0,0,0,0,0}, // pozycje figur gracza ktore moga "zdjac" szacha 
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0}}};

        std::array<std::array<int, 8>, 8> check_saving_moves = {{{0,0,0,0,0,0,0,0}, // ruchy ktore ratuja od szacha
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0}}};
        
        std::array<std::array<int, 8>, 8> king_allowed_moves = {{{0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0},
                                            {0,0,0,0,0,0,0,0}}};

        std::array<std::array<int, 8>, 8> final_moves_for_figure = {{{0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0}}};

        std::array<std::array<int, 8>, 8> final_strikes = {{{0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0}}};

        std::array<std::array<int, 8>, 8> final_moves = {{{0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0},
                                                {0,0,0,0,0,0,0,0}}};

                                                
                                                

        std::array<std::array<std::string, 8>, 8> board = {{{"0","0","0","0","0","0","0","0"}, // kodaowanie szachowncy male - czarme, duze - biale, dopisek f - figura nie wykonala jeszcze ruchu
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"}}};
        
        std::array<std::array<std::string, 8>, 8> board_cpy = {{{"0","0","0","0","0","0","0","0"}, // kodaowanie szachowncy male - czarme, duze - biale, dopisek f - figura nie wykonala jeszcze ruchu
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"},
                                        {"0","0","0","0","0","0","0","0"}}};

        bool whites_turn = true;
        
        GameEngine();
        // void init_board(const char (&myArray)[8][8]);
        void init_board(const std::array<std::array<char, 8>, 8> &myArray);
        void init_fig(int row, int col, char fig);
        void print_board(const std::array<std::array<std::string, 8>, 8> &myArray, bool compact);
        void print_board(const std::array<std::array<int, 8>, 8> &myArray, bool compact);
        void change_turn();
        void make_move(int row, int col, int new_row, int new_col);
        bool evaluate_checkmate();
        bool evaluate_stalemate();
        void get_final_moves_for_figure(const int row, const int col);
        MoveSolver moveSolver;
        void reset();

    private:
        void get_checking_figures(const std::array<std::array<std::string, 8>, 8> &myArray);
        void get_check_saving_moves();
        void get_check_saving_figures();
        bool check_move_for_check(int row, int col, int new_row, int new_col); //funkcja symuluje ruch figury i sprawdza czy dany ruch skutkuje szachem
        
        void get_king_allowed_moves();
        void get_castling_moves(std::array<std::array<std::string, 8>, 8> &myArray);
        bool short_castling_condition(int &king_row, std::array<std::array<std::string, 8>, 8> &myArray);
        bool long_castling_condition(int &king_row, std::array<std::array<std::string, 8>, 8> &myArray);

        std::array<int,2> get_king_cords(const std::array<std::array<std::string, 8>, 8> &myArray);
        std::array<int,2> get_only_one_cords(const std::array<std::array<int, 8>, 8> &myArray);
        int sum_array(const std::array<std::array<int, 8>, 8> &myArray);
        void clear_board(std::array<std::array<std::string, 8>, 8> &myArray);
        void clear_array(std::array<std::array<int, 8>, 8> &myArray);
        void separate_moves_strikes();
};