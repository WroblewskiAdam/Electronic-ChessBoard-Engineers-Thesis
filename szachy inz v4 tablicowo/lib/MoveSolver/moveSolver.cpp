#include "MoveSolver.h"

MoveSolver::MoveSolver()
{
  
}

 
void MoveSolver::get_all_moves_for_figure(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{	
    clear_array(fig_moves);
    clear_array(fig_strikes);
    clear_array(fig_all_moves);
    std::string figure = myArray[row][col]; 
	if (figure == "P" || figure == "P_" || figure == "p" || figure == "p_") get_pawn_moves(row, col, myArray);
    if (figure == "R" || figure == "R_" || figure == "r" || figure == "r_") get_rook_moves(row, col, myArray);
    if (figure == "N" || figure == "N_" || figure == "n" || figure == "n_") get_knight_moves(row, col, myArray);
    if (figure == "B" || figure == "B_" || figure == "b" || figure == "b_") get_bishop_moves(row, col, myArray);
    if (figure == "Q" || figure == "Q_" || figure == "q" || figure == "q_") get_queen_moves(row, col, myArray);
    if (figure == "K" || figure == "K_" || figure == "k" || figure == "k_") get_king_moves(row, col, myArray);
    combine_moves_strikes();
}


void MoveSolver::clear_array(std::array<std::array<int, 8>, 8> &myArray)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            myArray[i][j] = 0;
        }
    }
}


void MoveSolver::print_array(const std::array<std::array<int, 8>, 8> &myArray, bool compact)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
        Serial.print(myArray[i][j]);
        Serial.print(" ");
        if(!compact) Serial.print("   ");
    }
    if(!compact) Serial.println();
    Serial.println();
  }
  Serial.println();
}


void MoveSolver::get_pawn_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{
    std::string moving_figure = myArray[row][col];
    std::string attacked_figure;
    int move_type;

    int new_row;
    int new_col;

    //White bottom -> top
    if (moving_figure == "P" || moving_figure == "P_") 
    {   
        // Ruchy
        new_row = row - 1;
        new_col = col;
        if(in_range(new_row, new_col))
        {
            attacked_figure = myArray[new_row][new_col];
            move_type = check_move_type(moving_figure[0], attacked_figure[0]);
            if(move_type == 0) fig_moves[new_row][new_col] = 1;
        }

        new_row = row - 2;
        if(row == 6 && move_type == 0)
        {
            attacked_figure = myArray[new_row][new_col];
            move_type = check_move_type(moving_figure[0], attacked_figure[0]);
            if(move_type == 0) fig_moves[new_row][new_col] = 1;
        }

        // Bicia
        int col_inc[2] = {-1, 1};
        new_row = row - 1;
        for(int i = 0; i < 2; i++)
        {
            new_col = col + col_inc[i];
            if(in_range(new_row, new_col))
            {
                attacked_figure = myArray[new_row][new_col];
                move_type = check_move_type(moving_figure[0], attacked_figure[0]);
                if(move_type == -1) fig_strikes[new_row][new_col] = 1;
                if(new_col == white_en_passant_col) fig_strikes[new_row][new_col] = 1; // en pasant
            }
        }
    }
    
    // Black top -> bottom
    if (moving_figure == "p" || moving_figure == "p_")
    {   
        // Ruchy
        new_row = row + 1;
        new_col = col;
        if(in_range(new_row, new_col))
        {
            attacked_figure = myArray[new_row][new_col];
            move_type = check_move_type(moving_figure[0], attacked_figure[0]);
            if(move_type == 0) fig_moves[new_row][new_col] = 1;
        }

        new_row = row + 2;
        if(row == 1 && move_type == 0)
        {
            attacked_figure = myArray[new_row][new_col];
            move_type = check_move_type(moving_figure[0], attacked_figure[0]);
            if(move_type == 0) fig_moves[new_row][new_col] = 1;
        }

        // Bicia
        int col_inc[2] = {-1, 1};
        new_row = row + 1;
        for (int i = 0; i < 2; i++)
        {
            new_col = col + col_inc[i];
            if(in_range(new_row, new_col))
            {
                attacked_figure = myArray[new_row][new_col];
                move_type = check_move_type(moving_figure[0], attacked_figure[0]);
                if(move_type == -1) fig_strikes[new_row][new_col] = 1;
                if(new_col == black_en_passant_col) fig_strikes[new_row][new_col] = 1; // en pasant
            }
        }
    }
}


