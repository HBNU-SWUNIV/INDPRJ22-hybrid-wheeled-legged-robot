

#include <NineAxesMotion.h>        //Contains the bridge code between the API and the Arduino Environment
#include <Wire.h>
#include <Servo.h>

NineAxesMotion mySensor;         //Object that for the sensor
Servo LF, LB, RF, RB, LFR, LBR, RFR, RBR ;

int LFpin = 24;
int LBpin = 25;
int RFpin = 18;
int RBpin = 19;
int LFRpin = 14;
int LBRpin = 15;
int RFRpin = 16;
int RBRpin = 17;
float rollDeg, rollDegLast, pitchDeg, rollDif, pitchDegLast, alpha, beta;
int d, w, l, dInc, dInc2, dIncCal, dInc2Cal;
float pi = 3.1412;

void setup() {
  // put your setup code here, to run once:
  //Peripheral Initialization
  Serial.begin(115200);           //Initialize the Serial Port to view information on the Serial Monitor
  I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor.
  //Sensor Initialization
  mySensor.initSensor();          //The I2C Address can be changed here inside this function in the library
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  mySensor.setUpdateMode(MANUAL);  //The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions

  getRPY();
  delay(1000);
  //Setting to MANUAL requires fewer reads to the sensor
  LF.attach(LFpin);
  LB.attach(LBpin);
  RF.attach(RFpin);
  RB.attach(RBpin);
  LFR.attach(LFRpin);
  LBR.attach(LBRpin);
  RFR.attach(RFRpin);
  RBR.attach(RBRpin);
  calibServo();
  delay(5000);


}

void loop() {
  // put your main code here, to run repeatedly:
  mySensor.updateEuler();        //Update the Euler data into the structure of the object
  mySensor.updateCalibStatus();  //Update the Calibration Status
  LFR.write(90);
  LBR.write(90);
  RFR.write(90);
  RBR.write(90);
  // width between left wheel and right wheel
  w = 200;
  // distance between front wheel and back wheel
  l = 200;
  // distance for roll compensate
  rollDeg=0;
  pitchDeg=0;
  alpha = (mySensor.readEulerRoll() - rollDeg) * pi / 180;
  dIncCal = tan(abs(alpha)) * w;
  dInc = map(dIncCal, 0, 100, 0, 125 - 45);
  if (alpha > 0) { // robot lean to left side
    //increase the left side cylinder
    LF.write(45 + dInc); // min 45 at 0 mm  -  max 125 at 100mm
    LB.write(45 + dInc); // min 45 at 0 mm  -  max 122 at 100mm
    RF.write(45 ); // min 45 at 0 mm  -  max 125 at 100mm
    RB.write(45 );
    delay(10);

  }
  else
  {
    RF.write(45 + dInc); // min 45 at 0 mm  -  max 125 at 100mm
    RB.write(45 + dInc); // min 45 at 0 mm  -  max 122 at 100mm
    LF.write(45); // min 45 at 0 mm  -  max 125 at 100mm
    LB.write(45); // min 45 at 0 mm  -  max 122 at 100mm
    delay(10);
  }

  beta = (mySensor.readEulerPitch() - pitchDeg) * pi / 180;
  dInc2Cal = tan(abs(beta)) * l;
  dInc2 = map(dInc2Cal, 0, 100, 0, 125 - 45);

  if (beta > 0) { // robot incline front
    //increase the left side cylinder
    LF.write(45 + dInc2); // min 45 at 0 mm  -  max 125 at 100mm
    RF.write(45 + dInc2); // min 45 at 0 mm  -  max 122 at 100mm
    RB.write(45); // min 45 at 0 mm  -  max 125 at 100mm
    LB.write(45); // min 45 at 0 mm  -  max 122 at 100mm
    delay(10);

  }
  else
  {
    RB.write(45 + dInc2); // min 45 at 0 mm  -  max 125 at 100mm
    LB.write(45 + dInc2); // min 45 at 0 mm  -  max 122 at 100mm
    LF.write(45); // min 45 at 0 mm  -  max 125 at 100mm
    RF.write(45); // min 45 at 0 mm  -  max 122 at 100mm
    delay(10);

  }
  Serial.print(alpha);
  Serial.print("  ");
  Serial.print(beta);
  Serial.print("  ");
  Serial.print(mySensor.readEulerPitch());
  Serial.print("  ");
  Serial.print(mySensor.readEulerRoll());
  Serial.print("  ");
  Serial.print(dInc);
  Serial.print("  ");
  Serial.print(dInc2);
  Serial.println();
}

void calibServo() {
  LF.write(45); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(45);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(45);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(45);// min 45 at 0 mm  -  max 122 at 100mm
}

void getRPY() {
  mySensor.updateEuler();        //Update the Euler data into the structure of the object
  mySensor.updateCalibStatus();  //Update the Calibration Status
  rollDeg = mySensor.readEulerRoll();
  pitchDeg = mySensor.readEulerPitch();
}
