# StepperMotorLib
A comprehensive guide to setting up and using the StepperMotor library on Raspberry Pi.

## Prerequisites
Ensure that your system is equipped with the necessary tools:
```bash
sudo apt install -y git build-essential
```

## Setup
### WiringPi Library
First, fetch and install the WiringPi library:
```bash
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
git checkout tags/3.2
./build debian
sudo dpkg -i /home/pi/WiringPi/debian-template/wiringpi_3.2_arm64.deb
```

## Build and Install StepperMotor Library
Clone the StepperMotor repository and compile the source code:
```bash
git clone https://github.com/bmagsalan/StepperMotor.git
cd StepperMotor
make
sudo make install
# Refresh the library cache
sudo ldconfig /usr/local/lib
```

## Configuration
Add your user to the `gpio` group to allow operation without `sudo`:
```bash
sudo usermod -a -G gpio pi
newgrp gpio
```

## Usage
### Compilation
Compile your application with the following commands:
```bash
g++ -o test.bin main.cpp -lsteppermotor -lwiringPi
```

### Running the Application
Execute your compiled application:
```bash
./test.bin
```

### Example
Here is a simple example to control stepper motors using the library:
```c++
#include <StepperMotor.h>
#include <iostream>
#include <string>

int main() {
    StepperMotor motor1(5, 6, 13, 19);
    StepperMotor motor2(14, 15, 18, 23);

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

### Example Command
To control a motor:
```bash
1 start 4096 cw 15 full
```

## Additional Resources
For more information, visit the following links:
- [WiringPi Release 3.2](https://github.com/WiringPi/WiringPi/releases/tag/3.2)
- [RpiMotorLib](https://github.com/gavinlyonsrepo/RpiMotorLib)

This guide ensures a smooth setup and operation of the StepperMotor library for users of all levels.