// GUIMananger.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cstdint>

#include "includes/Consoles/liveIOConsole.h"
#include "includes/colours.h"

int main(int argc, char* argv[], char* envp[]){
    std::cout << argv[0];

    Console::LiveIOConsole console(nullptr, nullptr);

    std::string consoleIn;

    console.setOutline(true);

    while (1) {
        if (console.getControlKeys() & Console::ControlInputMask::F12) {
            break;
        }

        consoleIn = console.getInput();

        uint64_t controlKeys = console.getControlKeys();

        if(controlKeys & Console::ControlInputMask::F10){
            console.setOutline(true);
        }

        if(controlKeys & Console::ControlInputMask::F9){
            console.setOutline(false);
            console.clear();
        }

        Sleep(10);
    }

    console.setColour(Colours::makeLight(Colours::white));

    return 0;
}