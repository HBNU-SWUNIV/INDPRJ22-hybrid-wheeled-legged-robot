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
  straightBackwardGait();
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
void straightForwardGait() {
  //----------front/back right support  ----------


  for (i = 1; i < 31; i++) {
    RFP.write(60 + i);
    RF.write(105);
    RBP.write(90 - i);
    RB.write(105);
    delay(50);
    //Serial.println(i);
  }


  //----------back left leg transfer ----------
  for ( i = 30; i > 0; i--) {
    LBP.write(90 + i);
    if (i < 15) {
      LB.write(105 - 2 * i );
    }
    else
    {
      LB.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }
  //----------front left leg transfer  ----------

  for ( i = 30; i > 0; i--) {
    LFP.write(60 + i);
    if (i < 15) {
      LF.write(105 - 2 * i );
    }
    else
    {
      LF.write(45 + 2 * i );
    }
    delay(50);
    // Serial.println(i);
  }
  //---------------front/back left support
  for (i = 1; i < 31; i++) {
    LFP.write(60 + i);
    LF.write(105);
    LBP.write(90 + i);
    LB.write(105);
    delay(50);
    //Serial.println(i);
  }
  //----------back right leg transfer  ----------

  for (i = 1; i <= 30; i++) {
    RBP.write(60 + i);
    if (i < 15) {
      RB.write(105 - 2 * i );
    }
    else
    {
      RB.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }
  //----------front right leg transfer  ----------

  for ( i = 30; i > 0; i--) {
    RFP.write(60 + i);
    if (i < 15) {
      RF.write(105 - 2 * i );
    }
    else
    {
      RF.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }
}


//===========================straight backward gait ========================

void straightBackwardGait() {
  //----------front/back right support  ----------


  for ( i = 30; i > 0; i--) {
    RFP.write(60 + i/2);
    RF.write(105);
    RBP.write(90 - i/2);
    RB.write(105);
    delay(50);
    //Serial.println(i);
  }



  //----------front left leg transfer  ----------

  for (i = 1; i < 31; i++) {
    LFP.write(60 + i);
    if (i < 15) {
      LF.write(105 - 2* i );
    }
    else
    {
      LF.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }

  //----------back left leg transfer ----------
  for  (i = 1; i < 31; i++) {
    LBP.write(90 + i);
    if (i < 15) {
      LB.write(105 - 2 * i );
    }
    else
    {
      LB.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }
  //---------------front/back left support
  for ( i = 30; i > 0; i--) {
    LFP.write(60 + i/2);
    LF.write(105);
    LBP.write(90 + i/2);
    LB.write(105);
      RFP.write(60 + i/2);
    RF.write(105);
    RBP.write(90 - i/2);
    RB.write(105);
    delay(50);
    //Serial.println(i);
  }

  //----------front right leg transfer  ----------

  for (i = 1; i < 31; i++) {
    RFP.write(60 + i);
    if (i < 15) {
      RF.write(105 - 2 * i );
    }
    else
    {
      RF.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }
  //----------back right leg transfer  ----------

  for ( i = 30; i > 0; i--) {
    RBP.write(60 + i);
    if (i < 15) {
      RB.write(105 - 2 * i );
    }
    else
    {
      RB.write(45 + 2 * i );
    }
    delay(100);
    // Serial.println(i);
  }
}
