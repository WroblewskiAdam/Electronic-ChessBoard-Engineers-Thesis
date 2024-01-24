#include <Arduino.h>
#include <Detector.h>
#include <MoveSolver.h>
#include <GameEngine.h>
#include <Iluminator.h>


Detector my_detector;
MoveSolver my_move_solver;
GameEngine myGameEngine;
Iluminator my_iluminator;

int state = 0;
bool is_initialized = false;
bool is_consistent = true;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
std::string myStr;

bool dev_mode = true;

// do serial monitora
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}
// do serial monitora
void showNewData() {
  if (newData == true) {
    Serial.print("INPUT: ");
    newData = false;
    myStr = receivedChars;
    Serial.println(myStr.c_str());
    
    state = receivedChars[0] - '0';
  }
}


void check_consistency(){

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(my_detector.figures[i][j] != myGameEngine.board[i][j][0]) 
            {
                is_consistent = false;
                return;
            }
        }
    }
    is_consistent = true;
}

void light_incoherent_positions(){
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
           if(my_detector.figures[i][j] != myGameEngine.board[i][j][0])
           {
                my_iluminator.light(i,j,my_iluminator.orange);
           }
        }
    }
}


void setup() {
    Serial.begin(115200);
    state = 0; 
}


unsigned long start;
unsigned long end;
unsigned long delta;

void loop() {
    // unsigned long start = micros();
    
    // my_detector.scan(false);
    // my_detector.getValueChange();
    // my_detector.mapToFigure();

    // unsigned long end = micros();
    // unsigned long delta = end - start;
    // Serial.print("valueChange");
    // my_detector.printInt(my_detector.valueChange);
    // Serial.println("Figures");
    // my_detector.printChar(my_detector.figures);
    // Serial.print("Execution time: ");
    // Serial.print(delta);
    // Serial.println(" microSeconds");


    switch (state)
    {
        case 0:
            my_iluminator.light_all_at_once(my_iluminator.red);
            my_detector.scan(true);
            delay(1000);
            my_iluminator.flash(3, my_iluminator.green);
            state = 1; 

        case 1:
            my_detector.scanBoard();
            if(dev_mode)
            {
                Serial.println("Stan 1: Skanowanie");
                my_detector.scanBoard();
                Serial.println("scan:");
                my_detector.printChar(my_detector.figures);
            }
            
            my_detector.get_init_difference();
            if(my_detector.board_change) my_iluminator.clear();
            my_iluminator.light_moves(my_detector.initialization_difference, my_iluminator.purple);
            
            if(is_initialized == false) 
            {
                if(my_detector.check_for_init_board() || my_detector.start_sig_val == true)
                {
                    my_iluminator.flash(3, my_iluminator.green);
                    is_initialized = true;
                    state = 2; 
                }
            }
            break;

        case 2:
            myGameEngine.init_board(my_detector.figures);
            myGameEngine.print_board(myGameEngine.board,0);
            is_initialized = true;
            state = 3;
            break;
            
        case 3:
            my_detector.scanBoard();
            if(dev_mode)
            {
                Serial.println();
                Serial.println("Stna 3 - Rozgrywka");
                Serial.println("scan:");
                my_detector.printChar(my_detector.figures);
                Serial.println("board:");
                myGameEngine.print_board(myGameEngine.board,1);
            }
            
            if(is_initialized == true)
            {
                if(myGameEngine.evaluate_stalemate()) state = 6;
                if(myGameEngine.evaluate_checkmate()) state = 7;

                check_consistency();
                if (is_consistent == false && my_detector.is_fig_picked == false) state = 4;
        

                if(my_detector.is_fig_picked == true && myGameEngine.board[my_detector.picked_row][my_detector.picked_col] != "0") 
                {
                    myGameEngine.get_final_moves_for_figure(my_detector.picked_row,my_detector.picked_col);    
                    my_iluminator.light(my_detector.picked_row,my_detector.picked_col, my_iluminator.blue);
                    my_iluminator.light_moves(myGameEngine.final_moves, my_iluminator.green);
                    my_iluminator.light_moves(myGameEngine.final_strikes, my_iluminator.red);
                }
                
                
                if(my_detector.made_move == true)
                {
                    myGameEngine.make_move(my_detector.old_row, my_detector.old_col, my_detector.new_row, my_detector.new_col);
                    if(myGameEngine.correct_move == true)
                    {
                        myGameEngine.print_board(myGameEngine.board,1);
                        my_detector.reset();
                        my_iluminator.clear();
                        myGameEngine.check_for_promotion();
                        if (myGameEngine.promotion == true) state = 5;
                    }
                    else if(myGameEngine.correct_move == false)
                    {
                        light_incoherent_positions();
                        if(is_consistent == true) 
                        {
                            my_iluminator.clear();
                            my_detector.reset();
                        }
                    }
                }

                if(my_detector.is_fig_picked == false)
                {
                    my_iluminator.clear();
                    my_detector.reset();
                }

            }
            break;
        
        case 4:
            //Stan w którym obsługujemy sytuację niezgodną z zasadmi.
            if(dev_mode) Serial.println("Stan 4 - Sytuacja Nieprawidlowa");
            my_detector.scanBoard();
            if(my_detector.is_fig_picked) my_iluminator.clear();
            light_incoherent_positions();
            check_consistency();
            if (is_consistent)
            {
                state = 3;
                my_iluminator.clear();
                my_detector.reset();
            }
            break;
        
        case 5:
            //Stan w którym obsługujemy promocje.
            if(dev_mode) Serial.println("Stan 5 - Promocja");
            my_iluminator.light(myGameEngine.prom_row, myGameEngine.prom_col, my_iluminator.pink);
            my_detector.scanBoard();
            
            if(myGameEngine.promotion_white == true) // promocja bialych
            {
                if(my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col] != '0' &&
                   my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col] != 'P' && 
                   my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col] != 'K' && 
                   isupper(my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col]))
                {
                    myGameEngine.promote(myGameEngine.prom_row, myGameEngine.prom_col, my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col]);
                    my_iluminator.clear();
                    my_detector.reset();
                    myGameEngine.reset_promotion();
                    state = 3;
                }
            }
            else if (myGameEngine.promotion_white == false) //promocja czarnych
            {
                if(my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col] != '0' &&
                   my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col] != 'p' && 
                   my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col] != 'k' && 
                   islower(my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col]))
                {
                    myGameEngine.promote(myGameEngine.prom_row, myGameEngine.prom_col, my_detector.figures[myGameEngine.prom_row][myGameEngine.prom_col]);
                    my_iluminator.clear();
                    my_detector.reset();
                    myGameEngine.reset_promotion();
                    state = 3;
                }
            }
            break;
        
        case 6: //pat
            if(dev_mode) Serial.println("Stan 6 - Pat");
            my_iluminator.light_draw();
            delay(5000);
            state = 8;
            break;
        
        case 7: // mat
            if(dev_mode) Serial.println("Stan 6 - Mat");
            if(myGameEngine.whites_turn) my_iluminator.light_blacks_win();
            else my_iluminator.light_whites_win();
            delay(5000);
            state = 8;
            break;

        case 8:
            if(dev_mode) Serial.println("Stan 8 - Reset");
            my_iluminator.clear();
            my_detector.reset();
            myGameEngine.reset();
            is_initialized = false;
            state = 1;
            break;

        default:
            break;
    }

    if(dev_mode)
    {
        recvWithEndMarker();
        showNewData();
    }
}

