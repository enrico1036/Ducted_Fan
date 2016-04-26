################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.lst *.lis *.lpp *.map *.x *.lbp src/*.src src/*.p src/*.pp *.bls *.libelf *.lbk *.abs *.dbg *.sni *.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include src/LowLevelDrivers/MTU2a/subdir.mk
-include src/LowLevelDrivers/subdir.mk
-include src/Ducted_Drivers/subdir.mk
-include r_rspi_rx600/src/subdir.mk
-include r_riic_rx600/src/subdir.mk
-include r_glyph/src/subdir.mk
-include r_glyph/src/glyph/subdir.mk
-include r_glyph/src/glyph/fonts/subdir.mk
-include r_glyph/src/glyph/drivers/subdir.mk
-include r_bsp/board/rdkrx63n/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CP_DEPS)),)
-include $(CP_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CP_UPPER_DEPS)),)
-include $(CP_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(ABS_DEPS)),)
-include $(ABS_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
CONVERTOR_OUTPUT_OUTPUTS += \
ADC_OneShot.mot \

LINKER_OUTPUT_OUTPUTS += \
ADC_OneShot.abs \

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
ADC_OneShot.lib \

# All Target
all: ADC_OneShot.mot
	@echo 'Build complete.'

# Tool invocations
ADC_OneShot.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Converter'
	rlink   "C:\Renesas\e2_studio\Workspace\Ducted_Fan\Debug\ADC_OneShot.abs" -form=stype  -output="C:\Renesas\e2_studio\Workspace\Ducted_Fan\Debug\ADC_OneShot.mot"
	@echo 'Finished building target:'
	@echo.
	$(MAKE) --no-print-directory post-build

ADC_OneShot.abs: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(ALL_ASMS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rlink  -subcommand="LinkerSubCommand.tmp"  -library="C:\Renesas\E2_STU~1\WORKSP~1\DUCTED~2\Debug\ADC_OneShot.lib" -noprelink -list="ADC_OneShot.map" -show -nooptimize -debug -output="C:\Renesas\e2_studio\Workspace\Ducted_Fan\Debug\ADC_OneShot.abs" -nocompress -nologo -nomessage -rom=D=R,D_1=R_1,D_2=R_2 -vect=_undefined_interrupt_source_isr
	@echo 'Finished building:'
	@echo.

ADC_OneShot.lib:  
	@echo 'Invoking: Standard Library'
	lbgrx -lang=c99 -head=runtime,math,stdio,stdlib -cpu=rx600 -output="ADC_OneShot.lib"
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
	-$(RM) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS) 
	-rm -rf "src"/*.obj "src"/*.d "src"/*.src "src"/*.p "src"/*.pp "src"/*.mrc "src"/*.prn
	-rm -rf "src/LowLevelDrivers/MTU2a"/*.obj "src/LowLevelDrivers/MTU2a"/*.d "src/LowLevelDrivers/MTU2a"/*.src "src/LowLevelDrivers/MTU2a"/*.p "src/LowLevelDrivers/MTU2a"/*.pp "src/LowLevelDrivers/MTU2a"/*.mrc "src/LowLevelDrivers/MTU2a"/*.prn
	-rm -rf "src/LowLevelDrivers"/*.obj "src/LowLevelDrivers"/*.d "src/LowLevelDrivers"/*.src "src/LowLevelDrivers"/*.p "src/LowLevelDrivers"/*.pp "src/LowLevelDrivers"/*.mrc "src/LowLevelDrivers"/*.prn
	-rm -rf "src/Ducted_Drivers"/*.obj "src/Ducted_Drivers"/*.d "src/Ducted_Drivers"/*.src "src/Ducted_Drivers"/*.p "src/Ducted_Drivers"/*.pp "src/Ducted_Drivers"/*.mrc "src/Ducted_Drivers"/*.prn
	-rm -rf "r_rspi_rx600/src"/*.obj "r_rspi_rx600/src"/*.d "r_rspi_rx600/src"/*.src "r_rspi_rx600/src"/*.p "r_rspi_rx600/src"/*.pp "r_rspi_rx600/src"/*.mrc "r_rspi_rx600/src"/*.prn
	-rm -rf "r_riic_rx600/src"/*.obj "r_riic_rx600/src"/*.d "r_riic_rx600/src"/*.src "r_riic_rx600/src"/*.p "r_riic_rx600/src"/*.pp "r_riic_rx600/src"/*.mrc "r_riic_rx600/src"/*.prn
	-rm -rf "r_glyph/src"/*.obj "r_glyph/src"/*.d "r_glyph/src"/*.src "r_glyph/src"/*.p "r_glyph/src"/*.pp "r_glyph/src"/*.mrc "r_glyph/src"/*.prn
	-rm -rf "r_glyph/src/glyph"/*.obj "r_glyph/src/glyph"/*.d "r_glyph/src/glyph"/*.src "r_glyph/src/glyph"/*.p "r_glyph/src/glyph"/*.pp "r_glyph/src/glyph"/*.mrc "r_glyph/src/glyph"/*.prn
	-rm -rf "r_glyph/src/glyph/fonts"/*.obj "r_glyph/src/glyph/fonts"/*.d "r_glyph/src/glyph/fonts"/*.src "r_glyph/src/glyph/fonts"/*.p "r_glyph/src/glyph/fonts"/*.pp "r_glyph/src/glyph/fonts"/*.mrc "r_glyph/src/glyph/fonts"/*.prn
	-rm -rf "r_glyph/src/glyph/drivers"/*.obj "r_glyph/src/glyph/drivers"/*.d "r_glyph/src/glyph/drivers"/*.src "r_glyph/src/glyph/drivers"/*.p "r_glyph/src/glyph/drivers"/*.pp "r_glyph/src/glyph/drivers"/*.mrc "r_glyph/src/glyph/drivers"/*.prn
	-rm -rf "r_bsp/board/rdkrx63n"/*.obj "r_bsp/board/rdkrx63n"/*.d "r_bsp/board/rdkrx63n"/*.src "r_bsp/board/rdkrx63n"/*.p "r_bsp/board/rdkrx63n"/*.pp "r_bsp/board/rdkrx63n"/*.mrc "r_bsp/board/rdkrx63n"/*.prn
	@echo.
	@echo 'Clean complete.'

post-build:
	@echo.
	-C:\Renesas\E2_STU~1\DEBUGC~1\RX\RX_CON~1.EXE ADC_OneShot.abs ADC_OneShot.x
	@echo.

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
