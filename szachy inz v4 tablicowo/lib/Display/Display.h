#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Display
{
    private:
        const int I2C_SDA = 16;
        const int I2C_SCL = 17;
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);  
    
    public:
        Display();
        void scrollText(int row, String &message, int delayTime, int lcdColumns);
        void print(int row, String &message);
}


