#include "test_ui_init.h"
#include "MainWindow.h"
#include <process.h>
#include "Log.h"

void OnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
int TestUiInit()
{
	//ManagedCode::ManagedGlobals::w->MyButtonValue = "12";
	using namespace System::Windows::Controls;
	Button^ b = ManagedCode::ManagedGlobals::w->GetBtn();
	b->Click += gcnew System::Windows::RoutedEventHandler(&OnClick);
	return 0;
}

unsigned __stdcall MyThread1(void * param) { LOG("Button clicked!"); Sleep(5000); return 0; };

void OnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	unsigned tid1; // thread ID
	HANDLE hThread1; // thread handle

	hThread1 = (HANDLE)_beginthreadex(NULL, 0,
		MyThread1, (void *)NULL,
		0, &tid1);

}
