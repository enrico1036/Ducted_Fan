################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/LowLevelDrivers/MTU2a/MTU_C3.c \
..\src/LowLevelDrivers/MTU2a/MTU_C4.c \
..\src/LowLevelDrivers/MTU2a/MTU_C5.c 

C_DEPS += \
./src/LowLevelDrivers/MTU2a/MTU_C3.d \
./src/LowLevelDrivers/MTU2a/MTU_C4.d \
./src/LowLevelDrivers/MTU2a/MTU_C5.d 

OBJS += \
./src/LowLevelDrivers/MTU2a/MTU_C3.obj \
./src/LowLevelDrivers/MTU2a/MTU_C4.obj \
./src/LowLevelDrivers/MTU2a/MTU_C5.obj 


# Each subdirectory must supply rules for building sources it contributes
src/LowLevelDrivers/MTU2a/%.obj: ../src/LowLevelDrivers/MTU2a/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_bsp","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/LowLevelDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/DuctedDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src/glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_bsp","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/LowLevelDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src/DuctedDrivers","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_riic_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_glyph/src/glyph","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600","C:/Renesas/e2_studio/Workspace/Ducted_Fan/r_rspi_rx600/src","C:/Renesas/e2_studio/Workspace/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

