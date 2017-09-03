#pragma once

#include "Coords.h"

public class ConnectionError
{
public:
	static int DetermineLocation();
	static int ClickConnectionError();

private:
	static bool IsMsg();
	static int ClickBtnOk();

	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
	static Coords coordsBtnOk;
};