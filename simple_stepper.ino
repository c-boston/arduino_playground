// #include <Encoder.h>
// #include <Stepper.h>

// const int stepsPerRevolution = 200;
// Stepper stepperX(stepsPerRevolution, 2, 5);
// Stepper stepperY(stepsPerRevolution, 3, 6);

// Encoder encoder(11, 12);

// void setup()
// {
//   Serial.begin(9600);

//   Serial.println("Start");
//   stepperY.setSpeed(1000);

//   stepperX.setSpeed(1000);
// }

// long oldPosition = 0;
// unsigned long lastTime = 0;

// void loop()
// {
//   long newPosition = encoder.read();

//   long now = millis();
//   if (now - lastTime >= 50)
//   {
//     lastTime = now;

//     int posDiff = oldPosition - newPosition;
//     if (newPosition != oldPosition)
//     {
//       oldPosition = newPosition;
//     }

//     if (posDiff != 0)
//     {
//       int steps = posDiff * 75;
//       Serial.print(steps);
//       stepperY.step(steps);
//       Serial.println(" - done");
//     }
//   }
// }
