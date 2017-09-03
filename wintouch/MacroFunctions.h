#pragma once
#include <string>
#include <vector>

typedef int(*macroFuncType)(void);

struct MacroStep;
public class MacroFunctions
{
public:
	static int Run(std::string dungName);
	static int RunSequential(std::vector<MacroStep>& sequentialSteps, int stepName);

private:
	static int ProcessPauseAndStop();
	static int MacroFuncCaller(macroFuncType f);
};



