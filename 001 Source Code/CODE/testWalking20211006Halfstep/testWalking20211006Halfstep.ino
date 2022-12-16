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
 int stepRun = 300;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LF.attach(LFpin);
  LB.attach(LBpin);
  RF.attach(RFpin);
  RB.attach(RBpin);
  LFP.attach(LFPpin);
  LBP.attach(LBPpin);
  RFP.attach(RFPpin);
  RBP.attach(RBPpin);
  calibServo();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //calibServo();
  //turnRightGait();
   //turnLeftGait();
  //straightBackwardGait();
  //straightForwardGait();
int k=0;
  for (k=0;k<2;k++){
    straightForwardGait();
  }
  for (k=0;k<2;k++){
    straightBackwardGait();
  }
  for (k=0;k<2;k++){
    turnRightGait();
  }
  for (k=0;k<2;k++){
    turnLeftGait();
  }
}

void calibServo() {
  LF.write(105); // min 45 at 0 mm  -  max 125 at 100mm
  LB.write(105);// min 45 at 0 mm  -  max 122 at 100mm
  RF.write(105);// min 45 at 0 mm  -  max 125 at 100mm
  RB.write(105);// min 45 at 0 mm  -  max 122 at 100mm
  LFP.write(90); // min 45 at 0 mm  -  max 125 at 100mm
  LBP.write(90);// min 45 at 0 mm  -  max 122 at 100mm
  RFP.write(90);// min 45 at 0 mm  -  max 125 at 100mm
  RBP.write(90);// min 45 at 0 mm  -  max 122 at 100mm
}


//===========================straight forward gait ========================
void straightForwardGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(105);
  RF.write(105);
  RBP.write(75);
  RB.write(105);
  delay(stepRun );
  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(75 + i);
    if (i < 15) {
      RB.write(105 - 4 * i );
    }
    else
    {
      RB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }

  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++)  {
    RFP.write(105 - i);
    if (i < 15) {
      RF.write(105 - 4 * i );
    }
    else
    {
      RF.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }

  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(75 + i);
    RF.write(105);
    RBP.write(105 - i);
    RB.write(105);
    LFP.write(90 + i);
    LF.write(105);
    LBP.write(90 + i);
    LB.write(105);
    delay(stepRun );
    //Serial.println(i);
  }

  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++)  {
    LBP.write(105 - i);
    if (i < 15) {
      LB.write(105 - 4* i );
    }
    else
    {
      LB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }
  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++)  {
    LFP.write(105 - i);
    if (i < 15) {
      LF.write(105 - 4 * i );
    }
    else
    {
      LF.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }
  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(75 + i);
    LF.write(105);
    LBP.write(75 + i);
    LB.write(105);
    RFP.write(90 + i);
    RF.write(105);
    RBP.write(90 - i);
    RB.write(105);
    delay(stepRun );
    //Serial.println(i);
  }

}


//===========================straight backward gait ========================

void straightBackwardGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(75);
  RF.write(105);
  RBP.write(105);
  RB.write(105);
  delay(stepRun );
  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(75 +  i);
    if (i < 15) {
      RF.write(105 - 4*i );
    }
    else
    {
      RF.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }
  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(105 - i);
    if (i < 15) {
      RB.write(105 - 4 * i );
    }
    else
    {
      RB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }



  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(105 - i);
    RF.write(105);
    RBP.write(75 + i);
    RB.write(105);
    LFP.write(90 - i);
    LF.write(105);
    LBP.write(90 - i);
    LB.write(105);
    delay(stepRun );
    //Serial.println(i);
  }
  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(75 + i);
    if (i < 15) {
      LF.write(105 - 4 * i );
    }
    else
    {
      LF.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }

  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++) {
    LBP.write(75 + i);
    if (i < 15) {
      LB.write(105 - 4 * i );
    }
    else
    {
      LB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }

  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(105 - i);
    LF.write(105);
    LBP.write(105 - i);
    LB.write(105);
    RFP.write(90 - i);
    RF.write(105);
    RBP.write(90 + i);
    RB.write(105);
    delay(stepRun );
    //Serial.println(i);
  }
}

//===========================turn Left Gait ========================

void turnLeftGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(105);
  RF.write(105);
  RBP.write(75);
  RB.write(105);
  delay(stepRun );

  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(75 + i);
    if (i < 15) {
      RB.write(105 - 4 * i );
    }
    else
    {
      RB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }

  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(105 - i);
    if (i < 15) {
      RF.write(105 - 4 * i );
    }
    else
    {
      RF.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }

  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(75 + i);
    RF.write(105);
    RBP.write(105 - i);
    RB.write(105);
    LFP.write(90 - i);
    LF.write(105);
    LBP.write(90 - i);
    LB.write(105);
    delay(stepRun );
    //Serial.println(i);
  }


  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(75 + i);
    if (i < 15) {
      LF.write(105 - 4 * i );
    }
    else
    {
      LF.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }
  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++) {
    LBP.write(75 + i);
    if (i < 15) {
      LB.write(105 - 4 * i );
    }
    else
    {
      LB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun );
    // Serial.println(i);
  }
  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(105 - i);
    LF.write(105);
    LBP.write(105 - i);
    LB.write(105);
    RFP.write(90 + i);
    RF.write(105);
    RBP.write(90 - i);
    RB.write(105);
    delay(stepRun );
    //Serial.println(i);
  }
}
//===========================turnRightGait ========================

void turnRightGait()
{
  // ------------------ set initial position ------------------
  LFP.write(90);
  LF.write(105);
  LBP.write(90);
  LB.write(105);
  RFP.write(75);
  RF.write(105);
  RBP.write(105);
  RB.write(105);
  delay(stepRun );


  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(75 + i);
    if (i < 15) {
      RF.write(105 - 4 * i );
    }
    else
    {
      RF.write(45 + 4 * (i-15 ));
    }
    delay(stepRun);
    // Serial.println(i);
  }
  //----------back right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RBP.write(105 - i);
    if (i < 15) {
      RB.write(105 - 4 * i );
    }
    else
    {
      RB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun);
    // Serial.println(i);
  }

  //----------all legs support  ----------


  for (i = 1; i < 16; i++) {
    RFP.write(105 - i);
    RF.write(105);
    RBP.write(75 + i);
    RB.write(105);
    LFP.write(90 + i);
    LF.write(105);
    LBP.write(90 + i);
    LB.write(105);
    delay(stepRun);
    //Serial.println(i);
  }

  //----------back left leg transfer ----------
  for (i = 1; i < 31; i++) {
    LBP.write(105 - i);
    if (i < 15) {
      LB.write(105 - 4 * i );
    }
    else
    {
      LB.write(45 + 4 * (i-15 ) );
    }
    delay(stepRun);
    // Serial.println(i);
  }
  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(105 - i);
    if (i < 15) {
      LF.write(105 - 4 * i );
    }
    else
    {
      LF.write(45 + 4 * (i-15 ));
    }
    delay(stepRun);
    // Serial.println(i);
  }
  //---------------front/back left support
  for (i = 1; i < 16; i++) {
    LFP.write(75 + i);
    LF.write(105);
    LBP.write(75 + i);
    LB.write(105);
    RFP.write(90 - i);
    RF.write(105);
    RBP.write(90 + i);
    RB.write(105);
    delay(stepRun);
    //Serial.println(i);
  }
}
