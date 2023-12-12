#pragma once
#include <Arduino.h>
#include <string>

class MoveSolver
{
    public:
        MoveSolver();
        void get_all_moves_for_figure(int row, int col, const std::string (&myArray)[8][8]);
        void displayFigData(const int (&myArray)[8][8], bool compact);
        void clear_array(int (&myArray)[8][8]);
        
        int white_en_passant_col = NULL;
        int black_en_passant_col = NULL;

        int fig_moves[8][8] = {{0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}};
        
        int fig_strikes[8][8] = {{0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0}};
        

        void get_pawn_moves(int row, int col, const std::string (&myArray)[8][8]);
        void get_rook_moves(int row, int col, const std::string (&myArray)[8][8]);
        void get_knight_moves(int row, int col, const std::string (&myArray)[8][8]);
        void get_bishop_moves(int row, int col, const std::string (&myArray)[8][8]);
        void get_queen_moves(int row, int col, const std::string (&myArray)[8][8]);
        void get_king_moves(int row, int col, const std::string (&myArray)[8][8]);
        
    private:
        bool in_range(const int &row, const int &col);
        int check_move_type(char moving_figure, char figure_on_possible_pos);
};