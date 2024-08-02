#pragma once

#include "World.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_TRANSFORMEDVIEW
#include "olcPGEX_TransformedView.h"

namespace DJ
{
	class Engine : public olc::PixelGameEngine
	{
	public:
		Engine()
		{
			sAppName = "DimensionalJourney V1";
			_currentWorld = new World();
		}
	private:
		olc::TileTransformedView tv;
		World* _currentWorld = nullptr;
		std::unordered_map<v2f, int> hz;

		struct Camera
		{
			DJ::v2f pos;
			DJ::v2f vel;
		} _mainCamera;

	public:
		bool OnUserCreate() override
		{
			tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 32, 32 });
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			if (GetKey(olc::Key::W).bHeld) _mainCamera.vel += { 0.0f, -1.0f };
			if (GetKey(olc::Key::S).bHeld) _mainCamera.vel += { 0.0f, +1.0f };
			if (GetKey(olc::Key::A).bHeld) _mainCamera.vel += { -1.0f, 0.0f };
			if (GetKey(olc::Key::D).bHeld) _mainCamera.vel += { +1.0f, 0.0f };

			if (_mainCamera.vel.Mag2() > 0)
				_mainCamera.vel = _mainCamera.vel.GetNorm() * (GetKey(olc::Key::SHIFT).bHeld ? 5.0f : 2.0f);

			_mainCamera.pos += _mainCamera.vel * fElapsedTime;
			Clear(olc::VERY_DARK_BLUE);

			if (GetMouse(2).bPressed) tv.StartPan(GetMousePos());
			if (GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
			if (GetMouse(2).bReleased) tv.EndPan(GetMousePos());
			if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(2.0f, GetMousePos());
			if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.5f, GetMousePos());

			RenderWorld();
			return true;
		}
		void RenderWorld()
		{
			olc::vi2d vTL = tv.GetTopLeftTile();
			olc::vi2d vBR = tv.GetBottomRightTile();
			olc::vi2d vTile;
			for (vTile.y = vTL.y; vTile.y < vBR.y; vTile.y++)
				for (vTile.x = vTL.x; vTile.x < vBR.x; vTile.x++)
				{
					_currentWorld->GetBlock(vTile);
				}

			tv.DrawCircle(_mainCamera.pos, 5, olc::WHITE);

			if (_mainCamera.vel.Mag2() > 0)
			{
				tv.DrawLine(_mainCamera.pos, _mainCamera.pos + _mainCamera.vel.GetNorm() * 5, olc::MAGENTA);
			}
		}
	};
}