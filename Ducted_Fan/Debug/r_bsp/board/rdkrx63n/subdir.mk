################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SRC_SRCS += \
..\r_bsp/board/rdkrx63n/lowlvl.src 

C_SRCS += \
..\r_bsp/board/rdkrx63n/dbsct.c \
..\r_bsp/board/rdkrx63n/flash_options.c \
..\r_bsp/board/rdkrx63n/hwsetup.c \
..\r_bsp/board/rdkrx63n/lcd.c \
..\r_bsp/board/rdkrx63n/lowsrc.c \
..\r_bsp/board/rdkrx63n/resetprg.c \
..\r_bsp/board/rdkrx63n/sbrk.c \
..\r_bsp/board/rdkrx63n/vecttbl.c 

C_DEPS += \
./r_bsp/board/rdkrx63n/dbsct.d \
./r_bsp/board/rdkrx63n/flash_options.d \
./r_bsp/board/rdkrx63n/hwsetup.d \
./r_bsp/board/rdkrx63n/lcd.d \
./r_bsp/board/rdkrx63n/lowsrc.d \
./r_bsp/board/rdkrx63n/resetprg.d \
./r_bsp/board/rdkrx63n/sbrk.d \
./r_bsp/board/rdkrx63n/vecttbl.d 

SRC_DEPS += \
./r_bsp/board/rdkrx63n/lowlvl.d 

OBJS += \
./r_bsp/board/rdkrx63n/dbsct.obj \
./r_bsp/board/rdkrx63n/flash_options.obj \
./r_bsp/board/rdkrx63n/hwsetup.obj \
./r_bsp/board/rdkrx63n/lcd.obj \
./r_bsp/board/rdkrx63n/lowlvl.obj \
./r_bsp/board/rdkrx63n/lowsrc.obj \
./r_bsp/board/rdkrx63n/resetprg.obj \
./r_bsp/board/rdkrx63n/sbrk.obj \
./r_bsp/board/rdkrx63n/vecttbl.obj 


# Each subdirectory must supply rules for building sources it contributes
r_bsp/board/rdkrx63n/%.obj: ../r_bsp/board/rdkrx63n/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_bsp","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/LowLevelDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/DuctedDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src/glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_bsp","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/LowLevelDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src/DuctedDrivers","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_riic_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_glyph/src/glyph","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/r_rspi_rx600/src","C:/Users/Enrico/git/Ducted_Fan/Ducted_Fan/src","C:\PROGRA~2\Renesas\RX\2_4_1/include"  -debug -cpu=rx600 -speed -alias=noansi -nologo  -define=__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

r_bsp/board/rdkrx63n/%.obj: ../r_bsp/board/rdkrx63n/%.src
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	asrx  -MM -MP -MF="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)"  -nolistfile -cpu=rx600 -debug -nologo   "$<"
	asrx -output="$(@:%.d=%.obj)" -nolistfile -cpu=rx600 -debug -nologo   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

