
int steps = 1;
int stopAt = 2000; // 1000 steps ~ 125 millimeters

int stepperDelay = 200;

void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.println("SETUP");
}

void loop()
{

  if (steps < stopAt)
  {
    steps++;
    //      Serial.print("STEP ");
    //      Serial.println(steps);

    // X-AXIS MOVEMENT (SINGLE MOTOR) - 5 IS DIRECTION, 2 IS STEP
    digitalWrite(5, HIGH);
    digitalWrite(2, HIGH);
    delayMicroseconds(stepperDelay);
    digitalWrite(2, LOW);
    delayMicroseconds(stepperDelay);

    // Y-AXIS MOVEMENT (DUAL MOTOR) - 6 IS DIRECTION, 3 IS STEP
    digitalWrite(6, LOW);
    digitalWrite(3, HIGH);
    delayMicroseconds(stepperDelay);
    digitalWrite(3, LOW);
    delayMicroseconds(stepperDelay);
  }
}
