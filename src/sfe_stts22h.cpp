#include "sfe_stts22h.h"


/// @brief Initializes various system parameter for communicating with the STTS22H
/// @return  True on successful communication with STTS22H, false otherwise.
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

/// @brief Checks is the STTS22H is connected by retrieiving its' unique ID.
/// @return  True is the unidue ID is correct and false otherwise.
bool QwDevSTTS22H::isConnected()
{
		if (getUniqueId() != STTS22H_ID)
			return false; 

		return true; 
}


/// @brief Establishes the bus driver and i2c address to use to communicate with the STTS22H - I2C only for this device.
/// @return  nothing
void QwDevSTTS22H::setCommunicationBus(sfe_STTS22H::QwIDeviceBus &theBus, uint8_t i2cAddress)
{
    _sfeBus = &theBus;
		_i2cAddress = i2cAddress; 
}

/// @brief Establishes the bus driver to use to communicate with the STTS22H - I2C only for this device.
/// @return  nothing
void QwDevSTTS22H::setCommunicationBus(sfe_STTS22H::QwIDeviceBus &theBus)
{
    _sfeBus = &theBus;
}

/// @brief Writes to the given register using the selected bus - I2C only on this device.
/// @return  Returns -1 on bus error and zero otherwise.
int32_t QwDevSTTS22H::writeRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->writeRegisterRegion(_i2cAddress, offset, data, length);
}

/// @brief Reads from the given register using the selected bus - I2C only on this device.
/// @return  Returns -1 on bus error and zero otherwise.
int32_t QwDevSTTS22H::readRegisterRegion(uint8_t offset, uint8_t *data, uint16_t length)
{
    return _sfeBus->readRegisterRegion(_i2cAddress, offset, data, length);
}

/// @brief Retrieves the STTS22H's unique identification number
/// @return  Returns the unique ID
uint8_t QwDevSTTS22H::getUniqueId()
{

	uint8_t tempVal = 0;
	int32_t retVal = stts22h_dev_id_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return 0; 
	
	return tempVal;
}

/// @brief Retrieves the status of the lower/higher threshold and one-shot only busy-bit.
/// @return  Returns true on successful execution.
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

/// @brief Retrieves the output data rate of temperature values.
/// @return  Returns true on successful execution.
int8_t QwDevSTTS22H::getDataRate()
{
	stts22h_odr_temp_t tempVal;
	int32_t retVal;

	retVal = stts22h_temp_data_rate_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return -1;

	return (int8_t)tempVal;
}


/// @brief Enables/disables the bloack data update feature.
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::enableBlockDataUpdate(bool enable)
{
	int32_t retVal;

	retVal = stts22h_block_data_update_set(&sfe_dev, (uint8_t)enable);

	if( retVal != 0 )
		return false;

	return true;
}


/// @brief Enables/disables the register auto-increment feature - enabled by default.
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::enableAutoIncrement(bool enable)
{
	int32_t retVal;

	retVal = stts22h_auto_increment_set(&sfe_dev, (uint8_t)enable);

	if( retVal != 0 )
		return false;

	return true;
}

/// @brief Checks the auto-increment bit.
/// @return  Returns auto increment bit. 
uint8_t QwDevSTTS22H::getAutoIncrement()
{
	int32_t retVal;
	uint8_t tempVal;

	retVal = stts22h_auto_increment_get(&sfe_dev, &tempVal);

	if( retVal != 0 )
		return 0;

	return tempVal;
}

//----------------------------------------------Interrupt Settings---------------------------------------------------

/// @brief Sets the higher temperature threshold interrupt
/// @param temp - temperature in Celsius
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::setInterruptHighC(float temp)
{
	int32_t retVal;
	int8_t tempC = (int8_t)(temp/0.64) + 64;

	retVal = stts22h_temp_trshld_high_set(&sfe_dev, tempC);

	if( retVal != 0 )
		return false;

	return true;
}

