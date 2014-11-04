#include "ivs_timer.h"
#include "ivs_error.h"
#include "ivs_error.h"
#include <ctype.h>
#include <time.h>
#ifdef WIN32
#include <Windows.h>
#include <sys/timeb.h>
#endif

#pragma comment(lib,"Winmm.lib")

#define TARGET_RESOLUTION 1         // 1-millisecond target resolution

#define TIMER_ACCURACY 2

unsigned int timerID;

//距离10分钟发生翻转
unsigned long timeTick = 0xFFFF159F;
#ifdef WIN32
static void CALLBACK  TimerCallBack(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    timeTick += TIMER_ACCURACY;
}

int  IVS_StarTimer()
{
    TIMECAPS tc;

    UINT wTimerRes;

    if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
    {
        return IVS_FAIL;
    }

    wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);

    timeBeginPeriod(wTimerRes);

    timerID = timeSetEvent(TIMER_ACCURACY, wTimerRes, TimerCallBack, NULL, TIME_PERIODIC);
    if (!timerID)
    {
        return IVS_FAIL;
    }

    return IVS_SUCCEED;
}

void  IVS_StopTimer()
{
    if (timerID)
    {
        // is timer event pending?
        timeKillEvent(timerID);  // cancel the event
        timerID = 0;
    }
}

unsigned long  IVS_GetTimeTick()
{
    return timeTick;
}

unsigned long long IVS_GetSysTickUs(void)
{

#if 0	
	LARGE_INTEGER counter, freq;
	QueryPerformanceCounter(&counter);
	QueryPerformanceFrequency(&freq);

	lldiv_t d = lldiv (counter.QuadPart, freq.QuadPart);
	return (d.quot * 1000000) + ((d.rem * 1000000) / freq.QuadPart); //lint !e732
#endif 
	
#if 0
	return (unsigned long long)timeTick * 1000;
#endif 

	struct _timeb  localTime;
	struct timeval tv;
	_ftime(&localTime);
	tv.tv_sec  = (long)(localTime.time + localTime.timezone);
	tv.tv_usec = localTime.millitm * 1000;
	
	return (unsigned long long)tv.tv_sec * 1000000 + (unsigned long long)tv.tv_usec;//lint !e571
}

#else
int  IVS_StarTimer()
{
	return IVS_SUCCEED;
}
void  IVS_StopTimer()
{

}
unsigned long  IVS_GetTimeTick()
{
	return timeTick;
}
unsigned long long IVS_GetSysTickUs(void)
{
	return 0;
}
#endif