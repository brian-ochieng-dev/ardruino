#include <IRremote.h>
#include <Stepper.h>

/********** ir receiver **********/

int IR_Recv = 12; // IR Receiver Pin 12,
int led = 13;

IRrecv irrecv(IR_Recv);
decode_results results;

/********** stepper **********/
// set variables
const int stepsPerRevolution = 4;
volatile int count;

// motor one
int upMotion = 2;
int downMotion = -2;
// motor two
int rightSideMotion = 2;
int leftSideMotion = -2;
// motor three
int clockWiseMotion = 1;
int antiClockWiseMotion = -1;

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
            motorOne.step(upMotion * stepsPerRevolution);
            motorOne.step(downMotion * stepsPerRevolution);
            break;
        case 16615543: // when you press the 2 button
            ledOnOff(2);
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);
            motorTwo.step(leftSideMotion * stepsPerRevolution);
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);

            break;
        case 16599223: // when you press the 3 button
            ledOnOff(3);
            motorThree.step(clockWiseMotion * stepsPerRevolution);
            break;
        case 16591063: // when you press the 4 button
            ledOnOff(4);
            count = rightSideMotion / 2;

            // going up
            for (int i = 0; i < count; i++) // bottom center to right (1/16)
            {
                motorOne.step(upMotion / rightSideMotion);
                motorTwo.step(rightSideMotion / rightSideMotion);
            }
            for (int i = 0; i < 3; i++) // 2/16 -> 13/16
            {
                for (int i = 0; i < count * 2; i++)
                {
                    motorOne.step(upMotion / rightSideMotion);
                    motorTwo.step(-rightSideMotion / rightSideMotion);
                }
                for (int i = 0; i < count * 2; i++)
                {
                    motorOne.step(upMotion / rightSideMotion);
                    motorTwo.step(rightSideMotion / rightSideMotion);
                }
            }
            for (int i = 0; i < count * 2; i++) // 14/16 -> 15/16
            {
                motorOne.step(upMotion / rightSideMotion);
                motorTwo.step(-rightSideMotion / rightSideMotion);
            }
            for (int i = 0; i < count; i++) // left to top center(16/16)
            {
                motorOne.step((upMotion / 2) / (rightSideMotion / 2));
                motorTwo.step(rightSideMotion / rightSideMotion);
            }

            // going down
            for (int i = 0; i < count; i++) // top center to left (16/16)
            {
                motorOne.step(downMotion / (leftSideMotion / 2));
                motorTwo.step(leftSideMotion / leftSideMotion);
            }
            for (int i = 0; i < count * 2; i++) // 15/16 -> 14/16
            {
                motorOne.step(downMotion / leftSideMotion);
                motorTwo.step(-leftSideMotion / leftSideMotion);
            }
            for (int i = 0; i < 3; i++) // 13/16 -> 2/16
            {
                for (int i = 0; i < count * 2; i++)
                {
                    motorOne.step(downMotion / leftSideMotion);
                    motorTwo.step(leftSideMotion / leftSideMotion);
                }
                for (int i = 0; i < count * 2; i++)
                {
                    motorOne.step(downMotion / leftSideMotion);
                    motorTwo.step(-leftSideMotion / leftSideMotion);
                }
            }
            for (int i = 0; i < count; i++) // right to top center(1/16)
            {
                motorOne.step(downMotion / (leftSideMotion / 2));
                motorTwo.step(leftSideMotion / leftSideMotion);
            }

            break;
        case 16623703: // when you press the 5 button
            ledOnOff(5);
            count = clockWiseMotion;

            // going up
            for (int i = 0; i < count; i++)
            {
                motorOne.step(upMotion / clockWiseMotion);
                motorThree.step(clockWiseMotion / clockWiseMotion);
            }

            // going down
            for (int i = 0; i < count; i++)
            {
                motorOne.step(downMotion / clockWiseMotion);
                motorThree.step(-clockWiseMotion / clockWiseMotion);
            }

            break;
        case 16607383: // when you press the 6 button
            ledOnOff(6);

            motorOne.step(upMotion * stepsPerRevolution);                // 1
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 2
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 2
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 3
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 4
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 4
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 5
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 6
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 6
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 7
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 8
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 8
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 9
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 10
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 10
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 11
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 12
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 12
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 13
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 14
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 14
            break;
        case 16586983: // when you press the 7 button
            ledOnOff(7);

            motorOne.step(upMotion * stepsPerRevolution);                // 1
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 2
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 2
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 3
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 4
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 4
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 5
            motorOne.step(upMotion * stepsPerRevolution / 2.0);          // 6
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 6
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 7
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 8
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 8
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 9
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 10
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 11
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 11
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 12
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 13
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 13
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 14
            motorOne.step(upMotion * stepsPerRevolution / 2.0);          // 15
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 15
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 16
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 17
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 17
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 18
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 19
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 20
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 20
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 21
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 22
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 22
            motorTwo.step(leftSideMotion * stepsPerRevolution / 2.0);    // 23
            motorOne.step(upMotion * stepsPerRevolution / 2.0);          // 24
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 24
            motorTwo.step(rightSideMotion * stepsPerRevolution / 2.0);   // 25
            motorOne.step(downMotion * stepsPerRevolution / 2.0);        // 26
            motorThree.step(clockWiseMotion * stepsPerRevolution / 2.0); // 27

            break;
        }
        irrecv.resume(); // Receives the next value from the button
    }
    delay(10);
}
