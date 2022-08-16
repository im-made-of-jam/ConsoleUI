#pragma once

#include "blockIOConsole.h"

Console::BlockIOConsole::BlockIOConsole() : LiveIOConsole(nullptr, nullptr){
}

void
Console::BlockIOConsole::addBlock(IOBlock block){
    blocks.push_back(&block);
}

Console::IOBlock* 
Console::BlockIOConsole::getBlockP(uint64_t index){
    if(!blocks.size()){
        return nullptr;
    }
    
    if(index > blocks.size()){
        return nullptr;
    }

    return blocks[index];
}

void
Console::BlockIOConsole::removeBlock(uint64_t index){
    if(!blocks.size()){
        return;
    }
    
    if(index > blocks.size()){
        return;
    }

    blocks[index]->drawn = false;
}