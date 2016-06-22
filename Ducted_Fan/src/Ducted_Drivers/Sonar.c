#include <Ducted_Drivers/Sonar.h>

#include <machine.h>
#include <platform.h>


static enum SonarState sonar_state = SONAR_NOT_INITIALIZED;
static uint16_t sonar_echo_count = 0;

void sonarInitialize(void) {
	// Initialize and setup MTU5 (channel U)
	// on Pulse Width Measurement mode
	MTU5U_Setup();

	// Unlock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA50B;
#endif

	// Setup trigger pin
	// PD6 (pin 19 on jn2) output
	PORTD.PDR.BIT.B6 = 0x1;
	PORTD.PODR.BIT.B6 = 0x0;
	PORTD.PMR.BIT.B6 = 0x0;

	// Setup interrupt on falling edge on echo pin
	IEN (ICU, IRQ7)= 0x0;

	MPC.PD7PFS.BIT.ASEL = 0;	// Not used as analog
	MPC.PD7PFS.BIT.ISEL = 1;	// Used as interrupt

	// Set interrupt priority
	IPR(ICU, IRQ7)= 0x03;
	// Set interrupt detection on falling edge
	ICU.IRQCR[7].BIT.IRQMD = 0x1;

	// Enable interrupt requests
	IEN(ICU, IRQ7)= 0x1;

	// Lock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA500;
#endif

	sonar_state = SONAR_IDLE;
}

uint32_t sonarGetState(void) {
	return (uint32_t) sonar_state;
}

void sonarTriggerStart() {
	// Unlock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA50B;
#endif

	PORTD.PODR.BIT.B6 = 0x1;
	sonar_state = SONAR_TRIGGER;
	// Lock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA500;
#endif

}

void sonarTriggerStop() {
	// Unlock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA50B;
#endif

	PORTD.PODR.BIT.B6 = 0x0;
	sonar_state = SONAR_IDLE;

	// Lock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA500;
#endif
}

void sonarEchoCountStart() {
	MTU5U_Start();
	sonar_state = SONAR_ECHO;
}

void sonarEchoCountStop() {
	sonar_echo_count = MTU5U_GetTimerCounter();
	MTU5U_Stop();
	sonar_state = SONAR_IDLE;
}

double sonarGetDistance() {
	return ((((double) sonar_echo_count * SONAR_US_PER_COUNT) / 1000000.0) * SONAR_SOUND_SPEED) / 2;
	//return (sonar_echo_count * SONAR_US_PER_COUNT) / 58.0;
}

#pragma interrupt (sonarEchoISR(vect = VECT(ICU, IRQ7)))
static void sonarEchoISR() {
	// Copy counter
	sonar_echo_count = MTU5U_GetTimerCounter();
	// Stop timer
	MTU5U_Stop();
	// Return to idle state
	sonar_state = SONAR_IDLE;
}

