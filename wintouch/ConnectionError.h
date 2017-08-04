#pragma once

#include "Coords.h"

public class ConnectionError
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickBtnOk();

private:
	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
	static Coords coordsBtnOk;
};