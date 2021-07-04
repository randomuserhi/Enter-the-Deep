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
	typedef uint64_t ArchetypeHash;
	typedef uint64_t ECSHandle;
	typedef std::vector<ECSHandle> ECSType;

	class ArbitaryVector
	{
	public:
		virtual ~ArbitaryVector() {}
		virtual size_t Size() { return 0; }
		virtual int New() { return DEEP_ECS_NULL; }
	};

	template<typename T>
	class ArbitaryVectorDefinition : public ArbitaryVector
	{
	public:
		std::vector<T> Vector;

		//Vector.clear would need to be called here if Vector was a std::vector<destructable> so that the destructor of T is called, otherwise a for loop and delete for std::vector<pointers> etc...
		virtual ~ArbitaryVectorDefinition() {}
		virtual size_t Size() { return Vector.size(); }
		virtual int New() { Vector.push_back({}); return Size() - 1; }
	};

	struct ComponentList
	{
		ArbitaryVector* Elements; //vector<T>*
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

		ComponentList GetComponent(ECSHandle SingleType);
		std::vector<ComponentList> GetComponents(ECSType SubArchetype);
	};

	struct ECSReference
	{
		Archetype* Archetype = nullptr;
		int Index = -1;
	};

	struct DeepComponent
	{
		size_t Size; //sizeof(Component);
	};

	struct DeepIdentifier
	{
		std::string Name = "ECS_NULL";
	};

	class DeepECS
	{
	private:
		Archetype* CreateArchetype(Archetype* Root, ECSHandle Type);
		Archetype* AddArchetype(Archetype* Root, ECSHandle Type);
		Archetype* AddArchetype(Archetype* Root, ECSType& Type);
		ECSHandle GetHandle();

	public:
		std::unordered_map<ECSHandle, ECSReference> Hierarchy; //Contains a hierarchy table of existing entities and their archetype
		std::vector<ArbitaryVector*> AllocatedComponents; //Contains a list of component pointers to free
		std::unordered_map<ArchetypeHash, Archetype*> AllocatedArchetypes; //Contains a list of archetypes

		DeepECS();
		~DeepECS();
		void DebugEntityIndex(bool BinaryMode = false);
		
		template<typename T>
		ECSHandle CreateComponent();
		ECSHandle CreateComponent(size_t Size);

		template<typename T>
		inline T* GetComponent(ECSHandle Handle, ECSHandle Type) { return GetComponent<T>(Hierarchy[Handle], Type); }
		template<typename T>
		T* GetComponent(ECSReference Reference, ECSHandle Type);
	};

	extern Archetype RootArchetype;
	extern ECSType DefaultComponentArchetype;
}