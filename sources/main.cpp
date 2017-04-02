/*  *--<Preface>--*  //

 -=-  Author Details  -=-
 Blair Edwards (BE38)
 Heriot-Watt University

 -=-   Programme Details  -=-
 Title:  b31dg_assignment3
 Git Repo:  https://github.com/second-pair/b31dg_assignment3
 More Info:  Please read README.md

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
 =>  LED1 = Engine Status
 =>  LED2 = Side Lights
 =>  LED3 = Left Turn indicator
 =>  LED4 = Right Turn Indicator

 -=-  TODO  -=-
 =>  Abstract code in engineStatus
 =>  Some semblence of time for distance calculator
 =>  Scheduling - perhaps use signaling?
 =>  Documentation

//  *--</Preface>--*  */



//  *--<Main Code>--*  //

#include "includes.h"

int main (void)
{
    init ();

    //  Start threads
    readControlsThread.start (readControls);
    engineManagerThread.start (engineManager);
    lightingThread.start (lighting);
    indicatorStroberThread.start (indicatorStrober);
    engineStatusThread.start (engineStatus);
    sendSerialThread.start (sendSerial);

    while (true)
    {
        //  Manage and shedule threaed execution
        //TODO
        //Probably use signaling
    }

    return 0;
}

int init (void)
{
    //  Initialisation Function
    initLcd ();
    initSerial ();
    return 0;
}

//  *--</Main Code>--*  //
