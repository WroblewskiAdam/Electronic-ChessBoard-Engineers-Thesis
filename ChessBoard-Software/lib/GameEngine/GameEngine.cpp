#include <GameEngine.h>


GameEngine::GameEngine()
{
  
}


void GameEngine::init_board(const std::array<std::array<char, 8>, 8> &myArray){
    clear_board(board);
    whites_turn = true;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            char fig_org = myArray[i][j];
            std::string fig_cod(1, fig_org);
            if(fig_org != '0') fig_cod.append(1,'_');
            board[i][j] = fig_cod;
        }
    }
}

void GameEngine::reset()
{
    clear_board(board);
    clear_board(board_cpy);
    clear_array(checking_figures);
    clear_array(check_saving_figures);
    clear_array(check_saving_moves);
    clear_array(king_allowed_moves);
    clear_array(final_moves_for_figure);
    clear_array(final_strikes);
    clear_array(final_moves);
}



void GameEngine::init_fig(int row, int col, char fig){
    whites_turn = true;
    std::string fig_cod(1, fig);
    if(fig != '0') fig_cod.append(1,'_');
    board[row][col] = fig_cod;
}


void GameEngine::clear_board(std::array<std::array<std::string, 8>, 8> &myArray){
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = "0";
        }
    }
}


void GameEngine::print_board(const std::array<std::array<std::string, 8>, 8> &myArray, bool compact)
{
    if(!compact)
    {
        Serial.println("    0     1     2     3     4     5     6     7");
        Serial.println("-------------------------------------------------------");
    }
    for(int i = 0; i < 8; i++)
    {
        if(!compact)
        {
            Serial.print(i);
            Serial.print(" | ");
        }

        for(int j = 0; j < 8; j++)
        {
            Serial.print(myArray[i][j].c_str());
            Serial.print(" ");
            if(myArray[i][j].size() == 1) Serial.print(" ");
            if(!compact) Serial.print("   ");
        }
        if(!compact) 
        {   
            Serial.print("|  ");
            Serial.print(i);
            Serial.println();
            Serial.print("  |                                                 |  ");
        }   
        Serial.println();
    }

    if(!compact)
    {
        Serial.println("-------------------------------------------------------");
        Serial.println("    0     1     2     3     4     5     6     7");
    }

    Serial.println();
}


void GameEngine::print_board(const std::array<std::array<int, 8>, 8> &myArray, bool compact)
{
 if(!compact)
    {
        Serial.println("    0     1     2     3     4     5     6     7");
        Serial.println("-------------------------------------------------------");
    }
    for(int i = 0; i < 8; i++)
    {
        if(!compact)
        {
            Serial.print(i);
            Serial.print(" | ");
        }

        for(int j = 0; j < 8; j++)
        {
            Serial.print(myArray[i][j]);
            Serial.print(" ");
            Serial.print(" ");
            if(!compact) Serial.print("   ");
        }
        if(!compact) 
        {   
            Serial.print("|  ");
            Serial.print(i);
            Serial.println();
            Serial.print("  |                                                 |  ");
        }   
        Serial.println();
    }

    if(!compact)
    {
        Serial.println("-------------------------------------------------------");
        Serial.println("    0     1     2     3     4     5     6     7");
    }

    Serial.println();
}


void GameEngine::
make_move(int row, int col, int new_row, int new_col){
    std::string fig = board[row][col];
    if(fig != "0")
    {
        get_final_moves_for_figure(row, col);
        if(final_moves_for_figure[new_row][new_col] == 1) // ruch jest dozwolony
        {
            board[new_row][new_col] = fig[0];
            board[row][col] = "0";

            // flagi do en passant; black_EP - zbijamy czarnego bialym, white_EP - zbijamy bialego czarnym
            if(fig == "P_" && new_row == 4)
            {
                moveSolver.white_en_passant_row = row - 1;
                moveSolver.white_en_passant_col = col;
            }
            if(fig == "p_" && new_row == 3)
            {
                moveSolver.black_en_passant_row = row + 1;
                moveSolver.black_en_passant_col = col;
            }
            if(whites_turn && fig != "P" && new_col != moveSolver.black_en_passant_col && moveSolver.black_en_passant_col != -1) 
            {
                moveSolver.black_en_passant_row = -1;
                moveSolver.black_en_passant_col = -1;
            }
            if(!whites_turn && fig != "p" && new_col != moveSolver.white_en_passant_col && moveSolver.white_en_passant_col != -1) 
            {
                moveSolver.white_en_passant_row = -1;
                moveSolver.white_en_passant_col = -1;
            }
            
            // bicie przy en passant
            if(fig == "P") // bialy bije
            {
                if(new_col == moveSolver.black_en_passant_col && new_row == moveSolver.black_en_passant_row)
                {
                    board[new_row + 1][new_col] = "0";
                }
            }
            if(fig == "p") //czarny bije
            {
                if(new_col == moveSolver.white_en_passant_col && new_row == moveSolver.white_en_passant_row)
                {
                    board[new_row - 1][new_col] = "0";
                }
            }

            if(fig == "K_") // przeniesienie wiezy przy roszadzie krola bialego
            {
                if(new_row == 7 && new_col == 6) //krotka roszada
                {
                    board[7][5] = board[7][7][0];
                    board[7][7] = "0";
                }
                if(new_row == 7 && new_col == 2) //dluga roszada
                {
                    board[7][3] = board[7][0][0];
                    board[7][0] = "0";
                }
            }
            if(fig == "k_") // przeniesienie wiezy przy roszadzie krola czarnego
            {
                if(new_row == 0 && new_col == 6) //krotka roszada
                {
                    board[0][5] = board[0][7][0];
                    board[0][7] = "0";
                }
                if(new_row == 0 && new_col == 2) //dluga roszada
                {
                    board[0][3] = board[0][0][0];
                    board[0][0] = "0";
                }
            }

            change_turn();
            correct_move = true;
        }
        else 
        {
            correct_move = false;
        }
    }
}

