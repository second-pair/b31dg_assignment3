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
//  Functions
void writeLcd (char line, char offset, char *message);
//  Threaded
void readControls (void);
void lighting (void);

//  Logic Parameters
#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0

//  LCD Parameters
extern MCP23017 *par_port;
extern WattBob_TextLCD *lcd;

//  Threads
extern Thread readControlsThread;
extern Thread lightingThread;

//  Mutexes
extern Mutex writeLcdMutex;

//  Data Queues
extern Queue <unsigned short int, 16> accelerationQueue;
extern Queue <unsigned short int, 16> slowageQueue;
extern Queue <bool, 16> engineStatusQueue;

//  IO
//  Serial Comms
extern Serial pcSerial;
//  Digital Inputs
extern DigitalIn engineStatusSwt;
extern DigitalIn sideLightSwt;
extern DigitalIn leftSigSwt;
extern DigitalIn rightSigSwt;
//  Analogue Inputs
extern AnalogIn accelerator;
extern AnalogIn brake;
//speedometer PWM?
//  Digital Outputs
extern DigitalOut engineStatusLed;
extern DigitalOut sideLightLed;
extern DigitalOut leftSigLed;
extern DigitalOut rightSigLed;
//extern DigitalOut overspeedLed;
