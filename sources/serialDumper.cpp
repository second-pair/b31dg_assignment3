/*  *--<Preface>--*  //

 -=-  Author Details  -=-
 Blair Edwards (BE38)
 Heriot-Watt University

 -=-  Part Of  -=-
 b31dg_assignment3

//  *--</Preface>--*  */



//  *--<Main Code>--*  //

#include "includes.h"

//  Setup IO
//  Serial Comms
Serial pcSerial (USBTX, USBRX);

void sendSerial (void)
{
	//  Currently not implemented (planned)
	//  Need to decide between continuous thread and function calls
    //Serial Code
    pcSerial.printf ("Nothing to %s\n", "send yet.");

    return;
}

int initSerial (void)
{
    //  Send CSV Headers
    pcSerial.printf("Blair Edwards Assignment 2\n");
    pcSerial.printf ("Some Table Headers?\n");

	return 0;
}

//  *--</Main Code>--*  //
