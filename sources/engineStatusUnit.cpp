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

//  Data Queues (move both to "Engine Management" later)
Queue <char, 16> speedQueue;
Queue <int, 16> distanceQueue;

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
	int filteredSpeed = 65;
	int distance = 9001;
	char toSend [16];

	while (true)
	{
		//writeLcd (0, 0, "0");
		//  Read the Acceleration Queue
		accelerationQueueEvt = accelerationQueue.get ();
		//  Check if a message was received
		if (accelerationQueueEvt.status == osEventMessage)
			//  New value received -> store it
			//acceleration = *((unsigned short int *) (&accelerationQueueEvt.value.p));
			memcpy (&acceleration, accelerationQueueEvt.value.p, sizeof (unsigned short int));

		//writeLcd (0, 1, "1");
		//  Read the Slowage Queue
		slowageQueueEvt = slowageQueue.get ();
		//  Check if message was received
		if (slowageQueueEvt.status == osEventMessage)
			//  New value received -> store it
			//slowage = (unsigned short int) slowageQueueEvt.value.p;
			memcpy (&slowage, slowageQueueEvt.value.p, sizeof (unsigned short int));

		//writeLcd (0, 2, "2");
		//  Read the Speed Queue (FILTER)
		speedQueueEvt = speedQueue.get ();
		//  Check if a messagge was received
		//writeLcd (0, 3, "3");
		if (speedQueueEvt.status == osEventMessage)
		{
			//writeLcd (0, 4, "4");
			//  New value received -> filter and store it
			//  Could parhaps have a variable that cycles which vaule to write?
			rawSpeed [3] = rawSpeed [2];
			rawSpeed [2] = rawSpeed [1];
			rawSpeed [1] = rawSpeed [0];
			//rawSpeed [0] = (char) speedQueueEvt.value.p;
			//writeLcd (0, 5, "5");
			memcpy (&rawSpeed[0], speedQueueEvt.value.p, sizeof (char));
			//writeLcd (0, 6, "6");
			filteredSpeed = (rawSpeed [3] + rawSpeed [2] + rawSpeed [1]
				+ rawSpeed [0]) / 4;
		}

		//writeLcd (0, 7, "7");
		//  Read the Distance Queue
		distanceQueueEvt = distanceQueue.get ();
		//  Check if message was received
		if (distanceQueueEvt.status == osEventMessage)
			//  New value received -> store it
			//distance = (int) distanceQueueEvt.value.p;
			memcpy (&distance, distanceQueueEvt.value.p, sizeof (int));


		//  Control Servo to represent filtered speed
		//writeLcd (0, 8, "8");
		//  Write speed and distance to LCD
		strcpy (toSend, "Speed:  ");
		strcat (toSend, (char*) filteredSpeed);
		strcat (toSend, " MPH");
		writeLcd (0, 0, toSend);
		strcpy (toSend, "Dist:  ");
		strcat (toSend, (char*) distance);
		strcat (toSend, " m");
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