/// @brief Sets the lower temperature threshold interrupt
/// @param temp - temperature in Celsius
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::setInterruptLowC(float temp)
{
	int32_t retVal;
	int8_t tempC = (int8_t)(temp/0.64) + 64;

	retVal = stts22h_temp_trshld_low_set(&sfe_dev, tempC);

	if( retVal != 0 )
		return false;

	return true;
}


/// @brief Sets the higher temperature threshold interrupt
/// @param temp - temperature in Farenheit
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::setInterruptHighF(float temp)
{
	int32_t retVal;
	float tempC = (temp - 32)/1.8; 
	int8_t tempConv = (int8_t)(tempC/0.64) + 64;

	retVal = stts22h_temp_trshld_high_set(&sfe_dev, tempConv);

	if( retVal != 0 )
		return false;

	return true;
}

/// @brief Sets the lower temperature threshold interrupt
/// @param temp - temperature in Farenheit
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::setInterruptLowF(float temp)
{
	int32_t retVal;
	float tempC = (temp - 32)/1.8; 
	int8_t tempConv = (int8_t)(tempC/0.64) + 64;

	retVal = stts22h_temp_trshld_low_set(&sfe_dev, tempConv);

	if( retVal != 0 )
		return false;

	return true;
}

/// @brief Sets the higher temperature threshold interrupt
/// @param temp - temperature in Kelvin
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::setInterruptHighK(float temp)
{
	int32_t retVal;
	float tempK = temp - 273.15; 
	int8_t tempC = (int8_t)(tempK/0.64) + 64;

	retVal = stts22h_temp_trshld_high_set(&sfe_dev, tempC);

	if( retVal != 0 )
		return false;

	return true;
}

/// @brief Sets the lower temperature threshold interrupt
/// @param temp - temperature in Kelvin
/// @return  Returns true on successful execution.
bool QwDevSTTS22H::setInterruptLowK(float temp)
{
	int32_t retVal;
	float tempK = temp - 273.15; 
	int8_t tempC = (int8_t)(tempK/0.64) + 64;

	retVal = stts22h_temp_trshld_low_set(&sfe_dev, tempC);

	if( retVal != 0 )
		return false;

	return true;
}

/// @brief Gets the higher temperature threshold interrupt
/// @return  Returns the value in Celsius of the higher threshold.
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

/// @brief Gets the lower temperature threshold interrupt
/// @return  Returns the value in Celsius of the lower threshold.
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
/// @brief Checks the data ready bit and returns true if bit is set. 
/// @return  Returns true if bit is set
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


/// @brief Retrieves raw temperature values. 
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

/// @brief Converts raw temp to Celsius 
/// @param tempC 
/// @return  Returns true on successful retrieval. 
bool QwDevSTTS22H::getTemperatureC(float *tempC)
{
	int16_t tempVal;
	bool retVal;

	retVal = getTempRaw(&tempVal);
	*tempC = stts22h_from_lsb_to_celsius(tempVal);

	return retVal;
}

/// @brief Converts raw temp to Farenheit 
/// @param tempF 
/// @return  Returns true on successful retrieval. 
bool QwDevSTTS22H::getTemperatureF(float *tempF)
{
	int16_t tempVal;
	bool retVal;

	retVal = getTempRaw(&tempVal);
	*tempF = stts22h_from_lsb_to_celsius(tempVal);

	*tempF = (*tempF * 1.8) + 32; 

	return retVal;
}

/// @brief Converts raw temp to Kelvin 
/// @param tempK 
/// @return  Returns true on successful retrieval. 
bool QwDevSTTS22H::getTemperatureK(float *tempK)
{
	int16_t tempVal;
	bool retVal;

	retVal = getTempRaw(&tempVal);
	*tempK = stts22h_from_lsb_to_celsius(tempVal);

	*tempK = *tempK + 273.15;

	return retVal;
}
