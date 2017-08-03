#include "UiInit.h"

#include <process.h>
#include <msclr\marshal_cppstd.h>

#include "MainWindow.h"
#include "MacroFile.h"
#include "Log.h"

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
	if (MacroFile::LoadMacroFile() == 0)
	{
		for (MacroSteps dung : MacroFile::macroStepDB)
		{
			if (dung.dungName == MacroFile::ALL_DUNG_NAME) continue;
			System::String^ cliDung = msclr::interop::marshal_as<System::String^>(dung.dungName);
			ManagedCode::ManagedGlobals::w->AddDung(cliDung);
		}

		using namespace System::Windows::Controls;
		using namespace System::Windows::Controls::Primitives;

		ToggleButton ^btnRunPauseMacro = ManagedCode::ManagedGlobals::w->GetRunPauseMacroBtn();
		Button^ btnStopMacro = ManagedCode::ManagedGlobals::w->GetStopBtn();

		btnRunPauseMacro->Checked += gcnew System::Windows::RoutedEventHandler(&OnRunResumeBtnClick);
		btnRunPauseMacro->Unchecked += gcnew System::Windows::RoutedEventHandler(&OnPauseBtnClick);
		btnStopMacro->Click += gcnew System::Windows::RoutedEventHandler(&OnStopBtnClick);

		ManagedCode::ManagedGlobals::w->EnablePanel();
	}
	return 0; 
};

unsigned __stdcall UiInit::RunMacroThread(void * param)
{
	System::String^ cliDung = ManagedCode::ManagedGlobals::w->GetSelectedDungName();
	std::string dungName = msclr::interop::marshal_as<std::string>(cliDung);

	LOG("Starting: " + dungName);
	MacroFunctions::isPaused = false;
	MacroFunctions::isStopped = false;
	ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Running);

	MacroFunctions::Run(dungName);

	ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Stopped);

	return 0;
};


void UiInit::OnRunResumeBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	System::String^ cliDung = ManagedCode::ManagedGlobals::w->GetSelectedDungName();
	std::string dungName = msclr::interop::marshal_as<std::string>(cliDung);
	if (ManagedCode::ManagedGlobals::w->GetState() == TheUI::ObservableControlStates::StateEnum::Stopped)
	{
		LOG("Starting: " + dungName);
		unsigned tid; // thread ID
		_beginthreadex(NULL, 0, RunMacroThread, (void *)NULL, 0, &tid);
	}
	else
	{
		LOG("Resuming: " + dungName);
		MacroFunctions::isPaused = false;
		ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Running);
	}
}

void UiInit::OnPauseBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	if (ManagedCode::ManagedGlobals::w->GetState() == TheUI::ObservableControlStates::StateEnum::Running)
	{
		MacroFunctions::isPaused = true;
		ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Paused);
		LOG("Paused");
	}
}

void UiInit::OnStopBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e)
{
	MacroFunctions::isStopped = true;
	ManagedCode::ManagedGlobals::w->SetState(TheUI::ObservableControlStates::StateEnum::Stopped);
	LOG("Stopped");
}