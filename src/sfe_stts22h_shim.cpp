#include "sfe_stts22h_shim.h"
#include "sfe_stts22h.h"
#include "st_src/stts22h_reg.h"


// Initializes the interfacing struct for STMicroelectronic's library. 
void initCtx(void* handle, stmdev_ctx_t* dev){

	dev->handle = handle; 	
	dev->write_reg = sfeSTTS22HWrite;
	dev->read_reg = sfeSTTS22HRead;
}

// Points to the write method in the STTS22H Arduino Library
int32_t sfeISMWrite(void* fTarget, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
	return (((QwDevSTTS22H*)fTarget)->writeRegisterRegion(reg, (uint8_t*)bufp, len));
}

// Points to the read method in the STTS22H Arduino Library
int32_t sfeISMRead(void* fTarget, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    return (((QwDevSTTS22H*)fTarget)->readRegisterRegion(reg, bufp, len));
}



