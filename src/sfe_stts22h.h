/*
sfe_stts22h.h

This is a library written for SparkFun Temperature Sensor - STTS2H (Qwiic)

SparkFun sells these bpards at its website: www.sparkfun.com

Do you like this library? Help support SparkFun. Buy a board!

SparkFun Temperature Sensor - STTS2H              https://www.sparkfun.com/products/21262
SparkFun Micro Temperature Sensor - STTS2H        https://www.sparkfun.com/products/21051

Written by Elias Santistevan @ SparkFun Electronics, December 2022

Repository:
    https://github.com/sparkfun/SparkFun_STTS22H_Arduino_Library


SparkFun code, firmware, and software is released under the MIT
License(http://opensource.org/licenses/MIT).

SPDX-License-Identifier: MIT

   The MIT License (MIT)

   Copyright (c) 2022 SparkFun Electronics
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions: The
   above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
   "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
   PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

The following class defines all the enabling function for the STTS22H temperature sensor. 
*/

#pragma once

#include "sfe_bus.h"
#include "sfe_stts22h_shim.h"

#define STTS22H_ADDRESS_LOW 0x3F
#define STTS22H_ADDRESS_HIGH 0x38
#define STTS22H_ADDRESS_FIFTEEN 0x3C
#define STTS22H_ADDRESS_FIFTYSIX 0x3E

class QwDevSTTS22H
{
	public: 

		QwDevSTTS22H() : _i2cAddress{0} {};
				
		///////////////////////////////////////////////////// Device communication
		bool init();
		bool isConnected(); // Checks if sensor ack's the I2C request
		uint8_t getUniqueId();

		int32_t writeRegisterRegion(uint8_t reg, uint8_t *data, uint16_t length);
		int32_t readRegisterRegion(uint8_t reg, uint8_t *data, uint16_t length);
		void setCommunicationBus(sfe_STTS22H::QwIDeviceBus &theBus, uint8_t i2cAddress);
		void setCommunicationBus(sfe_STTS22H::QwIDeviceBus &theBus);

		///////////////////////////////////////////////////// General Settings

		bool setDataRate(uint8_t dataRate);
		int8_t getDataRate();
		int8_t getStatus();
		bool enableAutoIncrement(bool enable = true);
		uint8_t getAutoIncrement();
		bool enableBlockDataUpdate(bool enable = true);

		///////////////////////////////////////////////////// Interrupt Settings
		bool setInterruptHighC(float temp);
		bool setInterruptLowC(float temp);
		bool setInterruptHighF(float temp);
		bool setInterruptLowF(float temp);
		bool setInterruptHighK(float temp);
		bool setInterruptLowK(float temp);
		float getInterruptLowC();
		float getInterruptHighC();

		//////////////////////////////////////////////////// Data Retrieval
		bool dataReady();
		bool getTempRaw(int16_t *temperature);
		bool getTemperatureC(float *tempC);
		bool getTemperatureF(float *tempF);
		bool getTemperatureK(float *tempK);

	private: 

		sfe_STTS22H::QwIDeviceBus *_sfeBus; 
		uint8_t _i2cAddress;
		stmdev_ctx_t sfe_dev; 
};

