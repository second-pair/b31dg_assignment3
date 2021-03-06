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
Queue <float, 16> accelerationQueueEM;
Queue <float, 16> slowageQueueEM;
Queue <bool, 16> engineStatusQueueEM;
Queue <float, 16> accelerationQueueESU;
Queue <float, 16> slowageQueueESU;
Queue <bool, 16> engineStatusQueueLC;

//  IO
//  Digital Inputs
DigitalIn engineStatusSwt (p11);
//  Analogue Inputs
AnalogIn accelerator (p19);
AnalogIn brake (p20);

void readControls (void)
{
	float acceleration;
	float slowage;
	bool engineStatus;

	while (true)
	{
		//  Wait to be cycled
		Thread::signal_wait (0x1);

		//  Read Inputs
		acceleration = accelerator.read ();
		slowage = brake.read ();
		engineStatus = engineStatusSwt;

		//  Write to Engine Manager
		accelerationQueueEM.put (&acceleration);
		slowageQueueEM.put (&slowage);
		engineStatusQueueEM.put (&engineStatus);

		//  Write to Engine Status Unit
		accelerationQueueESU.put (&acceleration);
		slowageQueueESU.put (&slowage);
		engineStatusQueueLC.put (&engineStatus);
	}

	return;
}

//  *--</Main Code>--*  //
