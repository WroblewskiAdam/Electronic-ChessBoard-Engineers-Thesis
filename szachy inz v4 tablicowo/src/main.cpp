#pragma once
#include <Arduino.h>
#include <detector.h>
#include <moveSolver.h>
#include <GameEngine.h>


Detector my_detector;
MoveSolver my_move_solver;
GameEngine myGameEngine;

// char figures[8][8] = {{'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'},
//                       {'0','0','0','0','0','0','0','0'}};


char figures_full[8][8] ={{'r','n','b','q','k','b','n','r'},
                          {'p','p','p','p','p','p','p','p'},
                          {'0','0','0','0','0','0','0','0'},
                          {'0','0','0','0','0','0','0','0'},
                          {'0','0','0','0','0','0','0','0'},
                          {'0','0','0','0','0','0','0','0'},
                          {'P','P','P','P','P','P','P','P'},
                          {'R','N','B','Q','K','B','N','R'}};

char figures[8][8] = {{'0','0','0','r','0','k','0','0'},
                      {'0','0','0','0','0','0','0','0'},
                      {'b','0','0','0','Q','0','0','0'},
                      {'0','0','0','0','0','0','0','0'},
                      {'0','0','0','0','0','0','0','0'},
                      {'0','0','0','0','0','0','0','0'},
                      {'0','0','0','0','K','0','0','0'},
                      {'0','0','0','0','0','0','0','0'}};

int row = 0;
int col = 0;
int new_row = 0;
int new_col = 0;

int act = 0;
std::array<int,2> cords;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
std::string myStr;

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


void showNewData() {
  if (newData == true) {
    Serial.print("INPUT: ");
    newData = false;
    myStr = receivedChars;
    Serial.println(myStr.c_str());
    
    row = receivedChars[1] - '0';
    col = receivedChars[2] - '0';
    new_row = receivedChars[3] - '0';
    new_col = receivedChars[4] - '0';
    act = receivedChars[0] - '0';

    if (new_row < 0) new_row = 0;
    if (new_col < 0) new_col = 0;
    Serial.print("act: ");
    Serial.print(act);
    Serial.print(" row: ");
    Serial.print(row);
    Serial.print(" col: ");
    Serial.print(col);
    Serial.print(" new_row: ");
    Serial.print(new_row);
    Serial.print(" new_col: ");
    Serial.println(new_col);


  }
}

bool check_vals()
{
  if(row >=0 && row <=7 && col >=0 && col <=7 && new_row >=0 && new_row <=7 && new_col >=0 && new_col <=7)
  {
    return true;
  }
  else return false;
}

void setup() {
  Serial.begin(115200);
  
  delay(5000);
  Serial.println("Początkowa plansza: ");
  myGameEngine.init_board(figures);
  // myGameEngine.board[0][0] = "r";
  // myGameEngine.whites_turn = false;
  myGameEngine.print_board(myGameEngine.board,0);
  delay(2000);
}

void loop() {

  if(act == 1)
  {
    Serial.print("plansza ( ruch  ");
    if(myGameEngine.whites_turn) Serial.print("białych");
    else Serial.print("czarnych");
    Serial.println("  ):");
    myGameEngine.print_board(myGameEngine.board,0);

    act = 0;
  }
  else if(act == 2)
  {
    if (check_vals())
    {
      unsigned long start = micros();
      myGameEngine.get_final_moves_for_figure(row,col);
      unsigned long end = micros();
      unsigned long delta = end - start;
      Serial.print("Execution time: ");
      Serial.print(delta);
      Serial.println(" microSeconds");

      Serial.print("Ostateczne ruchy figury: ");
      Serial.print(myGameEngine.board[row][col].c_str());
      Serial.print(" row: ");
      Serial.print(row);
      Serial.print(" col: ");
      Serial.println(col);
      myGameEngine.print_board(myGameEngine.final_moves_for_figure,1);

    }
    act = 0;
  }
  
  else if(act == 3)
  {
    if (check_vals())
    {
      myGameEngine.make_move(row, col, new_row, new_col);
      // Serial.println("plansza: ");
      // myGameEngine.print_board(myGameEngine.board,0);
      act = 1;
    }
    else act = 0;
  }

  else if(act == 4)
  {
    Serial.println("Początkowa plansza: ");
    myGameEngine.init_board(figures_full);
    myGameEngine.print_board(myGameEngine.board,0);
    act = 0;
  }


  // Serial.println("1. pozycje figur szachujących: ");
  // myGameEngine.get_checking_figures(myGameEngine.board);
  // myGameEngine.print_board(myGameEngine.checking_figures, 1);
  // // delay(1000);
  
  // myGameEngine.get_check_saving_moves();
  // Serial.println("2. Ruchy save-ujące: ");
  // myGameEngine.print_board(myGameEngine.check_saving_moves,1);
  // // delay(1000);


  // Serial.println("3. pozycje figur save-ujacych: ");
  // myGameEngine.get_check_saving_figures();
  // myGameEngine.print_board(myGameEngine.check_saving_figures, 1);
  // // delay(1000);

  
  // myGameEngine.get_king_allowed_moves2();
  // Serial.println("5. ostateczne ruchy krola: ");
  // myGameEngine.print_board(myGameEngine.king_allowed_moves,1);
  // delay(1000);


  // // delay(1000);
  // row = 0;
  // col = 4;
  // myGameEngine.get_final_moves_for_figure(row,col);
  // Serial.print("8. Ostateczne ruchy figury: ");
  // Serial.println(myGameEngine.board[row][col].c_str());
  // myGameEngine.print_board(myGameEngine.final_moves_for_figure,1);
  // delay(2000);


  recvWithEndMarker();
  showNewData();

  // delay(5000);
}

