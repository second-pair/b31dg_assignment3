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
Thread engineStatusThread;

//  IO
//Out to Servo, LCD, Overspeed, MAIL
//In Raw speed (to be filtered), distance, acc, slowage
DigitalOut overspeedLed (p16);

void engineStatus (void)
{
	osEvent accelerationQueueEvt;
	osEvent slowageQueueEvt;
	osEvent speedQueueEvt;
	osEvent distanceQueueEvt;
	unsigned short int acceleration = 0;
	unsigned short int slowage = 0;
	char rawSpeed [4] = {0, 0, 0, 0};
	char filteredSpeed = 0;
	int distance = 0;
	char toSend [16];

	while (true)
	{
		//  Read the Acceleration Queue
		accelerationQueueEvt = accelerationQueue.get ();
		//  Check if a message was received
		if (accelerationQueueEvt.status == osEventMessage)
			//  New value received -> store it
			//acceleration = *((unsigned short int *) (&accelerationQueueEvt.value.p));
			memcpy (&acceleration, accelerationQueueEvt.value.p, sizeof (unsigned short int));

		//  Read the Slowage Queue
		slowageQueueEvt = slowageQueue.get ();
		//  Check if message was received
		if (slowageQueueEvt.status == osEventMessage)
			//  New value received -> store it
			//slowage = (unsigned short int) slowageQueueEvt.value.p;
			memcpy (&slowage, slowageQueueEvt.value.p, sizeof (unsigned short int));

		//  Read the Speed Queue (FILTER)
		speedQueueEvt = speedQueue.get ();
		//  Check if a messagge was received
		if (speedQueueEvt.status == osEventMessage)
		{
			//  New value received -> filter and store it
			//  Could parhaps have a variable that cycles which vaule to write?
			rawSpeed [3] = rawSpeed [2];
			rawSpeed [2] = rawSpeed [1];
			rawSpeed [1] = rawSpeed [0];
			//rawSpeed [0] = (char) speedQueueEvt.value.p;
			memcpy (&rawSpeed[0], speedQueueEvt.value.p, sizeof (char));
			filteredSpeed = (rawSpeed [3] + rawSpeed [2] + rawSpeed [1]
				+ rawSpeed [0]) / 4;
		}

		//  Read the Distance Queue
		distanceQueueEvt = distanceQueue.get ();
		//  Check if message was received
		if (distanceQueueEvt.status == osEventMessage)
			//  New value received -> store it
			//distance = (int) distanceQueueEvt.value.p;
			memcpy (&distance, distanceQueueEvt.value.p, sizeof (int));


		//  Control Servo to represent filtered speed
		//  Write speed and distance to LCD
		sprintf (toSend, "Speed:  %d MPH", filteredSpeed);
		writeLcd (0, 0, toSend);
		sprintf (toSend, "Dist:  %d m", distance);
		writeLcd (1, 0, toSend);

		//  Detect overspeed
		if (filteredSpeed > 70)
			overspeedLed = HIGH;
		else
			overspeedLed = LOW;

		//  MAIL Queue

		Thread::wait (1);
	}

	return;
}

//  *--</Main Code>--*  //