void GameEngine::promote(int row, int col, char fig)
{
    board[row][col] = fig;
}

void GameEngine::reset_promotion()
{
    promotion = false;
    promotion_white = false;
    prom_row = -1;
    prom_col = -1;
}

void GameEngine::check_for_promotion()
{
    for(int i = 0; i < 8; i++)
    {
        if(board[0][i] == "P")
        {
            promotion = true;
            prom_row = 0;
            prom_col = i;
            promotion_white = true;
        }
        
        if(board[7][i] == "p")
        {
            promotion = true;
            prom_row = 7;
            prom_col = i;
            promotion_white = false;
        }
    }
}

int GameEngine::sum_array(const std::array<std::array<int, 8>, 8> &myArray)
{
    int sum = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            sum += myArray[i][j];
        }
    }
    return sum;
}


std::array<int,2> GameEngine::get_king_cords(const std::array<std::array<std::string, 8>, 8> &myBoard){
    std::array<int,2> cords;
    
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(whites_turn && myBoard[i][j][0] == 'K')
            {
                cords = {i,j};
                return cords;
            }
            else if(!whites_turn && myBoard[i][j][0] == 'k')
            {
                cords = {i,j};
                return cords;
            }
        }
    }
    cords = {0,0};
    return cords;
} 


std::array<int,2> GameEngine::get_only_one_cords(const std::array<std::array<int, 8>, 8> &myArray){
    std::array<int,2> cords;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myArray[i][j] == 1) return cords = {i,j};
        }
    }
    cords = {0, 0};
    return cords;
} 


void GameEngine::change_turn()
{
    whites_turn = (whites_turn) ? false : true;
}


void GameEngine::clear_array(std::array<std::array<int, 8>, 8> &myArray)
{
    for(int i = 0; i < 8; i++)
    {
        myArray[i].fill(0);
    }
}


void GameEngine::get_checking_figures(const std::array<std::array<std::string, 8>, 8> &myBoard)
{
    clear_array(checking_figures);
    std::array<int,2> king_pos = get_king_cords(myBoard);
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(whites_turn && islower(myBoard[i][j][0]) && myBoard[i][j][0] != '0') // tylko figury czarne - atakujace
            {
                moveSolver.get_all_moves_for_figure(i, j, myBoard);
                if (moveSolver.fig_strikes[king_pos[0]][king_pos[1]] == 1) checking_figures[i][j] = 1;
            }
            if(!whites_turn && isupper(myBoard[i][j][0]) && myBoard[i][j][0] != '0') // tylko figury biale - atakujace
            {
                moveSolver.get_all_moves_for_figure(i, j, myBoard);
                if (moveSolver.fig_strikes[king_pos[0]][king_pos[1]] == 1) checking_figures[i][j] = 1;
            }
        }
    }
}


