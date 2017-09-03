#include "MainWindow.h"
#include <Windows.h>
#include "test_cli_wrap.h"
#include "test_ui_init.h"
#include "Nox.h"
#include "UiInit.h"

namespace ManagedCode
{
	using namespace System;
	using namespace System::Windows;
	using namespace System::Windows::Interop;
	using namespace System::Windows::Media;
	using namespace System::Windows::Controls;

	HWND GetHwnd(HWND parent, int x, int y, int width, int height) {
		HwndSource^ source = gcnew HwndSource(
			0, // class style  
			WS_VISIBLE | WS_CHILD, // style  
			0, // exstyle  
			x, y, width, height,
			"wintouch", // NAME  
			IntPtr(parent)        // parent window      
		);

		ManagedGlobals::w = gcnew TheUI::wintouch(width, height);

		InitApp();
		RunTests();

		source->RootVisual = ManagedGlobals::w;
		return (HWND)source->Handle.ToPointer();
	}

	int InitApp()
	{
		UiInit::Init();
		return 0;
	}

	int RunTests()
	{
		Nox::DetermineLocation();
		//TestUiInit();
		//TestCliWrap();
		return 0;
	}
}