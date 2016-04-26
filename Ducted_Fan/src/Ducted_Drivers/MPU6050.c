#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "r_riic_rx600.h"
#include "r_riic_rx600_master.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "IMU_write_read.h"
#include "CMT.h"
#include "I2C.h"
#include "support_functions.h"

uint8_t DISABLE = 0x00; 			//DISABLE FUNCTION
uint8_t INITIAL = 0x00;		 		//INITIALIZE TO ZERO
uint8_t ENABLE = 0x00; 				//ENABLE FUNCTION
uint8_t RATE_1000 = 0x07; 			//Sets sample rate to 8000/1+7 = 1000Hz
uint8_t D_GYRO_SELF_TEST = 0x08; 	//Disable gyro self test
uint8_t GYRO_CLOCK = 0x02; 			//Gyro clock reference

void MPU6050_Test_I2C()
{

    unsigned char Data = 0x00;
    riic_ret_t ret = IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, &Data, NUM_BYTES);

    if(Data == 0x68)
    {
        printf("\nI2C Read Test Passed, MPU6050 Address: 0x%x", Data);

    }
    else
    {
    	lcd_display(LCD_LINE8, "Err: I2Ctest");
        while(1){}
    }
}

void Setup_MPU6050()
{
    //Sets sample rate to 8000/1+7 = 1000Hz
	IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, &RATE_1000, NUM_BYTES);
    //Disable FSync, 256Hz DLPF
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_CONFIG, &DISABLE, NUM_BYTES);
    //Disable gyro self tests, scale of 500 degrees/s
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, &D_GYRO_SELF_TEST, NUM_BYTES);
    //Disable accel self tests, scale of +-2g, no DHPF
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &DISABLE, NUM_BYTES);
    //Freefall threshold of |0mg|
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_FF_THR, &INITIAL, NUM_BYTES);
    //Freefall duration limit of 0
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_FF_DUR, &INITIAL, NUM_BYTES);
    //Motion threshold of 0mg
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_MOT_THR, &INITIAL, NUM_BYTES);
    //Motion duration of 0s
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, &INITIAL, NUM_BYTES);
    //Zero motion threshold
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, &INITIAL, NUM_BYTES);
    //Zero motion duration threshold
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, &INITIAL, NUM_BYTES);
    //Disable sensor output to FIFO buffer
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, &DISABLE, NUM_BYTES);

    //AUX I2C setup
    //Set register mode in continous-measurement



    //Setup magnetometer HMC5883L as external sensor of MPU6050
    lcd_display(LCD_LINE8, "ISMAGN");
    Setup_HMC5883L();
    lcd_display(LCD_LINE8, "FSMAGN");
    //More slave config
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, &INITIAL, NUM_BYTES);
    //Reset sensor signal paths
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, &INITIAL, NUM_BYTES);
    //Motion detection control
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, &ENABLE, NUM_BYTES);
    //Sets clock source to gyro reference w/ PLL
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &GYRO_CLOCK, NUM_BYTES);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, &INITIAL, NUM_BYTES);
    //MPU6050_RA_BANK_SEL            //Not in datasheet
    //MPU6050_RA_MEM_START_ADDR        //Not in datasheet
    //MPU6050_RA_MEM_R_W            //Not in datasheet
    //MPU6050_RA_DMP_CFG_1            //Not in datasheet
    //MPU6050_RA_DMP_CFG_2            //Not in datasheet
    //MPU6050_RA_FIFO_COUNTH        //Read-only
    //MPU6050_RA_FIFO_COUNTL        //Read-only
    //Data transfer to and from the FIFO buffer
    IMU_write(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, &ENABLE, NUM_BYTES);
    //MPU6050_RA_WHO_AM_I             //Read-only, I2C address

}

