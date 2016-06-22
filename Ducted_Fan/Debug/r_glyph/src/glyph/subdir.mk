################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\r_glyph/src/glyph/glyph.c 

C_DEPS += \
./r_glyph/src/glyph/glyph.d 

OBJS += \
./r_glyph/src/glyph/glyph.obj 


# Each subdirectory must supply rules for building sources it contributes
r_glyph/src/glyph/%.obj: ../r_glyph/src/glyph/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_bsp","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/LowLevelDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/DuctedDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src/glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_bsp","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/LowLevelDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/DuctedDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src/glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

