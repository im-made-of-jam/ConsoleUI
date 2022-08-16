#pragma once

#include "inputConsole.h"
#include "drawConsole.h"
#include <string>
#include <vector>

namespace Console{

class LiveIOConsole {
  protected:
    Console::InputConsole* inConsole;
    Console::DrawConsole* outlineConsole;
    Console::OutputConsole* bareOutputConsole;

    bool outlineEnabled;

    // keeps a track of which row we are drawing to
    uint64_t rowNumber = 0;

    std::string footerText;

  public:
    LiveIOConsole(Console::InputConsole*, Console::DrawConsole*);

    // sets the outline visibility
    void setOutline(bool);

    // gets the outline visibility
    bool getOutline();

    // draws an outline around the edge of the console, but only if(outlineEnabled)
    void drawOutline();

    // sets the content to be put into the footer of the console
    // the footer will only be drawn if the outline is also enabled
    void setFooter(const std::string&);

    // returns user from the console, empty striing if there was none
    std::string getInput();

    // returns a 64 bit integer with a bit set for each control key listed in Console::ControlInputMask
    uint64_t getControlKeys();

    // prints the string given to it, and also a newline char afterwards
    void printLine(std::string, bool);

    // clears every char in the console, though not *truly*
    //   this is achieved by printing the space char (' ') to every place a char could be in the console
    void clear();

    // resets the counter for rows drawn, accounting for the outline if necessary
    void resetRowNumber();

    // moves the visual cursor to the given co-ordinates
    void setCursorPosition(int16_t, int16_t);

    // set the colour for both the background and foreground of the console
    void setColour(uint32_t);

    // returns the size of the console as a two-element array, horizontal size, then vertical size
    std::vector<uint64_t> getSize();
};

} // namespace Controller