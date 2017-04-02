/*
https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/tasks/rtos/
https://www.element14.com/community/docs/DOC-46650/l/arm-keil-rtx-real-time-operating-system-overview
*/

#include "mbed.h"
#include "rtos.h"

DigitalOut myled1 (LED1);
DigitalOut myled2 (LED2);
DigitalOut myled3 (LED3);
DigitalOut myled4 (LED4);

void led_thread1 (void)
{
    while (true)
    {
        myled1 = !myled1;
        Thread::wait (500);
    }
}
void led_thread2 (void)
{
    while (true)
    {
        myled2 = !myled2;
        Thread::wait (1000);
    }
}
void led_thread3 (void)
{
    while (true)
    {
        myled3 = !myled3;
        Thread::wait (2000);
    }
}
void led_thread4 (void)
{
    while (true)
    {
        myled4 = !myled4;
        Thread::wait (4000);
    }
}

int main ()
{
    Thread t1;
    Thread t2;
    Thread t3;
    Thread t4;
    t1.start (led_thread1);
    t2.start (led_thread2);
    t3.start (led_thread3);
    t4.start (led_thread4);

    Thread::wait (osWaitForever);
}
