/*
example3-one_shot.ino

This example shows basic data retrieval using the "one-shot" feature i.e. - get the temp
now feature. 

Output Data Rates: 

STTS22H_POWER_DOWN
STTS22H_ONE_SHOT   < -------- This one. 
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

void setup()
{

	Wire.begin();

	Serial.begin(115200);

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
	// Force new reading, temp sensor will power down after conversion. 
	mySTTS.setDataRate(STTS22H_ONE_SHOT); 

	// Enables incrementing register behavior for the IC.
	// It is not enabled by default as the datsheet states and
	// is vital for reading the two temperature registers.
	mySTTS.enableAutoIncrement();

	delay(100);
}

void loop()
{

	// Temp sensor will power down automatically after single read.
	if( mySTTS.dataReady() ) 
	{

		mySTTS.getTemperatureF(&temp);

		// Temperature in different units can be retrieved
		// using the following functions.

		//mySTTS.getTemperatureC(&temp);
		//mySTTS.getTemperatureK(&temp);

		Serial.print("Temp: "); 
		Serial.print(temp);
		Serial.println("F"); 

		// Wait 10 seconds for until we initiate another read.
		delay(10000);

		// Enable another reading.
		mySTTS.setDataRate(STTS22H_ONE_SHOT); 

	} 

	// Demonstrative delay. 
	delay(100);

}
