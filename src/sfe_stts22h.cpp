#include "sfe_stts22h.h"

//////////////////////////////////////////////////////////////////////////////
// init()
//
// init the system
//
// Return Value: false on error, true on success
//

bool QwDevSTTS22H::init(void)
{
    //  do we have a bus yet? is the device connected?
    if (!_sfeBus->ping(_i2cAddress))
        return false;
	
		initCtx((void*)this, &sfe_dev); 			

		// I2C ready, now check that we're using the correct sensor before moving on. 
		if (getUniqueId() != STTS22H_ID)
			return false; 


    return true;
}



///////////////////////////////////////////////////////////////////////
// isConnected()
//
// Called to determine if a ISM330DHCX device, at the provided i2c address
// is connected.
//
//  Parameter   Description
//  ---------   -----------------------------
//  retVal      true if device is connected, false if not connected

bool QwDevSTTS22H::isConnected()
{
		if (getUniqueId() != STTS22H_ID)
			return false; 
		else
			return true;
}


////////////////////////////////////////////////////////////////////////////////////
// setCommunicationBus()
//
// Method to set the bus object that is used to communicate with the device
//
//  Parameter    Description
//  ---------    -----------------------------
//  theBus       The communication bus object
//  i2cAddress   I2C address for the 6DoF

void QwDevSTTS22H::setCommunicationBus(sfe_STTS22H::QwIDeviceBus &theBus, uint8_t i2cAddress)
{
    _sfeBus = &theBus;
		_i2cAddress = i2cAddress; 
}

////////////////////////////////////////////////////////////////////////////////////
// setCommunicationBus()
//
// Overloaded option for setting the data bus (theBus) object to a SPI bus object.
//
//  Parameter    Description
//  ---------    -----------------------------
//  theBus       The communication bus object
//  

void QwDevSTTS22H::setCommunicationBus(sfe_STTS22H::QwIDeviceBus &theBus)
{
    _sfeBus = &theBus;
}

//////////////////////////////////////////////////////////////////////////////
// writeRegisterRegion()
//
// Writes data to the given register
//
//  Parameter    Description
//  ---------    -----------------------------
//  offset       The register to be written to
//  data         Data to be written
//  length       Number of bytes to be written

int32_t QwDevSTTS22H::writeRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->writeRegisterRegion(_i2cAddress, offset, data, length);
}

//////////////////////////////////////////////////////////////////////////////
// readRegisterRegion()
//
// Reads data from the given register, auto-incrementing fore each successive read
//
//  Parameter    Description
//  ---------    -----------------------------
//  offset       The register to be read from
//  data         Pointer to where data will be saved
//  length       Number of bytes to be read

int32_t QwDevSTTS22H::readRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->readRegisterRegion(_i2cAddress, offset, data, length);
}

//////////////////////////////////////////////////////////////////////////////
// setAccelFullScale()
//
// Sets the scale of the acceleromter's readings 2g - 16g
//
//  Parameter    Description
//  ---------    -----------------------------
//  val          The scale to be applied to the accelerometer (0 - 3)
//
// See sfe_ism330dhcx_defs.h for a list of valid arguments
//

uint8_t QwDevSTTS22H::getUniqueId()
{

	uint8_t buff = 0;
	int32_t retVal = (stts22h_dev_id_get(&sfe_dev, &buff));

	if(retVal != 0)
		return 0; 
	
	return buff;
}


bool QwDevSTTS22H::deviceReset()
{
	int32_t retVal;

	retVal = (&sfe_dev, 1);

	if( retVal != 0 )
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
// getDeviceReset()
// 
// Checks to see that the reset bit has been set
// 

bool QwDevSTTS22H::getDeviceReset()
{

	int32_t retVal;
	uint8_t tempVal;
	retVal = (&sfe_dev, &tempVal);

	if( retVal != 0 )
		return false;

	if( (tempVal & 0x01) == 0x00 ){
		return true; 
	}

	return false; 
	
}

