#include <stdio.h>
#include <time.h>
#include "gpio.h"
#include "rpiGpio.h"
#include "ThermoCouple.h"

ThermoCouple::ThermoCouple() {
    gpioSetFunction(CS_PIN, output);
    gpioSetPin(CS_PIN, high);
    gpioSetFunction(HEAT_PIN, output);
    gpioSetPin(HEAT_PIN, low);
    gpioSetFunction(CLOCK_PIN, output);
    gpioSetPin(CLOCK_PIN, low);
    gpioSetFunction(DATA_PIN, input);
    gpioSetPullResistor(DATA_PIN, pullup);
}

ThermoCouple::~ThermoCouple() {
    
}

double ThermoCouple::getTemp() {
        int pindata = readSPI();
        if (checkErrors(pindata)) {
            printf("errors on thermocouple\n");
        } else {
            double temp = to_f(data_to_tc_temperature(pindata));
//            double temp = data_to_tc_temperature(pindata);
            return temp;
        }
        return 0;
}

bool ThermoCouple::checkErrors(int data_32) {
        int anyErrors = (data_32 & 0x10000); // Fault bit, D16
        int noConnection = (data_32 & 1); // OC bit, D0
        int shortToGround = (data_32 & 2); // SCG bit, D1
        int shortToVCC = (data_32 & 4); // SCV bit, D2
        if (anyErrors != 0) {
            if (noConnection != 0) {
                printf("No Connection\n");
                return true;
            } else if (shortToGround != 0) {
                printf("Thermocouple short to ground\n");
                return true;
            } else if (shortToVCC != 0) {
                printf("Thermocouple short to VCC\n");
                return true;
            } else {
                // Perhaps another SPI device is trying to send data?
                // Did you remember to initialize all other SPI devices?
                printf("Unknown Error\n");
                return true;
            }
        }
        return false;
}

void ThermoCouple::nsleep(long nanoSeconds) {
    struct timespec req;
    req.tv_sec = 0;
    req.tv_nsec = nanoSeconds;
    nanosleep(&req, NULL);
}

int ThermoCouple::readSPI() {
    
        int bytesin = 0;
        // Select the chip
        gpioSetPin(CS_PIN, low);
        nsleep(10000);
        // Read in 32 bits
        for (int i = 0; i < 32; i++) {
            eState state;
            gpioSetPin(CLOCK_PIN, low);
            bytesin = bytesin << 1;
            gpioReadPin(DATA_PIN, &state);
//      printf("State low %d\n",state);
            gpioSetPin(CLOCK_PIN, high);
            if (state == high) {
                bytesin |= 1;
            }
            gpioSetPin(CLOCK_PIN, high);
        }
        gpioSetPin(CLOCK_PIN, low);
        // Unselect the chip
        gpioSetPin(CS_PIN, high);
        return bytesin;
}

double ThermoCouple::convert_tc_data(int tc_data) {
        int without_resolution;
        if ((tc_data & 0x2000) != 0) {
            // two's compliment
            without_resolution = ~tc_data & 0x1FFF;
            without_resolution += 1;
            without_resolution *= -1;
        } else {
            without_resolution = tc_data & 0x1FFF;
        }

        return without_resolution * 0.25;
}

double ThermoCouple::data_to_tc_temperature(int data_32) {
        int tc_data = ((data_32 >> 18) & 0x3FFF);
        return convert_tc_data(tc_data);
}

double ThermoCouple::to_f(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}