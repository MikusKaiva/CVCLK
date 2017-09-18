#include "MacroFunctions.h"

#include <Windows.h>

#include "Wait.h"

#define PROCESS_PAUSE_AND_STOP if (ProcessPauseAndStop() == STOP_THREAD) return STOP_THREAD

int MacroFunctions::ProcessPauseAndStop()
{
	if (WaitClass::IsStopped())
		return STOP_THREAD;
	while (WaitClass::IsPaused())
	{
		Sleep(250);
		if (WaitClass::IsStopped())
			return STOP_THREAD;
	}
	return 0;
}

int MacroFunctions::MacroFuncCaller(int (*function)(std::string), std::string funcName)
{
	PROCESS_PAUSE_AND_STOP;

	return function(funcName);
}


