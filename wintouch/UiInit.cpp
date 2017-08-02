#include "UiInit.h"

#include <process.h>
#include <msclr\marshal_cppstd.h>

#include "MainWindow.h"
#include "MacroFile.h"


unsigned __stdcall UiInitThread(void * param) 
{ 
	if (MacroFile::LoadMacroFile() == 0)
	{
		for (MacroSteps dung : MacroFile::macroStepDB)
		{
			if (dung.dungName == MacroFile::ALL_DUNG_NAME) continue;
			System::String^ cliDung = msclr::interop::marshal_as<System::String^>(dung.dungName);
			ManagedCode::ManagedGlobals::w->AddDung(cliDung);
		}

		ManagedCode::ManagedGlobals::w->EnablePanel();
	}
	return 0; 
};

void UiInit::Init()
{
	unsigned tid; // thread ID
	HANDLE hThread; // thread handle

	hThread = (HANDLE)_beginthreadex(NULL, 0,
		UiInitThread, (void *)NULL,
		0, &tid);
}
