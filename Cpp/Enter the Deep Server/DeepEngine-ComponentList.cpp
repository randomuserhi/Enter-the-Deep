#include "DeepEngine.h"

namespace DeepEngine
{
	ComponentList::ComponentList(size_t TypeSize)
	{
		this->TypeSize = TypeSize;
	}

	ComponentList::~ComponentList()
	{
		free(Data);
	}
}