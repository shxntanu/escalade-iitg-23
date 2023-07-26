#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

// =============================== CONSTANTS ===============================

// Motor pins to be configured
const int lLocoDir = 19; 
const int lLocoPWM = 18; 

const int rLocoDir = 17; 
const int rLocoPWM = 16; 

const int lPWMchannel = 0;
const int rPWMchannel = 1;

const int frequency = 30000;
const int resolution = 8;
const int mag = 50;
const int dutyCycle = 200;

// =============================== FUNCTIONS ===============================

// ****** DEADZONE ******

int deadzone(int x) {
  if(abs(x) < 8)
    return 0;
  else if(x>=8)
    return x-8;
  else
    return x+8;
}

// ****** LOCOMOTION ******

void Locomotion(int x, int y) {

    if( y < 0 ) {

      digitalWrite(lLocoDir, LOW);
      digitalWrite(rLocoDir, LOW);

      int t1 = map(abs(y), -128, -1, 255, 0);

      // Left
      if( x < 0 ) {
        int t2 = map(x, -128, -1, mag, 0);
        ledcWrite(lLocoPWM, t1-t2);
        ledcWrite(rLocoPWM, t1+t2);
      }

      // Right
      else {
        int t2 = map(x, 0, 127, 0, mag);
        ledcWrite(lLocoPWM, t1+t2);
        // ledcWrite(pwmL2, t1+t2);
        ledcWrite(rLocoPWM, t1-t2);
        // ledcWrite(pwmR2, t1-t2);
      }
  }
  // Forward
  else if( y > 0 ) {

    digitalWrite(lLocoDir, HIGH);

    // digitalWrite(L2Pin1, HIGH);
    // digitalWrite(L2Pin2, LOW);

    digitalWrite(rLocoDir, HIGH);

    // digitalWrite(R2Pin1, HIGH);
    // digitalWrite(R2Pin2, LOW);

    int t1 = map(abs(y), 0, 127, 255, 0);

    // LEFT
    if( x < 0 ) {
      int t2 = map(x, -128, -1, mag, 0);
      ledcWrite(lLocoPWM, t1-t2);
      // ledcWrite(pwmL2, t1-t2);
      ledcWrite(rLocoPWM, t1+t2);
      // ledcWrite(pwmR2, t1+t2);
    }

    // RIGHT
    else {
      int t2 = map(x, 0, 127, 0, mag);
      ledcWrite(lLocoPWM, t1+t2);
      // ledcWrite(pwmL2, t1+t2);
      ledcWrite(rLocoPWM, t1-t2);
      // ledcWrite(pwmR2, t1-t2);
    }
  }
}
 
void setup() {

  // PS4 Setup

  PS4.begin("9c:b6:d0:90:37:c2");
  Serial.println("Ready.");

  // PWM Setup

  ledcSetup(lPWMchannel, frequency, resolution);
  ledcSetup(rPWMchannel, frequency, resolution);

  ledcAttachPin(lLocoPWM, lPWMchannel);
  ledcAttachPin(rLocoPWM, rPWMchannel);
 
  Serial.begin(115200);
}
 
void loop() {
  int x = deadzone(PS4.LStickX());
  int y = deadzone(PS4.LStickY());

  digitalWrite(lLocoDir, y > 0 ? HIGH : LOW);
  digitalWrite(rLocoDir, y > 0 ? HIGH : LOW);

  ledcWrite(lPWMchannel, abs(y));
  ledcWrite(rPWMchannel, abs(y));

  Serial.printf("%d %d\n", x, y);
}



