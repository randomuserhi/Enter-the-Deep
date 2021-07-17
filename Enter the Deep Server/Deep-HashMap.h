#pragma once

#include "Deep.h"
#include "Deep-DynArray.h"

#define DEEP_DYNAMIC_HASHMAP_GROUP_SIZE 16 // Default group size
#define DEEP_DYNAMIC_HASHMAP_SIZE 10 // Default number of groups

//Implementation heavily inspired by: https://www.youtube.com/watch?v=ncHmEUmJZf4

typedef enum {
    kEmpty = -128,  // 0b10000000
    kDeleted = -2,  // 0b11111110
    kSentinel = -1, // 0b11111111
    //kFull =          0b0xxxxxxx
} cntrl_t;

typedef uint64_t Deep_Hash;

#define H1(hash) (size_t)(hash >> 7)
#define H2(hash) (cntrl_t)(hash & 0x7F)

#define _Deep_HashMap_Slot(keyType, valueType) \
struct \
{ \
    Deep_Hash hash; \
    keyType key; \
    valueType value; \
}

#define Deep_HashMap(keyType, valueType, name) \
struct { \
    _Deep_HashMap_Slot(keyType, valueType)* slots; \
    cntrl_t* metadata; \
    /* Temp values used to get sizeof in other macros */ \
    keyType tempKey; \
    valueType tempValue; \
}* name = NULL

#define Deep_HashMap_Insert(hashTable, key, value) \
do  { \
} while(0)