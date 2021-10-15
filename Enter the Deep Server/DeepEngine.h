#pragma once

#include "Deep.h"
#include "DeepContainers.h"

typedef uint64_t ECSHandle;

typedef struct
{
	Deep_UnorderedMap(raw, raw) hierarchy;
} Deep_ECS;
