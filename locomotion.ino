#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

// =============================== CONSTANTS ===============================

// Motor pins to be configured
const int lLocoDir = 19; 
const int lLocoPWM = 18; 

// int L2Pin1 = 27; 
// int L2Pin2 = 26; 
// int L2enable = 14; 

const int rLocoDir = 17; 
const int rLocoPWM = 16; 

// int R2Pin1 = 27; 
// int R2Pin2 = 26; 
// int R2enable = 14; 

const int lPWMchannel = 0;
// const int pwmL2 = 1;
const int rPWMchannel = 2;
// const int pwmR2 = 3;

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

    // X AND Y will be outputs of deadzone function

    if( x < 0 ) {
      // Reverse
      digitalWrite(lLocoDir, LOW);

      // digitalWrite(L2Pin1, LOW);
      // digitalWrite(L2Pin2, HIGH);

      digitalWrite(rLocoDir, LOW);

      // digitalWrite(R2Pin1, LOW);
      // digitalWrite(R2Pin2, HIGH);

      int t1 = map(abs(x), -128, -1, 255, 0);

      // Left
      if( y < 0 ) {
        int t2 = map(y, -128, -1, mag, 0);
        ledcWrite(lLocoPWM, t1-t2);
        // ledcWrite(pwmL2, t1-t2);
        ledcWrite(rLocoPWM, t1+t2);
        // ledcWrite(pwmR2, t1+t2);
      }

      // Right
      else {
        int t2 = map(y, 0, 127, 0, mag);
        ledcWrite(lLocoPWM, t1+t2);
        // ledcWrite(pwmL2, t1+t2);
        ledcWrite(rLocoPWM, t1-t2);
        // ledcWrite(pwmR2, t1-t2);
      }
  }
  // Forward
  else if( x > 0 ) {

    digitalWrite(lLocoDir, HIGH);

    // digitalWrite(L2Pin1, HIGH);
    // digitalWrite(L2Pin2, LOW);

    digitalWrite(rLocoDir, HIGH);

    // digitalWrite(R2Pin1, HIGH);
    // digitalWrite(R2Pin2, LOW);

    int t1 = map(abs(x), 0, 127, 255, 0);

    // LEFT
    if( y < 0 ) {
      int t2 = map(y, -128, -1, mag, 0);
      ledcWrite(lLocoPWM, t1-t2);
      // ledcWrite(pwmL2, t1-t2);
      ledcWrite(rLocoPWM, t1+t2);
      // ledcWrite(pwmR2, t1+t2);
    }

    // RIGHT
    else {
      int t2 = map(y, 0, 127, 0, mag);
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

  ledcAttachPin(lLocoPWM, lPWMchannel);
  ledcAttachPin(rLocoPWM, rPWMchannel);

  ledcSetup(lPWMchannel, frequency, resolution);
  ledcSetup(rPWMchannel, frequency, resolution);

 
  Serial.begin(115200);
}
 
void loop() {
  int tx = deadzone(PS4.LStickX());
  int ty = deadzone(PS4.LStickY());
  int x = map()
  Serial.printf("%d %d\n", x, y);
}