void GameEngine::get_check_saving_moves()
{   
    // fukcja zwraca pola między szachowanym królem a figurą szachującją wraz z polem tej figury
    // Pola które ratują od szacha
    clear_array(check_saving_moves);
    get_checking_figures(board);

    int num_of_checking_figs = sum_array(checking_figures);

    if(num_of_checking_figs == 1)
    {
        std::array<int,2> king_cords = get_king_cords(board);
        std::array<int,2> checking_cords = get_only_one_cords(checking_figures);
        const int k_row = king_cords[0];
        const int k_col = king_cords[1];
        const int c_row = checking_cords[0];
        const int c_col = checking_cords[1];

        if(k_row == c_row || k_col == c_col || abs(k_row - c_row) == abs(k_col - c_col))
        {
            int d_row;
            int d_col;
            
            if(k_row < c_row) d_row = 1;
            else if(k_row > c_row) d_row = -1;
            else if(k_row == c_row) d_row = 0;
        
            if(k_col < c_col) d_col = 1;
            else if(k_col > c_col) d_col = -1;
            else if (k_col == c_col) d_col = 0;

            int row = k_row + d_row;
            int col = k_col + d_col;

            bool run = true;
            while(run)
            {
                check_saving_moves[row][col] = 1;
                row += d_row;
                col += d_col;
                if(row == c_row && col == c_col) run = false;
            }
        }
        check_saving_moves[c_row][c_col] = 1;
    }
}


void GameEngine::get_check_saving_figures()
{   
    clear_array(check_saving_figures);
    get_checking_figures(board);
    int num_of_checking_figs = sum_array(checking_figures);
    
    get_check_saving_moves();

    if(num_of_checking_figs == 1)
    {
        std::array<int,2> checking_cords = get_only_one_cords(checking_figures);
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++) //dla kazdej figury gracza otrzymujemy jej ruchy, sprawdzamy czy rych figury jest w ruchach które moga zablokować szacha
            {
                if(whites_turn && isupper(board[i][j][0]) && board[i][j][0] != '0' && board[i][j][0] != 'K') // tylko figury biale
                {
                    moveSolver.get_all_moves_for_figure(i, j, board);
                    for(int n = 0; n < 8; n++)
                    {
                        for(int m = 0; m < 8; m++)
                        {
                            if(moveSolver.fig_all_moves[n][m] == 1 && check_saving_moves[n][m] == 1) check_saving_figures[i][j] = 1;
                        }
                    }
                }
                if(!whites_turn && islower(board[i][j][0]) && board[i][j][0] != '0' && board[i][j][0] != 'k') // tylko figury czarne
                {
                    moveSolver.get_all_moves_for_figure(i, j, board);
                    for(int n = 0; n < 8; n++)
                    {
                        for(int m = 0; m < 8; m++)
                        {
                            if(moveSolver.fig_all_moves[n][m] == 1 && check_saving_moves[n][m] == 1) check_saving_figures[i][j] = 1;
                        }
                    }
                }
            }
        }
    }
}


void GameEngine::get_final_moves_for_figure(const int row, const int col)
{
    clear_array(final_moves_for_figure);
    clear_array(final_moves);
    clear_array(final_strikes);
    char fig = board[row][col][0];
    if((isupper(fig) && whites_turn == true) || (islower(fig) && whites_turn == false))
    {
        if(fig != '0' && tolower(fig) != 'k')
        {
            get_checking_figures(board);
            int checking_num = sum_array(checking_figures);
            
            if (checking_num == 0) 
            {
                moveSolver.get_all_moves_for_figure(row, col, board);
                std::array<std::array<int, 8>, 8> fig_all_moves = moveSolver.fig_all_moves;
                for(int i = 0; i < 8; i++)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        if(fig_all_moves[i][j] == 1)
                        {
                            bool check = check_move_for_check(row, col, i, j); //tru jesli ruch skutkuje szachem
                            if(check == false) 
                            {
                                final_moves_for_figure[i][j] = 1;
                            }
                        }
                    }
                }
            }
            else if(checking_num == 1)
            {
                moveSolver.get_all_moves_for_figure(row, col, board);
                std::array<std::array<int, 8>, 8> fig_all_moves = moveSolver.fig_all_moves;
                get_check_saving_figures();
                if (check_saving_figures[row][col] == 1)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        for(int j = 0; j < 8; j++)
                        {
                            if(fig_all_moves[i][j] == 1 && check_saving_moves[i][j] == 1) final_moves_for_figure[i][j] = 1;
                        }
                    }
                }
            }
        }
        else if(fig != '0' && tolower(fig) == 'k')
        {
            clear_array(final_moves_for_figure);
            get_king_allowed_moves();
            final_moves_for_figure = king_allowed_moves;
        }
        moveSolver.get_all_moves_for_figure(row, col, board);
        separate_moves_strikes();
    }
}


void GameEngine::separate_moves_strikes()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(final_moves_for_figure[i][j] == 1)
            {
                char fig = board[i][j][0];
                if(fig == '0' && moveSolver.fig_strikes[i][j] != 1) final_moves[i][j] = 1;
                else if(moveSolver.fig_strikes[i][j] == 1) final_strikes[i][j] = 1;
            }
        }
    }
}


