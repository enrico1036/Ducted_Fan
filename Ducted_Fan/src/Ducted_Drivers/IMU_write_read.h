#ifndef IMU_WRITE_READ_H_
#define IMU_WRITE_READ_H_

#include "LowLevelDrivers/I2C.h"


riic_ret_t IMU_write (uint8_t riic_channel,
                      uint8_t slave_addr,
                      uint8_t register_number,
                      uint8_t *source_buff,
                      uint32_t num_bytes);

riic_ret_t IMU_read (uint8_t riic_channel,
                     uint8_t slave_addr,
                     uint8_t register_number,
                     uint8_t *dest_buff,
                     uint32_t num_bytes);

#endif /*IMU_WRITE_READ_H_*/
