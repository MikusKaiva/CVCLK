#pragma once
#include <string>
#include <vector>

struct MacroStep;
static public class MacroFunctions
{
public:
	static int Run(std::string dungName);
	static int RunSequential(std::vector<MacroStep>& sequentialSteps, int stepName);
	static int IsNoxPresent();

};



