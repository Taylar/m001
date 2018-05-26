#include "general.h"

uint16_t	sysAppHandle;

uint32_t rtcCntEvent;

uint32_t movtEvent;

uint32_t bleEvent;

uint32_t keyEvent;


void SetRtcEvent(void)
{
	rtcCntEvent++;
}

void SetMovtEvent(uint32_t event)
{
	movtEvent |= event;
}

void SetBleEvent(uint32_t event)
{
	bleEvent |= event;
}

void SetKeyEvent(uint32_t event)
{
	keyEvent |= event;
}


void NullFunc(void)
{
	
}



void OsalRun(void)
{
	uint32_t eventTemp;
	movt_task_msg_t msg;

	if(bleEvent)
	{
		__disable_irq();
		eventTemp = bleEvent;
		bleEvent  = 0;
        __enable_irq();


	}


	if(movtEvent)
	{
		__disable_irq();
		eventTemp = movtEvent;
		movtEvent = 0;
        __enable_irq();

        if(eventTemp & MOVT_FORWARD_FINISH_EVENT)
        {
        	MovtMClockForwardFinish();
        }

        if(eventTemp & MOVT_RESVERSE_FINISH_EVENT)
        {
        	MovtMClockReverseFinish();
        }
	}

	if(rtcCntEvent)
	{
        __disable_irq();
		eventTemp = rtcCntEvent;
		rtcCntEvent = 0;
        __enable_irq();

        while(eventTemp--)
        {
        	rtcApp.SecPeriodProcess();
        	msg.id = MOVT_MSG_MC_FORWARD;
			MovtEventSet(msg);
        }
	}

}

