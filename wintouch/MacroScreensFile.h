#pragma once

#include "FileReader.h"

#include "UniversalFunctions.h"

class MacroScreens
{
public:
	static int StoreData(const std::string& name, const FileReader::unionValue& value);
	static int LoadFile();
	//name, x1, x2, y1, y2
	static std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int> > > > imagesToShow;
	static bool areScreensLoaded;
private:
	enum PropObject
	{
		obj_screen
		, obj_click
		, obj_drag
	};
	static int InitDefaultValues(UniversalFunctions::screenFuncParameters&	params);
	static int InitDefaultValues(UniversalFunctions::clickFuncParameters&	params);
	static int InitDefaultValues(UniversalFunctions::dragFuncParameters&	params);

	static int StoreProperty(UniversalFunctions::screenFuncParameters*		params, const std::string& name, const FileReader::unionValue& value);
	static int StoreProperty(UniversalFunctions::clickFuncParameters*		params, const std::string& name, const FileReader::unionValue& value);
	static int StoreProperty(UniversalFunctions::dragFuncParameters*		params, const std::string& name, const FileReader::unionValue& value);
	static int StoreProperty(UniversalFunctions::funcLocationParameters*	params, const std::string& name, const FileReader::unionValue& value);
	static int StoreProperty(UniversalFunctions::funcActionParameters*		params, const std::string& name, const FileReader::unionValue& value);

	static std::string lastScreenName;
	static std::string lastClickName;
	static std::string lastDragName;
	static PropObject propObject;
};
