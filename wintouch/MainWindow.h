#pragma once
#include <Windows.h>

namespace ManagedCode
{
	public ref class ManagedGlobals {
	public:
		static TheUI::wintouch^ w;
	};
	HWND GetHwnd(HWND parent, int x, int y, int width, int height);
	int InitApp();
	int RunTests();
	
}
