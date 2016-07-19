#ifndef SRC_SONAR_H_
#define SRC_SONAR_H_

#include <MTU2a/MTU_C5U.h>

#include <machine.h>
#include <platform.h>

#define SONAR_SOUND_SPEED	343.80000
#define SONAR_MAX_DISTANCE	  4.00000
#define SONAR_MIN_DISTANCE 	  0.02000
#define SONAR_US_PER_COUNT    1.33333

enum SonarState {
	SONAR_NOT_INITIALIZED = 0x0,
	SONAR_IDLE = 0x1,
	SONAR_TRIGGER = 0x2,
	SONAR_ECHO = 0x3
};

void sonarInitialize(void) ;
uint32_t sonarGetState(void);

void sonarTriggerStart();
void sonarTriggerStop();

void sonarEchoCountStart();
void sonarEchoCountStop();

double sonarGetDistance();

#endif /* SRC_SONAR_H_ */
