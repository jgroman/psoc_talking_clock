/*******************************************************************************
* File Name: FRAM_I2C.c
*
* Version: 1.0
*
* Description:
*  This is source code for F-RAM I2C APIs provided with the dev kit CY15FRAMKIT-001
*  The APIs include initialization of block, write, current read and random read
*  from F-RAM
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include "FRAM_I2C.h"
#include <device.h>

// Macro definitions

//Initialize timeout
#define TimeOutInit(t)  (t = 0)

// I2C Communication Timeout Check
#define IsTimeOut(t) ((t > I2C_COM_TIMEOUT)? 1 : 0)

//****************************************************************************************
// Function   : FRAM_I2C_Init
// Arguments  : None
// Return     : None
// Purpose    : Initialization routine for FRAM_I2C component
// Usage      : Component_Name_Init();
//            : Component_Name is the name of the component. Eg: FRAM_I2C_Init(); where
//            : FRAM_I2C is the component name. This function is called at the
//            : beginning of program along with other initializations.
//****************************************************************************************
void FRAM_I2C_Init ( void )
{
    // Initialize I2C SCB
	FRAM_I2C_I2C_Start();
}
//****************************************************************************************
// Function   : FRAM_I2C_Write
// Arguments  : uint8  slave_id         -> 7 bit Slave ID
//            : uint32 addr             -> 32 bit FRAM address for write.
//            : uint8 *data_write_ptr   -> Pointer to an array of data bytes to be written.
//            : uint32 total_data_count -> Number of data bytes to be written.
// Return     : uint32                   -> error status
//            :    FRAM_I2C_I2C_I2C_MSTR_NO_ERROR  -- (0x00u)    /* Function complete without error  */
//                 FRAM_I2C_I2C_MSTR_ERR_ARB_LOST  -- (0x01u)    /* Master lost arbitration during communication */
//                 FRAM_I2C_I2C_MSTR_ERR_LB_NAK    -- (0x02u)    /* Last Byte Naked */
//                 FRAM_I2C_I2C_MSTR_NOT_READY     -- (0x04u)    /* Master on the bus or Slave operation is in progress */
//      	  	   FRAM_I2C_I2C_MSTR_BUS_BUSY      -- (0x08u)    /* Bus is busy, process not started */
//      	  	   FRAM_I2C_I2C_MSTR_ERR_ABORT_START -- (0x10u)  /* Slave was addressed before master begin Start gen */
//                 FRAM_I2C_I2C_MSTR_ERR_BUS_ERR   -- (0x100u)   /* Bus error    */
//                 FRAM_I2C_I2C_MSTR_ERR           -- (0xFFu)    /* other error  */
// Purpose    : I2C FRAM Write Function
// Usage      : Component_Name_Write();
//            : Component_Name is the name of the component.
//            : Eg: FRAM_I2C_Write(slave_id, addr, data_bytes, 8); where FRAM_I2C is the
//            : component name. This function is called to write data to FRAM.
//****************************************************************************************
uint32 FRAM_I2C_Write (uint8 slave_id, uint32 addr, uint8 *data_write_ptr, uint32 total_data_count )
{
    uint32 i;
    uint32 error_status = 0;

    // If write pointer is NULL, return error
    if(data_write_ptr == NULL_PTR)
        return FRAM_I2C_MSTR_ERR;

    // For 1-Mbit, add the MSB bit in slave id (bit0). 
    if(FRAM_I2C_i2c_density == i2c_1MBit)
	    slave_id = slave_id | A16_ADDR_BIT(addr);

    // Send Start condition and slave id for write
    error_status = FRAM_I2C_I2C_I2CMasterSendStart(slave_id, 0);
    if( error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR )
	{
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();
	    return error_status;
	}

    // Send address byte
	error_status = FRAM_I2C_I2C_I2CMasterWriteByte(ISB_ADDR_BYTE(addr));
    if( error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR )
	{
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();
	    return error_status;
	}

    // Send address byte
	error_status = FRAM_I2C_I2C_I2CMasterWriteByte(LSB_ADDR_BYTE(addr));
    if( error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR )
	{
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();
	    return error_status;
	}

    // Send data bytes for write
    for(i = 0; i < total_data_count; i++ )
    {
	   error_status = FRAM_I2C_I2C_I2CMasterWriteByte((uint8)(data_write_ptr[i]));
       if( error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR)
	   {
           // I2C Error. Send Stop
           FRAM_I2C_I2C_I2CMasterSendStop();
	       return error_status;
	   }
    }

    // Write success. Send STOP.
    FRAM_I2C_I2C_I2CMasterSendStop();

    // Return the error status
	return error_status;
}

