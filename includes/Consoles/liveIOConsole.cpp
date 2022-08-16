#pragma once

#include "liveIOConsole.h"

Console::LiveIOConsole::LiveIOConsole(Console::InputConsole* input, Console::DrawConsole* output) {
    if (input == nullptr){
        inConsole = new Console::InputConsole();
    }
    else {
        inConsole = input;
    }

    if (output == nullptr){
        outlineConsole = new Console::DrawConsole(nullptr);
    }
    else {
        outlineConsole = output;
    }

    bareOutputConsole = outlineConsole->getOutputConsole();
}

bool
Console::LiveIOConsole::getOutline(){
    return outlineEnabled;
}

void
Console::LiveIOConsole::setOutline(bool outlineDrawn){
    outlineEnabled = outlineDrawn;
}

std::string
Console::LiveIOConsole::getInput(){
    return inConsole->readContent();
}

void
Console::LiveIOConsole::printLine(std::string str, bool newline = true){
    if (outlineEnabled) {
        outlineConsole->print(str, rowNumber, false);
    }
    else {
        bareOutputConsole->print(str, rowNumber);
    }

    if(newline){
        rowNumber++;
    }
}

void
Console::LiveIOConsole::resetRowNumber(){
    if(outlineEnabled){
        rowNumber = 1;
    }
    else{
        rowNumber = 0;
    }
}

void
Console::LiveIOConsole::setColour(uint32_t colour){
    bareOutputConsole->setConsoleColour(colour);
}

void
Console::LiveIOConsole::drawOutline(){
    if(outlineEnabled){
        outlineConsole->drawOutline("-", "+", "|", false);

        // footer text rendered separately
        outlineConsole->print(footerText, bareOutputConsole->height - 1, true);
    }
}

uint64_t
Console::LiveIOConsole::getControlKeys(){
    return inConsole->getControlKeys();
}

void
Console::LiveIOConsole::clear(){
    std::string whitespace;

    bool oldOutlineEnabled = outlineEnabled;

    setOutline(false);

    resetRowNumber();

    uint64_t width = 0;
    uint64_t height = 0;

    for(uint64_t i = 0; i < bareOutputConsole->width; ++i){
        whitespace += " ";
    }

    for(uint64_t i = 0; i < (bareOutputConsole->height); ++i){
        printLine(whitespace, true);
    }

    // for whatever reason the very last char and the very first char are not replaces, so we do this manually
    bareOutputConsole->print(' ', width, height);

    // this also happens to move the cursor position, so we do the top left corner last to reset the cursor to (0, 0)
    bareOutputConsole->print(' ', 0, 0);

    setOutline(oldOutlineEnabled);
}

void
Console::LiveIOConsole::setFooter(const std::string& str){
    if(str.size() >= (bareOutputConsole->width - 2)){
        footerText = str.substr(0, (bareOutputConsole->width - 2));
        return;
    }

    footerText = str;
}

void
Console::LiveIOConsole::setCursorPosition(int16_t X, int16_t Y){
    SetConsoleCursorPosition(outlineConsole->getConsoleHandle(), COORD{X, Y});
}

std::vector<uint64_t>
Console::LiveIOConsole::getSize(){
    std::vector<uint64_t> s {bareOutputConsole->width, bareOutputConsole->height};

    return s;
}