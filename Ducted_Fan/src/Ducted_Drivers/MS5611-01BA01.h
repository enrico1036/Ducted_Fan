
#ifndef MS5611_01BA01_H_
#define MS5611_01BA01_H_

#define MS5611_ADDR 	0xEE   	// Module address write mode 1110 1110 bit1=CSB bit0=0 write
//#define MS5611_ADDRR	0xEF    // Module address read mode 1110 1111

#define CMD_RESET 		0x1E 	// ADC reset command 0001 1110
#define CMD_ADC_READ 	0x00 	// ADC read command
#define CMD_ADC_D1 		0x48 	// ADC D1 conversion
#define CMD_ADC_D2 		0x58 	// ADC D2 conversion
#define CMD_PROM_RD 	0xA0 	// Prom read command 1010 0000


void MS5611_Init(void);
void MS5611_Reset(void);

int MS5611_Read_Prom(int COEF_NUM); //read one byte from prom memory of sensor input coef_num from 1 to 7
void MS5611_Read_Coef(int C[]); //read all coefficients to table input C[8] table
int MS5611_Convert_Dx(int COMMAND); //read D1 for Temp counting or D2 for Alt counting input: CMD_ADC_D1 or CMD_ADC_D2
void MS5611_Read_PT(float * PRESSURE, float * TEMPERATURE); //count pressure and temperature

#endif /* MS5611_01BA01_H_ */
