#include <IRremote.h>

int IR_Recv = 12; // IR Receiver Pin 3
int led = 13;
int A = 8;
int B = 9;

IRrecv irrecv(IR_Recv);
decode_results results;

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

void setup()
{
    irrecv.enableIRIn(); // Starts the receiver
    pinMode(led, OUTPUT);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
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
            break;
        case 16615543: // when you press the 2 button
            ledOnOff(2);
            break;
        case 16599223: // when you press the 3 button
            ledOnOff(3);
            break;
        case 16591063: // when you press the 4 button
            ledOnOff(4);
            break;
        case 16623703: // when you press the 5 button
            ledOnOff(5);
            break;
        case 16607383: // when you press the 6 button
            ledOnOff(6);
            break;
        }
        irrecv.resume(); // Receives the next value from the button
    }
    delay(10);
}