#include <iostream>

#include "Deep.h"
#include "Net.h"

#define DEEP_DEBUG_MEMORY
#include "Debug/Memory.h"

int main()
{
    Deep::StartMemoryDebug();

    std::cout << "Hello World!" << std::endl;

    Deep::PrintAllocationMap();
    Deep::EndMemoryDebug();
}