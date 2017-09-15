#include "UiInit.h"

#include <process.h>
#include <msclr\marshal_cppstd.h>

#include "MainWindow.h"
#include "Nox.h"
#include "Log.h"
#include "Wait.h"

#include "MacroConstantFile.h"
#include "MacroGlobalsFile.h"
#include "MacroRelativeFile.h"
#include "MacroScreensFile.h"
#include "MacroStepsFile.h"
#include "MacroLoopsFile.h"
#include "UniversalFunctions.h"
#include "DesktopCapture.h"
#include "Coords.h"

void UiInit::Init()
{
	unsigned tid; // thread ID
	HANDLE hThread; // thread handle

	hThread = (HANDLE)_beginthreadex(NULL, 0,
		UiInitThread, (void *)NULL,
		0, &tid);
}


unsigned __stdcall UiInit::UiInitThread(void * param)
{ 
	if (   MacroConstants	::LoadFile() < 0
		|| MacroRelative	::LoadFile() < 0
		|| MacroGlobals		::LoadFile() < 0
		|| MacroScreens		::LoadFile() < 0
		|| MacroStepsF		::LoadFile() < 0
		|| MacroLoops		::LoadFile() < 0
		) return 0;

	for (std::pair<std::string, UniversalFunctions::loopFuncParameters> loop : UniversalFunctions::loopFuncParamDB)
	{
		System::String^ cliLoop = msclr::interop::marshal_as<System::String^>(loop.first);
		ManagedCode::ManagedGlobals::w->AddDung(cliLoop);
	}

	for (std::pair<std::string, UniversalFunctions::screenFuncParameters> screen : UniversalFunctions::screenFuncParamDB)
	{
		System::String^ cliScreen = msclr::interop::marshal_as<System::String^>(screen.first);
		ManagedCode::ManagedGlobals::w->AddScreen(cliScreen);
	}

	for (std::pair<std::string, UniversalFunctions::clickFuncParameters> click : UniversalFunctions::clickFuncParamDB)
	{
		System::String^ cliClick = msclr::interop::marshal_as<System::String^>(click.first);
		ManagedCode::ManagedGlobals::w->AddClick(cliClick);
	}

	for (std::pair<std::string, UniversalFunctions::dragFuncParameters> drag : UniversalFunctions::dragFuncParamDB)
	{
		System::String^ cliDrag = msclr::interop::marshal_as<System::String^>(drag.first);
		ManagedCode::ManagedGlobals::w->AddDrag(cliDrag);
	}

	using namespace System::Windows::Controls;
	using namespace System::Windows::Controls::Primitives;

	ToggleButton ^btnRunPauseMacro = ManagedCode::ManagedGlobals::w->GetRunPauseMacroBtn();
	Button^ btnStopMacro = ManagedCode::ManagedGlobals::w->GetStopBtn();

	btnRunPauseMacro->Checked += gcnew System::Windows::RoutedEventHandler(&OnRunResumeBtnClick);
	btnRunPauseMacro->Unchecked += gcnew System::Windows::RoutedEventHandler(&OnPauseBtnClick);
	btnStopMacro->Click += gcnew System::Windows::RoutedEventHandler(&OnStopBtnClick);

	Button^ btnShowScreen = ManagedCode::ManagedGlobals::w->GetShowScreenBtn();
	Button^ btnShowClick = ManagedCode::ManagedGlobals::w->GetShowClickBtn();
	Button^ btnShowDrag = ManagedCode::ManagedGlobals::w->GetShowDragBtn();
	btnShowScreen->Click += gcnew System::Windows::RoutedEventHandler(&OnShowObjectBtnClick);
	btnShowClick->Click += gcnew System::Windows::RoutedEventHandler(&OnShowObjectBtnClick);
	btnShowDrag->Click += gcnew System::Windows::RoutedEventHandler(&OnShowObjectBtnClick);


	ManagedCode::ManagedGlobals::w->EnablePanel();
	
	return 0; 
};

unsigned __stdcall UiInit::RunMacroThread(void * param)
{
	System::String^ cliLoop = ManagedCode::ManagedGlobals::w->GetSelectedDungName();
	std::string loopName = msclr::interop::marshal_as<std::string>(cliLoop);

	LOG("Starting: " + loopName);
	if (WaitClass::Start() == 0)
	{
		ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Running);
		UniversalFunctions::UniversalLoopFunction(loopName);
	}

	ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Stopped);

	return 0;
};

