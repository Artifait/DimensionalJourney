#pragma once
#include "olcPixelGameEngine.h"
#include "World.h"

#define OLC_PGEX_TRANSFORMEDVIEW
#include "olcPGEX_TransformedView.h"

namespace DJ
{
	class Engine
	{
	public:
		void RenderWorld(olc::TileTransformedView& tv)
		{
			
		}
	private:
		World* _currentWorld = nullptr;
	};
}