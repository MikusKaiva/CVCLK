#include "Nox.h"

int Nox::Start() { return 0; }
int Nox::StartApp(std::string appName) { return 0; }
bool Nox::IsRunning() { return true; }
int Nox::DetermineLocation() { return 0; }

Coords Nox::coords = Coords(0, 0, 360, 640, 0, 0);