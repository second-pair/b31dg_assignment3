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

//  Data Queues
Mail <serialDumperStruct, 16> serialDumperMail;

//  IO
//  Digital Outputs
DigitalOut overspeedLed (p16);
//  PWM Outputs
PwmOut speedometer (p21);

void engineStatus (void)
{
	osEvent accelerationQueueEvt;
	osEvent slowageQueueEvt;
	osEvent speedQueueEvt;
	osEvent distanceQueueEvt;
	float acceleration = 0;
	float slowage = 0;
	char rawSpeed [4] = {0, 0, 0, 0};
	char filteredSpeed = 0;
	int distance = 0;
	char toSend [16];
	speedometer.period (0.020);
	serialDumperStruct *serialDumperData = serialDumperMail.alloc ();

	while (true)
	{
		//  Read the Acceleration Queue
		accelerationQueueEvt = accelerationQueueESU.get ();
		//  Check if a message was received
		if (accelerationQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&acceleration, accelerationQueueEvt.value.p,
				sizeof (float));

		//  Read the Slowage Queue
		slowageQueueEvt = slowageQueueESU.get ();
		//  Check if message was received
		if (slowageQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&slowage, slowageQueueEvt.value.p, sizeof (float));

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
			memcpy (&rawSpeed[0], speedQueueEvt.value.p, sizeof (char));
			filteredSpeed = (rawSpeed [3] + rawSpeed [2] + rawSpeed [1]
				+ rawSpeed [0]) / 4;
		}

		//  Read the Distance Queue
		distanceQueueEvt = distanceQueue.get ();
		//  Check if message was received
		if (distanceQueueEvt.status == osEventMessage)
			//  New value received -> store it
			memcpy (&distance, distanceQueueEvt.value.p, sizeof (int));

		//  Control Servo to represent filtered speed
		speedometer.pulsewidth_us (2000 - (filteredSpeed * 8));

		//  Write speed and distance to LCD
		sprintf (toSend, "%3d", filteredSpeed);
		writeLcd (0, 13, toSend);
		sprintf (toSend, "%11d", distance);
		writeLcd (1, 5, toSend);

		//  Detect overspeed
		if (filteredSpeed > 70)
			overspeedLed = HIGH;
		else
			overspeedLed = LOW;

		//  MAIL Queue
		serialDumperData -> acceleration = acceleration;
		serialDumperData -> slowage = slowage;
		serialDumperData -> rawSpeed = rawSpeed [0];
		serialDumperData -> filteredSpeed = filteredSpeed;
		serialDumperMail.put (serialDumperData);

		Thread::wait (100);
	}

	serialDumperMail.free (serialDumperData);
	return;
}

//  *--</Main Code>--*  //
