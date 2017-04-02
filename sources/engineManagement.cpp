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
	//In:  acceleration, slowage, engine status
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
		//  Read the Acceleration Queue
		accelerationQueueEvt = accelerationQueueEM.get ();
		//  Check if a message was received
		if (accelerationQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&acceleration, accelerationQueueEvt.value.p, sizeof (float));

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
			newSpeed = speed + acceleration - slowage;
			if (newSpeed < 0)
				speed = 0;
			else if (newSpeed > 255)
				speed = 255;
			else
				speed = newSpeed;
		}
		else
			speed = 0;
		speedInt = (int) speed;

		//  Calculate distance
		//  1609.344 meters in a mile
		distance += (int) (speed * 0.44704);  //  Also factor in time

		//  Write to Engine Status Unit
		speedQueue.put (&speedInt);
		distanceQueue.put (&distance);

		Thread::wait (1);
	}
}

//  *--</Main Code>--*  //
