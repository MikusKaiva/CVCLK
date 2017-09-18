#pragma once
#include <string>

public class UiInit
{
public:
	static void Init();

private:
	struct showObjectArgsType
	{
		std::string name;
		int x1;
		int y1;
		int x2;
		int y2;
	};
	static unsigned __stdcall UiInitThread(void * param);
	static unsigned __stdcall RunMacroThread(void * param);
	static unsigned __stdcall RunDetermineLocationsThread(void * param);
	static unsigned __stdcall ShowPartOfDesktopThread(void * param);
	//static unsigned __stdcall ShowClickThread(void * param);
	//static unsigned __stdcall ShowDragThread(void * param);
	static void OnRunResumeBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
	static void OnPauseBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
	static void OnStopBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
	static void OnShowObjectBtnClick(System::Object ^ sender, System::Windows::RoutedEventArgs ^ e);
	static void OnReloadBtnClick(System::Object ^ sender, System::Windows::RoutedEventArgs ^ e);
	static int LoadMacros();
};