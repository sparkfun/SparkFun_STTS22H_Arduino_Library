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
		if ( getUniqueId() != STTS22H_ID )
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
// Reads data from the given register, auto-incrementing for each successive read
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

	uint8_t tempVal = 0;
	int32_t retVal = stts22h_dev_id_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return 0; 
	
	return tempVal;
}

int8_t QwDevSTTS22H::getStatus()
{
	int32_t retVal;
	stts22h_dev_status_t tempVal;

	retVal = stts22h_dev_status_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return -1;

	return (int8_t)tempVal.busy; 
}

//----------------------------------------------General Settings ---------------------------------------------------

/// @brief Sets the STTSH2 output data rate.
/// @param dataRate 
/// @return true on successful execution.
bool QwDevSTTS22H::setDataRate(uint8_t dataRate)
{
	int32_t retVal;

	retVal = stts22h_temp_data_rate_set(&sfe_dev, (stts22h_odr_temp_t)dataRate);

	if( retVal != 0 )
		return false;

	return true;
}

int8_t QwDevSTTS22H::getDataRate()
{
	stts22h_odr_temp_t tempVal;
	int32_t retVal;

	retVal = stts22h_temp_data_rate_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return -1;

	return (int8_t)tempVal;
}


bool QwDevSTTS22H::enableBlockDataUpdate(bool enable)
{
	int32_t retVal;

	retVal = stts22h_block_data_update_set(&sfe_dev, (uint8_t)enable);

	if( retVal != 0 )
		return false;

	return true;
}


bool QwDevSTTS22H::enableAutoIncrement(bool enable)
{
	int32_t retVal;

	retVal = stts22h_auto_increment_set(&sfe_dev, (uint8_t)enable);

	if( retVal != 0 )
		return false;

	return true;
}
// 0.63 x .24
//----------------------------------------------Interrupt Settings---------------------------------------------------

bool QwDevSTTS22H::setInterruptHighC(float temp)
{
	int32_t retVal;
	int8_t tempC = (int8_t)(temp/0.64) + 64;

	retVal = stts22h_temp_trshld_high_set(&sfe_dev, tempC);

	if( retVal != 0 )
		return false;

	return true;
}

bool QwDevSTTS22H::setInterruptLowC(float temp)
{
	int32_t retVal;
	int8_t tempC = (int8_t)(temp/0.64) + 64;

	retVal = stts22h_temp_trshld_high_set(&sfe_dev, tempC);

	if( retVal != 0 )
		return false;

	return true;
}



float QwDevSTTS22H::getInterruptHighC()
{
	int32_t retVal;
	uint8_t tempC;

	retVal = stts22h_temp_trshld_high_get(&sfe_dev, &tempC);

	if( retVal != 0 )
		return -1;

	tempC = (float)(tempC) * 0.64 - 64;

	return tempC;
}

float QwDevSTTS22H::getInterruptLowC()
{
	int32_t retVal;
	uint8_t tempC;

	retVal = stts22h_temp_trshld_low_get(&sfe_dev, &tempC);

	if( retVal != 0 )
		return -1;

	tempC = (float)(tempC) * 0.64 - 64;

	return tempC;
}

//----------------------------------Data Retreival------------------------------------------------------------------
bool QwDevSTTS22H::dataReady()
{
	uint8_t tempVal;
	int32_t retVal;

	retVal = stts22h_temp_flag_data_ready_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return false;

	if( tempVal )
		return true;

	return false;
}


/// @brief Retrieves signed temperature values. 
/// @param temperature 
/// @return  Returns true on successful retrieval. 
bool QwDevSTTS22H::getTempRaw(int16_t *temperature)
{
	int32_t retVal;

	retVal = stts22h_temperature_raw_get(&sfe_dev, temperature);

	if( retVal != 0 )
		return false;

	return true;
	
}

bool QwDevSTTS22H::getTemperatureC(float *tempC)
{
	int16_t tempVal;
	bool retVal;

	retVal = getTempRaw(&tempVal);
	*tempC = stts22h_from_lsb_to_celsius(tempVal);

	return retVal;
}


