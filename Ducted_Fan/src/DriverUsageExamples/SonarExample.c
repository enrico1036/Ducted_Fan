#include "../Ducted_Drivers/Sonar.h"

float distance;


void main(){
	// Initialize sonar status
	sonarInitialize();

	while(1){
		// Set trigger pin high
		sonarTriggerStart();
		// Delay at least 10us
		for(int i=0; i<1000; i++){
			nop();
		}
		// Clear trigger
		sonarTriggerStop();

		// Start counting on echo pin
		sonarEchoCountStart();
		// Delay to let the sonar transmit echo
		for(int i=0; i<1000000; i++){
			nop();
		}
		sonarEchoCountStop();

		// Retrieve calculated distance
		distance = sonarGetDistance();
	}

}