unsigned __stdcall UiInit::RunDetermineLocationsThread(void * param)
{
	while (true)
	{
		if (!WaitClass::IsStopped() && !WaitClass::IsPaused())
		{
			if (Nox::DetermineLocation() == -1)
			{
				WaitClass::Pause();
				ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Paused);
			}
			else if (MacroScreens::areScreensLoaded && !MacroScreens::imagesToShow.empty())
			{
				WaitClass::Pause();
				ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Paused);
				for (auto item : MacroScreens::imagesToShow)
				{
					Coords coords = Coords(item.second.first.first, item.second.second.first, item.second.first.second, item.second.second.second);
					ShowPartOfDesktop(item.first, coords.GetAbsX1(), coords.GetAbsY1(), coords.GetAbsX2(), coords.GetAbsY2());
				}
				MacroScreens::imagesToShow.clear();
			}
		}

		Sleep(200);
	}

	return 0;
};

unsigned __stdcall UiInit::ShowScreenThread(void * param)
{
	System::String^ cliName = ManagedCode::ManagedGlobals::w->GetSelectedScreenName();
	std::string cppName = msclr::interop::marshal_as<std::string>(cliName);

	for (auto item : UniversalFunctions::screenFuncParamDB)
	{
		if (item.first == cppName)
		{
			ShowPartOfDesktop(cppName, item.second.coords.GetAbsX1(), item.second.coords.GetAbsY1(), item.second.coords.GetAbsX2(), item.second.coords.GetAbsY2());
			break;
		}
	}
	return 0;
};

unsigned __stdcall UiInit::ShowClickThread(void * param)
{
	System::String^ cliName = ManagedCode::ManagedGlobals::w->GetSelectedClickName();
	std::string cppName = msclr::interop::marshal_as<std::string>(cliName);

	for (auto item : UniversalFunctions::clickFuncParamDB)
	{
		if (item.first == cppName)
		{
			ShowPartOfDesktop(cppName, item.second.coords.GetAbsX1(), item.second.coords.GetAbsY1(), item.second.coords.GetAbsX2(), item.second.coords.GetAbsY2());
			break;
		}
	}
	return 0;
};

unsigned __stdcall UiInit::ShowDragThread(void * param)
{
	System::String^ cliName = ManagedCode::ManagedGlobals::w->GetSelectedDragName();
	std::string cppName = msclr::interop::marshal_as<std::string>(cliName);

	for (auto item : UniversalFunctions::dragFuncParamDB)
	{
		if (item.first == cppName)
		{
			ShowPartOfDesktop(cppName, item.second.coords.GetAbsX1(), item.second.coords.GetAbsY1(), item.second.coords.GetAbsX2(), item.second.coords.GetAbsY2());
			break;
		}
	}
	return 0;
};

void UiInit::OnRunResumeBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	System::String^ cliDung = ManagedCode::ManagedGlobals::w->GetSelectedDungName();
	std::string dungName = msclr::interop::marshal_as<std::string>(cliDung);
	static bool locThreadStarted = false;
	if (ManagedCode::ManagedGlobals::w->GetState() == TheUI::ObservableControlStates::StateEnum::Stopped)
	{
		unsigned tid; // thread ID
		_beginthreadex(NULL, 0, RunMacroThread,				 (void *)NULL, 0, &tid);
		if (!locThreadStarted)
		{
			locThreadStarted = true;
			_beginthreadex(NULL, 0, RunDetermineLocationsThread, (void *)NULL, 0, &tid);
		}
	}
	else
	{
		LOG("Resuming: " + dungName);
		if (WaitClass::Resume() == 0)
			ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Running);
		else
			ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Paused);
	}
}

void UiInit::OnPauseBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	if (ManagedCode::ManagedGlobals::w->GetState() == TheUI::ObservableControlStates::StateEnum::Running)
	{
		WaitClass::Pause();
		ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Paused);
		LOG("Pausing");
	}
}

void UiInit::OnStopBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	WaitClass::Stop();
	ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Stopped);
	LOG("Stopping");
}

void UiInit::OnShowObjectBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	using namespace System::Windows::Controls;

	unsigned tid; // thread ID
	std::string x = msclr::interop::marshal_as<std::string>(((Button^)sender)->Name);
	if (x == "btnShowScreen")
	{
		_beginthreadex(NULL, 0, ShowScreenThread, (void *)NULL, 0, &tid);
	}
	else if (x == "btnShowClick")
	{
		_beginthreadex(NULL, 0, ShowClickThread, (void *)NULL, 0, &tid);
	}
	else if (x == "btnShowDrag")
	{
		_beginthreadex(NULL, 0, ShowDragThread, (void *)NULL, 0, &tid);
	}
}