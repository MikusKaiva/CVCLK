#include "test_ui_init.h"
#include "MainWindow.h"
#include <process.h>
#include <msclr\marshal_cppstd.h>
#include "Log.h"
#include "MacroFile.h"
#include "MacroFunctions.h"


void OnRunMacro(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
void OnPauseMacro(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
void OnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
int TestUiInit()
{
	using namespace System::Windows::Controls;
	using namespace System::Windows::Controls::Primitives;
	//Button^ b = ManagedCode::ManagedGlobals::w->GetBtn();
	//b->Click += gcnew System::Windows::RoutedEventHandler(&OnClick);
	ManagedCode::ManagedGlobals::w->AddDung("test1");
	ManagedCode::ManagedGlobals::w->AddDung("test2");

	ToggleButton ^btnRunPauseMacro = ManagedCode::ManagedGlobals::w->GetRunPauseMacroBtn();
	btnRunPauseMacro->Checked += gcnew System::Windows::RoutedEventHandler(&OnRunMacro);
	btnRunPauseMacro->Unchecked += gcnew System::Windows::RoutedEventHandler(&OnPauseMacro);

	return 0;
}

unsigned __stdcall MyThread1(void * param) 
{
	System::String^ cliDung = ManagedCode::ManagedGlobals::w->GetSelectedDungName();
	std::string dungName = msclr::interop::marshal_as<std::string>(cliDung);
	LOG("Starting: " + dungName);
	MacroFunctions::Run(dungName);
	return 0;
};

//void OnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
//{
//	unsigned tid1; // thread ID
//	HANDLE hThread1; // thread handle
//	hThread1 = (HANDLE)_beginthreadex(NULL, 0,
//		MyThread1, (void *)NULL,
//		0, &tid1);
//
//}

void OnRunMacro(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	unsigned tid1; // thread ID
	HANDLE hThread1; // thread handle
	hThread1 = (HANDLE)_beginthreadex(NULL, 0,
		MyThread1, (void *)NULL,
		0, &tid1);
}

void OnPauseMacro(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	unsigned tid1; // thread ID
	HANDLE hThread1; // thread handle
	hThread1 = (HANDLE)_beginthreadex(NULL, 0,
		MyThread1, (void *)NULL,
		0, &tid1);
}
