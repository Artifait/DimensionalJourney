#pragma once
#include <unordered_map>

#include "../DataStruct/v2f.h"
#include "Chunk.h"

namespace DJ
{
	class World
	{
	public:

	private:
		std::unordered_map<v2f, Chunk> _worldData;

	};
}