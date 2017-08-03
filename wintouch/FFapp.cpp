#include "FFapp.h"
#include "Nox.h"
#include "DungeonLocator.h"

bool FFapp::IsTitleScreen() { return false; }
bool FFapp::IsHomeScreen() { return false; }
bool FFapp::IsWorldMap() { return false; }
int FFapp::EnterHomeScreen() { return 0; }
int FFapp::EnterWorldMap() { return 0; }
int FFapp::DetermineLocation() 
{  
	coords.SetOffset(Nox::coords.GetOffsetX(), Nox::coords.GetOffsetY());
	coords.SetX(Nox::coords.GetX1(), Nox::coords.GetX2() - Nox::RIGHT_BAR_WIDTH);
	coords.SetY(Nox::coords.GetY1() + Nox::TOP_BAR_HEIGHT, Nox::coords.GetY2());
	DungeonLocator::DetermineLocation();

	return 0;
}

bool FFapp::CanGoBack() { return false; }

Coords FFapp::coords = Coords(0, 0, 360, 640, 0, 0);