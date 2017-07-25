#include "test_EShr.h"
#include <opencv2/opencv.hpp>
#include "MacroFunctions.h"

using namespace cv;
using namespace std;

int TestEShr()
{
	// Finding nox
	MacroFunctions macros = MacroFunctions();
	macros.Init(true); // inits only nox
	if (macros.IsNoxPresent() < 0)
		return -1;
	macros.Init(); // inits the rest of macros;
	macros.Run();

	return 0;
}
