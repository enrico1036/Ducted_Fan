#include <math.h>
#include "LowLevelDrivers/CMT.h"
#include "MS5611-01BA01.h"
#include "IMU_write_read.h"
#include "I2C.h"
#include <stdio.h>


int C[8];	//coefficients table for pressure sensor
uint8_t Buffer_Rx1[3]; 	//Buffer of data to be received by I2C1
uint8_t Buffer_Tx1;	//Buffer of data to be transmitted by I2C1
uint8_t Buffer_Rx2;	//Buffer of data to be received by I2C2
uint8_t Buffer_Tx2;	//Buffer of data to be transmitted by I2C2

void MS5611_Init(void){
    MS5611_Reset();
    MS5611_Read_Coef(C);
}

void MS5611_Reset(void)
{
    Buffer_Tx1 = CMD_RESET;

    riic_ret_t ret = IMU_write(CHANNEL, MS5611_ADDR, CMD_RESET, &Buffer_Tx1, NUM_BYTES);

    if(ret == RIIC_OK){
    	ms_delay(3); //wait for reset sequence timing
    	printf("RESET OK \n");
    }else{printf("RESET FAILED \n");}
}

//COMMAND can be CMD_ADC_D1 or CMD_ADC_D2
int MS5611_Convert_Dx(int COMMAND){

	int Dx = 0;

	for(short i = 0 ; i<3 ; i++)
    	Buffer_Rx1[i] = 0;
    Buffer_Tx1 = COMMAND;// send conversion command
    IMU_write(CHANNEL, MS5611_ADDR, COMMAND, &Buffer_Tx1, NUM_BYTES);
    ms_delay(10);

    //read 3 bytes conversion result
    riic_ret_t ret = IMU_read(CHANNEL, MS5611_ADDR, CMD_ADC_READ, Buffer_Rx1, 3);
    if (ret == RIIC_OK){
    	for(short i=0; i<3; i++)
    		Dx = (Dx << 8) + Buffer_Rx1[i];
    }else{Dx = -1;}

    return Dx;
}

int MS5611_Read_Prom(int COEF_NUM){

	int TEMP = 0, i;

	printf("COEFF: %d \n", COEF_NUM);

	// send read coefficient command
    Buffer_Tx2 = CMD_PROM_RD + (COEF_NUM*2);

    //read MSB and LSB
    riic_ret_t ret = IMU_read(CHANNEL, MS5611_ADDR, Buffer_Tx2, Buffer_Rx1, 2);
    if (ret == RIIC_OK){
    	for(i=0; i<2; i++)
    		TEMP = (TEMP << 8) + Buffer_Rx1[i];
    }else{TEMP = -1;}

    return TEMP;
}

//input C[] name of coefficient table
void MS5611_Read_Coef(int C[]){

	for(uint8_t j=0;j<8;j++){
    	C[j] = MS5611_Read_Prom(j);
    	printf("C%d = %d \n",j,C[j]);
	}

    }

void MS5611_Read_PT(float * PRESSURE, float * TEMPERATURE){

	int D1; //ADC value of the pressure conversion
	int D2; //ADC value of the temperature conversion
	float dT; //difference between actual and measured temp.
	float OFF; //offset at actual temperature
	float SENS; //sensitivity at actual temperature
	float T2;
	float OFF2;
	float SENS2;
	float TEMP;

    D1 = MS5611_Convert_Dx(CMD_ADC_D1);
    D2 = MS5611_Convert_Dx(CMD_ADC_D2);


    dT = D2 - C[5] * pow(2,8);
    OFF = (C[2] * pow(2,16)) + (dT * C[4]) / pow(2,7);
    SENS = C[1] * pow(2,15) + (dT * C[3]) / pow(2,8);
    *TEMPERATURE = 2000 + dT * C[6]/pow(2,23);

    //SECOND ORDER TEMP COMPENSATION
    if(*TEMPERATURE < 2000){
    T2 = (dT *dT) / pow(2,31);
    TEMP = *TEMPERATURE - 2000;
    OFF2 = (5 *  TEMP * TEMP) / 2;
    SENS2 = (5 *  TEMP * TEMP) / pow(2,2);
        if(*TEMPERATURE < -1500){
            TEMP = *TEMPERATURE + 1500;
            OFF2 = OFF2 + 7 * TEMP * TEMP;
            SENS2 = ((SENS2 + (11 * TEMP * TEMP)))/2;
        }
    *TEMPERATURE -= T2;
    OFF -= OFF2;
    SENS -= SENS2;
    }else{
    	T2 = 0;
    	OFF2 = 0;
    	SENS2 = 0;
    }
    *PRESSURE = (float)(((D1 * SENS / pow(2,21)) - OFF)/pow(2,15));

    printf("Temp: %d",*TEMPERATURE);
    printf("Press: %d",*PRESSURE);
}
