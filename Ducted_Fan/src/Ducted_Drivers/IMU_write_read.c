#include <machine.h>
#include <stdio.h>
#include "platform.h"
#include "r_riic_rx600.h"
#include "r_riic_rx600_master.h"
#include "math.h"
#include "IMU_write_read.h"

/*******************************************************************************
* Function name: IMU_write
* Description  : Writes a specified number of bytes starting from the specfied 
*                IMU register. 
* Arguments    : riic_channel - 
*                   Which IIC channel of the MCU to use.
*                slave_addr -
*                   IIC slave address of the IMU.
*                register_number - 
*                   Which register of the accelerometer to be written.
*                (uint8_t*)source_buff - 
*                   pointer to the buffer where data will be copied from.              
*                num_bytes -
*                   The number of bytes to be written
*
* Return value : ret : RIIC result_code
*******************************************************************************/
riic_ret_t IMU_write (uint8_t riic_channel,
                      uint8_t slave_addr,
                      uint8_t register_number, 
                      uint8_t *source_buff, 
                      uint32_t num_bytes)
{
    uint8_t     addr_and_register[2]; /* Storage for the slave address and target register. */
    riic_ret_t  ret = RIIC_OK;
 
    /* To write to a specific register in the accelerometer, first transmit the 
       accelerometer I2C slave address together with the register number. */         
    addr_and_register[0] = slave_addr;    /* The 7-bit I2C address of the ADXL345 and the R/W bit. */ 
    addr_and_register[1] = register_number;
               
    ret |= R_RIIC_MasterTransmitHead(CHANNEL_0, addr_and_register, 2);
    /* Now write the data from the source buffer into the target register. */
    ret |= R_RIIC_MasterTransmit(CHANNEL_0, source_buff, num_bytes);
    
    return ret;
} /* End of function IMU_write(). */


/******************************************************************************
* Function name: IMU_read
* Description  : Reads a specified number of bytes starting from the specfied 
*                IMU register.
* Arguments    : riic_channel - 
*                   Which IIC channel of the MCU to use.
*                slave_addr -
*                   IIC slave address of the accelerometer.
*                register_number - 
*                   Which register of the accelerometer to be written.
*                (uint8_t*)dest_buff - 
*                   pointer to the buffer into which the read data will be stored.              
*                num_bytes -
*                   The number of bytes to be read from the IMU
* 
* Return value : ret : RIIC result_code
******************************************************************************/
riic_ret_t IMU_read (uint8_t riic_channel,
                     uint8_t slave_addr,
                     uint8_t register_number, 
                     uint8_t *dest_buff, 
                     uint32_t num_bytes)
{ 
    uint8_t     addr_and_register[2]; /* Storage for the slave address and target register. */
    riic_ret_t  ret = RIIC_OK;
    
    /* To read from a specific register in the accelerometer, first transmit the 
       accelerometer I2C slave address together with the register number. */         
    addr_and_register[0] = slave_addr; /* The 7-bit I2C address of the ADXL345 and the R/W bit. */ 
    addr_and_register[1] = register_number;
            
    ret |= R_RIIC_MasterTransmitHead(CHANNEL_0, addr_and_register, 2);
    /* Now read the data from the target register into the destination buffer. */    
    ret |= R_RIIC_MasterReceive(CHANNEL_0, slave_addr, dest_buff, num_bytes);
    
    return ret;    
} /* End of function IMU_read(). */