// calibration of the gyroscope with the average of the first GYRO_MEASURES readings
void Calibrate_Accel (){

	float ACC_ZOUT_MEASURES_SUM = 0;

	int ACC_XOUT_init, ACC_YOUT_init, ACC_ZOUT_init;
	float ACC_ZOUT_OFFSET_0;
	float ACC_ZOUT_OFFSET;

	do
	{
		ACC_ZOUT_OFFSET_0 = ACC_ZOUT_OFFSET;
		/*??????? Sum must be Reinitialized each cycle ??????*/

		for(int x = 0; x<ACC_MEASURES; x++)
		{
			Get_Accel_Values(&ACC_XOUT_init, &ACC_YOUT_init, &ACC_ZOUT_init);
			ACC_ZOUT_MEASURES_SUM += ACC_ZOUT_init;
		}

		// ACC_ZOUT_OFFSET = (float)ACC_ZOUT_MEASURES_SUM/ACC_MEASURES;

		ACC_ZOUT_OFFSET = map(C2toD((float)ACC_ZOUT_MEASURES_SUM/ACC_MEASURES), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);

		char a[20];
		sprintf(a, "Z: %2d", ACC_ZOUT_OFFSET);
		lcd_display(LCD_LINE1, (const uint8_t*)a);

	} while(abs(ACC_ZOUT_OFFSET)>1.1);
}

//Gets raw accelerometer data, performs no processing
void Get_Accel_Values(int* ACCEL_XOUT, int* ACCEL_YOUT, int* ACCEL_ZOUT)
{
	uint8_t ACCEL_XOUT_H = 0, ACCEL_XOUT_L = 0;
	uint8_t ACCEL_YOUT_H = 0, ACCEL_YOUT_L = 0;
	uint8_t ACCEL_ZOUT_H = 0, ACCEL_ZOUT_L = 0;


	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, &ACCEL_XOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_L, &ACCEL_XOUT_L, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H, &ACCEL_YOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_L, &ACCEL_YOUT_L, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H, &ACCEL_ZOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L, &ACCEL_ZOUT_L, NUM_BYTES);

	*ACCEL_XOUT = ((ACCEL_XOUT_H<<8)|ACCEL_XOUT_L);
	*ACCEL_YOUT = ((ACCEL_YOUT_H<<8)|ACCEL_YOUT_L);
	*ACCEL_ZOUT = ((ACCEL_ZOUT_H<<8)|ACCEL_ZOUT_L);

}
//Accelerometer data in g
void Get_Accel_Gravity_Power(float* ACCEL_XPOWER, float* ACCEL_YPOWER, float* ACCEL_ZPOWER)
{
	int ACCEL_XOUT;
	int	ACCEL_YOUT;
	int	ACCEL_ZOUT;

	Get_Accel_Values(&ACCEL_XOUT, &ACCEL_YOUT, &ACCEL_ZOUT);

	*ACCEL_XPOWER = map(C2toD(ACCEL_XOUT), -QL/2, QL/2, -MPU6050_ACC_FULL_SCALE_RANGE, MPU6050_ACC_FULL_SCALE_RANGE);
//	*ACCEL_YPOWER = map(C2toD(ACCEL_YOUT), -QL/2, QL/2, -MPU6050_ACC_FULL_SCALE_RANGE, MPU6050_ACC_FULL_SCALE_RANGE);
//	*ACCEL_ZPOWER = map(C2toD(ACCEL_ZOUT), -QL/2, QL/2, -MPU6050_ACC_FULL_SCALE_RANGE, MPU6050_ACC_FULL_SCALE_RANGE);

	//Z=Y and Y=-Z due to imu rotation in positioning
	*ACCEL_ZPOWER = map(C2toD(ACCEL_YOUT), -QL/2, QL/2, -MPU6050_ACC_FULL_SCALE_RANGE, MPU6050_ACC_FULL_SCALE_RANGE);
	*ACCEL_YPOWER = -map(C2toD(ACCEL_ZOUT), -QL/2, QL/2, -MPU6050_ACC_FULL_SCALE_RANGE, MPU6050_ACC_FULL_SCALE_RANGE);
}

