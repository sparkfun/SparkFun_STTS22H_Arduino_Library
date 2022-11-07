#include "sfe_bus.h"
#include <Arduino.h>

#define kMaxTransferBuffer 32

// What we use for transfer chunk size
const static uint16_t kChunkSize = kMaxTransferBuffer;

//////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
//

namespace sfe_STTS22H 
{

QwI2C::QwI2C(void) : _i2cPort{nullptr}
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// I2C init()
//
// Methods to init/setup this device. The caller can provide a Wire Port, or this class
// will use the default

bool QwI2C::init(TwoWire &wirePort, bool bInit)
{

    // if we don't have a wire port already
    if( !_i2cPort )
    {
        _i2cPort = &wirePort;

        if( bInit )
            _i2cPort->begin();
    }
		
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// I2C init()
//
// Methods to init/setup this device. The caller can provide a Wire Port, or this class
// will use the default
bool QwI2C::init()
{
		if( !_i2cPort )
			return init(Wire);
		else
			return false;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
// ping()
//
// Is a device connected?
bool QwI2C::ping(uint8_t i2c_address)
{

    if( !_i2cPort )
        return false;

    _i2cPort->beginTransmission(i2c_address);
    return _i2cPort->endTransmission() == 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// writeRegisterByte()
//
// Write a byte to a register

bool QwI2C::writeRegisterByte(uint8_t i2c_address, uint8_t offset, uint8_t dataToWrite)
{

    if (!_i2cPort)
        return false;

    _i2cPort->beginTransmission(i2c_address);
    _i2cPort->write(offset);
    _i2cPort->write(dataToWrite);
    return _i2cPort->endTransmission() == 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
// writeRegisterRegion()
//
// Write a block of data to a device.

int QwI2C::writeRegisterRegion(uint8_t i2c_address, uint8_t offset, const uint8_t *data, uint16_t length)
{

    _i2cPort->beginTransmission(i2c_address);
    _i2cPort->write(offset);
    _i2cPort->write(data, (int)length);

    return _i2cPort->endTransmission() ? -1 : 0; // -1 = error, 0 = success
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// readRegisterRegion()
//
// Reads a block of data from an i2c register on the devices.
//
// For large buffers, the data is chuncked over KMaxI2CBufferLength at a time
//
//
int QwI2C::readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes)
{
    uint8_t nChunk;
    uint16_t nReturned;

    if (!_i2cPort)
        return -1;

    int i;                   // counter in loop
    bool bFirstInter = true; // Flag for first iteration - used to send register

    while (numBytes > 0)
    {
        _i2cPort->beginTransmission(addr);

        if (bFirstInter)
        {
            _i2cPort->write(reg);
            bFirstInter = false;
        }

        if (_i2cPort->endTransmission() != 0)
            return -1; // error with the end transmission

        // We're chunking in data - keeping the max chunk to kMaxI2CBufferLength
        nChunk = numBytes > kChunkSize ? kChunkSize : numBytes;

        nReturned = _i2cPort->requestFrom((int)addr, (int)nChunk, (int)true);

        // No data returned, no dice
        if (nReturned == 0)
            return -1; // error

        // Copy the retrieved data chunk to the current index in the data segment
        for (i = 0; i < nReturned; i++){
            *data++ = _i2cPort->read();
				}

        // Decrement the amount of data recieved from the overall data request amount
        numBytes = numBytes - nReturned;

    } // end while

    return 0; // Success
}

}
