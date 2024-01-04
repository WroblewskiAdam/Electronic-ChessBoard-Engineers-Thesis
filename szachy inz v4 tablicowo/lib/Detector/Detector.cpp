#include "Detector.h"


Detector::Detector()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sig1, INPUT);
  pinMode(sig2, INPUT);
  pinMode(sig3, INPUT);
  pinMode(sig4, INPUT);
}


void Detector::choosePin(int pin)
{
  digitalWrite(s0, bitRead(pin, 0));
  digitalWrite(s1, bitRead(pin, 1));
  digitalWrite(s2, bitRead(pin, 2));
  digitalWrite(s3, bitRead(pin, 3));
}


void Detector::scan(bool reference)
{   
  reading_num = 200;
  if (reference){
    Serial.println("Obtainig reference values");
    reading_num = 1000;
  }

  clear_array(rawValues);
  for (int k = 0; k < reading_num; k++)
  {
    iter++;
    if (reference){Serial.print("Reading "); Serial.println(iter);}
    for (int i = 0; i < 16; i++) // 16 pins on mux
    {
      choosePin(i); // choose an input pin on the 74HC4067 MUX
      if (i<8){
        rawValues[0][i]= rawValues[0][i] + analogRead(sig1); // 1.1
        rawValues[2][i]= rawValues[2][i] + analogRead(sig2); // 2.1
        rawValues[4][i]= rawValues[4][i] + analogRead(sig3); // 3.1
        rawValues[6][i]= rawValues[6][i] + analogRead(sig4); // 4.1
      }
      else{
        rawValues[1][i-8]= rawValues[1][i-8] + analogRead(sig1); // 1.2
        rawValues[3][i-8]= rawValues[3][i-8] + analogRead(sig2); // 2.2
        rawValues[5][i-8]= rawValues[5][i-8] + analogRead(sig3); // 3.2
        rawValues[7][i-8]= rawValues[7][i-8] + analogRead(sig4); // 4.2
      }
    }
    if(reference) delay(10);
    else delay(10);
  }
    
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      rawValues[i][j] = round(rawValues[i][j]/reading_num);
    }
  }

  if(reference){
    for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        referenceValues[i][j] = rawValues[i][j];
      }
    } 
  }
}


void Detector::mapToFigure()
{
  // prev_figures = figures;
  clearFigArray(figures);
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      // if      (dropDown[i][j] > calibration[0][i][j] - 40)
      //   { figures[i][j] = 'P';} //0 - P
      // else if (dropDown[i][j] < calibration[1][i][j] + 30 && dropDown[i][j] > calibration[1][i][j]-50)  
      //   { figures[i][j] = 'W';} //0,5 - W
      // else if (dropDown[i][j] < calibration[2][i][j] + 100 && dropDown[i][j] > calibration[2][i][j]-100)  
      //   { figures[i][j] = 'S';} //1 - S
      // else if (dropDown[i][j] < calibration[3][i][j] + 60 && dropDown[i][j] > calibration[3][i][j]-60)  
      //   { figures[i][j] = 'G';} //1,5 - G
      // else if (dropDown[i][j] < calibration[4][i][j] + 50 && dropDown[i][j] > calibration[4][i][j]-30)  
      //   { figures[i][j] = 'Q';} //2 - Q
      // else if (dropDown[i][j] < calibration[5][i][j] + 30 && dropDown[i][j] > calibration[5][i][j]-100)  
      //   { figures[i][j] = 'K';} //2,5 - K
      
      if      (dropDown[i][j] > calibration[0][i][j] - 60)
        { figures[i][j] = 'P';} //0 - Pawn
      else if (dropDown[i][j] < calibration[1][i][j] + 30 && dropDown[i][j] > calibration[1][i][j]-50)  
        { figures[i][j] = 'R';} //0,5 - Rook
      else if (dropDown[i][j] < calibration[2][i][j] + 100 && dropDown[i][j] > calibration[2][i][j]-100)  
        { figures[i][j] = 'N';} //1 - Knight
      else if (dropDown[i][j] < calibration[3][i][j] + 60 && dropDown[i][j] > calibration[3][i][j]-60)  
        { figures[i][j] = 'B';} //1,5 - Bishop
      else if (dropDown[i][j] < calibration[4][i][j] + 50 && dropDown[i][j] > calibration[4][i][j]-30)  
        { figures[i][j] = 'Q';} //2 - Queen
      else if (dropDown[i][j] < calibration[5][i][j] + 30 && dropDown[i][j] > calibration[5][i][j]-100)  
        { figures[i][j] = 'K';} //2,5 - King
      

    }
  }
}


void Detector::clearFigArray(std::array<std::array<char, 8>, 8> &myArray)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      myArray[i][j] = '0';
    }
  }
}


void Detector::getDropDown()
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
     dropDown[i][j] = rawValues[i][j] - referenceValues[i][j];
    }
  }
}


void Detector::printChar(const std::array<std::array<char, 8>, 8> &myArray)
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(myArray[i][j] >=0 ){
        Serial.print(" ");  
      } 
    //   if(mode == 1){Serial.print("  ");}
      Serial.print(myArray[i][j]);
      Serial.print(" ");
    }
    // Serial.println();
    Serial.println();
  }
}


