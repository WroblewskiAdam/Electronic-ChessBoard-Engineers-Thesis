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

char figures[8][8] = {{'r','n','b','k','q','b','n','r'},
                      {'p','p','p','0','0','p','p','p'},
                      {'0','0','0','0','0','0','0','0'},
                      {'b','0','0','0','0','0','Q','0'},
                      {'0','0','0','0','0','0','0','0'},
                      {'0','0','0','0','0','0','0','0'},
                      {'0','P','0','0','P','P','P','P'},
                      {'R','N','B','Q','K','B','N','R'}};

std::array<int,2> cords;
void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("Początkowa plansza");

  // my_move_solver.get_all_moves_for_figure(1, 6, figures);
  // my_move_solver.displayFigData(my_move_solver.fig_moves,1);

  myGameEngine.init_board(figures);
  myGameEngine.print_board(myGameEngine.board,1);
  delay(5000);
}

void loop() {
  // Serial.println("RUCHY:");
  // my_move_solver.displayFigData(my_move_solver.fig_moves,1);
  // Serial.println("BICIA:");
  // my_move_solver.displayFigData(my_move_solver.fig_strikes,1);
  
  // Serial.println("Wykonanie ruchu");
  // myGameEngine.make_move(1,0,2,0);
  // myGameEngine.print_board(myGameEngine.board,1);
  // delay(5000);
  // myGameEngine.make_move(2,0,3,0);
  // myGameEngine.print_board(myGameEngine.board,1);
  // delay(5000);

  // Serial.println("kordy krola białasa");
  // cords = myGameEngine.get_king_cords();
  // Serial.println(cords[0]);
  // Serial.println(cords[1]);
  // delay(5000);

  // Serial.println("kordy krola czarnucha");
  // myGameEngine.change_turn();
  // cords = myGameEngine.get_king_cords();
  // Serial.println(cords[0]);
  // Serial.println(cords[1]);
  // delay(5000);

  Serial.println("pozycje figur szachujących: ");
  myGameEngine.get_checking_figures();
  myGameEngine.print_board(myGameEngine.checking_figures, 1);
  delay(2000);
  
  Serial.println("pozycje figur save-ujacych: ");
  myGameEngine.get_check_saving_figures();
  myGameEngine.print_board(myGameEngine.check_saving_figures, 1);
  delay(5000);



}

