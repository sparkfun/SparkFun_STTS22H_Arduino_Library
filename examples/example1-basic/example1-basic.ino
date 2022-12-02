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
#include "SparkFun_Qwiic_OLED.h"
#include <string>

int intTemp = 1;


SparkFun_STTS22H mySTTS; 
QwiicMicroOLED oled; 
String highTemp = "High Temp";

float tempF; 

void setup()
{
	pinMode(intTemp, INPUT);

	Wire.begin();

	Serial.begin(115200);

	if( !mySTTS.begin() || !oled.begin())
	{
		Serial.println("Did not begin.");
		while(1);
	}

	mySTTS.setDataRate(STTS22H_50Hz);
	mySTTS.enableAutoIncrement();

	mySTTS.setInterruptHighF(80);



}

void loop()
{

	if( mySTTS.dataReady() )
	{
		mySTTS.getTemperatureF(&tempF);
		Serial.print("Temp: "); 
		Serial.print(tempF);
		Serial.println("F"); 
	}

	oled.setCursor(0,0);
	oled.erase();
	oled.print(tempF);
	oled.display();
	delay(200);

	if( digitalRead(intTemp) == LOW )
	{
		oled.setCursor(0,0);
		oled.erase();
		oled.print(highTemp);
		Serial.println("Interrupt!");
		while(1);
	}


}