void Detector::printInt(const std::array<std::array<int, 8>, 8> &myArray)
{
  Serial.println();
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(myArray[i][j] >=0 ){
        Serial.print(" ");  
      } 
    //   if(mode == 1){Serial.print("  ");}
      Serial.print(myArray[i][j]);
      Serial.print(" ");
    }
    // Serial.println();
    Serial.println();
  }
}


void Detector::clear_array(std::array<std::array<int, 8>, 8> &myArray)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            myArray[i][j] = 0;
        }
    }
}


bool Detector::detect_board_change()
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if (figures[i][j] != prev_figures[i][j])
      {
        change_row = i;
        change_col = j;
        return true;
      }
    }
  }
  return false;
}


void Detector::check_for_picked_fig()
{
  if(change_row != -1 && change_col != -1)
  {  
    if(figures[change_row][change_col] == '0' && fig_before_change[change_row][change_col] != '0' && is_fig_picked == false)
    {
        picked_fig = fig_before_change[change_row][change_col];
        is_fig_picked = true;
        picked_row = change_row;
        picked_col = change_col;

        Serial.print("2 Podniesiono: ");
        Serial.print("row: ");
        Serial.print(picked_row);
        Serial.print(" col: ");
        Serial.print(picked_col);
        Serial.print(" fig: ");
        Serial.println(picked_fig);
        }
    }
}

void Detector::check_for_placed_back()
{
  if(change_row != -1 && change_col != -1)
  {  
    // Serial.println("########## PlaceBACK ########");
    // Serial.print("Change row: ");
    // Serial.print(change_row);
    // Serial.print(" col: ");
    // Serial.println(change_col);
    // Serial.print("Picked row: ");
    // Serial.print(picked_row);
    // Serial.print(" col: ");
    // Serial.println(picked_col);
    // Serial.println(" Figs_before: ");
    // printChar(fig_before_change);
    // Serial.println(" Figs: ");
    // printChar(figures);

    if(figures[change_row][change_col] != '0' && fig_before_change[change_row][change_col] == '0' 
    && figures[change_row][change_col] == picked_fig && is_fig_picked == true 
    && picked_row == change_row && picked_col == change_col)
    {
      Serial.println("Wracasz na swoje miejsce");
      is_fig_picked = false;
      picked_row = -1;
      picked_col = -1;
    }
  }
}

void Detector::check_for_move()
{
  if(change_row != -1 && change_col != -1)
  {  
    // Serial.println("########## MOVE ########");
    // Serial.print("Change row: ");
    // Serial.print(change_row);
    // Serial.print(" col: ");
    // Serial.println(change_col);
    // Serial.print("Picked row: ");
    // Serial.print(picked_row);
    // Serial.print(" col: ");
    // Serial.println(picked_col);
    // Serial.println(" Figs_before: ");
    // printChar(fig_before_change);
    // Serial.println(" Figs: ");
    // printChar(figures);

    if(figures[change_row][change_col] != '0' && fig_before_change[change_row][change_col] == '0' 
    && figures[change_row][change_col] == picked_fig && is_fig_picked == true 
    && (picked_row != change_row || picked_col != change_col))
    {
      Serial.print("Ło ty kurwa spierdala   ");
      Serial.print(" z: ");
      Serial.print(picked_row);
      Serial.print(",");
      Serial.print(picked_col);
      Serial.print(" na: ");
      Serial.print(change_row);
      Serial.print(",");
      Serial.println(change_col);
      is_fig_picked = false;
      picked_row = -1;
      picked_col = -1;
    }
  }
}

void Detector::check_for_new_fig()
{
    if(change_row != -1 && change_col != -1)
    {  
    // Serial.println("########## MOVE ########");
    // Serial.print("Change row: ");
    // Serial.print(change_row);
    // Serial.print(" col: ");
    // Serial.println(change_col);
    // Serial.print("Picked row: ");
    // Serial.print(picked_row);
    // Serial.print(" col: ");
    // Serial.println(picked_col);
    // Serial.println(" Figs_before: ");
    // printChar(fig_before_change);
    // Serial.println(" Figs: ");
    // printChar(figures);

        if(figures[change_row][change_col] != '0' && fig_before_change[change_row][change_col] == '0' && is_fig_picked == false)
        {
            Serial.print("Nowy szon na rejonie");
            Serial.print(" na: ");
            Serial.print(change_row);
            Serial.print(",");
            Serial.println(change_col);

            is_fig_picked = false;
            picked_row = -1;
            picked_col = -1;
        }
    }
}

void Detector::scanBoard()
{
    prev_figures = figures;
    scan(false);
    getDropDown();
    mapToFigure();
    bool change = detect_board_change();

    if(change)
    {
    fig_before_change = prev_figures; // zapamiętanie planszy przed zmianą
    Serial.println();
    Serial.println("Sonduje mnie stara kurwa");
    // printChar(fig_before_change);
    }

    while(change) // przeczekanie okresu niestabilnego
    {
    prev_figures = figures;
    scan(false);
    getDropDown();
    mapToFigure();
    change = detect_board_change();
    }

    check_for_new_fig();
    check_for_picked_fig();
    check_for_placed_back();
    check_for_move();
}