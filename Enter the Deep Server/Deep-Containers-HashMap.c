#include "Deep-Containers-HashMap.h"

#if Deep$SizeOf_SizeT == 8
inline size_t load_bytes(const char* p, int n)
{
	size_t result = 0;
	--n;
	do
		result = (result << 8) + (unsigned char)(p[n]);
	while (--n >= 0);
	return result;
}

size_t shift_mix(size_t v)
{
	return v ^ (v >> 47);
}
#endif

inline size_t unaligned_load(const char* p)
{
	/*
	* Can be done using bit shifts:
	* 
		uint64_t Ret = 0;
		Ret |= (uint64_t) V[0];
		Ret |= ((uint64_t) V[1]) << 8;
		Ret |= ((uint64_t) V[2]) << 16;
		Ret |= ((uint64_t) V[3]) << 24;
		Ret |= ((uint64_t) V[4]) << 32;
		Ret |= ((uint64_t) V[5]) << 40;
		Ret |= ((uint64_t) V[6]) << 48;
		Ret |= ((uint64_t) V[7]) << 56;
   */
	size_t result;
	memcpy(&result, p, sizeof(result));
	return result;
}

size_t Deep_UnorderedMap_Hash(void* ptr, size_t len, size_t seed)
{
	// http://gcc.gnu.org/git/?p=gcc.git;a=blob_plain;f=libstdc%2b%2b-v3/libsupc%2b%2b/hash_bytes.cc;hb=HEAD
	// Murmur hash function for 32 bit size_t
#if Deep$SizeOf_SizeT == 4
	const size_t m = 0x5bd1e995;
	size_t hash = seed ^ len;
	const char* buf = ptr;

	// Mix 4 bytes at a time into the hash.
	while (len >= 4)
	{
		size_t k = unaligned_load(buf);
		k *= m;
		k ^= k >> 24;
		k *= m;
		hash *= m;
		hash ^= k;
		buf += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array.
	switch (len)
	{
	case 3:
		hash ^= (unsigned char)buf[2] << 16;
		[[gnu::fallthrough]];
	case 2:
		hash ^= (unsigned char)(buf[1]) << 8;
		[[gnu::fallthrough]];
	case 1:
		hash ^= (unsigned char)(buf[0]);
		hash *= m;
	};

	// Do a few final mixes of the hash.
	hash ^= hash >> 13;
	hash *= m;
	hash ^= hash >> 15;
	return hash;
#endif

#if Deep$SizeOf_SizeT == 8
	static const size_t mul = (((size_t)0xc6a4a793UL) << 32UL) + (size_t)0x5bd1e995UL;
	const char* const buf = ptr;

	// Remove the bytes not divisible by the sizeof(size_t).  This
	// allows the main loop to process the data as 64-bit integers.
	const size_t len_aligned = len & ~(size_t)0x7;
	const char* const end = buf + len_aligned;
	size_t hash = seed ^ (len * mul);
	for (const char* p = buf; p != end; p += 8)
	{
		const size_t data = shift_mix(unaligned_load(p) * mul) * mul;
		hash ^= data;
		hash *= mul;
	}
	if ((len & 0x7) != 0)
	{
		const size_t data = load_bytes(end, len & 0x7);
		hash ^= data;
		hash *= mul;
	}
	hash = shift_mix(hash) * mul;
	hash = shift_mix(hash);
	return hash;
#endif
}

int Deep_UnorderedMap_ByteCompare(void* hashKey, void* key, size_t keyTypeSize)
{
	return (memcmp(hashKey, key, keyTypeSize) == 0);
}

void $Deep_UnorderedMap_Create($Deep_UnorderedMap* unorderedMap, size_t keyTypeSize, size_t keyTypeAlignment, size_t valueTypeSize, size_t valueTypeAlignment)
{
	unorderedMap->keyTypeSize = keyTypeSize;
	unorderedMap->valueTypeSize = valueTypeSize;
	unorderedMap->valueTypeAlignment = valueTypeAlignment;
	unorderedMap->keyTypeAlignment = keyTypeAlignment;
	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	unorderedMap->size = 0;

	// Calculate offset for $Deep_UnorderedMap_HashSlot to be stored as a header to the key and value
	// refer to https://youtu.be/IAdLwUXRUvg?t=1716
	unorderedMap->keyOffset = (sizeof(**unorderedMap->hashes) + unorderedMap->keyTypeAlignment - 1) / unorderedMap->keyTypeAlignment * unorderedMap->keyTypeAlignment;
	unorderedMap->valueOffset = ((unorderedMap->keyOffset + sizeof(unorderedMap->keyTypeSize)) + unorderedMap->valueTypeAlignment - 1) / unorderedMap->valueTypeAlignment * unorderedMap->valueTypeAlignment;

	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	unorderedMap->start = NULL;
	unorderedMap->end = NULL;
}

void $Deep_UnorderedMap_Free($Deep_UnorderedMap* unorderedMap)
{
	for (Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL;)
	{
		Deep_UnorderedMap_HashSlot* Old = hashSlot;
		hashSlot = hashSlot->next;
		free(Old);
	}
	free(unorderedMap->hashes);
}

void $Deep_UnorderedMap_ReHash($Deep_UnorderedMap* unorderedMap)
{
	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	{
		size_t newBucketSize = unorderedMap->bucketSize * DEEP_UNORDEREDMAP_GROWTHRATE;
		void* tmp = calloc(newBucketSize, sizeof(*unorderedMap->hashes));
		if (tmp)
		{
			free(unorderedMap->hashes);
			unorderedMap->bucketSize = newBucketSize;
			unorderedMap->hashes = tmp;
			for (Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL; hashSlot = hashSlot->next)
			{
				size_t index = hashSlot->hash % unorderedMap->bucketSize;
				if (unorderedMap->hashes[index] == NULL)
				{
					unorderedMap->hashes[index] = hashSlot;
				}
				else
				{
					Deep_UnorderedMap_HashSlot* tmp = unorderedMap->hashes[index];
					while (tmp->$next != NULL)
					{
						tmp = tmp->$next;
					}
					tmp->$next = hashSlot;
				}
				hashSlot->$next = NULL;
			}
		}
	}
}

// keyCompareFunc returns true if the given key is equal to the hashKey its being compared with,
//     int keyCompareFunc(void* hashKey, void* key, size_t keyTypeSize);
void* $Deep_UnorderedMap_Insert($Deep_UnorderedMap* unorderedMap, size_t hash, void* key, int (*keyCompareFunc)(void*, void*, size_t))
{
	$Deep_UnorderedMap_ReHash(unorderedMap);

	size_t index = hash % unorderedMap->bucketSize;
	if (unorderedMap->hashes[index] == NULL)
	{
		void* tmp = malloc(unorderedMap->valueOffset + unorderedMap->valueTypeSize);
		if (tmp)
		{
			unorderedMap->hashes[index] = tmp;
			unorderedMap->hashes[index]->hash = hash;
			unorderedMap->hashes[index]->$next = NULL;
			unorderedMap->hashes[index]->next = NULL;
			unorderedMap->hashes[index]->prev = unorderedMap->end;
			unorderedMap->size++;
			if (unorderedMap->end != NULL)
				unorderedMap->end->next = unorderedMap->hashes[index];
			unorderedMap->end = unorderedMap->hashes[index];
			if (unorderedMap->start == NULL)
				unorderedMap->start = unorderedMap->hashes[index];
			
			//Set key
			memcpy((unsigned char*)unorderedMap->hashes[index] + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize);

			return (unsigned char*)unorderedMap->hashes[index] + unorderedMap->valueOffset;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->hashes[index];
		while (1)
		{
			if (keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
			{
				return (unsigned char*)hashSlot + unorderedMap->valueOffset;
			}

			if (hashSlot->$next)
				hashSlot = hashSlot->$next;
			else
				break;
		}
		unsigned char* tmp = malloc(unorderedMap->valueOffset + unorderedMap->valueTypeSize);
		if (tmp)
		{
			hashSlot->$next = (void*)tmp;
			hashSlot->$next->hash = hash;
			hashSlot->$next->next = NULL;
			hashSlot->$next->$next = NULL;
			hashSlot->$next->prev = unorderedMap->end;
			unorderedMap->size++;
			unorderedMap->end->next = hashSlot->$next;
			unorderedMap->end = hashSlot->$next;

			//Set key
			memcpy((unsigned char*)hashSlot->$next + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize);

			return (unsigned char*)hashSlot->$next + unorderedMap->valueOffset;
		}
		else
		{
			return NULL;
		}
	}
}

// keyCompareFunc returns true if the given key is equal to the hashKey its being compared with,
//     int keyCompareFunc(void* hashKey, void* key, size_t keyTypeSize);
void $Deep_UnorderedMap_Erase($Deep_UnorderedMap* unorderedMap, size_t hash, void* key, int (*keyCompareFunc)(void*, void*, size_t))
{
	size_t index = hash % unorderedMap->bucketSize;
	if (unorderedMap->hashes[index] != NULL)
	{
		Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->hashes[index];
		Deep_UnorderedMap_HashSlot* prevhashSlot = NULL;
		while (1)
		{
			if (keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
			{
				if (prevhashSlot)
					prevhashSlot->$next = hashSlot->$next;
				else
					unorderedMap->hashes[index] = hashSlot->$next;

				if (hashSlot->prev)
					hashSlot->prev->next = hashSlot->next;
				if (hashSlot->next)
					hashSlot->next->prev = hashSlot->prev;

				free(hashSlot);
				unorderedMap->size--;
				break;
			}

			if (hashSlot->$next)
			{
				prevhashSlot = hashSlot;
				hashSlot = hashSlot->$next;
			}
			else
				break;
		}
	}
}