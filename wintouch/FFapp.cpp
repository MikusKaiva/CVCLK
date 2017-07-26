#include "FFapp.h"

bool FFapp::IsTitleScreen() { return false; }
bool FFapp::IsHomeScreen() { return false; }
bool FFapp::IsWorldMap() { return false; }
int FFapp::EnterHomeScreen() { return 0; }
int FFapp::EnterWorldMap() { return 0; }
int FFapp::DetermineLocation() { return 0; }

bool FFapp::canGoBack() { return false; }

Coords FFapp::coords = Coords(0, 0, 360, 640, 0, 0);