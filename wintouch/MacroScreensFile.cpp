#include "MacroScreensFile.h"

#include "DesktopCapture.h"
#include "MacroGlobalsFile.h"
#include "Log.h"

std::string MacroScreens::lastScreenName = "unknown";
std::string MacroScreens::lastClickName = "unknown";
std::string MacroScreens::lastDragName = "unknown";
MacroScreens::PropObject MacroScreens::propObject = MacroScreens::obj_screen;
std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int> > > > MacroScreens::imagesToShow = 
	std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int> > > >();
bool MacroScreens::areScreensLoaded = false;

int MacroScreens::StoreData(const std::string& name, const FileReader::unionValue& value)
{
	if (name == "SCREEN")
	{
		if (UniversalFunctions::screenFuncParamDB.find(value.sValue) != UniversalFunctions::screenFuncParamDB.end())
		{
			LOG("Duplicate screen name!");
			return -1;
		}
		UniversalFunctions::screenFuncParameters screenParams;
		InitDefaultValues(screenParams);
		UniversalFunctions::screenFuncParamDB[value.sValue] = screenParams;
		lastScreenName = value.sValue;
		propObject = obj_screen;
		return 0;
	}
	else if (UniversalFunctions::screenFuncParamDB.empty())
	{
		LOG("Screen name should be defined first!");
		return -1;
	}

	if (name == "CLICK")
	{
		if (UniversalFunctions::clickFuncParamDB.find(value.sValue) != UniversalFunctions::clickFuncParamDB.end())
		{
			LOG("Duplicate click name!");
			return -1;
		}
		UniversalFunctions::clickFuncParameters clickParams;
		InitDefaultValues(clickParams);
		UniversalFunctions::clickFuncParamDB[value.sValue] = clickParams;
		lastClickName = value.sValue;
		propObject = obj_click;
	}
	else if (name == "DRAG")
	{
		if (UniversalFunctions::dragFuncParamDB.find(value.sValue) != UniversalFunctions::dragFuncParamDB.end())
		{
			LOG("Duplicate drag name!");
			return -1;
		}
		UniversalFunctions::dragFuncParameters dragParams;
		InitDefaultValues(dragParams);
		UniversalFunctions::dragFuncParamDB[value.sValue] = dragParams;
		lastDragName = value.sValue;
		propObject = obj_drag;
	}
	else
	{
		switch (propObject)
		{
		case MacroScreens::obj_screen:
			return StoreProperty(&UniversalFunctions::screenFuncParamDB[lastScreenName], name, value);
		case MacroScreens::obj_click:
			return StoreProperty(&UniversalFunctions::clickFuncParamDB	[lastClickName	], name, value);
		case MacroScreens::obj_drag:
			return StoreProperty(&UniversalFunctions::dragFuncParamDB	[lastDragName	], name, value);
		default:
			break;
		}
		return -1;
	}
	return 0;
}

int MacroScreens::LoadFile()
{
	int ret = FileReader::LoadFile("macro_screens.dat", StoreData);
	areScreensLoaded = true;
	return ret;
}

int MacroScreens::InitDefaultValues(UniversalFunctions::screenFuncParameters& params)
{
	params.x1Koef = MacroGlobals::X1_KOEF;
	params.x2Koef = MacroGlobals::X2_KOEF;
	params.y1Koef = MacroGlobals::Y1_KOEF;
	params.y2Koef = MacroGlobals::Y2_KOEF;
	params.lookFor = "undefined.png";
	params.horizMiddle = true;
	params.coords = Coords::Coords(	MacroGlobals::X1_REF_POINT + MacroGlobals::HORIZONTAL_UNITS * params.x1Koef / 1000,
									MacroGlobals::Y1_REF_POINT + MacroGlobals::VERTICAL_UNITS	* params.y1Koef / 1000,
									MacroGlobals::X2_REF_POINT - MacroGlobals::HORIZONTAL_UNITS * params.x1Koef / 1000,
									MacroGlobals::Y1_REF_POINT + (params.y1Koef + params.y2Koef) * MacroGlobals::VERTICAL_UNITS / 1000
								  );
	return 0;
}

int MacroScreens::InitDefaultValues(UniversalFunctions::clickFuncParameters& params)
{
	UniversalFunctions::screenFuncParameters& screenParams = UniversalFunctions::screenFuncParamDB[lastScreenName];

	params.x1Koef = screenParams.x1Koef;
	params.x2Koef = screenParams.x2Koef;
	params.y1Koef = screenParams.y1Koef;
	params.y2Koef = screenParams.y2Koef;
	params.horizMiddle = screenParams.horizMiddle;
	params.afterClickTime = MacroGlobals::AFTER_CLICK_TIME;
	params.beforeClickTime = MacroGlobals::BEFORE_CLICK_TIME;
	params.coords = Coords::Coords(screenParams.coords.GetX1(), screenParams.coords.GetY1(), screenParams.coords.GetX2(), screenParams.coords.GetY2());
	return 0;
}

