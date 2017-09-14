#include "UniversalFunctions.h"

#include "FindImage.h"
#include "Log.h"
#include "MouseControl.h"
#include "MacroFunctions.h"
#include "Wait.h"

std::map<std::string, UniversalFunctions::screenFuncParameters	>UniversalFunctions::screenFuncParamDB	= std::map<std::string, UniversalFunctions::screenFuncParameters>();
std::map<std::string, UniversalFunctions::clickFuncParameters	>UniversalFunctions::clickFuncParamDB	= std::map<std::string, UniversalFunctions::clickFuncParameters	>();
std::map<std::string, UniversalFunctions::dragFuncParameters	>UniversalFunctions::dragFuncParamDB	= std::map<std::string, UniversalFunctions::dragFuncParameters	>();
std::map<std::string, UniversalFunctions::stepFuncParameters	>UniversalFunctions::stepFuncParamDB	= std::map<std::string, UniversalFunctions::stepFuncParameters	>();
std::map<std::string, UniversalFunctions::loopFuncParameters	>UniversalFunctions::loopFuncParamDB	= std::map<std::string, UniversalFunctions::loopFuncParameters	>();

bool UniversalFunctions::UniversalScreenFunction(std::string funcName)
{
	screenFuncParameters params = screenFuncParamDB[funcName];
	int x1 = params.coords.GetAbsX1();
	int y1 = params.coords.GetAbsY1();
	int x2 = params.coords.GetAbsX2();
	int y2 = params.coords.GetAbsY2();

	if (FindImageInPartOfDesktop(params.lookFor, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int UniversalFunctions::UniversalClickFunction(std::string funcName)
{
	clickFuncParameters params = clickFuncParamDB[funcName];

	if (params.beforeClickTime > 0)
		WaitClass::Wait(params.beforeClickTime);
	int ret = MouseLeftClick(params.coords.GetAbsMidX(), params.coords.GetAbsMidY());
	if (params.afterClickTime > 0)
		WaitClass::Wait(params.afterClickTime);

	return ret;
}

int UniversalFunctions::UniversalDragFunction(std::string funcName)
{
	dragFuncParameters params = dragFuncParamDB[funcName];
	int ret = -1;
	if (params.beforeClickTime > 0)
		WaitClass::Wait(params.afterClickTime);

	ret = SetMousePosition(params.coords.GetAbsMidX(), params.coords.GetAbsMidY());

	if (ret == 0)
	{
		ret = MouseLeftDown();
	}

	if (ret == 0)
	{
		ret = MoveMouseTo(params.coords.GetAbsMidX(), params.coords.GetAbsMidY() + params.coords.GetVertUnits() * params.yDragKoef, 500);
	}

	if (ret == 0)
	{
		ret = MouseLeftUp();
	}

	if (params.afterClickTime > 0)
		WaitClass::Wait(params.afterClickTime);

	return ret;
}

int UniversalFunctions::UniversalStepFunction(std::string funcName)
{
	stepFuncParameters params = stepFuncParamDB[funcName];
	bool isRetAssigned = false;
	bool done = false;
	bool repeat = false;

	do
	{
		isRetAssigned = false;
		repeat = false;
		for (std::pair<fType, stepFuncArgs> step : params.steps)
		{
			switch (step.first)
			{
			case f_screen:
			{
				if (params.succ)
					params.succ = UniversalScreenFunction(step.second.sParam);
				break;
			}
			case f_click:
			{
				if (params.succ)
					UniversalClickFunction(step.second.sParam);
				break;
			}
			case f_drag:
			{
				if (params.succ)
					UniversalDragFunction(step.second.sParam);
				break;
			}
			case f_step:
			{
				if (params.succ)
				{
					params.ret = UniversalStepFunction(step.second.sParam);
					isRetAssigned = true;
				}
				break;
			}
			case f_MaxWait:
			{
				if (params.ret == 0)
					params.maxWait = step.second.iParam;
				break;
			}
			case f_Wait:
			{
				if (params.succ)
					params.maxWait -= step.second.iParam;
				break;
			}
			case f_Return:
			{
				if (params.succ)
					done = true;
				break;
			}
			case f_Reset:
			{
				if (step.second.sParam == "SUCC")
					params.succ = 1;
				else if (step.second.sParam == "RET")
				{
					params.ret = -1;
					isRetAssigned = false;
				}
				break;
			}
			case f_Ret:
			{
				if (params.succ)
				{
					params.ret = 0;
					isRetAssigned = true;
				}
				break;
			}
			case f_Next:
			{
				if (params.succ)
					repeat = true;
				break;
			}
			default:
			{
				done = true;
				break;
			} }

			if (done || repeat) break;
		}
		//if commands f_Ret or f_step are never called, SUCC value will be used to determine RET
		if (!isRetAssigned) params.ret = params.succ ? 0 : -1;
	} while ((params.maxWait > 0 && !done && params.ret != 0) || repeat);

	return params.ret;
}

int UniversalFunctions::UniversalLoopFunction(std::string funcName)
{
	loopFuncParameters params = loopFuncParamDB[funcName];
	int failures = 0;
	int ret = -1;

	do {
		for (std::pair<std::string, std::string> step : params.steps)
		{
			ret = MacroFunctions::MacroFuncCaller(UniversalStepFunction, step.first);
			if (ret == 0)
			{
				failures = 0;
				if (!step.second.empty())
				{
					ret = MacroFunctions::MacroFuncCaller(UniversalStepFunction, step.second);
				}
			}
			if (ret == STOP_THREAD)
			{
				return ret;
			}
			else failures++;
		}
		failures++; // just to exit loop in case inner loop crashes
	} while (failures / params.steps.size() < params.maxFailures);

	LOG("Max Failure count reached, stopping.. " + funcName);

	return ret;
}

