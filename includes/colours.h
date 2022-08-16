#pragma once

#include <cstdint>
#include <Windows.h>

class Colours {
  public:
    // add the light bit to a colour
    static inline uint32_t makeLight(uint32_t colour){
        return colour | 8; 
    }

    // remove the light bit from a colour
    static inline uint32_t makeDark(uint32_t colour){
        return colour & 0xF7;
    }

    // a colour for a windows console is 8 bits, the upper 4 being for the backgroung
    //   this makes the coulour from a foreground colour into a background colour
    static inline uint32_t makeBackground(uint32_t colour){
        return colour << 4;
    }

    // light primary colours
    const static uint32_t red = FOREGROUND_RED;
    const static uint32_t green = FOREGROUND_GREEN;
    const static uint32_t blue = FOREGROUND_BLUE;

    // light secondary colours
    const static uint32_t yellow = red | green;
    const static uint32_t cyan = green | blue;
    const static uint32_t magenta = blue | red;

    const static uint32_t white = red | green | blue;

    const static uint32_t black = 0; // no colour flags set
};