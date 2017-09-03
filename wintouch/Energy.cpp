#include "Energy.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"

Coords Energy::coordsMsgNoEne				= Coords(0, 0, 500, 500); //Random numbers
Coords Energy::coordsMsgNoEneSearchArea		= Coords(0, 0, 500, 500);
Coords Energy::coordsBtnBack				= Coords(0, 0, 500, 500);
Coords Energy::coordsBtnUseLapis			= Coords(0, 0, 500, 500);
Coords Energy::coordsMsgUseLapis			= Coords(0, 0, 500, 500);
Coords Energy::coordsMsgUseLapisSearchArea	= Coords(0, 0, 500, 500);
Coords Energy::coordsBtnYes					= Coords(0, 0, 500, 500);

int Energy::DetermineLocation()
{

	// Energy recovery... Use Item, Use Lapis, Back
	// You can use 100 lapis to fully... No, Yes

	// determine the location of message box, asking to refill energy
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;
	
	coordsMsgNoEne.SetX(x1, x2);
	coordsMsgNoEne.SetY(y1, y2);


	// The area in which to search for Message indicating image
	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsgNoEneSearchArea.SetX(x1, x2);
	coordsMsgNoEneSearchArea.SetY(y1, y2);


	// The location of button to go back
	x1 = coordsMsgNoEne.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = coordsMsgNoEne.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsBtnBack.SetX(x1, x2);
	coordsBtnBack.SetY(y1, y2);


	// The location of button to use lapis for refill
	x1 = coordsMsgNoEne.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	y1 = coordsMsgNoEne.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsBtnUseLapis.SetX(x1, x2);
	coordsBtnUseLapis.SetY(y1, y2);


	// The location of message asking to agree to fill ene using lapis
	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsgUseLapis.SetX(x1, x2);
	coordsMsgUseLapis.SetY(y1, y2);


	// The area in which to search for Message indicating image
	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsgUseLapisSearchArea.SetX(x1, x2);
	coordsMsgUseLapisSearchArea.SetY(y1, y2);


	// The location of button YES to agree to use lapis
	x1 = coordsMsgNoEne.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	y1 = coordsMsgNoEne.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsBtnYes.SetX(x1, x2);
	coordsBtnYes.SetY(y1, y2);


	return 0;
}

bool Energy::IsMsgNoEne()
{
	int x1 = coordsMsgNoEne.GetAbsX1();
	int y1 = coordsMsgNoEne.GetAbsY1();
	int x2 = coordsMsgNoEne.GetAbsX2();
	int y2 = coordsMsgNoEne.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_NO_ENE_MSG, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

bool Energy::IsMsgUseLapis()
{
	int x1 = coordsMsgUseLapis.GetAbsX1();
	int y1 = coordsMsgUseLapis.GetAbsY1();
	int x2 = coordsMsgUseLapis.GetAbsX2();
	int y2 = coordsMsgUseLapis.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_NO_ENE_MSG, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int Energy::ClickBtnBack()
{
	return MouseLeftClick(coordsBtnBack.GetAbsMidX(), coordsBtnBack.GetAbsMidY());
}

int Energy::ClickBtnUseLapis()
{
	return MouseLeftClick(coordsBtnUseLapis.GetAbsMidX(), coordsBtnUseLapis.GetAbsMidY());
}

int Energy::ClickBtnYes()
{
	return MouseLeftClick(coordsBtnYes.GetAbsMidX(), coordsBtnYes.GetAbsMidY());
}
