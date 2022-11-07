/*
example1_basic.ino

This example shows basic data retrieval from the SparkFun Temperature Sensor - STTS22H

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

void setup()
{
	Wire.begin();

	Serial.begin(115200);

	if( !mySTTS.begin() )
	{
		Serial.println("Did not begin.");
		while(1);
	}

}

void loop()
{
	delay(200);
}
