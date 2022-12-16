#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>
#include <Wire.h>

Servo LF, LB, RF, RB , LFP, LBP, RFP, RBP;
int LFpin = 16;
int LBpin = 15;
int RFpin = 18;
int RBpin = 17;
int LFPpin = 26;
int LBPpin = 24;
int RFPpin = 27;
int RBPpin = 25;
int i;
int stepRun = 150;
int stepInc = 2000;
int m1in1 = 40; //m1 RF
int m1in2 = 39;
//int m1pwm = 6;
int m2in1 = 38;// m2 RB
int m2in2 = 37;
//int m2pwm = 9;
int m3in1 = 36; // m3 LF
int m3in2 = 35;
//int m3pwm = 10;
int m4in1 = 34; //m4 LB
int m4in2 = 33;
//int m4pwm = 11;

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {
  Serial.begin(57600);
  pinMode(m1in1, OUTPUT);
  pinMode(m1in2, OUTPUT);
  pinMode(m2in1, OUTPUT);
  pinMode(m2in2, OUTPUT);
  pinMode(m3in1, OUTPUT);
  pinMode(m3in2, OUTPUT);
  pinMode(m4in1, OUTPUT);
  pinMode(m4in2, OUTPUT);
  LF.attach(LFpin);
  LB.attach(LBpin);
  RF.attach(RFpin);
  RB.attach(RBpin);
  LFP.attach(LFPpin);
  LBP.attach(LBPpin);
  RFP.attach(RFPpin);
  RBP.attach(RBPpin);
  delay(2000);
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  error = ps2x.config_gamepad(49, 47, 48, 46, true, false); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
  setServoNormal();
  delay(2000);
}

void loop() {
  /* You must Read Gamepad to get new values
    Read GamePad and set vibration values
    ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
    if you don't enable the rumble, use ps2x.read_gamepad(); with no values

    you should call this at least once a second
  */

  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) { //Guitar Hero Controller

    return;
  }

  else { //DualShock Controller

    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed




    if (ps2x.Button(PSB_PAD_UP)) {        //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);

      if (ps2x.Button(PSB_GREEN)) {
        setServoNormal();
        runForward();
      }
      if (ps2x.Button(PSB_R2)) {
        straightForwardGait();
        stopMotor();
      }
    }
    else if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      if (ps2x.Button(PSB_GREEN)) {
        setServoNormal();
        turnRight();
      }
      if (ps2x.Button(PSB_PINK)) {
        setServoSide();
        sideRight();
      }
      if (ps2x.Button(PSB_BLUE)) {
        setServoMidRot();
        turnRight();
      }
      if (ps2x.Button(PSB_RED)) {
        setServoRightRot();
        turnRight();
      }
      if (ps2x.Button(PSB_R2)) {
        turnRightGait();
        stopMotor();
      }
    }
    else if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      if (ps2x.Button(PSB_GREEN)) {
        setServoNormal();
        turnLeft();
      }
      if (ps2x.Button(PSB_PINK)) {
        setServoSide();
        sideLeft();
      }
      if (ps2x.Button(PSB_BLUE)) {
        setServoMidRot();
        turnLeft();
      }
      if (ps2x.Button(PSB_RED)) {
        setServoLeftRot();
        turnLeft();
      }
      if (ps2x.Button(PSB_R2)) {
        turnLeftGait();
        stopMotor();
      }
    }
    else if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      if (ps2x.Button(PSB_GREEN)) {
        setServoNormal();
        runBackward();
      }

      if (ps2x.Button(PSB_R2)) {
        straightBackwardGait();
        stopMotor();
      }
    }
    else
    {
      stopMotor();
    }
  }
  delay(50);
}

void runBackward() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, LOW);
  digitalWrite(m1in2, HIGH);
  digitalWrite(m2in1, LOW);
  digitalWrite(m2in2, HIGH);
  digitalWrite(m3in1, HIGH);
  digitalWrite(m3in2, LOW);
  digitalWrite(m4in1, HIGH);
  digitalWrite(m4in2, LOW);
  Serial.println("Run forward");
}
void runForward() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, !LOW);
  digitalWrite(m1in2, !HIGH);
  digitalWrite(m2in1, !LOW);
  digitalWrite(m2in2, !HIGH);
  digitalWrite(m3in1, !HIGH);
  digitalWrite(m3in2, !LOW);
  digitalWrite(m4in1, !HIGH);
  digitalWrite(m4in2, !LOW);
  Serial.println("Run backward");
}

