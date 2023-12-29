#include <Iluminator.h>

Iluminator::Iluminator(){
    pixels.begin();
    // pixels.show();
    // pixels.setBrightness(255);
}

int Iluminator::get_pixel_id(int row, int col)
{
    int n = row*8 + col - (row%2)*(col-7+col);
    return n;
}

void Iluminator::light(int row, int col, uint32_t color)
{
    int n = get_pixel_id(row, col);
    pixels.setPixelColor(n, color);
    pixels.show();
}

void Iluminator::clear()
{
    pixels.clear();
    pixels.show();
}


void Iluminator::light_moves(const std::array<std::array<int, 8>, 8> &myArray, int move_type)
{
    uint32_t color;
    if(move_type == 0) color = green;
    else if(move_type == -1) color = red;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
           if(myArray[i][j] == 1) light(i, j, color);
        }
    }
}

void Iluminator::light_all_sequence(uint32_t my_color)
{
  pixels.clear();
  for(int i = 0; i < 64; i++)
  {
    pixels.setPixelColor(i,my_color);
    pixels.show();
    delay(50);
  }
}

void Iluminator::start_animation()
{
    light_all_sequence(red);
    delay(1000);
    light_all_sequence(green);
    delay(1000);
    light_all_sequence(blue);
    delay(1000);
    clear();
}
