// Test derrived class for base class SparkFunIMU
#ifndef __THERMOCOUPLE_H__
#define __THERMOCOUPLE_H__


class ThermoCouple
{
    private:
        bool checkErrors(int data_32);
        int readSPI();
        double convert_tc_data(int tc_data);
        double data_to_tc_temperature(int data_32);
        double to_f(double celsius);
        void nsleep(long nanoSeconds);
        const int CS_PIN = 23;
        const int CLOCK_PIN = 25;
        const int DATA_PIN = 24;
        const int HEAT_PIN = 4;
        const double CYCLE = 1.0e3;
        
    public:
        ThermoCouple();
        ~ThermoCouple();
        double getTemp();
        
    
};

#endif // __THERMOCOUPLE_H__
