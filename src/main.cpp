#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

    int val = analogRead(A0);
    Serial.println(val);
    delay(500);

    // put your main code here, to run repeatedly:
}