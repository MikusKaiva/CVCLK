#include "Wait.h"

#include <Windows.h>

#include "ConnectionError.h"
#include "Log.h"
#include "Nox.h"

bool WaitClass::isStopped = true;
bool WaitClass::isPaused = false;

int WaitClass::Wait(int miliSeconds)
{
	int step = 100;
	do
	{
		if (isStopped)
			return STOP_THREAD;
		while (isPaused)
		{
			Sleep(250);
			miliSeconds -= 250;
			if (isStopped)
				return STOP_THREAD;
		}
		Sleep(step);
		miliSeconds -=step;
	} while (miliSeconds > 0);
	return 0;
}

int WaitClass::WaitClickableObject(bool(*object)())
{
	int ret = -1;
	int howLong = 15;

	while (howLong >= 0)
	{
		if (object)
		{
			ret = 0;
			break;
		}
		ret = ConnectionError::ClickConnectionError();
		if (ret == 0)
		{
			howLong = 10;
			continue;
		}
		if (ret == STOP_THREAD)
		{
			break;
		}
		howLong--;
		ret = WaitClass::Wait(1000);
		if (ret != 0)
		{
			break;
		}
		ret = -1;
	}
	return ret;
}

int WaitClass::Start()
{
	if (Nox::DetermineLocation() < 0)
	{
		return -1;
	}
	isPaused = false;
	isStopped = false;
	return 0;
}

void WaitClass::Pause()
{
	isPaused = true;
}

int WaitClass::Resume()
{
	if (Nox::DetermineLocation() < 0)
	{
		return -1;
	}
	isPaused = false;
	return 0;
}

void WaitClass::Stop()
{
	isStopped = true;
}

bool WaitClass::IsPaused()
{
	return isPaused;
}

bool WaitClass::IsStopped()
{
	return isStopped;
}