bool GameEngine::check_move_for_check(int row, int col ,int new_row, int new_col) //true jestli ruch skutkuje szachem
{
    char fig = board[row][col][0];
    board_cpy = board;
    board_cpy[new_row][new_col] = fig;
    board_cpy[row][col] = "0";

    get_checking_figures(board_cpy);
    int checking_num = sum_array(checking_figures);
    
    if(checking_num >= 1) return true;
    else return false;
} 


void GameEngine::get_king_allowed_moves()
{
    clear_array(king_allowed_moves);
    std::array<int,2> king_pos = get_king_cords(board);

    moveSolver.get_all_moves_for_figure(king_pos[0], king_pos[1], board);
    king_allowed_moves = moveSolver.fig_all_moves;
  
    bool check;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(king_allowed_moves[i][j] == 1)
            {
                check = check_move_for_check(king_pos[0], king_pos[1], i, j);
                if(check) king_allowed_moves[i][j] = 0;
            }
        }
    }
    get_castling_moves(board);
}


void GameEngine::get_castling_moves(std::array<std::array<std::string, 8>, 8> &myArray)
{
    std::array<int,2> king_pos = get_king_cords(myArray);
    bool short_castling = short_castling_condition(king_pos[0], board);
    bool long_castling = long_castling_condition(king_pos[0], board);
    if(short_castling)
    {
        king_allowed_moves[king_pos[0]][6] = 1;
    }
    if(long_castling)
    {
        king_allowed_moves[king_pos[0]][2] = 1;
    }
}


bool GameEngine::short_castling_condition(int &king_row, std::array<std::array<std::string, 8>, 8> &myArray)
{
    if ((myArray[king_row][4] == "K_" || myArray[king_row][4] =="k_") && (myArray[king_row][7] == "R_" || myArray[king_row][7] == "r_")) // wieza i krol nie wykonaly ruchu
    {
        if(myArray[king_row][5] == "0" && myArray[king_row][6] == "0") // nie ma bierek pomiedzy K a R
        {
            bool check_1 = check_move_for_check(king_row, 4, king_row, 5); //true jesli szach na pozycji miedzy królem a wieza
            bool check_2 = check_move_for_check(king_row, 4, king_row, 6); // true jesli szach na pozycji miedzy królem a wieza
            get_checking_figures(board);
            bool check_3 = (sum_array(checking_figures) == 0) ? true : false; 

            if( !check_1 && !check_2 && check_3) return true;
            else return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool GameEngine::long_castling_condition(int &king_row, std::array<std::array<std::string, 8>, 8> &myArray)
{
    if ((myArray[king_row][4] == "K_" || myArray[king_row][4] =="k_") && (myArray[king_row][0] == "R_" || myArray[king_row][0] == "r_")) // wieza i krol nie wykonaly ruchu
    {
        if(myArray[king_row][1] == "0" && myArray[king_row][2] == "0" && myArray[king_row][3] == "0") // nie ma bierek pomiedzy K a R
        {
            bool check_1 = check_move_for_check(king_row, 4, king_row, 2); //true jesli szach
            bool check_2 = check_move_for_check(king_row, 4, king_row, 3); // true jesli szach
            get_checking_figures(board);
            bool check_3 = (sum_array(checking_figures) == 0) ? true : false; 
            if( !check_1 && !check_2 && check_3) return true;
            else return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool GameEngine::evaluate_checkmate()
{
    get_checking_figures(board);
    int num_of_checking = sum_array(checking_figures);

    if(num_of_checking > 0)
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(whites_turn && isupper(board[i][j][0]) && board[i][j][0] != '0') // tylko figury białe
                {
                    get_final_moves_for_figure(i, j);
                    if(sum_array(final_moves_for_figure) != 0) return false;

                }
                else if(!whites_turn && islower(board[i][j][0]) && board[i][j][0] != '0') // tylko figury czarne
                {
                    get_final_moves_for_figure(i, j);
                    if(sum_array(final_moves_for_figure) != 0) return false;
                }
            }
        }
        return true;
    }
    else return false;
}


bool GameEngine::evaluate_stalemate()
{
    get_checking_figures(board);
    int num_of_checking = sum_array(checking_figures);

    if(num_of_checking == 0)
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(whites_turn && isupper(board[i][j][0]) && board[i][j][0] != '0') // tylko figury białe
                {
                    get_final_moves_for_figure(i, j);
                    if(sum_array(final_moves_for_figure) != 0) return false;

                }
                else if(!whites_turn && islower(board[i][j][0]) && board[i][j][0] != '0') // tylko figury czarne
                {
                    get_final_moves_for_figure(i, j);
                    if(sum_array(final_moves_for_figure) != 0) return false;
                }
                
            }
        }
        return true;
    }
    else return false;
}