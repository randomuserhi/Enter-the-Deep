#pragma once

#include "Deep.h"
#include "Deep-DynArray.h"

/*

NOTE:: This hashmap only supports 64bit hashes

LoadFactor 7/8 ?? => 

*/

#define DEEP_HASHMAP_GROUP_SIZE 16 // Default group size = 16, its important for SSE instructions
#define DEEP_HASHMAP_SIZE 20 // Default number of groups
#define DEEP_HASHMAP_ELEMENT_SIZE DEEP_HASHMAP_GROUP_SIZE * DEEP_HASHMAP_SIZE

#define DEEP_HASHMAP_SEED 0x31415296

//Implementation heavily inspired by: https://www.youtube.com/watch?v=ncHmEUmJZf4

typedef enum {
    Deep_HashMap_kEmpty = -128,  // 0b10000000
    Deep_HashMap_kDeleted = -2,  // 0b11111110
    Deep_HashMap_kSentinel = -1, // 0b11111111
    //Deep_HashMap_kFull =          0b0xxxxxxx
} cntrl_t;

typedef uint64_t Deep_Hash;

#define H1(hash) (size_t)(hash >> 7)
#define H2(hash) (cntrl_t)(hash & 0x7F)

#define _Deep_HashMap_Slot(keyType) \
struct \
{ \
    keyType key; \
    size_t index; \
}

#define _Deep_HashMap_KeyPair(keyType, valueType) \
struct \
{ \
    keyType key; \
    valueType value; \
}

#define Deep_HashMap(keyType, valueType) \
struct { \
    /* Note that these two share the same allocation => malloc(sizeof metadata * size + sizeof slots * size) */ \
    cntrl_t* metadata; \
    _Deep_HashMap_Slot(keyType)* slots; \
    _Deep_HashMap_KeyPair(keyType, valueType)* values; \
    size_t numGroups; \
    /* Temp values used to get sizeof in other macros */ \
    keyType tmpKey; \
    valueType tmpValue; \
}

#if defined DEEP_ERRORHANDLING_VERBOSE

#else

#define Deep_HashMap_Create(keyType, valueType, name) Deep_HashMap(keyType, valueType)* name = NULL; \
do { \
    void* tmp = malloc(sizeof *name + sizeof *name->metadata * DEEP_HASHMAP_ELEMENT_SIZE + sizeof *name->slots * DEEP_HASHMAP_ELEMENT_SIZE); \
    if (tmp) \
    { \
        name = tmp; \
        name->metadata = (cntrl_t*)(name + 1); \
        name->slots = (void*)(name->metadata + DEEP_HASHMAP_ELEMENT_SIZE); \
        name->numGroups = DEEP_HASHMAP_SIZE; \
        name->values = (void*)Deep_DynamicArr_Create(*name->values); \
        /*Initialize metadata*/ \
        for (size_t i = 0; i < DEEP_HASHMAP_ELEMENT_SIZE; ++i) name->metadata[i] = Deep_HashMap_kEmpty; \
    } \
} while(0)

#define Deep_HashMap_Insert(hashtable, _key, _value) \
do { \
    if (hashtable) \
    { \
        hashtable->tmpKey = _key; \
        Deep_Hash hash = Deep_HashMap_DefaultBitHash(&hashtable->tmpKey, sizeof hashtable->tmpKey, DEEP_HASHMAP_SEED); \
        size_t group = H1(hash) % hashtable->numGroups; \
        cntrl_t slot = H2(hash) % DEEP_HASHMAP_GROUP_SIZE; \
        int slotsChecked = 0; \
        int groupsChecked = 0; \
        do \
        { \
            if (hashtable->metadata[group * DEEP_HASHMAP_GROUP_SIZE + slot] == Deep_HashMap_kEmpty) \
            { \
                hashtable->metadata[group * DEEP_HASHMAP_GROUP_SIZE + slot] = slot; \
                hashtable->slots[group * DEEP_HASHMAP_GROUP_SIZE + slot].key = _key; \
                hashtable->slots[group * DEEP_HASHMAP_GROUP_SIZE + slot].index = Deep_DynamicArr_Size(hashtable->values); \
                Deep_DynamicArr_EmptyPush(hashtable->values); \
                hashtable->values[Deep_DynamicArr_Size(hashtable->values) - 1].key = _key; \
                hashtable->values[Deep_DynamicArr_Size(hashtable->values) - 1].value = _value; \
                break; \
            } \
            /* Check if simply assigning to same key */ \
            else if (hashtable->slots[group * DEEP_HASHMAP_GROUP_SIZE + slot].key == _key) \
            { \
                hashtable->values[hashtable->slots[group * DEEP_HASHMAP_GROUP_SIZE + slot].index].value = _value; \
                break; \
            } \
            Collision += 1; \
            slot = (slot + 1) % DEEP_HASHMAP_GROUP_SIZE; \
            /* Traverse to next group once all slots have been searched */ \
            ++slotsChecked; \
            if (slotsChecked == DEEP_HASHMAP_GROUP_SIZE) \
            { \
                slotsChecked = 0; \
                group = (group + 1) % hashtable->numGroups; \
                ++groupsChecked; \
                /* Hashtable full, all groups traversed */ \
                if (groupsChecked == hashtable->numGroups) break; \
            } \
        } while(1); \
    } \
} while(0)

#endif

#define Deep_HashMap_Free(hashtable) free(hashtable)
#define Deep_HashMap_Size(hashtable) Deep_DynamicArr_Size(hashtable->values)

