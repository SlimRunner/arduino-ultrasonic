#include "UltrasonicSensor.hpp"

void setup() { Serial.begin(115200); }

void loop() {
  static UltrasonicSensor ultrasonic(7, 8);
  int cm = ultrasonic.readDistance();
  int inch = ultrasonic.readCache(DistUnit::INCHES);
  Serial.print(cm);
  Serial.print(" cm, ");
  Serial.print(inch);
  Serial.println(" in");
}