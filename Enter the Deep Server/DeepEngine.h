#pragma once

#include <iostream> //Probs should do a IFDEF thing to not include this when not debugging
#include <bitset> //Probs should do a IFDEF thing to not include this when not debugging
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "DeepMath.h"

//ECS archetype design: https://ajmmertens.medium.com/building-an-ecs-1-types-hierarchies-and-prefabs-9f07666a1e9d

//DeepECS uses a specific bit pattern for identification:
//

#define DEEP_ECS_NULL 0 //Null entity
#define DEEP_ECS_COMPONENT 0b100000000 //EntityHandle given to Components
#define DEEP_ECS_ID 0b1000000000 //Component used for providing a name to entities (for readability)

//Type flags
#define DEEP_ECS_ENTITY_MASK 0b1111111111111111111111111111111111111111111111111111111100000000 //Mask to provide Entity ID handle
#define DEEP_ECS_CHILDOF 0b1 //This entity is a child of <EntityHandle> provided
#define DEEP_ECS_INSTANCEOF 0b10 //This entity is an instance of <EntityHandle> provided

namespace DeepEngine
{
	typedef uint64_t ECSHandle;
	typedef std::vector<ECSHandle> ECSType;

	struct ComponentList
	{
		void* Elements; //vector<T>*
	};

	struct Archetype
	{
		struct Edge
		{
			Archetype* Add;
			Archetype* Remove;
		};

		ECSType Type;
		std::vector<ECSHandle> Handles;
		std::vector<ComponentList> Components;
		std::unordered_map<ECSHandle, Edge> Edges;
	};

	struct ECSReference
	{
		Archetype* Archetype;
		int Index;
	};

	struct DeepComponent
	{
		ECSHandle Handle;
		size_t Size;
	};

	struct DeepIdentifier
	{
		ECSHandle Handle;
		std::string Name = "ECS_NULL";
	};

	struct DeepECS
	{
		std::unordered_map<ECSHandle, ECSReference> Hierarchy; //Contains a hierarchy table of existing entities and their archetype

		DeepECS();
		~DeepECS();
		void DebugEntityIndex(bool BinaryMode = false);

		inline Archetype* CreateArchetype(Archetype* Root, ECSHandle Type);
		Archetype* AddArchetype(Archetype* Root, ECSHandle Type);
		Archetype* AddArchetype(Archetype* Root, ECSType& Type);
	};

	static Archetype RootArchetype;
	static ECSType DefaultComponentArchetype { DEEP_ECS_COMPONENT, DEEP_ECS_ID };
}