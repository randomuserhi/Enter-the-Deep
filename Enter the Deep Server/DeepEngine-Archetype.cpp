#include "DeepEngine.h"

namespace DeepEngine
{
	ComponentList Archetype::GetComponent(ECSHandle SingleType)
	{
		for (int i = 0; i < Type.size(); ++i)
		{
			if (Type[i] == SingleType) return Components[i];
		}
		return {};
	}
}