#include <iostream>

#include "Deep.h"

#define DEEP_DEBUG_MEMORY
#include "Debug/Memory.h"

int main()
{
    Deep::StartMemoryDebug();

    void* b = new char[5];
    delete[] b;

    std::cout << "Hello World!\n";

    Deep::PrintAllocationMap();
    Deep::EndMemoryDebug();
}