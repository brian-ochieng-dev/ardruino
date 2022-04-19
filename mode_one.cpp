#include <Stepper.h>

volatile int count;
int stop = 0;
const int stepsPerRevolution = 10;

// initialize the stepper library on pins 0 through 11:
Stepper motorOne(stepsPerRevolution, 0, 1, 2, 3);

void setup()
{
    motorOne.setSpeed(60);
}
void loop()
{
    motorOne.step(stepsPerRevolution);
}