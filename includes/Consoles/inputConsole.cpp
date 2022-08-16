#pragma once

#include "inputConsole.h"

#define kIsPressed(key) GetKeyState(key) & 0x8000
#define kIsToggled(key) GetKeyState(key) & 0x1

std::string
Console::InputConsole::keyEventTranslate(KEY_EVENT_RECORD event) {
    std::string ret;

    if(std::isprint(event.uChar.AsciiChar)){
        for (uint32_t i = 0; i < event.wRepeatCount; ++i) {
            if (event.bKeyDown) {
                ret += event.uChar.AsciiChar;
            }
        }
    }

    return ret;
}

void 
Console::InputConsole::getContent() {
    while (1) {
        while (hasContent) { // wait for some other thread to make this false, should be the getContent function, meaning that content has been read
            if (contentThreadEnd) {
                break;
            }

            Sleep(15); // sleep a bit so that this thread does not consume 100% of the CPU it runs on
        }

        contentThreadString = ""; // dont need what has already been used

        ReadConsoleInput(console, inputArr, 8, &inputCharsRead); // read 8 chars from the console into inputCharsRead. not raw chars but key event records.

        for (uint32_t i = 0; i < inputCharsRead; ++i) { // for every record, we translate it and add it to the string that goes across threads
            if (inputArr[i].EventType == KEY_EVENT) {
                inputString += keyEventTranslate(inputArr[i].Event.KeyEvent);
            }
        }

        contentThreadString = inputString; // contentThreadString is the one intended to be read by getContent
        inputString = "";

        hasContent = true; // now the waiting will begin

        if (contentThreadEnd) { // should only be the destructor that makes this true
            break;
        }
    }
}

Console::InputConsole::InputConsole() : contentThread{} {
    console = GetStdHandle(STD_INPUT_HANDLE);

    contentThread = std::thread(&Console::InputConsole::getContent, this);
}

Console::InputConsole::~InputConsole() {
    contentThreadEnd = true;
    contentThread.join();
}

std::string
Console::InputConsole::readContent() {
    // if nothing has been typed and there is nothing to see, return empty
    if (!hasContent) {
        return "";
    }

    std::string ret = contentThreadString;

    hasContent = false; // signal to content thread that the string it wants has been read from

    return ret;
}

uint64_t
Console::InputConsole::getControlKeys(){
    // these are all bitmasks defined in inputConsole.h
    uint64_t keys = 0;

    if (kIsPressed(VK_LSHIFT)){ // left shift
        keys = keys | ControlInputMask::leftShift;
    }

    if (kIsPressed(VK_RSHIFT)){ // right shift
        keys = keys | ControlInputMask::rightShift;
    }

    if (kIsPressed(VK_LCONTROL)){ // left control
        keys = keys | ControlInputMask::leftControl;
    }

    if (kIsPressed(VK_RCONTROL)){ // right control
        keys = keys | ControlInputMask::rightControl;
    }

    if (kIsPressed(VK_LMENU)){ // left alt
        keys = keys | ControlInputMask::leftAlt;
    }

    if (kIsPressed(VK_RMENU)){ // right alt
        keys = keys | ControlInputMask::rightAlt;
    }

    if (kIsToggled(VK_CAPITAL)){ // is caps lock enabled
        keys = keys | ControlInputMask::capsEnabled;
    }

    if (kIsPressed(VK_CAPITAL)){ // is the caps lock key pressed
        keys = keys | ControlInputMask::capsLockKey;
    }

    if (kIsPressed(VK_INSERT)){ // insert
        keys = keys | ControlInputMask::insert;
    }

    if (kIsPressed(VK_DELETE)){ // delete
        keys = keys | ControlInputMask::Delete;
    }

    if (kIsPressed(VK_HOME)){  // home
        keys = keys | ControlInputMask::home;
    }

    if (kIsPressed(VK_END)){ // end
        keys = keys | ControlInputMask::end;
    }

    if (kIsPressed(VK_PRIOR)){ // page up
        keys = keys | ControlInputMask::pageUp;
    }

    if (kIsPressed(VK_NEXT)){ // page down
        keys = keys | ControlInputMask::pageDown;
    }

    if (kIsPressed(VK_SNAPSHOT)){ // print screen
        keys = keys | ControlInputMask::printScreen;
    }

    if (kIsToggled(VK_SCROLL)){ // is scroll lock enabled
        keys = keys | ControlInputMask::scrollEnabled;
    }

    if (kIsPressed(VK_SCROLL)){ // is the scroll lock key pressed
        keys = keys | ControlInputMask::scrollLockKey;
    }

    if (kIsPressed(VK_PAUSE)){ // pause break key
        keys = keys | ControlInputMask::pause;
    }

    if (kIsPressed(VK_CANCEL)){  // cancel key
        keys = keys | ControlInputMask::cancel;
    }

    if (kIsPressed(VK_LEFT)){ // left arrow key
        keys = keys | ControlInputMask::leftArrow;
    }

    if (kIsPressed(VK_UP)){  // up arrow key
        keys = keys | ControlInputMask::upArrow;
    }

    if (kIsPressed(VK_RIGHT)){  // right arrow key
        keys = keys | ControlInputMask::rightArrow;
    }

    if (kIsPressed(VK_DOWN)){  // down arrow key
        keys = keys | ControlInputMask::downArrow;
    }

    if (kIsToggled(VK_NUMLOCK)){ // is num lock enabled
        keys = keys | ControlInputMask::numEnabled;
    }

    if (kIsPressed(VK_NUMLOCK)){ // is the num lock key pressed
        keys = keys | ControlInputMask::numLockKey;
    }
    if (kIsPressed(VK_ESCAPE)){ // escape key
        keys = keys | ControlInputMask::escape;
    }


    // function keys
    if (kIsPressed(VK_F1)){
        keys = keys | ControlInputMask::F1;
    }

    if (kIsPressed(VK_F2)){
        keys = keys | ControlInputMask::F2;
    }

    if (kIsPressed(VK_F3)){
        keys = keys | ControlInputMask::F3;
    }

    if (kIsPressed(VK_F4)){
        keys = keys | ControlInputMask::F4;
    }

    if (kIsPressed(VK_F5)){
        keys = keys | ControlInputMask::F5;
    }
    
    if (kIsPressed(VK_F6)){
        keys = keys | ControlInputMask::F6;
    }

    if (kIsPressed(VK_F7)){
        keys = keys | ControlInputMask::F7;
    }

    if (kIsPressed(VK_F8)){
        keys = keys | ControlInputMask::F8;
    }

    if (kIsPressed(VK_F9)){
        keys = keys | ControlInputMask::F9;
    }

    if (kIsPressed(VK_F10)){
        keys = keys | ControlInputMask::F10;
    }

    if (kIsPressed(VK_F11)){
        keys = keys | ControlInputMask::F11;
    }

    if (kIsPressed(VK_F12)){
        keys = keys | ControlInputMask::F12;
    }

    return keys;
}