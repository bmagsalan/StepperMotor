#include "StepperMotor.h"
#include <wiringPi.h>
#include <unistd.h>

StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4) : stopRequested(false) {
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;
    wiringPiSetupGpio();  // Use Broadcom GPIO pin numbers
    for (int i = 0; i < 4; ++i) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
}

void StepperMotor::start(int steps, bool ccw, int RPM, const std::string& stepMode) {
    stopRequested = false;
    int delayMicros = 60000000 / (4096 * RPM); // Convert RPM to delay in microseconds
    std::thread motorThread(&StepperMotor::stepMotor, this, steps, ccw, delayMicros, stepMode);
    motorThread.detach();
}

void StepperMotor::stop() {
    stopRequested = true;
}

StepperMotor::~StepperMotor() {
    stop();
    for (int pin : pins) {
        digitalWrite(pin, LOW);
    }
}

void StepperMotor::stepMotor(int totalSteps, bool ccw, int stepDelayMicros, const std::string& stepMode) {
    int halfStepSequence[][4] = {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {1, 0, 0, 1}
    };
    int fullStepSequence[][4] = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {1, 0, 0, 1}
    };
    int waveStepSequence[][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    int(*stepSequence)[4];
    int stepCount;

    if (stepMode == "full") {
        stepSequence = fullStepSequence;
        stepCount = sizeof(fullStepSequence) / sizeof(fullStepSequence[0]);
    } else if (stepMode == "wave") {
        stepSequence = waveStepSequence;
        stepCount = sizeof(waveStepSequence) / sizeof(waveStepSequence[0]);
    } else { // Default to half-step if anything else
        stepSequence = halfStepSequence;
        stepCount = sizeof(halfStepSequence) / sizeof(halfStepSequence[0]);
    }

    for (int i = 0; i < totalSteps && !stopRequested; ++i) {
        int index = ccw ? (stepCount - 1 - (i % stepCount)) : (i % stepCount);
        for (int pin = 0; pin < 4; ++pin) {
            digitalWrite(pins[pin], stepSequence[index][pin]);
        }
        usleep(stepDelayMicros);
    }
    for (int pin : pins) {  // Ensure all pins are low after stopping
        digitalWrite(pin, LOW);
    }
}
