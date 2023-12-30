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
  reading_num = 10;
  if (reference){
    Serial.println("Obtainig reference values");
    reading_num = 100;
  }

  clear_array(rawValues);
  for (int k = 0; k < reading_num; k++)
  {
    if (reference){Serial.print("Reading "); Serial.println(k);}
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
    if (reference){delay(10);}
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

  // Serial.println("REFERENCE: ");
  // printInt(referenceValues);
  // Serial.println("Raw: ");
  // printInt(rawValues);

}




void Detector::mapToFigure()
{
  prev_figures = figures;
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
      
      if      (dropDown[i][j] > calibration[0][i][j] - 40)
        { figures[i][j] = '1';} //0 - P
      else if (dropDown[i][j] < calibration[1][i][j] + 30 && dropDown[i][j] > calibration[1][i][j]-50)  
        { figures[i][j] = '2';} //0,5 - W
      else if (dropDown[i][j] < calibration[2][i][j] + 100 && dropDown[i][j] > calibration[2][i][j]-100)  
        { figures[i][j] = '3';} //1 - S
      else if (dropDown[i][j] < calibration[3][i][j] + 60 && dropDown[i][j] > calibration[3][i][j]-60)  
        { figures[i][j] = '4';} //1,5 - G
      else if (dropDown[i][j] < calibration[4][i][j] + 50 && dropDown[i][j] > calibration[4][i][j]-30)  
        { figures[i][j] = '5';} //2 - Q
      else if (dropDown[i][j] < calibration[5][i][j] + 30 && dropDown[i][j] > calibration[5][i][j]-100)  
        { figures[i][j] = '6';} //2,5 - K

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


void Detector::getChosenFigure()
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if ((figures[i][j] != prev_figures[i][j]) && figures[i][j] == '0')
      {
        chosen_fig = prev_figures[i][j];
        chosen_row = i;
        chosen_col = j;
      }
    }
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

void Detector::scanBoard()
{
  scan(false);
  getDropDown();
  mapToFigure();

  // chosen_row = NULL;
  // chosen_col = NULL;
  getChosenFigure();
}