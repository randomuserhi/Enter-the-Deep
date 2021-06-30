#include "DeepEngine.h"

namespace DeepEngine
{
	Archetype RootArchetype;
	ECSType DefaultComponentArchetype{ DEEP_ECS_COMPONENT, DEEP_ECS_ID };

	int TypeHash(ECSType* Type)
	{
		int Seed = Type->size();
		for (auto& i : *Type) 
		{
			Seed ^= i + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
		}
		return Seed;
	}

	inline Archetype* DeepECS::CreateArchetype(Archetype* Root, ECSHandle Type)
	{
		ECSType NewType = Root->Type;
		NewType.push_back(Type);
		std::sort(NewType.begin(), NewType.end());

		int ArchetypeHash = TypeHash(&NewType);
		
		if (AllocatedArchetypes.find(ArchetypeHash) == AllocatedArchetypes.end())
		{
			Archetype* NewArchetype = new Archetype;
			NewArchetype->Type = NewType;

			AllocatedArchetypes[ArchetypeHash] = NewArchetype;
		}

		return AllocatedArchetypes[ArchetypeHash];
	}

	Archetype* DeepECS::AddArchetype(Archetype* Root, ECSHandle Type)
	{
		Archetype::Edge* Edge = &Root->Edges[Type];
		if (!Edge->Add)
		{
			Edge->Add = CreateArchetype(Root, Type);
		}
		return Edge->Add;
	}

	Archetype* DeepECS::AddArchetype(Archetype* Root, ECSType& Type)
	{
		Archetype* Node = Root;
		for (int i = 0; i < Type.size(); ++i)
		{
			Node = AddArchetype(Node, Type[i]);
		}
		return Node;
	}

	DeepECS::DeepECS()
	{
		//Add Root Archetype
		Hierarchy[DEEP_ECS_NULL].Archetype = &RootArchetype;

		Archetype* DeepEcsComponent = AddArchetype(&RootArchetype, DefaultComponentArchetype);

		ComponentList TempList;

		DeepComponent TempComponent;

		std::vector<DeepComponent>* Components = new std::vector<DeepComponent>();
		TempComponent.Handle = DEEP_ECS_COMPONENT;
		Components->push_back(TempComponent);
		TempComponent.Handle = DEEP_ECS_ID;
		Components->push_back(TempComponent);

		TempList.Elements = Components;
		AllocatedComponents.push_back((void*)Components);
		DeepEcsComponent->Components.push_back(TempList);

		DeepIdentifier TempIdentifier;

		std::vector<DeepIdentifier>* Identifiers = new std::vector<DeepIdentifier>();
		TempIdentifier.Handle = DEEP_ECS_COMPONENT;
		TempIdentifier.Name = "DEEP_ECS_COMPONENT";
		Identifiers->push_back(TempIdentifier);
		TempIdentifier.Handle = DEEP_ECS_ID;
		TempIdentifier.Name = "DEEP_ECS_ID";
		Identifiers->push_back(TempIdentifier);

		TempList.Elements = Identifiers;
		AllocatedComponents.push_back((void*)Identifiers);
		DeepEcsComponent->Components.push_back(TempList);

		Hierarchy[DEEP_ECS_COMPONENT].Archetype = DeepEcsComponent;
		Hierarchy[DEEP_ECS_COMPONENT].Index = 0;
		Hierarchy[DEEP_ECS_ID].Archetype = DeepEcsComponent;
		Hierarchy[DEEP_ECS_ID].Index = 1;

		std::cout << AllocatedArchetypes.size() << '\n';
	}

	DeepECS::~DeepECS()
	{
		//TODO:: After writing proper code for storing Archetypes in memory free them here
		for (void* Pointer : AllocatedComponents)
		{
			free(Pointer);
		}
		for (std::pair<ArchetypeHash, Archetype*> KeyPair : AllocatedArchetypes)
		{
			free(KeyPair.second);
		}
	}
	
	//NOTE:: this returns a pointer to a vector element, this means that once the the vector (Components[i].Elements) expands and is reallocated, the pointer returned is no longer valid.
	//		 This is fine as long as the component is used and the vector remains untouched whilst doing so.
	//	     A fix to this would be to make it return a Handle that is managed (but this can cuck performance).
	//		 The prefered fix would be to return all components (return the vector*) and use the index to access the element.
	//		 This results in less clean code, but it is pointer safe, however, when the storage method of the Archetypes and its Components are changed
	//	     it may no longer be true that the pointer to the vector is always valid as it is now due to a similar reallocation problem.
	template<typename T>
	T* GetComponent(ECSHandle Type, ECSReference Reference)
	{
		for (int i = 0; i < Reference.Archetype->Type.size(); ++i)
		{
			if (Reference.Archetype->Type[i] == Type)
			{
				return &((*(std::vector<T>*)(Reference.Archetype->Components[i].Elements))[Reference.Index]);
			}
		}
		return nullptr;
	}

	void DeepECS::DebugEntityIndex(bool BinaryMode)
	{
		std::cout << "EntityIndex\n{\n";
		for (std::pair<ECSHandle, ECSReference> KeyPair : Hierarchy)
		{
			if (KeyPair.first == DEEP_ECS_NULL) continue;

			std::string Seperator;
			if (BinaryMode) std::cout << '\t' << std::bitset<64>(KeyPair.first) << " : [ ";
			else std::cout << '\t' << GetComponent<DeepIdentifier>(DEEP_ECS_ID, KeyPair.second)->Name << " : [ ";
			for (ECSHandle Entity : KeyPair.second.Archetype->Type)
			{
				if (BinaryMode) std::cout << Seperator << std::bitset<64>(Entity) << " : [ ";
				else std::cout << Seperator << GetComponent<DeepIdentifier>(DEEP_ECS_ID, Hierarchy[Entity])->Name;
				Seperator = ", ";
			}
			std::cout << " ]\n";
		}
		std::cout << "}\n";
	}
}