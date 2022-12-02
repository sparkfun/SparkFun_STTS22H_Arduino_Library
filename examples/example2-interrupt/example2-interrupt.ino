/*
example2_basic.ino

This example desmonstrates how to set temperature thresholds to trigger an interrupt. 

Output Data Rates: 

STTS22H_POWER_DOWN
STTS22H_ONE_SHOT  
STTS22H_1Hz       
STTS22H_25Hz      
STTS22H_50Hz      
STTS22H_100Hz     
STTS22H_200Hz     

Written by: 
Elias Santistevan @ SparkFun Electronics December, 2022

Products: 
   SparkFun Temperature Sensor - STTS2H              https://www.sparkfun.com/products/21262
   SparkFun Micro Temperature Sensor - STTS2H        https://www.sparkfun.com/products/21051
 
Repository:
     https://github.com/sparkfun/SparkFun_STTS22H_Arduino_Library

SparkFun code, firmware, and software is released under the MIT
License(http://opensource.org/licenses/MIT).

*/

#include <Wire.h>
#include "SparkFun_STTS22H.h"

SparkFun_STTS22H mySTTS; 

float temp; 

// These values are in Farenheit
float interruptHighValue = 90.5;
float interruptLowValue = 42.0;

int tempInterrupt = 1; 

void setup()
{

	Wire.begin();

	Serial.begin(115200);

	pinMode(tempInterrupt, INPUT);

	if( !mySTTS.begin() )
	{
		Serial.println("Did not begin.");
		while(1);
	}

	Serial.println("Ready");

	// Other output data rates can be found in the description
	// above. To change the ODR or mode, the device must first be
	// powered down.
	mySTTS.setDataRate(STTS22H_POWER_DOWN);
	delay(10);
	mySTTS.setDataRate(STTS22H_25Hz);

	// Enables incrementing register behavior for the IC.
	// It is not enabled by default as the datsheet states and
	// is vital for reading the two temperature registers.
	mySTTS.enableAutoIncrement();


	// Set interrupts for both lower and higher thresholds.
	// Note: These functions accept Farenheit as their arguments.
	// Other functions for different units just below. 
	mySTTS.setInterruptLowF(interruptLowValue);
	mySTTS.setInterruptHighF(interruptHighValue);

	//mySTTS.setInterruptLowC(interruptLowValue);
	//mySTTS.setInterruptHighC(interruptHighValue);

	//mySTTS.setInterruptLowK(interruptLowValue);
	//mySTTS.setInterruptHighK(interruptHighValue);

	delay(100);
}

void loop()
{

	// Checking if data ready is not necessary when output is set higher 
	// than 1Hz. 
	mySTTS.getTemperatureF(&temp);

	// Temperature in different units can be retrieved
	// using the following functions.

	//mySTTS.getTemperatureC(&temp);
	//mySTTS.getTemperatureK(&temp);

	Serial.print("Temp: "); 
	Serial.print(temp);
	Serial.println("F"); 

	if( digitalRead(tempInterrupt) == LOW )
	{
		Serial.println("Temperature threshold"); 
		while(1);
	}

	// delay = 1/ODR 
	delay(40);

}
