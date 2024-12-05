#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic {
public:
    static void init(int trigPin , int echoPin);  
    static float getDistance();
private:
    static int trig;
    static int echo;
};

#endif // ULTRASONIC_H
