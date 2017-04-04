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
Thread sendSerialThread;

//  Setup IO
//  Serial Comms
Serial pcSerial (USBTX, USBRX);

void sendSerial (void)
{
    osEvent serialDumperMailEvt;
    while (true)
    {
        //  Get Latest MAIL Data
        serialDumperMailEvt = serialDumperMail.get ();
        //  Check if data was received
        if (serialDumperMailEvt.status == osEventMail)
        {
            //  New values received -> store them
            serialDumperStruct *serialDumperData =
                (serialDumperStruct *) serialDumperMailEvt.value.p;

            //  Send MAIL data to serial port
            pcSerial.printf ("%f,%f,%d,%d\r\n",
                serialDumperData -> acceleration,
                serialDumperData -> slowage,
                serialDumperData -> rawSpeed,
                serialDumperData -> filteredSpeed);

            //  Free up the struct
            serialDumperMail.free (serialDumperData);
        }
    }

    return;
}

int initSerial (void)
{
    //  Setup Parameters
    pcSerial.baud (9600);
    pcSerial.format (8, SerialBase::None, 1);
    //pcSerial.set_flow_control (SerialBase::None);

    //  Send CSV Headers
    pcSerial.printf("Blair Edwards Assignment 3\r\n");
    pcSerial.printf ("Acceleration,Slowage,Raw Speed,Filtered Speed\r\n");

	return 0;
}

//  *--</Main Code>--*  //
