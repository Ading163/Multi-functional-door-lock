#include "Ultrasonic.h"

int Ultrasonic::trig;
int Ultrasonic::echo;

void Ultrasonic::init(int trigPin, int echoPin) {
    trig = trigPin;
    echo = echoPin;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

float Ultrasonic::getDistance() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duration = pulseIn(echo, HIGH);
    // Calculate the distance 
    float distance = duration * 0.034 / 2.0;
    return distance;
}
