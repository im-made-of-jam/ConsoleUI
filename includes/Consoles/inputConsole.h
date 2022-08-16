#pragma once

#include <string>
#include <cstdint>
#include <iostream>
#include <thread>

#include <Windows.h>

namespace Console{

// gets key inputs from the console being used by the program
class InputConsole {
  protected:
    // WIN32 handle to stdin
    HANDLE console;

    // string copied from the content thread then returned from readContent()
    std::string inputString;
    // array of INPUT_RECORDs returned from WIN32 API functio ReadConsoleInput()
    INPUT_RECORD inputArr[128];
    // number of INPUT_RECORDs returned from WIN32 API function ReadConsoleInput()
    DWORD inputCharsRead;

    // the thread that takes care of finding and communicating inputs from the console to the main thread
    std::thread contentThread;
    std::string contentThreadString;

    // contentThread waits for this to be false before continuing, set to false by readContent()
    volatile bool hasContent = false;
    volatile bool contentThreadEnd = false;

    // turn a key event into a string. might be longer than one char, hence the function rather than directly accessing it
    std::string keyEventTranslate(KEY_EVENT_RECORD);

    // this is meant to run in its own thread, and constantly checks for input from the user
    //    if there is input from the user, it stores it in a string, then waits for the flag that 
    //     that string has been read before continuing to listen for input
    void getContent();

  public:
    // constructor and destructor handle the I/O thread starting and stopping
    InputConsole();

    ~InputConsole();

    // return a string which contains content that was typed to the console, empty string if there was nothing typed
    std::string readContent();

    // keys such as shift, ctrl, alt, etc.
    static uint64_t getControlKeys();
};

// bit masks for control keys
class ControlInputMask{
  private:    
    static const uint64_t one = 1;

  public:
    static const uint64_t leftShift     =  one;
    static const uint64_t rightShift    = (one << 1 );
    static const uint64_t leftControl   = (one << 2 );
    static const uint64_t rightControl  = (one << 3 );
    static const uint64_t leftAlt       = (one << 4 );
    static const uint64_t rightAlt      = (one << 5 );
    static const uint64_t capsEnabled   = (one << 6 );
    static const uint64_t capsLockKey   = (one << 7 );
    static const uint64_t insert        = (one << 8 );
    static const uint64_t Delete        = (one << 9 );
    static const uint64_t home          = (one << 10);
    static const uint64_t end           = (one << 11);
    static const uint64_t pageUp        = (one << 12);
    static const uint64_t pageDown      = (one << 13);
    static const uint64_t printScreen   = (one << 14);
    static const uint64_t scrollEnabled = (one << 15);
    static const uint64_t scrollLockKey = (one << 16);
    static const uint64_t pause         = (one << 17);
    static const uint64_t cancel        = (one << 18);
    static const uint64_t leftArrow     = (one << 19);
    static const uint64_t upArrow       = (one << 20);
    static const uint64_t rightArrow    = (one << 21);
    static const uint64_t downArrow     = (one << 22);
    static const uint64_t numEnabled    = (one << 23);
    static const uint64_t numLockKey    = (one << 24);
    static const uint64_t escape        = (one << 25);

    static const uint64_t F1  = (one << 40);
    static const uint64_t F2  = (one << 41);
    static const uint64_t F3  = (one << 42);
    static const uint64_t F4  = (one << 43);
    static const uint64_t F5  = (one << 44);
    static const uint64_t F6  = (one << 45);
    static const uint64_t F7  = (one << 46);
    static const uint64_t F8  = (one << 47);
    static const uint64_t F9  = (one << 48);
    static const uint64_t F10 = (one << 49);
    static const uint64_t F11 = (one << 50);
    static const uint64_t F12 = (one << 51);
    static const uint64_t F13 = (one << 52);
    static const uint64_t F14 = (one << 53);
    static const uint64_t F15 = (one << 54);
    static const uint64_t F16 = (one << 55);
    static const uint64_t F17 = (one << 56);
    static const uint64_t F18 = (one << 57);
    static const uint64_t F19 = (one << 58);
    static const uint64_t F20 = (one << 59);
    static const uint64_t F21 = (one << 60);
    static const uint64_t F22 = (one << 61);
    static const uint64_t F23 = (one << 62);
    static const uint64_t F24 = (one << 63);

    // combinations for when side doesnt matter
    static const uint64_t shift   = leftShift   | rightShift;
    static const uint64_t control = leftControl | rightControl;
    static const uint64_t alt     = leftAlt     | rightAlt;
};

}; // namespace Console