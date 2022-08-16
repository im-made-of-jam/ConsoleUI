#pragma once

#include "outputConsole.h"

#define consoleWidth (consoleInfo->srWindow.Right - consoleInfo->srWindow.Left + 1)
#define consoleHeight (consoleInfo->srWindow.Bottom - consoleInfo->srWindow.Top + 1)

Console::OutputConsole::OutputConsole() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    consoleInfo = new CONSOLE_SCREEN_BUFFER_INFO;

    GetConsoleScreenBufferInfo(consoleHandle, consoleInfo);

    width = consoleWidth;
    height = consoleHeight;
}

void
Console::OutputConsole::print(const std::string& str, uint64_t row){
    GetConsoleScreenBufferInfo(consoleHandle, consoleInfo);
    
    std::string outStr = str;

    width = consoleWidth;
    height = consoleHeight;

    if (str.length() > width) {
        outStr = str.substr(0, width);
    }

    // construct the COORD struct in place in the call, since we know exactly
    // what we need and only need it once
    // this static cast means that row numbers above 32767 do not work, not that that should really matter
    SetConsoleCursorPosition(consoleHandle, {1, static_cast<int16_t>(row)});

    std::cout << outStr;
}

void
Console::OutputConsole::print(const char c, uint64_t X, uint64_t Y){
    GetConsoleScreenBufferInfo(consoleHandle, consoleInfo);

    width = consoleWidth;
    height = consoleHeight;

    if (consoleInfo->dwCursorPosition.X >= width) {
        return;
    }

    SetConsoleCursorPosition(consoleHandle, {static_cast<int16_t>(X), static_cast<int16_t>(Y)});

    std::cout << c;
}

void
Console::OutputConsole::setConsoleColour(uint32_t colour){
    SetConsoleTextAttribute(consoleHandle, colour);
}