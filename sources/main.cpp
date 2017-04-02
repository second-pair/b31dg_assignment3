/*
https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/tasks/rtos/
https://www.element14.com/community/docs/DOC-46650/l/arm-keil-rtx-real-time-operating-system-overview
*/

#include "includes.h"

MCP23017 *par_port;
WattBob_TextLCD *lcd;
//DigitalOut myled1 (LED1);

Thread recvDataThd;
Thread sendDataThd;
Queue <char, 16> dataQueue;


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
}

int init (void)
{
    initLcd ();
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
