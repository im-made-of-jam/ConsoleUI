#pragma once

#include <string>
#include <cstdint>

namespace Console{

class IOBlock{
  public:
    // whether or not the block is drawn to the console
    bool drawn;

    // the console that is printed
    // due to the way that printing is handled, this cannot traverse multiple lines, and will always be cut short at the end of a line
    std::string content;

    // the colour for the content to be upon being printed
    uint32_t colour;

    // X and Y co ordinates for the left side of the block on the console
    uint32_t X;
    uint32_t Y;
};

} // napespace Console