//Converts the already acquired accelerometer data into 3D euler angles
void Get_Accel_Angles(float* ACCEL_XANGLE, float* ACCEL_YANGLE)
{
//	int ACCEL_XOUT;
//	int	ACCEL_YOUT;
//	int	ACCEL_ZOUT;
//
//	Get_Accel_Values(&ACCEL_XOUT, &ACCEL_YOUT, &ACCEL_ZOUT);
//
//	*ACCEL_XANGLE = 57.295*atan2(-(float)C2toD(ACCEL_YOUT), (float)C2toD(ACCEL_ZOUT));
//	*ACCEL_YANGLE = 57.295*atan2((float)C2toD(ACCEL_XOUT), sqrt(pow((float)C2toD(ACCEL_YOUT),2)+pow((float)C2toD(ACCEL_ZOUT),2)));

	float ACCEL_XOUT;
	float ACCEL_YOUT;
	float ACCEL_ZOUT;

	Get_Accel_Gravity_Power(&ACCEL_XOUT, &ACCEL_YOUT, &ACCEL_ZOUT);

	*ACCEL_XANGLE = 57.295*atan2(-ACCEL_YOUT, ACCEL_ZOUT);
	*ACCEL_YANGLE = 57.295*atan2(ACCEL_XOUT, sqrt(pow(ACCEL_YOUT,2)+pow(ACCEL_ZOUT,2)));
}

void Calibrate_Gyros()
{
	uint32_t GYRO_XOUT_OFFSET_GYRO_MEASURES_SUM = 0;
	uint32_t GYRO_YOUT_OFFSET_GYRO_MEASURES_SUM = 0;
	uint32_t GYRO_ZOUT_OFFSET_GYRO_MEASURES_SUM = 0;
	//uint8_t GYRO_XOUT_H = 0, GYRO_XOUT_L = 0;
	//uint8_t GYRO_YOUT_H = 0, GYRO_YOUT_L = 0;
	//uint8_t GYRO_ZOUT_H = 0, GYRO_ZOUT_L = 0;

	int GYRO_XOUT_init;
	int GYRO_YOUT_init;
	int GYRO_ZOUT_init;

	float GYRO_XOUT_OFFSET0 = 0;
	float GYRO_YOUT_OFFSET0 = 0;
	float GYRO_ZOUT_OFFSET0 = 0;

	float GYRO_XOUT_OFFSET_MAP;
	float GYRO_YOUT_OFFSET_MAP;
	float GYRO_ZOUT_OFFSET_MAP;

	int iteration = 1;
	do
	{
		GYRO_XOUT_OFFSET0 = GYRO_XOUT_OFFSET_MAP;
		GYRO_YOUT_OFFSET0 = GYRO_YOUT_OFFSET_MAP;
		GYRO_ZOUT_OFFSET0 = GYRO_ZOUT_OFFSET_MAP;

		for(int x = 0; x<GYRO_MEASURES; x++)
		{

			/*
			IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, &GYRO_XOUT_H, NUM_BYTES);
			IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_L, &GYRO_XOUT_L, NUM_BYTES);
			IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H, &GYRO_YOUT_H, NUM_BYTES);
			IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_L, &GYRO_YOUT_L, NUM_BYTES);
			IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H, &GYRO_ZOUT_H, NUM_BYTES);
			IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_L, &GYRO_ZOUT_L, NUM_BYTES);
			*/

			Get_Gyro_Value(&GYRO_XOUT_init, &GYRO_YOUT_init, &GYRO_ZOUT_init);

			GYRO_XOUT_OFFSET_GYRO_MEASURES_SUM += GYRO_XOUT_init;
			GYRO_YOUT_OFFSET_GYRO_MEASURES_SUM += GYRO_YOUT_init;
			GYRO_ZOUT_OFFSET_GYRO_MEASURES_SUM += GYRO_ZOUT_init;

		}

	GYRO_XOUT_OFFSET = (float)GYRO_XOUT_OFFSET_GYRO_MEASURES_SUM/GYRO_MEASURES;
	GYRO_YOUT_OFFSET = (float)GYRO_YOUT_OFFSET_GYRO_MEASURES_SUM/GYRO_MEASURES;
	GYRO_ZOUT_OFFSET = (float)GYRO_ZOUT_OFFSET_GYRO_MEASURES_SUM/GYRO_MEASURES;

	GYRO_XOUT_OFFSET_MAP = map(C2toD(GYRO_XOUT_OFFSET), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);
	GYRO_YOUT_OFFSET_MAP = map(C2toD(GYRO_YOUT_OFFSET), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);
	GYRO_ZOUT_OFFSET_MAP = map(C2toD(GYRO_ZOUT_OFFSET), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);

	char a[20];
	sprintf(a, "X: %4.2f", GYRO_XOUT_OFFSET_MAP);
	lcd_display(LCD_LINE4, (const uint8_t*)a);
	sprintf(a, "Y: %4.2f", GYRO_YOUT_OFFSET_MAP);
	lcd_display(LCD_LINE5, (const uint8_t*)a);
	sprintf(a, "Z: %4.2f", GYRO_ZOUT_OFFSET_MAP);
	lcd_display(LCD_LINE6, (const uint8_t*)a);
	sprintf(a, "iter: %2d", iteration);
	lcd_display(LCD_LINE7, (const uint8_t*)a);

	iteration++;

} while((abs(GYRO_XOUT_OFFSET0 - GYRO_XOUT_OFFSET_MAP) > OFFSET_ERROR) || (abs(GYRO_YOUT_OFFSET0 - GYRO_YOUT_OFFSET_MAP) > OFFSET_ERROR) || (abs(GYRO_ZOUT_OFFSET0 - GYRO_ZOUT_OFFSET_MAP) > OFFSET_ERROR));
}

