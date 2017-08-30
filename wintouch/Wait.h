#pragma once

#define STOP_THREAD -2

public class WaitClass
{
public:
	static int Wait(int miliSeconds);
	static int WaitClickableObject(bool(*object)());
	static int Start();
	static void Pause();
	static int Resume();
	static void Stop();
	static bool IsPaused();
	static bool IsStopped();

private:
	static bool isStopped;
	static bool isPaused;
};
