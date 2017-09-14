#pragma once

#include <map>
#include <vector>
#include <string>

#include "Coords.h"

class UniversalFunctions
{
public:
	struct stepFuncArgs
	{
		int iParam;
		std::string sParam;
	};
	enum fType
	{
		f_screen,	// screen search function
		f_click,	// mouse click function
		f_drag,		// mouse drag function
		f_step,		// step function, which includes set of screen, click, drag functions and timed loop
		f_MaxWait,	// used in f_step, set max time to perform loop
		f_Wait,		// used in f_step, wait in looop
		f_Return,	// used in f_step, quit loop and return value
		f_Reset,	// used in f_step, resets "return value" or "step succeed" to default value
		f_Ret,		// used in f_step, puts "step succeed" in "return value"
		f_Next
	};
	struct funcLocationParameters
	{
		int x1Koef;
		int x2Koef;
		int y1Koef;
		int y2Koef;
		bool horizMiddle;
		Coords coords;
	};
	struct funcActionParameters
	{
		int afterClickTime;
		int beforeClickTime;
	};
	struct screenFuncParameters : public funcLocationParameters
	{
		std::string lookFor;
	};
	struct clickFuncParameters : public funcLocationParameters, public funcActionParameters
	{
	};
	struct dragFuncParameters : public funcLocationParameters, public funcActionParameters
	{
		int xDragKoef;
		int yDragKoef;
	};
	struct stepFuncParameters
	{
		int maxWait;
		std::vector<std::pair<fType, stepFuncArgs> > steps;
		int ret;
		bool succ;
	};
	struct loopFuncParameters
	{
		int maxFailures;
		std::vector<std::pair<std::string, std::string> > steps;
	};

	static std::map<std::string, screenFuncParameters	>screenFuncParamDB;
	static std::map<std::string, clickFuncParameters	>clickFuncParamDB;
	static std::map<std::string, dragFuncParameters		>dragFuncParamDB;
	static std::map<std::string, stepFuncParameters		>stepFuncParamDB;
	static std::map<std::string, loopFuncParameters		>loopFuncParamDB;

	static bool UniversalScreenFunction	(std::string funcName);
	static int UniversalClickFunction	(std::string funcName);
	static int UniversalDragFunction	(std::string funcName);
	static int UniversalStepFunction	(std::string funcName);
	static int UniversalLoopFunction	(std::string funcName);

};