int MacroScreens::InitDefaultValues(UniversalFunctions::dragFuncParameters & params)
{
	UniversalFunctions::screenFuncParameters& screenParams = UniversalFunctions::screenFuncParamDB[lastScreenName];

	params.x1Koef = screenParams.x1Koef;
	params.x2Koef = screenParams.x2Koef;
	params.y1Koef = screenParams.y1Koef;
	params.y2Koef = screenParams.y2Koef;
	params.horizMiddle = screenParams.horizMiddle;
	params.afterClickTime = MacroGlobals::AFTER_CLICK_TIME;
	params.beforeClickTime = MacroGlobals::BEFORE_CLICK_TIME;
	params.xDragKoef = 0;
	params.yDragKoef = 0;
	params.coords = Coords::Coords(screenParams.coords.GetX1(), screenParams.coords.GetY1(), screenParams.coords.GetX2(), screenParams.coords.GetY2());
	return 0;
}

int MacroScreens::StoreProperty(UniversalFunctions::screenFuncParameters* params, const std::string& name, const FileReader::unionValue& value)
{
	if (name == "LOOK_FOR")
	{
		params->lookFor = value.sValue;
	}
	else
	{
		return StoreProperty((UniversalFunctions::funcLocationParameters*)params, name, value);
	}

	return 0;
}

int MacroScreens::StoreProperty(UniversalFunctions::clickFuncParameters* params, const std::string& name, const FileReader::unionValue& value)
{
	if (StoreProperty((UniversalFunctions::funcLocationParameters*)params, name, value) < 0)
	{
		return StoreProperty((UniversalFunctions::funcActionParameters*)params, name, value);
	}

	return 0;
}

int MacroScreens::StoreProperty(UniversalFunctions::dragFuncParameters* params, const std::string& name, const FileReader::unionValue& value)
{
	if (name == "X_DRAG_KOEF")
	{
		params->xDragKoef = value.iValue;
	}
	else if (name == "Y_DRAG_KOEF")
	{
		params->yDragKoef = value.iValue;
	}
	else if (StoreProperty((UniversalFunctions::funcLocationParameters*)params, name, value) < 0)
	{
		return StoreProperty((UniversalFunctions::funcActionParameters*)params, name, value);
	}
	return 0;
}

int MacroScreens::StoreProperty(UniversalFunctions::funcLocationParameters* params, const std::string& name, const FileReader::unionValue& value)
{
	if (name == "X1_KOEF")
	{
		params->x1Koef = value.iValue;
		int x1 = MacroGlobals::X1_REF_POINT + MacroGlobals::HORIZONTAL_UNITS * params->x1Koef / 1000;
		int x2 = 0;
		if (params->horizMiddle)
		{
			x2 = MacroGlobals::X2_REF_POINT - MacroGlobals::HORIZONTAL_UNITS * params->x1Koef / 1000;
		}
		else
		{
			x2 = x1 + MacroGlobals::HORIZONTAL_UNITS * params->x2Koef / 1000;
		}
		params->coords.SetX(x1, x2);
	}
	else if (name == "X2_KOEF")
	{
		params->x2Koef = value.iValue;
		if (!params->horizMiddle)
		{
			params->coords.SetX(params->coords.GetX1(), params->coords.GetX1() + MacroGlobals::HORIZONTAL_UNITS * params->x2Koef / 1000);
		}
	}
	else if (name == "Y1_KOEF")
	{
		params->y1Koef = value.iValue;
		int y1 = MacroGlobals::Y1_REF_POINT + MacroGlobals::VERTICAL_UNITS * params->y1Koef / 1000;
		params->coords.SetY(y1, y1 + MacroGlobals::VERTICAL_UNITS * params->y2Koef / 1000);
	}
	else if (name == "Y2_KOEF")
	{
		params->y2Koef = value.iValue;
		params->coords.SetY(params->coords.GetY1(), params->coords.GetY1() + MacroGlobals::VERTICAL_UNITS * params->y2Koef / 1000);
	}
	else if (name == "HORIZ_MIDDLE")
	{
		params->horizMiddle = (bool)value.iValue;
		int x1 = params->coords.GetX1();
		int x2 = 0;
		if (params->horizMiddle)
		{
			x2 = MacroGlobals::X2_REF_POINT - MacroGlobals::HORIZONTAL_UNITS * params->x1Koef / 1000;
		}
		else
		{
			x2 = x1 + MacroGlobals::HORIZONTAL_UNITS * params->x2Koef / 1000;
		}
		params->coords.SetX(x1, x2);
	}
	else if (name == "SHOW")
	{
		if (value.iValue == 1)
		{
			imagesToShow.push_back( std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int> > >(
				std::string(lastScreenName), std::pair<std::pair<int, int>, std::pair<int, int> >(
					std::pair<int, int>(params->coords.GetAbsX1(), params->coords.GetAbsX2()),
					std::pair<int, int>(params->coords.GetAbsY1(), params->coords.GetAbsY2()) 
				))
			);
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int MacroScreens::StoreProperty(UniversalFunctions::funcActionParameters* params, const std::string& name, const FileReader::unionValue& value)
{
	if (name == "AFTER_CLICK_TIME")
	{
		params->afterClickTime = value.iValue;
	}
	if (name == "BEFORE_CLICK_TIME")
	{
		params->beforeClickTime = value.iValue;
	}

	return 0;
}
