#include <PS4Controller.h>

const int lLocoDir = 16;
const int lLocoPwm = 17;

const int rLocoDir = 18;
const int rLocoPwm = 19;

const int lLiftDir = 22;
const int lLiftPwm = 23;

const int rLiftDir = 25;
const int rLiftPwm = 26;

class Motor {
  private:

  int pwmChannel;
  int dirPin;
  int pwmPin;
  int resolution;
  int maxPwm, minPwm;

  public:

  Motor(int pwmChannel, int dirPin, int pwmPin, int resolution = 8, int frequency = 30000) {
    this->pwmChannel = pwmChannel;
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->resolution = resolution;
    this->maxPwm = int(pow(2, resolution) - 1);
    this->minPwm = int(-pow(2, resolution) + 1);
    ledcSetup(pwmChannel, frequency, resolution);
    ledcAttachPin(pwmPin, pwmChannel);
  }

  void setSpeed(int pwm) {
    pwm = max(min(maxPwm, pwm), minPwm);
    digitalWrite(dirPin, pwm > 0 ? HIGH : LOW);
    ledcWrite(pwmChannel, abs(pwm));
  }

};

int deadzone(int n) {
  if (abs(n) < 10) {
    return 0;
  } else {
    if (n > 0) {
      return n - 10;
    } else {
      return n + 10;
    }
  }
}

void setup() {
  Serial.begin(115200);
  PS4.begin("3c:a6:f6:21:ba:85");
  Serial.println("Ready.");
}

Motor lLoco(0, lLocoDir, lLocoPwm);
Motor rLoco(1, rLocoDir, rLocoPwm);
Motor lLift(2, lLiftDir, lLiftPwm);
Motor rLift(3, rLiftDir, rLiftPwm);

void loop() {

  if (PS4.isConnected()) {
    int x = deadzone(PS4.LStickX());
    int y = deadzone(PS4.LStickY());
    int l2 = PS4.L2Value();
    int r2 = PS4.R2Value();

    lLoco.setSpeed(y*2);
    rLoco.setSpeed(y*2);

    lLift.setSpeed(r2-l2);
    rLift.setSpeed(r2-l2);

    Serial.printf("%d %d %d %d\n", x, y, l2, r2);
  } else {
    Serial.println("NC");
    lLoco.setSpeed(0);
    rLoco.setSpeed(0);
    lLift.setSpeed(0);
    rLift.setSpeed(0);
  }
}
