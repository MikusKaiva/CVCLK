#pragma once

#include "Coords.h"

public class DailyQuestCompleted
{
public:
	static int DetermineLocation();
	static int ClickDailyQuestCompleted();

private:
	static bool IsMsg();
	static int ClickBtnClose();

	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
	static Coords coordsBtnClose;
};