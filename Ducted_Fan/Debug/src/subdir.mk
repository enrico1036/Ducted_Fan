################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/S12ADC.c \
..\src/main.c 

C_DEPS += \
./src/S12ADC.d \
./src/main.d 

OBJS += \
./src/S12ADC.obj \
./src/main.obj 


# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_bsp","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/LowLevelDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/DuctedDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src/glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_bsp","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/LowLevelDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/DuctedDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src/glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