//****************************************************************************************
// Function   : FRAM_I2C_Current_Read
// Arguments  : uint8  slave_id         -> 7 bit Slave ID
//            : uint8 *data_read_ptr    -> Pointer to an array for storing data bytes.
//            : uint32 total_data_count -> Number of data bytes to be read.
// Return     : uint32                   -> error status
//            :    FRAM_I2C_I2C_I2C_MSTR_NO_ERROR  -- (0x00u)    /* Function complete without error  */
//                 FRAM_I2C_I2C_MSTR_ERR_ARB_LOST  -- (0x01u)    /* Master lost arbitration during communication */
//                 FRAM_I2C_I2C_MSTR_ERR_LB_NAK    -- (0x02u)    /* Last Byte Naked */
//                 FRAM_I2C_I2C_MSTR_NOT_READY     -- (0x04u)    /* Master on the bus or Slave operation is in progress */
//      	  	   FRAM_I2C_I2C_MSTR_BUS_BUSY      -- (0x08u)    /* Bus is busy, process not started */
//      	  	   FRAM_I2C_I2C_MSTR_ERR_ABORT_START -- (0x10u)  /* Slave was addressed before master begin Start gen */
//                 FRAM_I2C_I2C_MSTR_ERR_BUS_ERR   -- (0x100u)   /* Bus error    */
//                 FRAM_I2C_I2C_MSTR_ERR           -- (0xFFu)    /* other error  */
// Purpose    : I2C FRAM Current Read Function
// Usage      : Component_Name_Current_Read();
//            : Component_Name is the name of the component.
//            : Eg: FRAM_I2C_Current_Read(slave_id, addr, data_bytes, 8); where FRAM_I2C is the
//            : component name. This function is called to read data from I2C FRAM.
//****************************************************************************************
uint32 FRAM_I2C_Current_Read ( uint8 slave_id, uint8 *data_read_ptr, uint32 total_data_count )
{
    uint32 error_status = 0;
    uint8  status_reg;    
    uint32 timeout;

    // If read pointer is NULL, return error
    if(data_read_ptr == NULL_PTR)
        return FRAM_I2C_MSTR_ERR;

    // Clear error status
    error_status = FRAM_I2C_MSTR_NO_ERROR;
    
    // Clear the status register. If error, return
    status_reg = FRAM_I2C_I2C_I2CMasterClearStatus();
    if(status_reg & FRAM_I2C_I2C_I2C_MSTAT_ERR_XFER)
    {
        // Error in I2C Communication            
        error_status = FRAM_I2C_MSTR_ERR_BUS_ERR;
            
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();            
            
        return error_status;
    }

    // Read the data from the I2C Slave
    error_status = FRAM_I2C_I2C_I2CMasterReadBuf(slave_id, (uint8 *) data_read_ptr,
                          total_data_count, FRAM_I2C_I2C_I2C_MODE_COMPLETE_XFER);
    
    if(error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR)
    {
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();        
        return error_status;
    }

    // Initialize the timeout value and Wait for the Master to complete reading
    TimeOutInit(timeout);

    // Read the status register
    status_reg = FRAM_I2C_I2C_I2CMasterStatus();
    
    while(!( status_reg & FRAM_I2C_I2C_I2C_MSTAT_RD_CMPLT))
    {
        // Wait for 1 us and then check for timeout
        CyDelayUs(1);

        // Check for any communication error or timeout error
        if((status_reg & FRAM_I2C_I2C_I2C_MSTAT_ERR_XFER) || IsTimeOut(timeout++))
        {
            // Error in I2C Communication            
            error_status = FRAM_I2C_MSTR_ERR_BUS_ERR;
            
            // I2C Error. Send Stop
            FRAM_I2C_I2C_I2CMasterSendStop();

            return error_status;            
        }
        
        // Read the status register
        status_reg = FRAM_I2C_I2C_I2CMasterStatus();
    }

    // return the status
    return error_status;
}
//****************************************************************************************
// Function   : FRAM_I2C_Random_Read
// Arguments  : uint8  slave_id         -> 7 bit Slave ID
//            : uint32 addr             -> 32 bit FRAM address for read.
//            : uint8 *data_read_ptr    -> Pointer to an array for storing data bytes.
//            : uint32 total_data_count -> Number of data bytes to be read.
// Return     : uint32                   -> error status
//            :    FRAM_I2C_I2C_I2C_MSTR_NO_ERROR  -- (0x00u)    /* Function complete without error  */
//                 FRAM_I2C_I2C_MSTR_ERR_ARB_LOST  -- (0x01u)    /* Master lost arbitration during communication */
//                 FRAM_I2C_I2C_MSTR_ERR_LB_NAK    -- (0x02u)    /* Last Byte Naked */
//                 FRAM_I2C_I2C_MSTR_NOT_READY     -- (0x04u)    /* Master on the bus or Slave operation is in progress */
//      	  	   FRAM_I2C_I2C_MSTR_BUS_BUSY      -- (0x08u)    /* Bus is busy, process not started */
//      	  	   FRAM_I2C_I2C_MSTR_ERR_ABORT_START -- (0x10u)  /* Slave was addressed before master begin Start gen */
//                 FRAM_I2C_I2C_MSTR_ERR_BUS_ERR   -- (0x100u)   /* Bus error    */
//                 FRAM_I2C_I2C_MSTR_ERR           -- (0xFFu)    /* other error  */
// Purpose    : I2C FRAM Random Read Function
// Usage      : Component_Name_Random_Read();
//            : Component_Name is the name of the component.
//            : Eg: FRAM_I2C_Random_Read(slave_id, addr, data_bytes, 8); where FRAM_I2C is the
//            : component name. This function is called to read data from I2C FRAM.
//****************************************************************************************
uint32 FRAM_I2C_Random_Read ( uint8 slave_id, uint32 addr, uint8 *data_read_ptr, uint32 total_data_count )
{
    uint32 error_status = 0;
    uint8  status_reg;
    uint32 timeout;
    uint8  writebuf[2];

    // Clear error status
    error_status = FRAM_I2C_MSTR_NO_ERROR;
    
    // If read pointer is NULL, return error
    if(data_read_ptr == NULL_PTR)
        return FRAM_I2C_MSTR_ERR;

    // For 1-Mbit, add the MSB bit in slave id (bit0)
    if(FRAM_I2C_i2c_density == i2c_1MBit)
	    slave_id = slave_id | A16_ADDR_BIT(addr);

    writebuf[0] = ISB_ADDR_BYTE(addr);
    writebuf[1] = LSB_ADDR_BYTE(addr);

    // Clear the status register. If error, return
    status_reg = FRAM_I2C_I2C_I2CMasterClearStatus();
    if(status_reg & FRAM_I2C_I2C_I2C_MSTAT_ERR_XFER)
    {
        // Error in I2C Communication            
        error_status = FRAM_I2C_MSTR_ERR_BUS_ERR;
            
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();            
            
        return error_status;
    }
    
    // Write SRAM address to the slave
    error_status = FRAM_I2C_I2C_I2CMasterWriteBuf(slave_id, (uint8 *) writebuf,
                            NO_OF_ADDRBYTES, FRAM_I2C_I2C_I2C_MODE_NO_STOP);

    if(error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR)
    {
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();                
        return error_status;
    }
        
    // Initialize the timeout value and Wait for the Master to complete writing
    TimeOutInit(timeout);

    // Read the status register
    status_reg = FRAM_I2C_I2C_I2CMasterStatus();
    
    while(!(status_reg & FRAM_I2C_I2C_I2C_MSTAT_WR_CMPLT))
    {
        // Wait for 1 us and then check for timeout
        CyDelayUs(1);

        // Check for any communication error or timeout error
        if((status_reg & FRAM_I2C_I2C_I2C_MSTAT_ERR_XFER) || IsTimeOut(timeout++))
        {
            // Error in I2C Communication
            error_status = FRAM_I2C_MSTR_ERR_BUS_ERR;

            // I2C Error. Send Stop
            FRAM_I2C_I2C_I2CMasterSendStop();

            return error_status;
        }

        // Read the status register        
        status_reg = FRAM_I2C_I2C_I2CMasterStatus();        
    }

    // Clear the status register. If error, return
    status_reg = FRAM_I2C_I2C_I2CMasterClearStatus();
    if(status_reg & FRAM_I2C_I2C_I2C_MSTAT_ERR_XFER)
    {
        // Error in I2C Communication            
        error_status = FRAM_I2C_MSTR_ERR_BUS_ERR;
            
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();            
            
        return error_status;
    }    
    
    // Read the data from the I2C F-RAM by issuing a Restart
    error_status = FRAM_I2C_I2C_I2CMasterReadBuf(slave_id, (uint8 *) data_read_ptr,
                          total_data_count, FRAM_I2C_I2C_I2C_MODE_REPEAT_START);

    if(error_status != FRAM_I2C_I2C_I2C_MSTR_NO_ERROR)
    {
        // I2C Error. Send Stop
        FRAM_I2C_I2C_I2CMasterSendStop();        
        return error_status;
    }    

    // Initialize the timeout value and Wait for the Master to complete reading
    TimeOutInit(timeout);
    
    // Read the status register
    status_reg = FRAM_I2C_I2C_I2CMasterStatus();    

    while(!(status_reg & FRAM_I2C_I2C_I2C_MSTAT_RD_CMPLT))
    {
        // Wait for 1 us and then check for timeout
        CyDelayUs(1);

        // Check for any communication error or timeout error
        if((status_reg & FRAM_I2C_I2C_I2C_MSTAT_ERR_XFER) || IsTimeOut(timeout++))
        {
            // Error in I2C Communication            
            error_status = FRAM_I2C_MSTR_ERR_BUS_ERR;
            
            // I2C Error. Send Stop
            FRAM_I2C_I2C_I2CMasterSendStop();            
            
            return error_status;            
        }
        
        // Read the status register
        status_reg = FRAM_I2C_I2C_I2CMasterStatus();          
    }

    // return the status
    return error_status;

}



