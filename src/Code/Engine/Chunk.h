#pragma once
#include "EngineSettings.h"
#include "Block.h"

namespace DJ
{
	class Chunk
	{
	public:
		Chunk()
		{
			chunkData = new Block[EngineSettings::Settings().ChunkWidth() * EngineSettings::Settings().ChunkHeight()];
		}

		Block& GetBlock(int x, int y) {
			return chunkData[x + y * EngineSettings::Settings().ChunkWidth()];
		}
		Block& operator[](v2i pos) { return GetBlock(pos.x, pos.y); }

	private:
		Block* chunkData;
	};
}