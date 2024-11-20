#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "Morse/Morse.h"
#include "Fingerprint/Fingerprint.h"
#include "Remote/Remote.h"
#include "Lock/Lock.h"
#include "Display/Display.h"
#include "Feedback/Feedback.h"
#include "Cloud/Cloud.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}