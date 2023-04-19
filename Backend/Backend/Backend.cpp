#include <iostream>

#include "Deep.h"
#include "Net.h"

#define DEEP_DEBUG_MEMORY
#include "Debug/Memory.h"

// TODO(randomuserhi): Documentation, I need to stay on top of documentation
//                     in code docs along side doc website

int main()
{
    Deep::StartMemoryDebug();

    std::cout << "Hello World!" << std::endl;

    Deep::PrintAllocationMap();
    Deep::EndMemoryDebug();
}