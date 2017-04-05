/*  *--<Preface>--*  //

 -=-  Author Details  -=-
 Blair Edwards (BE38)
 Heriot-Watt University

 -=-  Part Of  -=-
 b31dg_assignment3

//  *--</Preface>--*  */



//  *--<Main Code>--*  //

#include "includes.h"

//  Threads
Thread lightingThread;
Thread indicatorStroberThread;

//  Mutexes
Mutex indicatorStateMutex;

//  IO
//  Digital Inputs
DigitalIn sideLightSwt (p12);
DigitalIn leftSigSwt (p13);
DigitalIn rightSigSwt (p14);
//  Digital Outputs
DigitalOut engineStatusLed (LED1);
DigitalOut sideLightLed (LED2);
DigitalOut leftSigLed (LED3);
DigitalOut rightSigLed (LED4);

//  Global Variables
char indicatorState = 0;

void lighting (void)  //  Threaded
{
	osEvent engineStatusQueueEvt;
	bool engineStatus = 0;
	bool sideLight;
	bool leftSig;
	bool rightSig;

	while (true)
	{
		//  Wait to be cycled
		Thread::signal_wait (0x1);

		//  Read lighting data from switches
		sideLight = sideLightSwt;
		leftSig = leftSigSwt;
		rightSig = rightSigSwt;

		//  Set Side Lights
		sideLightLed = sideLight;

		//  Set indicator Status
		if ((leftSig == HIGH) && (rightSig == HIGH))
		{
			//  Hazard Mode
			indicatorStateMutex.lock ();
			indicatorState = 3;
			indicatorStateMutex.unlock ();
		}
		else if (leftSig == HIGH)
		{
			//  Left Indicator
			indicatorStateMutex.lock ();
			indicatorState = 1;
			indicatorStateMutex.unlock ();
		}
		else if (rightSig == HIGH)
		{
			//  Right Indicator
			indicatorStateMutex.lock ();
			indicatorState = 2;
			indicatorStateMutex.unlock ();
		}
		else
		{
			//  No Mode
			indicatorStateMutex.lock ();
			indicatorState = 0;
			indicatorStateMutex.unlock ();
		}

		//  Read the Engine Status Queue
		engineStatusQueueEvt = engineStatusQueueLC.get ();
		//  Check if a message was received
		if (engineStatusQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&engineStatus, engineStatusQueueEvt.value.p, sizeof (bool));
		//  Update Engine Status LED with stored value
		engineStatusLed = engineStatus;
	}

	return;
}

void indicatorStrober (void)
{
	char currIndicatorState;
	while (true)
	{
		//  Read stored Indicator State to local variable
		indicatorStateMutex.lock ();
		currIndicatorState = indicatorState;
		indicatorStateMutex.unlock ();

		//  Strobe indicators as necessary
		if (currIndicatorState == 0)
		{
			//  No Indication
			Thread::wait (100);
		}
		else if (currIndicatorState == 1)
		{
			//  Left Indicator
			leftSigLed = HIGH;
			Thread::wait (500);
			leftSigLed = LOW;
			Thread::wait (500);
		}
		else if (currIndicatorState == 2)
		{
			//  Right Indicator
			rightSigLed = HIGH;
			Thread::wait (500);
			rightSigLed = LOW;
			Thread::wait (500);
		}
		else if (currIndicatorState == 3)
		{
			//  Hazard Mode
			leftSigLed = HIGH;
			rightSigLed = HIGH;
			Thread::wait (1000);
			leftSigLed = LOW;
			rightSigLed = LOW;
			Thread::wait (1000);
		}

	}
}

//  *--</Main Code>--*  //
