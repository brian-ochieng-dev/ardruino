void setup()
{
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
}

void clockwise(int period)
{
    digitalWrite(12, LOW);
    digitalWrite(9, HIGH);
    delay(period);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    delay(period);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    delay(period);
    digitalWrite(10, LOW);
    digitalWrite(12, HIGH);
    delay(period);
}

void antiClockwise(int period)
{
    digitalWrite(10, LOW);
    digitalWrite(12, HIGH);
    delay(period);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    delay(period);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    delay(period);
    digitalWrite(12, LOW);
    digitalWrite(9, HIGH);
    delay(period);
}

void halfRotation(int period)
{
    period = period / 2;
    digitalWrite(9, HIGH);
    delay(period);
    digitalWrite(12, LOW);
    delay(period);
    digitalWrite(11, HIGH);
    delay(period);
    digitalWrite(9, LOW);
    delay(period);
    digitalWrite(10, HIGH);
    delay(period);
    digitalWrite(11, LOW);
    delay(period);
    digitalWrite(12, HIGH);
    delay(period);
    digitalWrite(10, LOW);
    delay(period);
}

void loop()
{
    int period = 300;
    int option = 1;
    switch (option)
    {
    case 1:
    {
        clockwise(period);
        break;
    };
    case 2:
    {
        antiClockwise(period);
        break;
    };
    case 3:
    {
        halfRotation(period);
        break;
    };
    default:
    {
        antiClockwise(period);
        break;
    };
    }
}