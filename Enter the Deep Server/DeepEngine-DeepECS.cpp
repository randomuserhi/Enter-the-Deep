#include "DeepEngine.h"

namespace DeepEngine
{
	Archetype RootArchetype;
	Archetype* ComponentArchetype = nullptr;
	ECSType DefaultComponentArchetype{ DEEP_ECS_COMPONENT, DEEP_ECS_ID };

	ArchetypeHash TypeHash(ECSType* Type) //TODO:: this hash function needs to change as it doesnt fully support ECSHandle being 64 bit => i is of type uint64 but Seed is of type int32
	{
		ArchetypeHash Seed = Type->size();
		for (auto& i : *Type) 
		{
			Seed ^= i + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
		}
		return Seed;
	}

	Archetype* DeepECS::CreateArchetype(Archetype* Root, ECSHandle Type)
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

		//Add the key component archetypes
		ComponentArchetype = AddArchetype(&RootArchetype, DefaultComponentArchetype);

		ComponentList TempList;

		DeepComponent TempComponent;

		ArbitaryVectorDefinition<DeepComponent>* Components = new ArbitaryVectorDefinition<DeepComponent>();
		TempComponent.Size = sizeof(DeepComponent);
		Components->Vector.push_back(TempComponent);
		TempComponent.Size = sizeof(DeepIdentifier);
		Components->Vector.push_back(TempComponent);

		TempList.Elements = Components;
		AllocatedComponents.push_back(Components);
		ComponentArchetype->Components.push_back(TempList);
		ComponentArchetype->Handles.push_back(DEEP_ECS_COMPONENT);

		DeepIdentifier TempIdentifier;

		ArbitaryVectorDefinition<DeepIdentifier>* Identifiers = new ArbitaryVectorDefinition<DeepIdentifier>();
		TempIdentifier.Name = "DEEP_ECS_COMPONENT";
		Identifiers->Vector.push_back(TempIdentifier);
		TempIdentifier.Name = "DEEP_ECS_ID";
		Identifiers->Vector.push_back(TempIdentifier);

		TempList.Elements = Identifiers;
		AllocatedComponents.push_back(Identifiers);
		ComponentArchetype->Components.push_back(TempList);
		ComponentArchetype->Handles.push_back(DEEP_ECS_ID);

		Hierarchy[DEEP_ECS_COMPONENT].Archetype = ComponentArchetype;
		Hierarchy[DEEP_ECS_COMPONENT].Index = 0;
		Hierarchy[DEEP_ECS_ID].Archetype = ComponentArchetype;
		Hierarchy[DEEP_ECS_ID].Index = 1;
	}

	DeepECS::~DeepECS()
	{
		for (ArbitaryVector* Pointer : AllocatedComponents)
		{
			delete Pointer;
		}
		for (std::pair<ArchetypeHash, Archetype*> KeyPair : AllocatedArchetypes)
		{
			delete KeyPair.second;
		}
	}
	
	ECSHandle DeepECS::GetHandle() //TODO:: this needs changing for obvious reasons
	{
		static ECSHandle Value = DEEP_ECS_ID; //shared across all instances of DeepECS => kinda problematic in a way
		return Value + 0b100000000;
	}

	template<typename T>
	ECSHandle DeepECS::CreateComponent()
	{
		ECSHandle Handle = GetHandle();
		//std::cout << std::bitset<64>(Handle) << '\n';

		ECSReference* Ref = &Hierarchy[Handle];
		Ref->Archetype = ComponentArchetype;
		Ref->Index = ComponentArchetype->Components[0].Elements->New();
		ComponentArchetype->Components[1].Elements->New();
		ComponentArchetype->Handles.push_back(Handle);
		DeepComponent* Component = DeepECS_GetComponent<DeepComponent>(Handle, *Ref);
		Component->Size = sizeof(T);

		return Handle;
	}

	ECSHandle DeepECS::CreateComponent(size_t Size)
	{
		ECSHandle Handle = GetHandle();
		//std::cout << std::bitset<64>(Handle) << '\n';

		ECSReference* Ref = &Hierarchy[Handle];
		Ref->Archetype = ComponentArchetype;
		Ref->Index = ComponentArchetype->Components[0].Elements->New();
		ComponentArchetype->Components[1].Elements->New();
		ComponentArchetype->Handles.push_back(Handle);
		GetComponent<DeepComponent>(*Ref, DEEP_ECS_COMPONENT)->Size = Size;

		return Handle;
	}

	//NOTE:: this returns a pointer to a vector element, this means that once the the vector (Components[i].Elements) expands and is reallocated, the pointer returned is no longer valid.
	//		 This is fine as long as the component is used and the vector remains untouched whilst doing so.
	//	     A fix to this would be to make it return a Handle that is managed (but this can cuck performance).
	//		 The prefered fix would be to return all components (return the vector*) and use the index to access the element.
	//		 This results in less clean code, but it is pointer safe, however, when the storage method of the Archetypes and its Components are changed
	//	     it may no longer be true that the pointer to the vector is always valid due to a similar reallocation problem.
	template<typename T>
	T* DeepECS::GetComponent(ECSReference Reference, ECSHandle Type)
	{
		for (int i = 0; i < Reference.Archetype->Type.size(); ++i)
		{
			if (Reference.Archetype->Type[i] == Type)
			{
				return &((*(ArbitaryVectorDefinition<T>*)(Reference.Archetype->Components[i].Elements)).Vector[Reference.Index]);
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
			else std::cout << '\t' << GetComponent<DeepIdentifier>(KeyPair.second, DEEP_ECS_ID)->Name << " : [ ";
			for (ECSHandle Entity : KeyPair.second.Archetype->Type)
			{
				if (BinaryMode) std::cout << Seperator << std::bitset<64>(Entity) << " : [ ";
				else std::cout << Seperator << GetComponent<DeepIdentifier>(Hierarchy[Entity], DEEP_ECS_ID)->Name;
				Seperator = ", ";
			}
			std::cout << " ]\n";
		}
		std::cout << "}\n";
	}
}