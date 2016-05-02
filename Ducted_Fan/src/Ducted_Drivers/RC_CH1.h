#ifndef SRC_RC_H_
#define SRC_RC_H_

#include <MTU2a/MTU_C5W.h>

#include <machine.h>
#include <platform.h>


#define RC_US_PER_COUNT    0.333333

enum RcState {
	RC_MEASURING = 0x0,
	RC_READY = 0x1,
	RC_NOT_INITIALIZED = 0x2
};

void rcInitialize(void) ;

uint32_t rcGetState(void);

void rcCountStart();
void rcCountStop();

double rcGetUs();

#endif /* SRC_RC_H_ */
