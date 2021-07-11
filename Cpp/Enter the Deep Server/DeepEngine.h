#pragma once

#include <iostream> //Probs should do a IFDEF thing to not include this when not debugging
#include <bitset> //Probs should do a IFDEF thing to not include this when not debugging
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "DeepMath.h"

//ECS archetype design: https://ajmmertens.medium.com/building-an-ecs-1-types-hierarchies-and-prefabs-9f07666a1e9d

//DeepEngine storage values
#define DEEP_ECS_DYNAMIC_SIZE 3 //Default size for dynamic arrays (component storage)

#define DEEP_ECS_DYNAMIC_NOERROR 0
#define DEEP_ECS_DYNAMIC_NULL 1 //The component list storage is of type null (generated when size is unknown and thus storage is invalid)
#define DEEP_ECS_DYNAMIC_ERROR_MALLOC 2 //Malloc failed
#define DEEP_ECS_DYNAMIC_ERROR_ALIGNMENT 3 //sizeof(Type) was note equal to size of elements

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
		virtual size_t New() { return DEEP_ECS_NULL; }
	};

	template<typename T>
	class ArbitaryVectorDefinition : public ArbitaryVector
	{
	public:
		std::vector<T> Vector;

		//Vector.clear would need to be called here if Vector was a std::vector<destructable> so that the destructor of T is called, otherwise a for loop and delete for std::vector<pointers> etc...
		virtual ~ArbitaryVectorDefinition() {}
		virtual size_t Size() { return Vector.size(); }
		virtual size_t New() { Vector.push_back({}); return Size() - 1; }
	};

	class ComponentList
	{
	private:
		unsigned char* Data = nullptr; //Pointer to data
		unsigned char* End = nullptr;
		size_t TypeSize = 0; //Size of type
		size_t Capacity = 0;

	public:
		ComponentList() {} //Essentially null component list
		ComponentList(size_t TypeSize);
		~ComponentList();

		int Reserve(int Num)
		{
			if (Data == nullptr)// [[unlikely]]
			{
				unsigned char* Temp = (unsigned char*)malloc(TypeSize * DEEP_ECS_DYNAMIC_SIZE);
				//TODO:: handle malloc error
				Capacity = TypeSize * DEEP_ECS_DYNAMIC_SIZE;
				Data = Temp;
				End = Data;
			}
			else if (Size() + Num * TypeSize >= Capacity)
			{
				size_t NewCapacity = Size() + Num * TypeSize;
				unsigned char* Temp = (unsigned char*)realloc(Data, NewCapacity);
				//TODO:: handle realloc error
				Data = Temp;
				End = Data + Capacity;
				Capacity = NewCapacity;
				//std::cout << Capacity << ", Grow\n";
			}

			End += TypeSize * Num;

			return DEEP_ECS_DYNAMIC_NOERROR;
		}

		template<typename T>
		int Add(T Item) //Micro optimization might be to do with branch prediction : https://stackoverflow.com/questions/3702903/portable-branch-prediction-hints 
						//														    => http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0479r0.html (implemented in VC2019)
						//															Make sure to profile this as branch prediction is mostly done in PBO and this can hinder performance if I am wrong
						//															https://timsong-cpp.github.io/cppwp/dcl.attr.likelihood
						//															https://godbolt.org/z/EvsG4csY5
						//															Kinda a big problem:
						//															https://stackoverflow.com/questions/68276728/msvc-c-compiler-being-inconsistent-when-using-unlikely-likely-attributes
						//															Turns out this is a problem with '/Gy' (function level linking), if its off '/Gy-' Then it works fine, but /O2 implies /Gy
						//															This problem seems to root deep man...
		{
			if (TypeSize == 0)// [[unlikely]]
			{
				return DEEP_ECS_DYNAMIC_NULL;
			}
			if (TypeSize != sizeof(T))// [[unlikely]]
			{
				return DEEP_ECS_DYNAMIC_ERROR_ALIGNMENT;
			}

			if (Data == nullptr)// [[unlikely]]
			{
				unsigned char* Temp = (unsigned char*)malloc(TypeSize * DEEP_ECS_DYNAMIC_SIZE);
				//TODO:: handle malloc error
				Capacity = TypeSize * DEEP_ECS_DYNAMIC_SIZE;
				Data = Temp;
				End = Data;
			}
			else if (Size() == Capacity)
			{
				size_t NewCapacity = (size_t)((Capacity / TypeSize) * 1.5);
				NewCapacity *= TypeSize;
				unsigned char* Temp = (unsigned char*)realloc(Data, NewCapacity);
				if (Temp == nullptr) return DEEP_ECS_DYNAMIC_ERROR_MALLOC;
				Data = Temp;
				End = Data + Capacity;
				Capacity = NewCapacity;
				std::cout << Capacity << ", Grow\n";
			}

			*((T*)End) = Item;

			End += TypeSize;

			return DEEP_ECS_DYNAMIC_NOERROR;
		}

		template<typename T>
		inline size_t Size() { return (T*)End - (T*)Data; }
		inline size_t Size() { return End - Data; }
		
		template<typename T>
		T& Get(size_t Index)
		{
			return ((T*)Data)[Index];
		}

		ArbitaryVector* Elements; //vector<T>* => this will be refactored later to have my own storage mechanism
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
		size_t Index = -1;
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