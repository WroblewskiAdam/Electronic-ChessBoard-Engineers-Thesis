#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <array>

#ifdef __AVR__
  #include <avr/power.h>
#endif

class Iluminator
{
    public:
        Iluminator();
        void light(int row, int col, uint32_t color);
        void light_moves(const std::array<std::array<int, 8>, 8> &myArray, int move_type);
        void light_all_sequence(uint32_t my_color);
        void clear();
        void start_animation();
        uint32_t red = pixels.Color(255, 0, 0);
        uint32_t green = pixels.Color(0, 255, 0);
        uint32_t blue = pixels.Color(0, 0, 255);

        bool is_dark = true;
            
    private:
        const int pin = 26;
        const int pixel_num = 64;
        // Adafruit_NeoPixel *pixels;
        Adafruit_NeoPixel pixels = Adafruit_NeoPixel(pixel_num, pin, NEO_GRB + NEO_KHZ800);
        int get_pixel_id(int row, int col);

};