#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "rpiGpio.h"
#include "SparkFunLSM303C.h"
#include "i2c-dev.h"
#include "ThermoCouple.h"

int mymillis()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec) * 1000 + (tv.tv_usec)/1000;
}


int main(int argc, char *argv[])
{
  
  if (gpioSetup() != OK)
  {
        dbgPrint(DBG_INFO, "gpioSetup failed. Exiting\n");
        return 1;
  }
  LSM303C myIMU;
  ThermoCouple myTC;
  
  sleep(1);
  
  struct  timeval tvBegin, tvEnd,tvDiff;
  int startInt  = mymillis();
  printf("This is my main\n");
    if (myIMU.begin() != IMU_SUCCESS)
  {
    printf("Failed setup.\n");
    _exit(1);
  }
  
  gettimeofday(&tvBegin, NULL);
  
  while(1) {
  startInt = mymillis();
    //Get all parameters
  //printf("\nAccelerometer:\n");
  //printf(" X = ");
  //printf("%f\n",myIMU.readAccelX());
  //printf(" Y = ");
  //printf("%f\n",myIMU.readAccelY());
  //printf(" Z = ");
  //printf("%f\n",myIMU.readAccelZ());

  // Not supported by hardware, so will return NAN
  //printf("\nGyroscope:\n");
  //printf(" X = ");
  //printf("%f",myIMU.readGyroX());
  //printf(" Y = ");
  //printf("%f",myIMU.readGyroY());
  //printf(" Z = ");
  //printf("%f",myIMU.readGyroZ());

  printf("\nMagnetometer:\n");
  printf(" X = ");
  printf("%f",myIMU.readMagX());
  printf(" Y = ");
  printf("%f",myIMU.readMagY());
  printf(" Z = ");
  printf("%f \n",myIMU.readMagZ());

  //printf("\nThermometer:\n");
  //printf(" Degrees C = ");
  //printf("%f",myIMU.readTempC());
  //printf(" Degrees F = ");
  //printf("%f",myIMU.readTempF());
  
  double temp = myTC.getTemp();
  
  
  printf("Thermocouple output is %f\n", temp);
  
	//Each loop should be at least 20ms.
        while(mymillis() - startInt < 200)
        {
            usleep(100);
        }

	printf("Loop Time %d\t", mymillis()- startInt);
  }
  
}