void turnRight() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, HIGH);
  digitalWrite(m1in2, LOW);
  digitalWrite(m2in1, HIGH);
  digitalWrite(m2in2, LOW);
  digitalWrite(m3in1, HIGH);
  digitalWrite(m3in2, LOW);
  digitalWrite(m4in1, HIGH);
  digitalWrite(m4in2, LOW);
  Serial.println("turn left");
}

void turnLeft() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, !HIGH);
  digitalWrite(m1in2, !LOW);
  digitalWrite(m2in1, !HIGH);
  digitalWrite(m2in2, !LOW);
  digitalWrite(m3in1, !HIGH);
  digitalWrite(m3in2, !LOW);
  digitalWrite(m4in1, !HIGH);
  digitalWrite(m4in2, !LOW);
  Serial.println("turn right");
}
void stopMotor() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, LOW);
  digitalWrite(m1in2, LOW);
  digitalWrite(m2in1, LOW);
  digitalWrite(m2in2, LOW);
  digitalWrite(m3in1, LOW);
  digitalWrite(m3in2, LOW);
  digitalWrite(m4in1, LOW);
  digitalWrite(m4in2, LOW);
  Serial.println("stop motor");
}

void calibServo() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90 + 35); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90 - 35); // min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90 - 30); // min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90 + 30); // min 45 at 0 mm  -  max 122 at 100mm
}

void setServoNormal() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90 + 35); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90 - 35); // min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90 - 25); // min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90 + 30); // min 45 at 0 mm  -  max 122 at
}


void setServoSide() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90 - 30); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90 + 30); // min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90 + 30); // min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90 - 35); // min 45 at 0 mm  -  max 122 at 100mm
}
void setServoMidRot() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90);// min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90);// min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90);// min 45 at 0 mm  -  max 122 at 100mm
}

void setServoRightRot() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90 + 15); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90 - 15); // min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90 - 40); // min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90 + 40); // min 45 at 0 mm  -  max 122 at 100mm
}

void setServoLeftRot() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90 + 45); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90 - 45); // min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90 - 15); // min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90 + 15); // min 45 at 0 mm  -  max 122 at 100mm
}
void setServoParallel() {
  LF.write(50); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(50);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(50);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90); // min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90); // min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90); // min 45 at 0 mm  -  max 122 at 100mm
}

void sideRight() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, LOW);
  digitalWrite(m1in2, HIGH);
  digitalWrite(m2in1, HIGH);
  digitalWrite(m2in2, LOW);
  digitalWrite(m3in1, LOW);
  digitalWrite(m3in2, HIGH);
  digitalWrite(m4in1, HIGH);
  digitalWrite(m4in2, LOW);
  Serial.println("side right");
}
void sideLeft() {
  //  analogWrite(m1pwm, 250);
  //  analogWrite(m2pwm, 250);
  //  analogWrite(m3pwm, 250);
  //  analogWrite(m4pwm, 250);
  digitalWrite(m1in1, !LOW);
  digitalWrite(m1in2, !HIGH);
  digitalWrite(m2in1, !HIGH);
  digitalWrite(m2in2, !LOW);
  digitalWrite(m3in1, !LOW);
  digitalWrite(m3in2, !HIGH);
  digitalWrite(m4in1, !HIGH);
  digitalWrite(m4in2, !LOW);
  Serial.println("side left");
}

void straightForwardGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(75);
  RF.write(105);
  RBP.write(75);
  RB.write(105);
  delay(stepRun );
  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(75 + i);
    if (i < 16) {
      RB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++)  {
    RFP.write(75 + i);
    if (i < 16) {
      RF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RF.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(105 - i);
    RF.write(105);
    RBP.write(105 - i);
    RB.write(105);
    LFP.write(90 + i);
    LF.write(105);
    LBP.write(90 + i);
    LB.write(105);
    stopMotor();
    delay(stepRun );
    //Serial.println(i);
  }
  delay(stepInc);
  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++)  {
    LBP.write(105 - i);
    if (i < 16) {
      LB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++)  {
    LFP.write(105 - i);
    if (i < 16) {
      LF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LF.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //---------------all legs support -------------------
  for (i = 1; i < 16; i++) {
    LFP.write(75 + i);
    LF.write(105);
    LBP.write(75 + i);
    LB.write(105);
    RFP.write(90 - i);
    RF.write(105);
    RBP.write(90 - i);
    RB.write(105);
    stopMotor();
    delay(stepRun );
    //Serial.println(i);
  }
  delay(stepInc);

}


//===========================straight backward gait ========================

void straightBackwardGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(105);
  RF.write(105);
  RBP.write(105);
  RB.write(105);
  stopMotor();
  delay(stepRun );
  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(105 -  i);
    if (i < 16) {
      RF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RF.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  //----------back right leg transfer  ----------
  delay(stepInc);
  for (i = 1; i < 31; i++) {
    RBP.write(105 - i);
    if (i < 16) {
      RB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);


  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(75 + i);
    RF.write(105);
    RBP.write(75 + i);
    RB.write(105);
    LFP.write(90 - i);
    LF.write(105);
    LBP.write(90 - i);
    LB.write(105);
    stopMotor();
    delay(stepRun );
    //Serial.println(i);
  }
  delay(stepInc);
  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(75 + i);
    if (i < 16) {
      LF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LF.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++) {
    LBP.write(75 + i);
    if (i < 16) {
      LB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(105 - i);
    LF.write(105);
    LBP.write(105 - i);
    LB.write(105);
    RFP.write(90 + i);
    RF.write(105);
    RBP.write(90 + i);
    RB.write(105);
    stopMotor();
    delay(stepRun );
    //Serial.println(i);
  }
  delay(stepInc);
}

//===========================turn Left Gait ========================

void turnLeftGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(75);
  RF.write(105);
  RBP.write(75);
  RB.write(105);
  stopMotor();
  delay(stepRun );

  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(75 + i);
    if (i < 16) {
      RB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(75 + i);
    if (i < 16) {
      RF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RF.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(105 - i);
    RF.write(105);
    RBP.write(105 - i);
    RB.write(105);
    LFP.write(90 - i);
    LF.write(105);
    LBP.write(90 - i);
    LB.write(105);
    stopMotor();
    delay(stepRun );

    //Serial.println(i);
  }
  delay(stepInc);

  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(75 + i);
    if (i < 16) {
      LF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LF.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++) {
    LBP.write(75 + i);
    if (i < 16) {
      LB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun );
    // Serial.println(i);
  }
  delay(stepInc);
  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(105 - i);
    LF.write(105);
    LBP.write(105 - i);
    LB.write(105);
    RFP.write(90 - i);
    RF.write(105);
    RBP.write(90 - i);
    RB.write(105);
    stopMotor();
    delay(stepRun );
    //Serial.println(i);
  }
  delay(stepInc);
}
//===========================turnRightGait ========================

void turnRightGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(105);
  RF.write(105);
  RBP.write(105);
  RB.write(105);
  stopMotor();
  delay(stepRun );


  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(105 - i);
    if (i < 16) {
      RF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RF.write(45 + 4 * (i - 15 ));
      stopMotor();
    }
    delay(stepRun);
    // Serial.println(i);
  }
  delay(stepInc);
  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(105 - i);
    if (i < 16) {
      RB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      RB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun);
    // Serial.println(i);
  }
  delay(stepInc);
  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(75 + i);
    RF.write(105);
    RBP.write(75 + i);
    RB.write(105);
    LFP.write(90 + i);
    LF.write(105);
    LBP.write(90 + i);
    LB.write(105);
    stopMotor();
    delay(stepRun);
    //Serial.println(i);
  }
  delay(stepInc);
  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++) {
    LBP.write(105 - i);
    if (i < 16) {
      LB.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LB.write(45 + 4 * (i - 15 ) );
      stopMotor();
    }
    delay(stepRun);
    // Serial.println(i);
  }
  delay(stepInc);
  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(105 - i);
    if (i < 16) {
      LF.write(105 - 4 * i );
      stopMotor();
    }
    else
    {
      LF.write(45 + 4 * (i - 15 ));
      stopMotor();
    }
    delay(stepRun);
    // Serial.println(i);
  }
  delay(stepInc);
  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(75 + i);
    LF.write(105);
    LBP.write(75 + i);
    LB.write(105);
    RFP.write(90 + i);
    RF.write(105);
    RBP.write(90 + i);
    RB.write(105);
    stopMotor();
    delay(stepRun);
    //Serial.println(i);
  }
  delay(stepInc);
}
