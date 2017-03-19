#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn test (p5);

int main() {
    int temp;
    temp = test;
    while(1) {
        myled = 1;
        wait(0.2);
        myled = 0;
        wait(0.2);
    }
}
