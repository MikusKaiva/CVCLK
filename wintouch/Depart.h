#pragma once

#include "Coords.h"

public class Depart
{
public:
	static int DetermineLocation();
	static int ClickDepart();

private:
	static bool IsMsg();
	static int ClickBtnDepart();

	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
	static Coords coordsBtnDepart;
};