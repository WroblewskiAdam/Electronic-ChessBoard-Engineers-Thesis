#include <Iluminator.h>

Iluminator::Iluminator(){
    pixels.begin();
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
    is_dark = false;
}


void Iluminator::clear()
{   
    if(!is_dark)
    {
        pixels.clear();
        pixels.show();
        is_dark = true;
    }
}

void Iluminator::light_whites_win()
{
    for(int j = 0; j < 8; j++)
    {
        light(6, j, green);
        light(7, j, green);
        light(0, j, red);
        light(1, j, red);
    }
    is_dark = false;
}

void Iluminator::light_blacks_win()
{
     for(int j = 0; j < 8; j++)
    {
        light(6, j, red);
        light(7, j, red);
        light(0, j, green);
        light(1, j, green);
    }
    is_dark = false;
}

void Iluminator::light_draw()
{
     for(int j = 0; j < 8; j++)
    {
        light(6, j, green);
        light(7, j, green);
        light(0, j, green);
        light(1, j, green);
    }
    is_dark = false;
}

void Iluminator::light_moves(const std::array<std::array<int, 8>, 8> &myArray, uint32_t color)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
           if(myArray[i][j] == 1) light(i, j, color);
        }
    }
    is_dark = false;
}


void Iluminator::light_all_sequence(uint32_t my_color)
{
    // pixels.clear();
    for(int i = 0; i < 64; i++)
    {
        pixels.setPixelColor(i,my_color);
        pixels.show();
        delay(30);
    }
    is_dark = false;
}


void Iluminator::light_all_at_once(uint32_t my_color)
{
    for(int i = 0; i < 64; i++)
    {
        pixels.setPixelColor(i,my_color);
    }
    pixels.show();
    is_dark = false;
}

void Iluminator::flash(int num, uint32_t my_color)
{
    for(int j = 0; j < num; j++)
    {
        for(int i = 0; i < 64; i++)
        {
            pixels.setPixelColor(i,my_color);
        }
        pixels.show();
        delay(250);
        pixels.clear();
        pixels.show();
        delay(250);
    }
    is_dark = false;
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
