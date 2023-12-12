#include <GameEngine.h>

// TODO roszada

GameEngine::GameEngine()
{
  
}

void GameEngine::init_board(const char (&myArray)[8][8]){
    clear_board(board);
    
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

void GameEngine::clear_board(std::string (&board)[8][8]){
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = "0";
        }
    }
}

void GameEngine::print_board(const std::string (&myArray)[8][8], bool compact)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
        Serial.print(myArray[i][j].c_str());
        Serial.print(" ");
        if(myArray[i][j].size() == 1) Serial.print(" ");
        if(!compact) Serial.print("   ");
    }
    if(!compact) Serial.println();
    Serial.println();
  }
  Serial.println();
}

void GameEngine::print_board(const int (&myArray)[8][8], bool compact)
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


void GameEngine::make_move(int row, int col, int new_row, int new_col){
    std::string fig = board[row][col];
    if(fig != "0")
    {
        board[new_row][new_col] = fig[0];
        board[row][col] = "0";
    }
    // TODO dodac ustawianie flagi do en passant przy ruchu piona
}


int GameEngine::sum_array(const int (&myArray)[8][8])
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


std::array<int,2> GameEngine::get_king_cords(){
    std::array<int,2> cords;
    
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(whites_turn && board[i][j][0] == 'K')
            {
                cords = {i,j};
                return cords;
            }
            else if(!whites_turn && board[i][j][0] == 'k')
            {
                cords = {i,j};
                return cords;
            }
        }
    }
} 

std::array<int,2> GameEngine::get_only_one_cords(const int (&myArray)[8][8]){
    std::array<int,2> cords;
    
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(myArray[i][j] == 1) return cords = {i,j};
        }
    }
} 


void GameEngine::get_checking_figures()
{
    clear_array(checking_figures);
    std::array<int,2> king_pos = get_king_cords();

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(whites_turn && islower(board[i][j][0]) && board[i][j][0] != '0') // tylko figury czarne - atakujace
            {
                moveSolver.get_all_moves_for_figure(i, j, board);
                if (moveSolver.fig_strikes[king_pos[0]][king_pos[1]] == 1) checking_figures[i][j] = 1;
            }
            if(!whites_turn && isupper(board[i][j][0]) && board[i][j][0] != '0') // tylko figury biale - atakujace
            {
                moveSolver.get_all_moves_for_figure(i, j, board);
                if (moveSolver.fig_strikes[king_pos[0]][king_pos[1]] == 1) checking_figures[i][j] = 1;
            }
        }
    }
}

void GameEngine::get_check_saving_figures()
{   
    clear_array(check_saving_figures);
    get_checking_figures();
    int num_of_checking_figs = sum_array(checking_figures);

    if(num_of_checking_figs == 1)
    {
        std::array<int,2> checking_cords = get_only_one_cords(checking_figures);
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(whites_turn && isupper(board[i][j][0]) && board[i][j][0] != '0') // tylko figury biale
                {
                    moveSolver.get_all_moves_for_figure(i, j, board);

                    if (moveSolver.fig_strikes[checking_cords[0]][checking_cords[1]] == 1) check_saving_figures[i][j] = 1;
                }
                if(!whites_turn && islower(board[i][j][0]) && board[i][j][0] != '0') // tylko figury czarne
                {
                    moveSolver.get_all_moves_for_figure(i, j, board);
                    if (moveSolver.fig_strikes[checking_cords[0]][checking_cords[1]] == 1) check_saving_figures[i][j] = 1;
                }
            }
        }
    }
}


void GameEngine::change_turn()
{
    whites_turn = (whites_turn) ? false : true;
}


void GameEngine::clear_array(int (&myArray)[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            myArray[i][j] = 0;
        }
    }
}
