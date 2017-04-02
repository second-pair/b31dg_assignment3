/*  *--<Preface>--*  //

 -=-  Author Details  -=-
 Blair Edwards (BE38)
 Heriot-Watt University

 -=-  Part Of  -=-
 b31dg_assignment3

 -=-  Notes  -=-
 =>  Data communication between threads uses the "Queue" method

//  *--</Preface>--*  */



//  Headers
#include "mbed.h"
#include "rtos.h"
#include "MCP23017.h"
#include "WattBob_TextLCD.h"

//  Function Prototypes
//  Since file-specific function headers would only have function prototypes
//    in them, I'll just define them all here and save on multiple files.
int main (void);
int init (void);
int initLcd (void);
int initSerial (void);

//  Logic Parameters
#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0

//  LCD Parameters
extern MCP23017 *par_port;
extern WattBob_TextLCD *lcd;

//  Threads
extern Thread recvDataThd;
extern Thread sendDataThd;

//  Data Queues
extern Queue <char, 16> dataQueue;

//  IO
//  Serial Comms
extern Serial pcSerial;
//  Digital Inputs
//extern DigitalIn aDigitalIn;
//  Analogue Inputs
//extern AnalogIn anAnalogueIn;
//  Digital Outputs
//extern DigitalOut aDigitalOut;
