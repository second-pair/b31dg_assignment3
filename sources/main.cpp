/*  *--<Preface>--*  //

 -=-  Author Details  -=-
 Blair Edwards (BE38)
 Heriot-Watt University

 -=-  Dates  -=-
 Started 2017-03-20
 Edited  2017-04-02

 -=-  Description  -=-
 This programme attempts to create a Real-Time car controller.
 This programme is intended to run on an MBED.
 Input is through GPIO pins, the onboard ADC and hard-coded values.
 Output is through GPIO pins, the onboard LCD and via serial port to a PC.
 This programme is intended to talk to a real engine.  Since one might not
    be available, an engine simulator has also been written.

 -=-  Task  -=-
 1>  Read brake & accelerator values (use pots feeding to ADC)
 2>  Read engine on/off state from switch, display using onboard LED
 3>  Filter simulated speed (averaging last n readings)
 4>  Use RC Servo to simulate speedometer dial (averaged speed)
 5>  Have overspeed (> 70mph) LED (on red box)
 6>  Display on LCD:  Average speed, odometer (distance travelled)
 7>  Send to MAIL Queue:  Speed (from engine), acceleration (ADC), slowage (ADC)
 8>  Dump MAIL Queue to PC via Serial
 9>  Toggle sidelights with switch
 10> Turn indicator switches - if only one, flash 1KHz; if both, flash 2KHz

 -=-  Notes  -=-
 =>  Data communication between threads uses the "Queue" method

 -=-  TODO  -=-
 =>  Write many
 =>  Make engine simulation toggleable?  Investigate

//  *--</Preface>--*  */



//  *--<Preparations>--*  //

#include "includes.h"

//  LCD Parameters
MCP23017 *par_port;
WattBob_TextLCD *lcd;

//  Threads
Thread recvDataThd;
Thread sendDataThd;

//  Data Queues
Queue <char, 16> dataQueue;

//  IO
//  Serial Comms
Serial pcSerial (USBTX, USBRX);
//  Digital Inputs
//DigitalIn aDigitalIn (p0);
//  Analogue Inputs
//AnalogIn anAnalogueIn (p0);
//  Digital Outputs
//DigitalOut aDigitalOut (p0);

//  *--</Preparations>--*  //



//  *--<Main Code>--*  //

void sendData (void)
{
    Thread::signal_wait (0x1);
    lcd -> locate (0, 0);
    lcd -> printf ("Sig");
    Thread::wait (2500);

    dataQueue.put ("456");
    recvDataThd.signal_set (0x2);
    return;
}

void recvData (void)
{
    Thread::signal_wait (0x2);
    osEvent evt = dataQueue.get ();
    lcd -> locate (1, 0);
    lcd -> printf ("msg %s", evt.value.p);
    return;
}


int main (void)
{
    init ();

    recvDataThd.start (recvData);
    sendDataThd.start (sendData);

    Thread::wait (2500);
    sendDataThd.signal_set (0x1);

    Thread::wait (osWaitForever);
    return 0;
}

int init (void)
{
    initLcd ();
    initSerial ();
    return 0;
}

int initLcd (void)
{
    //  Initialise the display
    par_port = new MCP23017(p9, p10, 0x40);
    par_port->config(0x0F00, 0x0F00, 0x0F00);  // configure MCP23017 chip on WattBob
    lcd = new WattBob_TextLCD(par_port);
    par_port->write_bit(1,BL_BIT);  // turn LCD backlight ON

    //  Setup initial fields
    lcd -> cls ();  //  Clear LCD
    return 0;
}

int initSerial (void)
{
    //  Send CSV Headers
    pcSerial.printf("Blair Edwards Assignment 2\n");
    pcSerial.printf ("Some Table Headers?\n");
}

//  *--</Main Code>--*  //
