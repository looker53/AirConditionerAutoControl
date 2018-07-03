#include <AirConditionerAutoControl.h>

#define apname "test"
#define apsecret "test"

AirControl air(apname, apsecret);

void setup() {
  Serial.begin(9600);
}

void loop() {
  air.listen();
  delay(50000);
}

