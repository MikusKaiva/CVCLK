#pragma once

#include "Coords.h"

public class DailyQuestCompleted
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickBtnClose();

private:
	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
	static Coords coordsBtnClose;
};