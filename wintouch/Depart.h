#pragma once

#include "Coords.h"

public class Depart
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickBtnDepart();

private:
	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
};