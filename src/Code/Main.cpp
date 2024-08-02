
#include "Engine/GameEngine.h"

int main()
{
	DJ::Engine demo;
	if (demo.Construct(640, 480, 2, 2))
		demo.Start();

	return 0;
}