//Function to read the gyroscope rate data and convert it into degrees/s
void Get_Gyro_Value(int* GYRO_XOUT, int* GYRO_YOUT, int* GYRO_ZOUT)
{
	uint8_t GYRO_XOUT_H = 0, GYRO_XOUT_L = 0;
	uint8_t GYRO_YOUT_H = 0, GYRO_YOUT_L = 0;
	uint8_t GYRO_ZOUT_H = 0, GYRO_ZOUT_L = 0;

	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, &GYRO_XOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_L, &GYRO_XOUT_L, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H, &GYRO_YOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_L, &GYRO_YOUT_L, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H, &GYRO_ZOUT_H, NUM_BYTES);
	IMU_read(CHANNEL, MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_L, &GYRO_ZOUT_L, NUM_BYTES);

	*GYRO_XOUT = ((GYRO_XOUT_H<<8)|GYRO_XOUT_L) - GYRO_XOUT_OFFSET;
	*GYRO_YOUT = ((GYRO_YOUT_H<<8)|GYRO_YOUT_L) - GYRO_YOUT_OFFSET;
	*GYRO_ZOUT = ((GYRO_ZOUT_H<<8)|GYRO_ZOUT_L) - GYRO_ZOUT_OFFSET;



}

void Get_Gyro_Rates(float* GYRO_XRATE, float* GYRO_YRATE, float* GYRO_ZRATE)
{
	int GYRO_XOUT;
	int GYRO_YOUT;
	int GYRO_ZOUT;

	Get_Gyro_Value(&GYRO_XOUT, &GYRO_YOUT, &GYRO_ZOUT);

	*GYRO_XRATE = map(C2toD(GYRO_XOUT), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);
//	*GYRO_YRATE = map(C2toD(GYRO_YOUT), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);
//	*GYRO_ZRATE = map(C2toD(GYRO_ZOUT), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);

	//Z=Y and Y=-Z due to imu rotation in positioning
	*GYRO_ZRATE = map(C2toD(GYRO_YOUT), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);
	*GYRO_YRATE = -map(C2toD(GYRO_ZOUT), -QL/2, QL/2, -MPU6050_GYROC_FULL_SCALE_RANGE, MPU6050_GYROC_FULL_SCALE_RANGE);

}

