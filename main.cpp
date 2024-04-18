#include <StepperMotor.h>
#include <iostream>
#include <string>

int main() {
    StepperMotor motor1(5, 6, 13, 19); // Motor 1 using GPIO BCM pin numbers
    StepperMotor motor2(14, 15, 18, 23); // Motor 2 using GPIO BCM pin numbers

    std::string command;
    int steps, speed;
    bool ccw;
    std::string stepMode;
    std::cout << "Motor Control (commands: '1 start [steps] [cw/ccw] [speed] [full/half/wave]', '1 stop', '2 start [steps] [cw/ccw] [speed] [full/half/wave]', '2 stop', 'exit'):" << std::endl;

    while (true) {
        std::cin >> command;
        if (command == "1") {
            std::cin >> command;
            if (command == "start") {
                std::cin >> steps >> command >> speed >> stepMode;
                ccw = (command == "ccw");
                motor1.start(steps, ccw, speed, stepMode);
            } else if (command == "stop") {
                motor1.stop();
            }
        } else if (command == "2") {
            std::cin >> command;
            if (command == "start") {
                std::cin >> steps >> command >> speed >> stepMode;
                ccw = (command == "ccw");
                motor2.start(steps, ccw, speed, stepMode);
            } else if (command == "stop") {
                motor2.stop();
            }
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}