void MoveSolver::get_rook_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{   
    std::string moving_figure = myArray[row][col];
    std::string attacked_figure;
    int move_type;
    int new_row;
    int new_col;

    for (int i = 1; i<=8; i++) // W gore
    {
        new_row = row - i;
        new_col = col;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);

        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop1;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop1;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop1:

    for (int i = 1; i<=8; i++) // W dol
    {
        new_row = row + i;
        new_col = col;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);
       
        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop2;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop2;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop2:

    for (int i = 1; i<=8; i++) // W prawo
    {
        new_row = row;
        new_col = col + i;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);

        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop3;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop3;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop3:

    for (int i = 1; i<=8; i++) // W lewo
    {
        new_row = row;
        new_col = col - i;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);

        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop4;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop4;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop4:
    
    for(int i = 0; i<=1; i++)
    {
        break;
    }
}


void MoveSolver::get_bishop_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{   
    std::string moving_figure = myArray[row][col];
    std::string attacked_figure;
    int move_type;
    int new_row;
    int new_col;

    for (int i = 1; i<=8; i++) 
    {
        new_row = row - i;  // prawy gorny ukos
        new_col = col + i;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);

        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop1;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop1;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop1:

    for (int i = 1; i<=8; i++) 
    {       
        new_row = row + i; // prawy dolny ukos
        new_col = col + i;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);
       
        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop2;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop2;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop2:

    for (int i = 1; i<=8; i++)
    {
        new_row = row + i; // lewy dolny ukos
        new_col = col - i;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);

        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop3;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop3;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop3:

    for (int i = 1; i<=8; i++)
    {
        new_row = row - i; // lewy gorny ukos
        new_col = col - i;
        attacked_figure = myArray[new_row][new_col];
        move_type = check_move_type(moving_figure[0], attacked_figure[0]);

        if (!in_range(new_row, new_col) || move_type == 1){
            goto exitloop4;
        }
        else if (move_type == -1){
            fig_strikes[new_row][new_col] = 1;
            goto exitloop4;
        }
        else if (move_type == 0){
            fig_moves[new_row][new_col] = 1;
        }
    }
    exitloop4:
    for(int i = 0; i<=1; i++)
    {
        break;
    }
    
}


void MoveSolver::get_queen_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{
    get_rook_moves(row, col, myArray);
    get_bishop_moves(row, col, myArray);
}


void MoveSolver::get_knight_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{
    int row_inc[8] = { 1,  2, 2, 1, -1, -2, -2, -1};
    int col_inc[8] = {-2, -1, 1, 2,  2,  1, -1, -2};
    int new_row;
    int new_col;
    int move_type;
    std::string moving_figure = myArray[row][col];
    std::string attacked_figure;
    
    for(int i = 0; i<8; i++)
    {
        new_row = row + row_inc[i];
        new_col = col + col_inc[i];
        if(in_range(new_row, new_col))
        {
            attacked_figure = myArray[new_row][new_col];
            move_type = check_move_type(moving_figure[0], attacked_figure[0]);
            
            if(move_type == 0) fig_moves[new_row][new_col] = 1;
            else if (move_type == -1) fig_strikes[new_row][new_col] = 1;
        }
    }
}


void MoveSolver::get_king_moves(int row, int col, const std::array<std::array<std::string, 8>, 8> &myArray)
{
    int row_inc[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int col_inc[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
    int new_row;
    int new_col;
    int move_type;
    std::string moving_figure = myArray[row][col];
    std::string attacked_figure;
    
    for(int i = 0; i<8; i++)
    {
        new_row = row + row_inc[i];
        new_col = col + col_inc[i];
        if(in_range(new_row, new_col))
        {
            attacked_figure = myArray[new_row][new_col];
            move_type = check_move_type(moving_figure[0], attacked_figure[0]);
            
            if(move_type == 0) fig_moves[new_row][new_col] = 1;
            else if (move_type == -1) fig_strikes[new_row][new_col] = 1;
        }
    }
}


bool MoveSolver::in_range(const int &row, const int &col)
{
	if (row >= 0 && col >= 0 && row < 8 && col < 8)
		return true;
	else
		return false;
}


int MoveSolver::check_move_type(char moving_figure, char figure_on_possible_pos){ 
    // funkcja sprawdza rodzaj ruchu na dane pole - wolne  = 0, zajete przez bratnia figure = 1, wroga figura = - 1
    if (isupper(moving_figure)) //ruch bialego
    {
        if (isupper(figure_on_possible_pos)) return 1;// biale na atakowanym polu
        else if (islower(figure_on_possible_pos)) return -1; // czarne na atakowanym polu
        else if (figure_on_possible_pos == '0') return 0; //pole wolne
    }
    else // ruch czarnego
    {
        if (islower(figure_on_possible_pos)) return 1;// czarne na atakowanym polu
        else if (isupper(figure_on_possible_pos)) return -1; 
        else if (figure_on_possible_pos == '0') return 0;
    }
}

void MoveSolver::combine_moves_strikes()
{
    clear_array(fig_all_moves);
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(fig_moves[i][j] == 1 || fig_strikes[i][j] == 1) 
            {
                fig_all_moves[i][j] = 1;
            }
        }   
    }
}

