#pragma once

#include "../liveIOConsole.h"
#include "IOBlock.h"

namespace Console{

class BlockIOConsole : LiveIOConsole {
  protected:
    std::vector<IOBlock*> blocks;

  public:
    BlockIOConsole();

    // add an IOBlock to the collection
    void addBlock(IOBlock);

    // returns a pointer to the IOBlock at the given index of the blocks vector, or nullptr if the given index is invalid
    // will also return nullptr if there are no blocks
    IOBlock* getBlockP(uint64_t index);

    // stops the block at the given index from being drawn, and does nothing if the index is out of range
    void removeBlock(uint64_t index);
};

} // namespace Console