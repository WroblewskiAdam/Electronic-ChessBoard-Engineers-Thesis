#include <Arduino.h>
#include <Detector.h>
#include <MoveSolver.h>
#include <GameEngine.h>
#include <Iluminator.h>
// #include <Display.h>
// #include <LiquidCrystal_I2C.h>



Detector my_detector;
MoveSolver my_move_solver;
GameEngine myGameEngine;
Iluminator my_iluminator;
// Display my_display;

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

char figures[8][8] =     {{'r','n','b','q','k','b','n','r'},
                          {'p','p','p','p','p','0','0','p'},
                          {'0','0','0','0','0','0','0','0'},
                          {'0','0','0','0','0','0','0','0'},
                          {'0','0','0','0','0','0','0','0'},
                          {'0','0','0','0','0','0','0','0'},
                          {'P','P','P','0','0','P','P','P'},
                          {'R','N','B','Q','K','B','N','R'}};

int state = 0;

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
    
    state = receivedChars[0] - '0';
  }
}



void end_game()
{
  Serial.print("Stan gry: ");
  if(myGameEngine.evaluate_stalemate())
  {
    Serial.println("REMIS");
  }
  else if(myGameEngine.evaluate_checkmate())
  {
    Serial.print("WYGRYWAJĄ ");
    Serial.println((myGameEngine.whites_turn)? "CZARNE" : "BIAŁE");
  }
  else
  {
    Serial.println("nierozstrzygnięta");
  }
}




void setup() {
    Serial.begin(115200);
    // lcd.init();
    // lcd.backlight();
    // lcd.setCursor(0,0);
    // lcd.print("Inicjalizacja");
    my_detector.scan(true);
    state = 1; 
}


void loop() {
    // unsigned long start = micros();
    
    
    my_detector.scan(false);
    my_detector.getDropDown();
    // my_detector.mapToFigure();

    // unsigned long end = micros();
    // unsigned long delta = end - start;
    // Serial.println("Dropdown");
    my_detector.printInt(my_detector.dropDown);
    // Serial.println("Figures");
    // my_detector.printChar(my_detector.figures);
    // Serial.print("Execution time: ");
    // Serial.print(delta);
    // Serial.println(" microSeconds");


    // switch (state)
    // {
    //     case 1:
    //         Serial.println("Stan 1");
    //         // lcd.clear();
    //         // lcd.print("Stan 1");
    //         // display...

    //         state = 0;
    //         break;
        
    //     case 2:
    //         Serial.println("Stan 2");
    //         Serial.println("Init");
    //         // lcd.clear();
    //         // lcd.print("Stan 2");
            
    //         myGameEngine.init_board(figures);
            
    //         Serial.print("plansza ( ruch  ");
    //         if(myGameEngine.whites_turn) Serial.print("białych");
    //         else Serial.print("czarnych");
    //         Serial.println("  ):");
    //         myGameEngine.print_board(myGameEngine.board,0);
            
    //         state = 0;

    //         break;

    //     case 3:
    //         Serial.println("Stan 3");
    //         Serial.println("Scan");
    //         state = 4;
    //         break;

    //     case 4:
    //         my_detector.scanBoard();
    //         break;

    //     default:
    //         break;
    // }

    // recvWithEndMarker();
    // showNewData();





//   if(act == 1)
//   { 
//     Serial.print("plansza ( ruch  ");
//     if(myGameEngine.whites_turn) Serial.print("białych");
//     else Serial.print("czarnych");
//     Serial.println("  ):");
//     end_game();
    

//     myGameEngine.print_board(myGameEngine.board,0);

//     act = 0;
//   }
//   else if(act == 2)
//   {
//     if (check_vals())
//     {
//       my_iluminator.clear();
//       unsigned long start = micros();
//       myGameEngine.get_final_moves_for_figure(row,col);
//       unsigned long end = micros();
//       unsigned long delta = end - start;
//       Serial.print("Execution time: ");
//       Serial.print(delta);
//       Serial.println(" microSeconds");

//       Serial.print("Ostateczne ruchy figury: ");
//       Serial.print(myGameEngine.board[row][col].c_str());
//       Serial.print(" row: ");
//       Serial.print(row);
//       Serial.print(" col: ");
//       Serial.println(col);
//       myGameEngine.print_board(myGameEngine.final_moves_for_figure,0);
//       Serial.println("RUCHY: ");
//       myGameEngine.print_board(myGameEngine.final_moves,0);
//       Serial.println("BICIA: ");
//       myGameEngine.print_board(myGameEngine.final_strikes,0);
      

//       my_iluminator.light_moves(myGameEngine.final_moves, 0);
//       my_iluminator.light_moves(myGameEngine.final_strikes, -1);

//     }
//     act = 0;
//   }
  
//   else if(act == 3)
//   {
//     if (check_vals())
//     {
//       myGameEngine.make_move(row, col, new_row, new_col);
//       act = 1;
//     }
//     else act = 0;
//   }

//   else if(act == 4)
//   {
//     Serial.println("Początkowa plansza: ");
//     myGameEngine.init_board(figures_full);
//     myGameEngine.print_board(myGameEngine.board,0);
//     act = 0;
//   }
//   else
//   {
//     my_detector.scanBoard();
//     // Serial.println("DropDown: ");
//     // my_detector.printInt(my_detector.dropDown);
//     // Serial.println("Figures: ");
//     // my_detector.printChar(my_detector.figures);
//     // Serial.print("Wybrana figura: ");
//     // Serial.print(my_detector.chosen_fig);
//     // Serial.print(" Row: ");
//     // Serial.print(my_detector.chosen_row);
//     // Serial.print(" Col: ");
//     // Serial.println(my_detector.chosen_col);
//     // if(my_detector.fig_picked == true) my_iluminator.light(my_detector.chosen_row, my_detector.chosen_col, my_iluminator.red);
//     // else my_iluminator.clear();

//     // delay(1000);
//   }


}

