const int repairToolTrigger = 9;
const int repairToolMonitor = 10;

int repairToolState = HIGH;
int repairToolLastState = HIGH;
bool repairInProgress = false;

void setup()
{
    Serial.begin(9600);

    pinMode(repairToolTrigger, OUTPUT);
    pinMode(repairToolMonitor, INPUT);
}

void loop()
{
    if (repairInProgress == false)
    {
        // wait 5 seconds before triggering
        delay(5000);

        triggerRepair(true);
        repairInProgress = true;
        Serial.println('Repair start');
    }
    else
    {
        checkRepairState();
        // if now its false then repair cycle must be done
        if (repairInProgress == false)
        {
            triggerRepair(false);
        }
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
        if (repairToolState == LOW)
        {
            Serial.println('Repairing...');
        }
        else
        {
            Serial.println('Repair done');
            repairInProgress = false;
        }
        // Delay a little bit to avoid bouncing
        delay(50);
    }

    repairToolLastState = repairToolState;
}
