#pragma once

public class UiInit
{
public:
	static void Init();

private:
	static unsigned __stdcall UiInitThread(void * param);
	static unsigned __stdcall RunMacroThread(void * param);
	static unsigned __stdcall RunDetermineLocationsThread(void * param);
	static void OnRunResumeBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
	static void OnPauseBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
	static void OnStopBtnClick(System::Object ^sender, System::Windows::RoutedEventArgs ^e);
};