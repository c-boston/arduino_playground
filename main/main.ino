#include <Encoder.h>

Encoder encoder(11, 12);

const int repairToolTrigger = 9;
const int repairToolMonitor = 10;

void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(repairToolTrigger, OUTPUT);
  pinMode(repairToolMonitor, INPUT_PULLUP);
}

int repairToolState = LOW;
int repairToolLastState = LOW;
bool repairInProgress = false;

int startBound = 0;
long endBoundX = 30000;
long endBoundY = 22000;
long targetY = 0;
long realY = 0;
int currentY = 0;
long targetX = 0;
int currentX = 0;

int loopCount = 0;
int startDeccelAt = 2000;
int topSpeed = 40;
int baseSpeed = 80;

int currentSpeedY = baseSpeed;
int currentSpeedX = baseSpeed;

char sensorMessage;
int beginningStepsConstant = 16800;
int sensorSpacingConstant = 1108;

void loop()
{
  loopCount++;

  if (currentX == targetX)
  {
    if (repairInProgress == true)
    {
      checkRepairState();
      // if no longer in progress now then it finished and send X back home
      if (repairInProgress == false)
      {
        targetX = startBound;
        triggerRepair(false);
      }
    }
    else
    {
      if (currentX == startBound)
      {
        checkSerialReadAndGetTargetX();
      }
      else
      {
        triggerRepair(true);
        repairInProgress = true;
        Serial.println("Repair start");
      }
    }
  }
  else
  {
    processXMove();
  }

  // only read Encoder once X has left the startBound
  if (currentX != startBound)
  {
    readEncoderAndGetNewTargetY();

    // wait for X to finish move before letting Y move
    // if (currentX == targetX)
    processYMove();
  }
}

void triggerRepair(bool turnOn)
{
  if (turnOn == true)
  {
    digitalWrite(repairToolTrigger, HIGH);
  }
  else
  {
    digitalWrite(repairToolTrigger, LOW);
  }
}

void checkRepairState()
{
  int repairToolState = digitalRead(repairToolMonitor);
  if (repairToolState != repairToolLastState)
  {
    if (repairToolState == HIGH)
    {
      Serial.println("Repairing...");
    }
    else
    {
      Serial.println("Repair done");
      repairInProgress = false;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }

  repairToolLastState = repairToolState;
}

String incoming = "";
String inString = "";
bool shouldReturn = false;
void checkSerialReadAndGetTargetX()
{
  while (Serial.available() > 0)
  {
    int inChar = Serial.read();

    if (inChar != '\n')
    {
      inString += (char)inChar;
    }
    else
    {
      Serial.println("-----");
      Serial.print("String received: ");
      Serial.println(inString);

      if (inString == "r")
      {
        targetX = startBound;
      }
      else
      {
        int sensor = inString.toInt();
        Serial.print("Sensor: ");
        Serial.println(sensor);
        targetX = beginningStepsConstant + sensor * sensorSpacingConstant;
        targetX = max(targetX, startBound);
        targetX = min(targetX, endBoundX);
      }
      Serial.print("Target X: ");
      Serial.println(targetX);
      Serial.println("-----");

      // clear the string for new input:
      inString = "";
    }
  }
}

void processXMove()
{
  if (currentX != targetX)
  {
    int direction = HIGH;
    if (currentX < targetX)
    {
      direction = HIGH;
      currentX++;
    }
    else
    {
      direction = LOW;
      currentX--;
    }

    stepX(direction, currentSpeedX);

    int stepsToGo = abs(targetX - currentX);

    if (currentSpeedX > topSpeed && stepsToGo > startDeccelAt && loopCount % 50 == 0)
    {
      currentSpeedX--;
    }

    if (currentSpeedX < baseSpeed && stepsToGo < startDeccelAt && loopCount % 50 == 0)
    {
      currentSpeedX++;
    }
  }
  else
  {
    currentSpeedX = baseSpeed;
  }
}

void processYMove()
{
  if (currentY != targetY)
  {
    int direction = HIGH;
    if (currentY < targetY)
    {
      direction = LOW;
      currentY++;
    }
    else
    {
      direction = HIGH;
      currentY--;
    }

    stepY(direction, currentSpeedY);

    int stepsToGo = abs(targetY - currentY);

    if (currentSpeedY > topSpeed && stepsToGo > startDeccelAt && loopCount % 50 == 0)
    {
      currentSpeedY--;
    }

    if (currentSpeedY < baseSpeed && stepsToGo < startDeccelAt && loopCount % 50 == 0)
    {
      currentSpeedY++;
    }
  }
  else
  {
    currentSpeedY = baseSpeed;
  }
}

long oldPosition = 0;
long newPosition = 0;
long posDiff = 0;
float stepsPerEncoderPosChange = 7;

void readEncoderAndGetNewTargetY()
{
  newPosition = encoder.read();

  if (newPosition != oldPosition)
  {
    posDiff = oldPosition - newPosition;
    oldPosition = newPosition;

    int steps = posDiff * stepsPerEncoderPosChange;

    realY = realY + steps;
    if (realY > endBoundY)
      targetY = endBoundY;
    else if (realY < startBound)
      targetY = startBound;
    else
      targetY = realY;
  }
}

void stepX(int direction, int speed)
{
  digitalWrite(5, direction);
  digitalWrite(2, HIGH);
  delayMicroseconds(speed);
  digitalWrite(2, LOW);
  delayMicroseconds(speed);
}

void stepY(int direction, int speed)
{
  digitalWrite(6, direction);
  digitalWrite(3, HIGH);
  delayMicroseconds(speed);
  digitalWrite(3, LOW);
  delayMicroseconds(speed);
}
