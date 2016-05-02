#include <Ducted_Drivers/RC_CH1.h>

#include <machine.h>
#include <platform.h>


static enum RcState rc_state = RC_NOT_INITIALIZED;
static uint16_t rc_count = 0;

void rcInitialize(void) {
	// Initialize and setup MTU5 (channel W)
	// on Pulse Width Measurement mode
	MTU5W_Setup();

	// Unlock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA50B;
#endif

	// Setup interrupt on falling edge on echo pin
	IEN (ICU, IRQ5) = 0x0;

	MPC.PD5PFS.BIT.ASEL = 0;	// Not used as analog
	MPC.PD5PFS.BIT.ISEL = 1;	// Used as interrupt

	// Set interrupt priority
	IPR(ICU, IRQ5)= 0x03;

	// Set interrupt detection on falling edge
	ICU.IRQCR[5].BIT.IRQMD = 0x1;

	// Enable interrupt requests
	IEN(ICU, IRQ5)= 0x1;

	// Lock ports
#ifdef PLATFORM_BOARD_RDKRX63N
	SYSTEM.PRCR.WORD = 0xA500;
#endif

	rc_state = RC_READY;
}

uint32_t rcGetState(void) {
	return (uint32_t) rc_state;
}


void rcCountStart() {
	MTU5W_Start();
	rc_state = RC_MEASURING;
}

void rcCountStop() {
	rc_count = MTU5W_GetTimerCounter();
	MTU5W_Stop();
	rc_state = RC_READY;
}

double rcGetUs() {
	return ((double) rc_count * RC_US_PER_COUNT);
}

#pragma interrupt (rcISR(vect = VECT(ICU, IRQ5)))
static void rcISR() {
	// Copy counter
	rc_count = MTU5W_GetTimerCounter();
	// Stop timer
	MTU5W_Stop();
	// Return to ready state
	rc_state = RC_READY;
}

