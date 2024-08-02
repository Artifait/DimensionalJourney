#pragma once
#include <unordered_map>

#include "../DataStruct/v2i.h"
#include "Chunk.h"
#include "EngineSettings.h"


namespace DJ
{
    class World
    {
    public:
        World() {
            chunkWidth = EngineSettings::Settings().ChunkWidth();
            chunkHeight = EngineSettings::Settings().ChunkHeight();
            hashChunkSize = EngineSettings::Settings().ChunkSize();
        }

        Block& GetBlock(const v2i& chunkId, const v2i& blockId)
        {
            TestChunk(chunkId);
            return _worldData[chunkId][blockId];
        }

        Block& GetBlock(const v2i& GBID)
        {
            const v2i chunkId = v2i::GetFloorFrom(GBID / hashChunkSize);

            int blockIdX = ((GBID.x < 0) ? chunkWidth : 0) + GBID.x % chunkWidth;
            int blockIdY = ((GBID.y < 0) ? chunkHeight : 0) + GBID.y % chunkHeight;

            const v2i blockId { blockIdX, blockIdY };

            return GetBlock(chunkId, blockId);
        }

    private:
        void TestChunk(v2i chunkId)
        {
            if (_worldData.find(chunkId) == _worldData.end())
            {
                _worldData[chunkId] = Chunk();
            }
        }

    private:
        std::unordered_map<v2i, Chunk> _worldData;
        int chunkWidth;
        int chunkHeight;
        v2i hashChunkSize;
    };
}