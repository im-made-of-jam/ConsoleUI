#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

namespace Console{

class OutputConsole{
  protected:
    HANDLE consoleHandle;
    CONSOLE_SCREEN_BUFFER_INFO* consoleInfo;

  public:
    // size of the console along both edges
    uint64_t width;
    uint64_t height;

    OutputConsole();

    // takes a new line, then cuts the string to the width of the console, then prints to stdout on the row specified
    void print(const std::string&, uint64_t);

    // in case of a char, just straight to stdout unless it would go over the end of the line, in which case nothing
    //   X and Y co-ordinates must be specified, and the char shall be printed to said co-ordinate
    void print(const char, uint64_t, uint64_t);

    // sets the colour of the text in the console, and the background also
    //   see colours.h for colours that can be used
    void setConsoleColour(uint32_t);
};

}