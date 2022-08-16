#pragma once

#include "outputConsole.h"

namespace Console{

class DrawConsole{
  protected:
    OutputConsole* outP;
    HANDLE console;
    CONSOLE_SCREEN_BUFFER_INFO* consoleInfo;

  public:
    // uses the output console passed in the constructor if is not nullptr
    //   if is nullptr, constructs new output console then binds to pointer argument
    //   this is so can be used to create output console if neccessary
    DrawConsole(OutputConsole*);

    // whether or not to delete the output console when this object is destroyed
    //   if the output console was created by this object during construction, then by deafult, it will also destroy the output console
    bool destructOutputConsole = false;

    ~DrawConsole();

    // draw outline around console. adapts to current size of console
    //   first char of strings will be used if they are not empty, else no char will be used
    //   if not drawBottom, the bottom line will instead have only a char at the very start and very end of a line, like a line in the middle of the screen
    //   does not work when width or height of console screen is less than 2
    void drawOutline(const std::string& topBottom,
                     const std::string& corner,
                     const std::string& side,
                     const bool& drawBottom);

    // this print is just like std::cout except it respects the outline
    //   if no space should be left around the edge of the console use OutputConsole::print instead
    //   row is the index of the row onto which the string shall be printed
    //    index of 1 is the very first line after the outline
    //    as much as it shouldnt matter, row numbers above 32767 will not work properly
    // if overwriteBottom, the string will be allowed to be printed onto the very last line of the console
    void print(      std::string&,
               const uint64_t row,
               const bool overwriteBottom);

    // returns the pointer to the output console used by this console instance
    //   probably not the greatest idea to use this, instead favour creating a separate instance of OutputConsole
    Console::OutputConsole* getOutputConsole();

    // returns the windows handle to the console itself
    HANDLE getConsoleHandle();
};

} // namespace Console