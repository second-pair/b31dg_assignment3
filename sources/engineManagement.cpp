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
Thread engineManagerThread;

//  Data Queues
Queue <char, 16> speedQueue;
Queue <int, 16> distanceQueue;


void engineManager (void)
{
	osEvent accelerationQueueEvt;
	osEvent slowageQueueEvt;
	osEvent engineStatusQueueEvt;
	bool engineStatus = LOW;
	float acceleration = 0;
	float slowage = 0;
	float newSpeed;
	float speed = 0;
	char speedInt = 0;
	int distance = 0;

	while (true)
	{
		//  This thread is cycled every 50ms
		//  Wait to be cycled
		Thread::signal_wait (0x1);

		//  Read the Acceleration Queue
		accelerationQueueEvt = accelerationQueueEM.get ();
		//  Check if a message was received
		if (accelerationQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&acceleration, accelerationQueueEvt.value.p,
				sizeof (float));

		//  Read the Slowage Queue
		slowageQueueEvt = slowageQueueEM.get ();
		//  Check if a message was received
		if (slowageQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&slowage, slowageQueueEvt.value.p, sizeof (float));

		//  Read the Engine Status Queue
		engineStatusQueueEvt = engineStatusQueueEM.get ();
		//  Check if a message was received
		if (engineStatusQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&engineStatus, engineStatusQueueEvt.value.p, sizeof (bool));

		//  Calculate speed
		if (engineStatus == HIGH)
		{
			//  Max acceleration taken as 0 -> 60 in 5 seconds = 12MPH/s
			newSpeed = speed + ((acceleration - slowage) * 0.6);
			if (newSpeed < 0)
				speed = 0;
			else if (newSpeed > MAX_SPEED)
				speed = MAX_SPEED;
			else
				speed = newSpeed;
		}
		else
			speed = 0;
		speedInt = (int) speed;

		//  Calculate m/c from Miles/h
		//  1609.344 meters in a mile
		//  60 * 60 * 20 = 72000 cycles in an hour
		//  1 MPH = (1609.344 / 72000 =) 0.022352 meters per cycle
		distance += (int) (speed * 0.022352);

		//  Write to Engine Status Unit
		speedQueue.put (&speedInt);
		distanceQueue.put (&distance);
	}
}

//  *--</Main Code>--*  //
