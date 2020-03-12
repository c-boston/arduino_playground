
// #include <AccelStepper.h>
// #include <Encoder.h>

// AccelStepper stepperX(AccelStepper::FULL2WIRE, 2, 5);
// AccelStepper stepperY(AccelStepper::FULL2WIRE, 3, 6);

// Encoder encoder(11, 12);

// void setup()
// {
//   Serial.begin(19200);

//   stepperY.setMaxSpeed(10000);
//   stepperY.setAcceleration(10000);

//   stepperX.setMaxSpeed(5000);
//   stepperX.setAcceleration(5000);
//   stepperX.moveTo(50000);
// }

// // based on rough estimate 2400 pulses per encoder revolution and 12800 steps per motor revolution
// float stepsPerEncoderPosChange = 5.3;
// int minYSteps = 0;
// long maxYSteps = 90000;
// long overallY = 0;

// long oldPosition = 0;
// long posDiff = 0;
// unsigned long lastTime = 0;

// void loop()
// {
//   // long newPosition = encoder.read();
//   // long now = millis();

//   // if (now - lastTime >= 100)
//   // {
//   //   lastTime = now;

//   //   if (newPosition != oldPosition)
//   //   {
//   //     posDiff = oldPosition - newPosition;
//   //     oldPosition = newPosition;

//   //     if (posDiff != 0)
//   //     {
//   //       int steps = posDiff * stepsPerEncoderPosChange;

//   //       overallY = overallY + steps;
//   //       overallY = max(overallY, minYSteps);
//   //       overallY = min(overallY, maxYSteps);

//   //       // Serial.println(overallY);
//   //       stepperY.moveTo(overallY);
//   //       stepperX.moveTo(overallY);
//   //     }
//   //   }
//   // }

//   stepperX.run();
//   stepperY.run();
// }
