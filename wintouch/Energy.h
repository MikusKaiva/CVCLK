#pragma once

#include "Coords.h"

public class Energy
{
public:
	static int DetermineLocation();
	static bool IsMsgNoEne();
	static bool IsMsgUseLapis();
	static int ClickBtnBack();
	static int ClickBtnUseLapis();
	static int ClickBtnYes();

private:
	static Coords coordsMsgNoEne;
	static Coords coordsMsgNoEneSearchArea;
	static Coords coordsBtnBack;
	static Coords coordsBtnUseLapis;
	static Coords coordsMsgUseLapis;
	static Coords coordsMsgUseLapisSearchArea;
	static Coords coordsBtnYes;
};