#pragma once

#include "drawConsole.h"

#include <Windows.h>

#define consoleWidth (consoleInfo->srWindow.Right - consoleInfo->srWindow.Left)
#define consoleHeight (consoleInfo->srWindow.Bottom - consoleInfo->srWindow.Top)

Console::DrawConsole::DrawConsole(OutputConsole* drawer){
    if (drawer == nullptr) {
        outP = new OutputConsole;
        destructOutputConsole = true;
    }
    else {
        outP = drawer;
    }

    console = GetStdHandle(STD_OUTPUT_HANDLE);
    consoleInfo = new CONSOLE_SCREEN_BUFFER_INFO;
}

Console::DrawConsole::~DrawConsole(){ 
    if (destructOutputConsole) {
        delete outP;
    }
}

void
Console::DrawConsole::drawOutline(const std::string& topBottom,
                                  const std::string& corner,
                                  const std::string& side,
                                  const bool& drawBottom){
    GetConsoleScreenBufferInfo(console, consoleInfo);

    COORD formerPosition = consoleInfo->dwCursorPosition;

    uint32_t width = consoleWidth;
    uint32_t height = consoleHeight;

    // these are more as a sanity check than anything
    if (width > 32767) {
        return;
    }

    if (height > 32767) {
        return;
    }

    if (width < 2) {
        return;
    }

    // chars for constructing outline from widh defaults
    std::string topChar = "-";
    std::string sideChar = "|";
    std::string cornerChar = "+";

    if (!topBottom.empty()){
        topChar = topBottom[0];
    }

    if (!corner.empty()){
        cornerChar = corner[0];
    }

    if (!side.empty()){
        sideChar = side[0];
    }

    std::string topString;

    topString += cornerChar;

    for (uint64_t i = 0; i < width - 1; ++i){
        topString += topChar;
    } 

    topString += cornerChar;


    // this will be used when moving the cursor around
    COORD cursorPos;

    cursorPos.X = 0;
    cursorPos.Y = 0;

    SetConsoleCursorPosition(console, cursorPos);

    std::cout << topString;

    // for the side chars we need to preserve what is already on the screen of the console
    //   this is achieved by moving the cursor around the console using the windows API
    for (uint64_t i = 1; i < height; ++i){
        // for the left side of the screen, X is 0 and Y is the row we are on
        cursorPos.X = 0;
        cursorPos.Y = i;
        SetConsoleCursorPosition(console, cursorPos);
        std::cout << sideChar;

        // for the right side of the screen, X is the width of the console minus 1, since the char we draw will cause the cursor to be on the next line afterwards
        //   Y is again the row we are on
        cursorPos.X = width;
        cursorPos.Y = i;
        SetConsoleCursorPosition(console, cursorPos);
        std::cout << sideChar;
    }

    // bottom line should be the same as the top line for a complete outline
    if (drawBottom){
      std::cout << "\n" << topString;
    }
    // otherwise we just do the side dance again
    else {
        cursorPos.X = 0;
        cursorPos.Y += 1;
        SetConsoleCursorPosition(console, cursorPos);
        std::cout << sideChar;

        cursorPos.X = width;
        // do nothing to Y since we want it to be the same
        SetConsoleCursorPosition(console, cursorPos);
        std::cout << sideChar;
    }

    std::cout << std::flush;

    // now we reset the cursor back to where it was so we do not make life difficult for the caller

    SetConsoleCursorPosition(console, formerPosition);
}

void
Console::DrawConsole::print(std::string& str, const uint64_t row, const bool overwriteBottom){
    // row is 0, but thats where the top outline goes
    
    std::string outString = str;

    if (!row) {
        return;
    }

    GetConsoleScreenBufferInfo(console, consoleInfo);

    if (row > consoleInfo->dwSize.Y){
        return;
    }

    if (row == consoleInfo->dwSize.Y){
        if (!overwriteBottom) {
            return;
        }
    }

    if (outString.length() >= (consoleInfo->dwSize.X - 2)) {
        outString = str.substr(0, (consoleInfo->dwSize.X - 2));
    }

    outP->print(outString, row);

    // do not need to print space char at end of line as this is essentially same as printing blank space
}

Console::OutputConsole*
Console::DrawConsole::getOutputConsole(){
    return outP;
}

HANDLE
Console::DrawConsole::getConsoleHandle(){
    return console;
}