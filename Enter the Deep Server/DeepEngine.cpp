#include "DeepEngine.h"

namespace DeepEngine
{
	inline Archetype* DeepECS::CreateArchetype(Archetype* Root, ECSHandle Type)
	{
		Archetype* NewArchetype = new Archetype;
		NewArchetype->Type = Root->Type;
		NewArchetype->Type.push_back(Type);
		std::sort(NewArchetype->Type.begin(), NewArchetype->Type.end());
		return NewArchetype;
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
		DeepEcsComponent->Components.push_back(TempList);

		Hierarchy[DEEP_ECS_COMPONENT].Archetype = DeepEcsComponent;
		Hierarchy[DEEP_ECS_COMPONENT].Index = 0;
		Hierarchy[DEEP_ECS_ID].Archetype = DeepEcsComponent;
		Hierarchy[DEEP_ECS_ID].Index = 1;
	}

	DeepECS::~DeepECS()
	{
		//TODO:: After writing proper code for storing Archetypes in memory free them here
	}
	
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