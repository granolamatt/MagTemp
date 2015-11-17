# MagTemp
A small program to get the temperature and magnetometer data using a Raspberry PI.

This program interfaces with the SparkFun [*LSM303C Breakout (BOB-13303)*](https://www.sparkfun.com/products/13303)
and the MAX31855 thermocouple interface.  I am using the [fork of SparkFun's libraries] (https://github.com/granolamatt/SparkFun_LSM303C_6_DOF_IMU_Breakout_Arduino_Library)
and [Raspberry PI GPIO Interface Library](https://github.com/alanbarr/RaspberryPi-GPIO.git) which I included for convenience.

Load the code into your Raspbery PI and use the compile.sh script to compile.