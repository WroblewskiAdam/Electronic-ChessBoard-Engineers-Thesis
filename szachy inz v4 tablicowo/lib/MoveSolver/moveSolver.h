#pragma once
#include <Arduino.h>
#include <string>
#include <array>

class MoveSolver
{
    public:
        MoveSolver();
        void get_all_moves_for_figure(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        void print_array(const std::array<std::array<int, 8>, 8> &myArray, bool compact);
        
        int white_en_passant_col = NULL;
        int black_en_passant_col = NULL;

        std::array<std::array<int, 8>, 8> fig_moves = {{{0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0},
                                                        {0,0,0,0,0,0,0,0}}};
        
        std::array<std::array<int, 8>, 8> fig_strikes =   {{{0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0}}};
        
        std::array<std::array<int, 8>, 8> fig_all_moves = {{{0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0},
                                                            {0,0,0,0,0,0,0,0}}};

        
    
        void get_pawn_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        void get_rook_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        void get_knight_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        void get_bishop_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        void get_queen_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        void get_king_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray);
        

    private:
        void clear_array(std::array<std::array<int, 8>, 8> &myArray);
        bool in_range(const int &row, const int &col);
        int check_move_type(char moving_figure, char figure_on_possible_pos);
        void combine_moves_strikes();
};