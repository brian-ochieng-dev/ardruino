#include <IRremote.h>
#include <Stepper.h>

/********** ir receiver **********/

int IR_Recv = 12; // IR Receiver Pin 12,
int led = 13;

IRrecv irrecv(IR_Recv);
decode_results results;

/********** stepper **********/

// set variables
const int stepsPerRevolution = 200;
volatile int count;
int mode = 0;

// motor one
int upMotion = 2000;
int downMotion = -2000;
// motor two
int rightSideMotion = 15;
int leftSideMotion = -15;
int halfSideMotion = 15 / 2.0;
// motor three
int clockWiseMotion = 6;
int antiClockWiseMotion = -6;
int halfRotation = 6 / 2.0;

// initialize the stepper library on pins 0 through 11:
Stepper motorOne(stepsPerRevolution, 0, 1, 2, 3);
Stepper motorTwo(stepsPerRevolution, 4, 5, 6, 7);
Stepper motorThree(stepsPerRevolution, 8, 9, 10, 11);

/********** led mode **********/

void ledOnOff(int times)
{
    for (int i = 0; i < times; i++)
    {
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
    }
}

/********** main **********/

void setup()
{
    irrecv.enableIRIn();   // Starts the receiver
    motorOne.setSpeed(60); // set the speed at 60 rpm:
    motorTwo.setSpeed(60);
    motorThree.setSpeed(60);
    pinMode(led, OUTPUT);
}
void loop()
{
    // decodes the infrared input
    if (irrecv.decode(&results))
    {
        long int decCode = results.value;

        // switch case to use the selected remote control button
        switch (results.value)
        {
        case 16582903: // when you press the 1 button
            ledOnOff(1);
            mode = 1;

            motorOne.step(upMotion * stepsPerRevolution);
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution);
            break;
        case 16615543: // when you press the 2 button
            ledOnOff(2);
            mode = 2;

            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);
            delay(100);
            motorTwo.step(leftSideMotion * stepsPerRevolution);
            delay(100);
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);

            break;
        case 16599223: // when you press the 3 button
            ledOnOff(3);
            mode = 3;

            motorThree.step(clockWiseMotion * stepsPerRevolution);
            break;
        case 16591063: // when you press the 4 button
            ledOnOff(4);
            mode = 4;
            count = rightSideMotion;

            // going up
            for (int i = 0; i < count / 2.0; i++) // bottom center to right (1/16)
            {
                motorOne.step(((upMotion / 8.0) / 2) / (rightSideMotion / 2));
                motorTwo.step(rightSideMotion / rightSideMotion);
            }
            for (int i = 0; i < 3; i++) // 2/16 -> 13/16
            {
                for (int i = 0; i < count; i++)
                {
                    motorOne.step((upMotion / 8.0) / rightSideMotion);
                    motorTwo.step(-rightSideMotion / rightSideMotion);
                }
                for (int i = 0; i < count; i++)
                {
                    motorOne.step((upMotion / 8.0) / rightSideMotion);
                    motorTwo.step(rightSideMotion / rightSideMotion);
                }
            }
            for (int i = 0; i < count; i++) // 14/16 -> 15/16
            {
                motorOne.step((upMotion / 8.0) / rightSideMotion);
                motorTwo.step(-rightSideMotion / rightSideMotion);
            }
            for (int i = 0; i < count / 2.0; i++) // left to top center(16/16)
            {
                motorOne.step(((upMotion / 8.0) / 2) / (rightSideMotion / 2));
                motorTwo.step(rightSideMotion / rightSideMotion);
            }
            delay(100);

            // going down
            for (int i = 0; i < count / 2.0; i++) // top center to left (16/16)
            {
                motorOne.step(((downMotion / 8.0) / 2) / (leftSideMotion / 2));
                motorTwo.step(leftSideMotion / leftSideMotion);
            }
            for (int i = 0; i < count; i++) // 15/16 -> 14/16
            {
                motorOne.step((downMotion / 8.0) / leftSideMotion);
                motorTwo.step(-leftSideMotion / leftSideMotion);
            }
            for (int i = 0; i < 3; i++) // 13/16 -> 2/16
            {
                for (int i = 0; i < count; i++)
                {
                    motorOne.step((downMotion / 8.0) / leftSideMotion);
                    motorTwo.step(leftSideMotion / leftSideMotion);
                }
                for (int i = 0; i < count; i++)
                {
                    motorOne.step((downMotion / 8.0) / leftSideMotion);
                    motorTwo.step(-leftSideMotion / leftSideMotion);
                }
            }
            for (int i = 0; i < count / 2.0; i++) // right to top center(1/16)
            {
                motorOne.step(((downMotion / 8.0) / 2) / (leftSideMotion / 2));
                motorTwo.step(leftSideMotion / leftSideMotion);
            }

            break;
        case 16623703: // when you press the 5 button
            ledOnOff(5);
            mode = 5;
            count = clockWiseMotion;

            // going up
            for (int i = 0; i < count; i++)
            {
                motorOne.step((upMotion / 6.0) / clockWiseMotion);
                motorThree.step(clockWiseMotion / clockWiseMotion);
            }
            delay(100);

            // going down
            for (int i = 0; i < count; i++)
            {
                motorOne.step((downMotion / 6.0) / clockWiseMotion);
                motorThree.step(-clockWiseMotion / clockWiseMotion);
            }

            break;
        case 16607383: // when you press the 6 button
            ledOnOff(6);
            mode = 6;

            motorOne.step(upMotion * stepsPerRevolution); // 1
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 2
            motorThree.step(halfRotation * stepsPerRevolution); // 2
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 6.0); // 3
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 4
            motorThree.step(halfRotation * stepsPerRevolution); // 4
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 6.0); // 5
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 6
            motorThree.step(halfRotation * stepsPerRevolution); // 6
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 6.0); // 7
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 8
            motorThree.step(halfRotation * stepsPerRevolution); // 8
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 6.0); // 9
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 10
            motorThree.step(halfRotation * stepsPerRevolution); // 10
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 6.0); // 11
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 12
            motorThree.step(halfRotation * stepsPerRevolution); // 12
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 6.0); // 13
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 14
            motorThree.step(halfRotation * stepsPerRevolution); // 14
            break;
        case 16586983: // when you press the 7 button
            ledOnOff(7);
            mode = 7;

            motorOne.step(upMotion * stepsPerRevolution); // 1
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 2
            motorThree.step(halfRotation * stepsPerRevolution); // 2
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 3
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 4
            motorThree.step(halfRotation * stepsPerRevolution); // 4
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution); // 5
            delay(100);
            motorOne.step(upMotion * stepsPerRevolution / 8.0); // 6
            motorThree.step(halfRotation * stepsPerRevolution); // 6
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 7
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 8
            motorThree.step(halfRotation * stepsPerRevolution);   // 8
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 9
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 10
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 11
            motorThree.step(halfRotation * stepsPerRevolution); // 11
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 12
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 13
            motorThree.step(halfRotation * stepsPerRevolution); // 13
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution); // 14
            delay(100);
            motorOne.step(upMotion * stepsPerRevolution / 8.0); // 15
            motorThree.step(halfRotation * stepsPerRevolution); // 15
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 16
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 17
            motorThree.step(halfRotation * stepsPerRevolution);   // 17
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 18
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 19
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 20
            motorThree.step(halfRotation * stepsPerRevolution); // 20
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 21
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution);  // 22
            motorThree.step(halfRotation * stepsPerRevolution); // 22
            delay(100);
            motorTwo.step(-halfRotation * stepsPerRevolution); // 23
            delay(100);
            motorOne.step(upMotion * stepsPerRevolution / 8.0); // 24
            motorThree.step(halfRotation * stepsPerRevolution); // 24
            delay(100);
            motorTwo.step(halfSideMotion * stepsPerRevolution); // 25
            delay(100);
            motorOne.step(downMotion * stepsPerRevolution / 8.0); // 26
            delay(100);
            motorThree.step(halfRotation * stepsPerRevolution); // 27

            break;
        case 16621663:     // when the pause button is pressed
            if (mode == 6) // positioning code
            {
                motorTwo.step(halfSideMotion * stepsPerRevolution);
                delay(100);
                motorThree.step(halfRotation * stepsPerRevolution);
            }
            else
            {
                // do nothing
                // since the modes 1, 2, 3, 4, 5 and 7 reset themselves
            }
            break;
        }
        irrecv.resume(); // Receives the next value from the button
    }
    delay(10);
}
