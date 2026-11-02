
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>

// LEFT MOTOR
#define ENA 25
#define IN1 26
#define IN2 27

// RIGHT MOTOR
#define ENB 14
#define IN3 32
#define IN4 33

// PWM speed
int motorSpeed = 150;
const int speedStep = 20;

// Button state tracking
bool lastSquare = false;
bool lastCircle = false;

// Motor control
void leftMotor(int direction, int speedValue) {

  if (direction == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (direction == -1) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  analogWrite(ENA, speedValue);
}

void rightMotor(int direction, int speedValue) {

  if (direction == 1) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (direction == -1) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  analogWrite(ENB, speedValue);
}

// Movement functions
void forward() {
  leftMotor(1, motorSpeed);
  rightMotor(1, motorSpeed);
}

void backward() {
  leftMotor(-1, motorSpeed);
  rightMotor(-1, motorSpeed);
}

void turnLeft() {
  leftMotor(-1, motorSpeed);
  rightMotor(1, motorSpeed);
}

void turnRight() {
  leftMotor(1, motorSpeed);
  rightMotor(-1, motorSpeed);
}

void stopMotors() {
  leftMotor(0, 0);
  rightMotor(0, 0);
}

// Setup
void setup() {

  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  // Start Bluetooth using Dabble
  Dabble.begin("UGV_Dabble");

  Serial.println("UGV Started");
  Serial.println("Connect through Dabble GamePad");
}

// Main loop
void loop() {

  Dabble.processInput();

  // Increase speed using SQUARE
  bool square = GamePad.isSquarePressed();

  if (square && !lastSquare) {
    motorSpeed += speedStep;

    if (motorSpeed > 255)
      motorSpeed = 255;

    Serial.print("Speed: ");
    Serial.println(motorSpeed);
  }

  lastSquare = square;

  // Decrease speed using CIRCLE
  bool circle = GamePad.isCirclePressed();

  if (circle && !lastCircle) {
    motorSpeed -= speedStep;

    if (motorSpeed < 0)
      motorSpeed = 0;

    Serial.print("Speed: ");
    Serial.println(motorSpeed);
  }

  lastCircle = circle;

  // Movement controls
  if (GamePad.isCrossPressed()) {
    stopMotors();
  }
  else if (GamePad.isUpPressed()) {
    forward();
  }
  else if (GamePad.isDownPressed()) {
    backward();
  }
  else if (GamePad.isLeftPressed()) {
    turnLeft();
  }
  else if (GamePad.isRightPressed()) {
    turnRight();
  }
  else {
    stopMotors();
  }
}
