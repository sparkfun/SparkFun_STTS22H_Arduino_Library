#include "sfe_bus.h"
#include "sfe_stts22h_shim.h"

#define STTS22H_ADDRESS_LOW 0x3F
#define STTS22H_ADDRESS_HIGH 0x38
#define STTS22H_ADDRESS_FIFTEEN 0x3C
#define STTS22H_ADDRESS_FIFTYSIX 0x3E


class QwDevSTTS22H
{
	public: 

		QwDevSTTS22H() : _i2cAddress{0}, _cs{0} {};
			

    ///////////////////////////////////////////////////////////////////////
    // init()
    //
    // Called to init the system. Connects to the device and sets it up for 
    // operation

    bool init();

    ///////////////////////////////////////////////////////////////////////
    // isConnected()
    //
    //
    //  Parameter   Description
    //  ---------   -----------------------------
    //  retval      true if device is connected, false if not connected

    bool isConnected(); // Checks if sensor ack's the I2C request

    int32_t writeRegisterRegion(uint8_t reg, uint8_t *data, uint16_t length);

    //////////////////////////////////////////////////////////////////////////////////
    // readRegisterRegion()
    //
    //
    //  Parameter    Description
    //  ---------    -----------------------------
    //  reg          register to read from
    //  data         Array to store data in
    //  length       Length of the data to read
    //  retval       -1 = error, 0 = success

    int32_t readRegisterRegion(uint8_t reg, uint8_t *data, uint16_t length);

    //////////////////////////////////////////////////////////////////////////////////
    // setCommunicationBus()
    //
    // Called to set the Communication Bus object to use
    //
    //  Parameter    Description
    //  ---------    -----------------------------
    //  theBus       The Bus object to use
    //  idBus        The bus ID for the target device.
    //

		void setCommunicationBus(sfe_ISM330DHCX::QwIDeviceBus &theBus, uint8_t i2cAddress);
		void setCommunicationBus(sfe_ISM330DHCX::QwIDeviceBus &theBus);

		uint8_t getUniqueId();

		// Linear, Angular, and Temp Data retrieval 

	private: 

		
		sfe_STTS22H::QwIDeviceBus *_sfeBus; 
		uint8_t _i2cAddress;
		uint8_t _cs;
		stmdev_ctx_t sfe_dev; 
};

