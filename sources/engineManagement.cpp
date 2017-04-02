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
	char speed = 65;
	int distance = 9001;

	while (true)
	{
		//  Read from Engine Control Grabber
		//read from queues

		//  Write to Engine Status Unit
		speedQueue.put (&speed);
		distanceQueue.put (&distance);

		Thread::wait (1);
	}
}

//  *--</Main Code>--*  //
