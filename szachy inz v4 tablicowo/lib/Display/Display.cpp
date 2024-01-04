#include <Display.h>

Display::Display()
{
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
}

void Display::scrollText(int row, String &message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) 
  {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) 
  {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void Display::print(int row, String &message)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}