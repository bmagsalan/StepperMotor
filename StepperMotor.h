#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <atomic>
#include <thread>
#include <string>

class StepperMotor {
private:
    int pins[4];
    std::atomic<bool> stopRequested;

    void stepMotor(int totalSteps, bool ccw, int stepDelayMicros, const std::string& stepMode);

public:
    StepperMotor(int pin1, int pin2, int pin3, int pin4);
    void start(int steps, bool ccw, int RPM, const std::string& stepMode);
    void stop();
    ~StepperMotor();
};

#endif // STEPPERMOTOR_H
