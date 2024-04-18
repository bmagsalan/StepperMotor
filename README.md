# StepperMotorLib
## Setup
```bash
# fetch the source
sudo apt install -y git build-essential
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
git checkout tags/3.2

# build the package
./build debian
sudo dpkg -i /home/pi/WiringPi/debian-template/wiringpi_3.2_arm64.deb
```
## Build and Install
```bash
git clone git@github.com:bmagsalan/StepperMotor.git
cd StepperMotor
make
sudo make install
# Refresh lib cache
sudo ldconfig /usr/local/lib
```
## Usage
Add user to gpio they won't need `sudo` to run.
```bash
sudo usermod -a -G gpio pi
newgrp gpio
```
Example:
```c++
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
```
Buld it:
```bash
g++ -o test.bin main.cpp -lsteppermotor -lwiringPi
./test.bin
# Motor Control (commands: '1 start [steps] [cw/ccw] [speed] [full/half/wave]', '1 stop', '2 start [steps] [cw/ccw] [speed] [full/half/wave]', '2 stop', 'exit'):
1 start 4096 cw 15 "full"
```
## Links
* [wiringPi](https://github.com/WiringPi/WiringPi/releases/tag/3.2)
* [RpiMotorLib](https://github.com/gavinlyonsrepo/RpiMotorLib)