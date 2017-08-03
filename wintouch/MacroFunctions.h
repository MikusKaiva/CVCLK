#pragma once
#include <string>
#include <vector>

typedef int(*macroFuncType)(void);

struct MacroStep;
static public class MacroFunctions
{
public:
	static int Run(std::string dungName);
	static int RunSequential(std::vector<MacroStep>& sequentialSteps, int stepName);
	static int IsNoxPresent();

	static int isPaused;
	static int isStopped;

private:
	static int MacroFuncCaller(macroFuncType f);
	static int ProcessPauseAndStop();
};



