/*
SparkFun_STTS22H.h

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


The following class specifies the Arduino Interface establishing the I2C
bus(Wire) and I2C address.

*/
#pragma once
#include "sfe_stts22h.h"
#include "sfe_bus.h"
#include <Wire.h>

class SparkFun_STTS22H : public QwDevSTTS22H
{

	public: 

		SparkFun_STTS22H() {};

    ///////////////////////////////////////////////////////////////////////
    // begin()
    //
    // This method is called to initialize the STTS22H library and connect to
    // the STTS22H device. This method must be called before calling any other method
    // that interacts with the device.
    //
    // This method follows the standard startup pattern in SparkFun Arduino
    // libraries.
    //
    //  Parameter   Description
    //  ---------   ----------------------------
    //  wirePort    optional. The Wire port. If not provided, the default port is used
    //  address     optional. I2C Address. If not provided, the default address is used.
    //  retval      true on success, false on startup failure
    //
    // This method is overridden, implementing two versions.
    //
    // Version 1:
    // User skips passing in an I2C object which then defaults to Wire.
		bool begin(uint8_t deviceAddress = STTS22H_ADDRESS_FIFTEEN)
		{
        // Setup  I2C object and pass into the superclass
        setCommunicationBus(_i2cBus, deviceAddress);

				// Initialize the I2C buss class i.e. setup default Wire port
        _i2cBus.init();

        // Initialize the system - return results
        return this->QwDevSTTS22H::init();
		}

		//Version 2:
    // User passes in an I2C object and an address (optional).
    bool begin(TwoWire &wirePort, uint8_t deviceAddress = STTS22H_ADDRESS_HIGH)
    {
        // Setup  I2C object and pass into the superclass
        setCommunicationBus(_i2cBus, deviceAddress);

				// Give the I2C port provided by the user to the I2C bus class.
        _i2cBus.init(wirePort, true);

        // Initialize the system - return results
        return this->QwDevSTTS22H::init();
    }

	private: 

		//I2C bus class
		sfe_STTS22H::QwI2C _i2cBus; 

};
	
