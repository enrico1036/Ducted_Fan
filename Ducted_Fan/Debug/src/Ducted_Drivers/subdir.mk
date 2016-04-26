################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/Ducted_Drivers/AHRS.c \
..\src/Ducted_Drivers/AHRS_Mahony.c \
..\src/Ducted_Drivers/AverageFilter.c \
..\src/Ducted_Drivers/HMC5883L.c \
..\src/Ducted_Drivers/IMU_write_read.c \
..\src/Ducted_Drivers/Kalman.c \
..\src/Ducted_Drivers/MPU6050.c \
..\src/Ducted_Drivers/MS5611-01BA01.c \
..\src/Ducted_Drivers/Motor.c \
..\src/Ducted_Drivers/PID.c \
..\src/Ducted_Drivers/Servo.c \
..\src/Ducted_Drivers/Sonar.c \
..\src/Ducted_Drivers/WatchDogTimer.c 

C_DEPS += \
./src/Ducted_Drivers/AHRS.d \
./src/Ducted_Drivers/AHRS_Mahony.d \
./src/Ducted_Drivers/AverageFilter.d \
./src/Ducted_Drivers/HMC5883L.d \
./src/Ducted_Drivers/IMU_write_read.d \
./src/Ducted_Drivers/Kalman.d \
./src/Ducted_Drivers/MPU6050.d \
./src/Ducted_Drivers/MS5611-01BA01.d \
./src/Ducted_Drivers/Motor.d \
./src/Ducted_Drivers/PID.d \
./src/Ducted_Drivers/Servo.d \
./src/Ducted_Drivers/Sonar.d \
./src/Ducted_Drivers/WatchDogTimer.d 

OBJS += \
./src/Ducted_Drivers/AHRS.obj \
./src/Ducted_Drivers/AHRS_Mahony.obj \
./src/Ducted_Drivers/AverageFilter.obj \
./src/Ducted_Drivers/HMC5883L.obj \
./src/Ducted_Drivers/IMU_write_read.obj \
./src/Ducted_Drivers/Kalman.obj \
./src/Ducted_Drivers/MPU6050.obj \
./src/Ducted_Drivers/MS5611-01BA01.obj \
./src/Ducted_Drivers/Motor.obj \
./src/Ducted_Drivers/PID.obj \
./src/Ducted_Drivers/Servo.obj \
./src/Ducted_Drivers/Sonar.obj \
./src/Ducted_Drivers/WatchDogTimer.obj 


# Each subdirectory must supply rules for building sources it contributes
src/Ducted_Drivers/%.obj: ../src/Ducted_Drivers/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_bsp","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/LowLevelDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/DuctedDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src/glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_bsp","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/LowLevelDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/DuctedDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src/glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