#define Deep_HashMap_HashBits  ((sizeof(Deep_Hash)) * 8)
#define Deep_HashMap_Siphash_C_Rounds 1
#define Deep_HashMap_Siphash_D_Rounds 1
#define Deep_HashMap_Rotate_Left(hash, num)  (((hash) << (num)) | ((hash) >> (Deep_HashMap_HashBits - (num))))
#define Deep_HashMap_Rotate_Right(hash, num)  (((hash) >> (num)) | ((hash) << (Deep_HashMap_HashBits - (num))))

Deep__Inline Deep_Hash Deep_HashMap_Siphash(void* value, size_t valueSize, Deep_Hash seed)
{
    unsigned char* d = (unsigned char*)value;
    Deep_Hash i, j;
    Deep_Hash v0, v1, v2, v3, data;

    // hash that works on 32- or 64-bit registers without knowing which we have
    // (computes different results on 32-bit and 64-bit platform)
    // derived from siphash, but on 32-bit platforms very different as it uses 4 32-bit state not 4 64-bit
    v0 = ((((Deep_Hash)0x736f6d65 << 16) << 16) + 0x70736575) ^ seed;
    v1 = ((((Deep_Hash)0x646f7261 << 16) << 16) + 0x6e646f6d) ^ ~seed;
    v2 = ((((Deep_Hash)0x6c796765 << 16) << 16) + 0x6e657261) ^ seed;
    v3 = ((((Deep_Hash)0x74656462 << 16) << 16) + 0x79746573) ^ ~seed;

#define Deep_HashMap_Sipround() \
    do { \
      v0 += v1; v1 = Deep_HashMap_Rotate_Left(v1, 13);  v1 ^= v0; v0 = Deep_HashMap_Rotate_Left(v0,Deep_HashMap_HashBits/2); \
      v2 += v3; v3 = Deep_HashMap_Rotate_Left(v3, 16);  v3 ^= v2; \
      v2 += v1; v1 = Deep_HashMap_Rotate_Left(v1, 17);  v1 ^= v2; v2 = Deep_HashMap_Rotate_Left(v2,Deep_HashMap_HashBits/2); \
      v0 += v3; v3 = Deep_HashMap_Rotate_Left(v3, 21);  v3 ^= v0; \
    } while (0)

    for (i = 0; i + sizeof(Deep_Hash) <= valueSize; i += sizeof(Deep_Hash), d += sizeof(Deep_Hash)) 
    {
        data = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
        data |= (Deep_Hash)(d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24)) << 16 << 16; // discarded if size_t == 4

        v3 ^= data;
        for (j = 0; j < Deep_HashMap_Siphash_C_Rounds; ++j)
            Deep_HashMap_Sipround();
        v0 ^= data;
    }
    data = valueSize << (Deep_HashMap_HashBits - 8);
    switch (valueSize - i) 
    {
        case 7: data |= ((Deep_Hash)d[6] << 24) << 24; // fall through
        case 6: data |= ((Deep_Hash)d[5] << 20) << 20; // fall through
        case 5: data |= ((Deep_Hash)d[4] << 16) << 16; // fall through
        case 4: data |= (d[3] << 24); // fall through
        case 3: data |= (d[2] << 16); // fall through
        case 2: data |= (d[1] << 8); // fall through
        case 1: data |= d[0]; // fall through
        case 0: break;
    }
    v3 ^= data;
    for (j = 0; j < Deep_HashMap_Siphash_C_Rounds; ++j)
        Deep_HashMap_Sipround();
    v0 ^= data;
    v2 ^= 0xff;
    for (j = 0; j < Deep_HashMap_Siphash_D_Rounds; ++j)
        Deep_HashMap_Sipround();

    return v1 ^ v2 ^ v3;
}

Deep__Inline Deep_Hash Deep_HashMap_DefaultBitHash(void* value, size_t valueSize, Deep_Hash seed)
{
    unsigned char* d = (unsigned char*)value;

    // Len == 4 (off for now, so to force 64 bit hash)
    if (valueSize == 4) 
    {
        unsigned int hash = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
        hash ^= seed;
        hash *= 0xcc9e2d51;
        hash = (hash << 17) | (hash >> 15);
        hash *= 0x1b873593;
        hash ^= seed;
        hash = (hash << 19) | (hash >> 13);
        hash = hash * 5 + 0xe6546b64;
        hash ^= hash >> 16;
        hash *= 0x85ebca6b;
        hash ^= seed;
        hash ^= hash >> 13;
        hash *= 0xc2b2ae35;
        hash ^= hash >> 16;
        return (((Deep_Hash)hash << 16 << 16) | hash) ^ seed;
    }
    else if (valueSize == 8 && sizeof(Deep_Hash) == 8) 
    {
        Deep_Hash hash = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
        hash |= (Deep_Hash)(d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24)) << 16 << 16;
        hash ^= seed;
        hash = (~hash) + (hash << 21);
        hash ^= Deep_HashMap_Rotate_Right(hash, 24);
        hash *= 265;
        hash ^= Deep_HashMap_Rotate_Right(hash, 14);
        hash ^= seed;
        hash *= 21;
        hash ^= Deep_HashMap_Rotate_Right(hash, 28);
        hash += (hash << 31);
        hash = (~hash) + (hash << 18);
        return hash;
    }
    else {
        return Deep_HashMap_Siphash(value, valueSize, seed);
    }
}