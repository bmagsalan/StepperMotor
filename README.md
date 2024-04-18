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
```
## Usage

