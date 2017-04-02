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
Thread readControlsThread;

//  Data Queues
Queue <unsigned short int, 16> accelerationQueue;
Queue <unsigned short int, 16> slowageQueue;
Queue <bool, 16> engineStatusQueue;

//  IO
//  Digital Inputs
DigitalIn engineStatusSwt (p11);
//  Analogue Inputs
AnalogIn accelerator (p19);
AnalogIn brake (p20);

void readControls (void)
{
	unsigned short int acceleration;
	unsigned short int slowage;
	bool engineStatus;

	while (true)
	{
		//  Read Inputs
		acceleration = accelerator.read ();
		slowage = brake.read ();
		engineStatus = engineStatusSwt;

		//  Write to Engine Manager

		//  Write to Engine Status Unit
		accelerationQueue.put (&acceleration);
		slowageQueue.put (&slowage);
		engineStatusQueue.put (&engineStatus);

		Thread::wait (1);
}

	return;
}

//  *--</Main Code>--*  //
