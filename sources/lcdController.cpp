/*  *--<Preface>--*  //

 -=-  Author Details  -=-
 Blair Edwards (BE38)
 Heriot-Watt University

 -=-  Part Of  -=-
 b31dg_assignment3

//  *--</Preface>--*  */



//  *--<Main Code>--*  //

#include "includes.h"

//  LCD Parameters
MCP23017 *par_port;
WattBob_TextLCD *lcd;

//  Mutexes
Mutex writeLcdMutex;

void writeLcd (char line, char offset, const char *message)
{
	writeLcdMutex.lock ();
	lcd -> locate (line, offset);
    lcd -> printf ("%s", message);
	writeLcdMutex.unlock ();
	return;
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
	writeLcd (0, 0, "S(MPH)");
	writeLcd (1, 0, "D(m)  ");
    return 0;
}

//  *--</Main Code>--*  //
