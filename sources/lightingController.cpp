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

//  Data Queues
Queue <bool, 16> engineStatusQueue;  //  Move to "Engine Control Grabber" later

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

void lighting (void)  //  Threaded
{
	osEvent engineStatusQueueEvt;
	bool engineStatus = 0;

	while (true)
	{
		//  Simply route switch inputs to LEDs
		sideLightLed = sideLightSwt;
		leftSigLed = leftSigSwt;
		rightSigLed = rightSigSwt;

		//  Read the Engine Status Queue
		engineStatusQueueEvt = engineStatusQueue.get ();
		//  Check if a message was received
		if (engineStatusQueueEvt.status == osEventMessage)
			//  New value received -> store it
			engineStatus = (bool) engineStatusQueueEvt.value.p;
		//  Update Engine Status LED with stored value
		engineStatusLed = engineStatus;
	}

	return;
}

//  *--</Main Code>--*  //
