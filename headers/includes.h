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
void writeLcd (char line, char offset, const char *message);
//  Threaded
void readControls (void);
void engineManager (void);
void lighting (void);
void indicatorStrober (void);
void engineStatus (void);

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
extern Thread engineManagerThread;
extern Thread lightingThread;
extern Thread indicatorStroberThread;
extern Thread engineStatusThread;

//  Mutexes
extern Mutex writeLcdMutex;
extern Mutex indicatorStateMutex;

//  Data Queues
extern Queue <float, 16> accelerationQueueEM;
extern Queue <float, 16> slowageQueueEM;
extern Queue <bool, 16> engineStatusQueueEM;
extern Queue <float, 16> accelerationQueueESU;
extern Queue <float, 16> slowageQueueESU;
extern Queue <bool, 16> engineStatusQueueLC;
extern Queue <char, 16> speedQueue;
extern Queue <int, 16> distanceQueue;

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
extern DigitalOut overspeedLed;

//  Structs
//theMailQueue struct
