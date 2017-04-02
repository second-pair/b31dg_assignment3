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
	bool sideLight;
	bool leftSig;
	bool rightSig;

	while (true)
	{
		//  Read lighting data from switches
		sideLight = sideLightSwt;
		leftSig = leftSigSwt;
		rightSig = rightSigSwt;
		//  Drive LEDs with lighting data
		sideLightLed = sideLight;
		leftSigLed = leftSig;
		rightSigLed = rightSig;

		//  Read the Engine Status Queue
		engineStatusQueueEvt = engineStatusQueue.get ();
		//  Check if a message was received
		if (engineStatusQueueEvt.status == osEventMessage)
			//  New value received -> store it
			engineStatus = (bool) engineStatusQueueEvt.value.p;
		//  Update Engine Status LED with stored value
		engineStatusLed = engineStatus;

		Thread::wait (1);
	}

	return;
}

//  *--</Main Code>--*  //
