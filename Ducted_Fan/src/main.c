
#include <stdint.h>
#include <stdio.h>
#include <machine.h>
#include "platform.h"
#include "s12adc.h"
#include "Ducted_Drivers/Motor.h"
#include "Ducted_Drivers/Servo.h"
#include "Ducted_Drivers/map.h"
#include "Ducted_Drivers/PID.h"
#include "Ducted_Drivers/Sonar.h"
#include "LowLevelDrivers/CMT.h"
#include "I2C.h"
#include "Ducted_Drivers/lcd_buffer.h"
#include "Ducted_Drivers/Kalman.h"
#include "Ducted_Drivers/MPU6050.h"
#include "Ducted_Drivers/HMC5883L.h"
#include "Ducted_Drivers/AHRS.h"
#include "Ducted_Drivers/WatchDogTimer.h"
#include "Ducted_Drivers/AverageFilter.h"
#include "Ducted_Drivers/RC_CH1.h"

/*******************************************************************************
 Prototypes for local functions
 *******************************************************************************/
void Setup();
void Callback_1ms();
void Callback_5ms();
void Callback_10ms();
void Callback_20ms();
void Callback_50ms();
void Callback_100ms();
void Callback_500ms();
void Callback_1000ms();
void Fallback();
void Sonar_Fallback();
void Rc_Fallback();

/*******************************************************************************
 Global variables
 *******************************************************************************/
struct axis {
	float x;
	float y;
	float z;
};
struct dynamic {
	struct axis acc;
	struct axis vel;
	struct axis pos;
};

struct physicalState {
	struct dynamic accel;
	struct dynamic gyro;
	struct dynamic magn;
	struct dynamic abs;
	struct dynamic Kalman;
	float avg_motor_us;
	float motor_diff_us;
	float x_servo_deg;
	float y_servo_deg;
};
union {
	struct physicalState key;
	float index[sizeof(struct physicalState)];
} desiredState;	//state variables you want to reach

union {
	struct physicalState key;
	float index[sizeof(struct physicalState)];
} currentState;	//current state variables of the DuctedFan

// Pointer to kalman structures
extern KALMAN *pitchKalman;
extern KALMAN *rollKalman;

// Structure containing timer flags
extern struct timerClocks timers;

/* Create PID structure used f+or PID properties */
PID_config z_axis_PID;
PID_config Pitch_PID;
PID_config Roll_PID;

// These structure are used to store
// moving-average filter buffers for roll and pitch
AVG_Filter_struct pitchAVG;
AVG_Filter_struct rollAVG;


/*Stores the value read from analog input  */
uint16_t analogRead;

/* Used to store value of altitude need to be reached */
float altitudeValue;

/* Time in seconds every which PID control is made */
float dt = 0.02;

// Structures for software watchdogs
WDT_struct sonarWDT;
WDT_struct mainWDT;
WDT_struct rcWDT;


void main(void) {
	/* One time initialize instructions */
	Setup();

	/* Endless loop*/
	while (1) {
		if (timers.timer_1mS) {
			timers.timer_1mS = 0;
			Callback_1ms();								//Operations to do every 1ms
			if (timers.timer_5mS) {
				timers.timer_5mS = 0;
				Callback_5ms();							// Operations to do every 5ms
				if (timers.timer_10mS) {
					timers.timer_10mS = 0;
					Callback_10ms();					// Operations to do every 10ms
					if (timers.timer_20mS) {
						timers.timer_20mS = 0;
						Callback_20ms();				// Operations to do every 20ms
					}
					if (timers.timer_50mS) {
						timers.timer_50mS = 0;
						Callback_50ms();				// Operations to do every 50ms	
						if (timers.timer_100mS) {
							timers.timer_100mS = 0;
							Callback_100ms();			// Operations to do every 100ms
							if (timers.timer_500mS) {
								timers.timer_500mS = 0;
								Callback_500ms();		// Operations to do every half a second
								if (timers.timer_1000mS) {
									timers.timer_1000mS = 0;
									Callback_1000ms();	// Operations to do every second 
								}
							}
						}

					}
				}
			}
		}
		// Reset wdt in order to keep the program running
		WDT_Reset(&mainWDT);
	}
	// Shutdown everything
	Fallback();

} /* End function main() */

void Setup() {
	/* Initialize LCD */
	lcd_initialize();

	/* Clear LCD */
	lcd_clear();

	/* Display message on LCD */
	lcd_buffer_print(LCD_LINE2, "    TEST   ");

	/* Initialize motors */
	Motors_Init();
	/* Turn on motors relay */
	Motors_On();
	/* Send arm signal to motors */
	Motor_Arm(MOTOR_UPPER);
	Motor_Arm(MOTOR_BOTTOM);

	/* Initialize servos */
	Servos_Init();

	/* Initialize sonar */
	sonarInitialize(); //must be initialized before IIC, otherwise it will not work

	/* Initialize radio command */
	rcInitialize();

	/* Setup the 12-bit A/D converter */
	S12ADC_init();


	/* Initialize I2C with control */
	riic_ret_t iic_ret = RIIC_OK;
	iic_ret |= riic_master_init();
	while (RIIC_OK != iic_ret) {
		nop(); /* Failure to initialize here means demo can not proceed. */
	}

	/* Setup Compare Match Timer */
	CMT_init();

	// Initialize PID structures used for PID properties
	// with their respective coefficents for proportional, 
	// derivative and integrative
	PID_Init(&z_axis_PID, 0.7, 0.05, 0.30, dt, 0, 0.5);
	PID_Init(&Pitch_PID, 1, 0, 0.01, dt, -30, 30);
	PID_Init(&Roll_PID, 1, 0, 0.01, dt, -30, 30);
	
	// Initialize average filters
	Init_AVG(0, &pitchAVG);
	Init_AVG(0, &rollAVG);

	/* Make the port connected to SW1 an input */
	PORT4.PDR.BIT.B0 = 0;

	/*MPU6050 Initialization*/
	MPU6050_Test_I2C();
	Setup_MPU6050();
	Calibrate_Gyros();
	
	/*Kalman Initialization*/
	init_Kalman();

	desiredState.key.motor_diff_us = 0;
	desiredState.key.abs.pos.z = 0.20;
	altitudeValue = 0;
	
	// Software watchdogs initialization
	mainWDT = WDT_Init(500, Fallback);
	WDT_Start(&mainWDT);
	sonarWDT = WDT_Init(60, Sonar_Fallback);
	WDT_Start(&sonarWDT);
	rcWDT = WDT_Init(40, Rc_Fallback);
	WDT_Start(&rcWDT);
}
void Callback_1ms() {
	/* Start the A/D converter */
	S12ADC_start();

	/*!!Safety check: stop timer count if sonar doesn't answer anymore */
	if (sonarGetState() == SONAR_ECHO){
		WDT_Increase(&sonarWDT);
	}
	if(rcGetState() != RC_READY) {
		WDT_Increase(&rcWDT);
	}

	/* Wait for the conversion to complete */
	while (false == S12ADC_conversion_complete()) {
	}
	/* Fetch the results from the ADC */
	analogRead = S12ADC_read_AN002();

}


void Callback_5ms() {
	// Stop the trigger and start echo counting
	if (sonarGetState() == SONAR_TRIGGER) {
		sonarTriggerStop();
		sonarEchoCountStart();
		WDT_Reset(&sonarWDT);
	}

	if(rcGetState() == RC_READY) {
		// If pwm high is between 950 and 995 us shut down
		// (safety lever trigger)
		if(rcGetUs() > 950 && rcGetUs() < 995)
			Rc_Fallback();
		// Map the microseconds into meters and use them as
		// a setpoint for height PID
		altitudeValue = map(rcGetUs(), 1068, 2000, 0, 3);
		rcCountStart();
		WDT_Reset(&rcWDT);
	}
}

static double sonarDistance = 0;
void Callback_10ms() {
	// Retrieve distance in meters
	sonarDistance = sonarGetDistance();
}

float outValue;	// Temporary storage for PID results
void Callback_20ms() {
	desiredState.key.abs.pos.z = altitudeValue;
	lcd_buffer_print(LCD_LINE3, "Set: %1.3f", desiredState.key.abs.pos.z);

	/* Setting motor speed based on altitude */
	lcd_buffer_print(LCD_LINE4, "In: %1.3f", sonarDistance);
	outValue = PID_Compute(sonarDistance, desiredState.key.abs.pos.z, &z_axis_PID);
	desiredState.key.avg_motor_us = map(outValue * map(analogRead, 0, 4096, 0, 1), 0, 0.5, MOTOR_MIN_US, MOTOR_MAX_US);
	lcd_buffer_print(LCD_LINE5, "Mot: %4.0f", desiredState.key.avg_motor_us);

	/* Obtain accelerometer an gyro values */
	Get_Gyro_Rates(&currentState.key.gyro.vel.x, &currentState.key.gyro.vel.y, &currentState.key.gyro.vel.z);
	Get_Accel_Angles(&currentState.key.accel.pos.x, &currentState.key.accel.pos.y);

	Get_Accel_Gravity_Power(&currentState.key.accel.vel.x, &currentState.key.accel.vel.y, &currentState.key.accel.vel.z);
	get_Angle_AHRS(currentState.key.gyro.vel.x, currentState.key.gyro.vel.y, currentState.key.gyro.vel.z, currentState.key.accel.vel.x, currentState.key.accel.vel.y, currentState.key.accel.vel.z, currentState.key.magn.pos.x, currentState.key.magn.pos.y, currentState.key.magn.pos.z, &currentState.key.Kalman.acc.x, &currentState.key.Kalman.acc.y, &currentState.key.Kalman.acc.z);

	/* Perform a double pass filtering with Kalman first and moving-average next*/
	currentState.key.Kalman.pos.x = Compute_AVG(getAngle(currentState.key.accel.pos.x, currentState.key.gyro.vel.x, dt, rollKalman), &rollAVG);
	currentState.key.Kalman.pos.y = Compute_AVG(getAngle(currentState.key.accel.pos.y, currentState.key.gyro.vel.y, dt, pitchKalman), &pitchAVG);
	
	// Map Kalman results into degrees for servos
	desiredState.key.x_servo_deg = map(PID_Compute(-currentState.key.Kalman.pos.x, 0, &Roll_PID), -30, 30, 60, 120);
	desiredState.key.y_servo_deg = map(PID_Compute(-currentState.key.Kalman.pos.y, 0, &Pitch_PID), -30, 30, 60, 120);

	currentState.key.Kalman.pos.z += currentState.key.gyro.vel.z*dt;

	// Write new results to motors and servos
	Motor_Write_us(MOTOR_UPPER, desiredState.key.avg_motor_us + desiredState.key.motor_diff_us);
	Motor_Write_us(MOTOR_BOTTOM, desiredState.key.avg_motor_us - desiredState.key.motor_diff_us);

	Servo_Write_deg(SERVO_ROLL, desiredState.key.x_servo_deg);
	Servo_Write_deg(SERVO_PITCH, desiredState.key.y_servo_deg); // pitch servo is trimmed 18°
}

void Callback_50ms() {
	// Start sonar measurement if idle
	if (sonarGetState() == SONAR_IDLE)
		sonarTriggerStart();
}

void Callback_100ms() {
}

void Callback_500ms() {
}

void Callback_1000ms() {
	// Flush temporary buffer into real lcd buffer
	lcd_buffer_flush();
}

void Fallback() {
	lcd_display(LCD_LINE2, "  Fallback  ");
	lcd_display(LCD_LINE3, " condition! ");
	/* Turno off motors */
	Motor_Write_us(MOTOR_UPPER, 0);
	Motor_Write_us(MOTOR_BOTTOM, 0);
	Motors_Off();
	/* Turn off servos */
	Servo_Write_deg(SERVO_PITCH, (SERVO_MAX_BOUND_DEG+SERVO_MIN_BOUND_DEG)/2);
	Servo_Write_deg(SERVO_ROLL, (SERVO_MAX_BOUND_DEG+SERVO_MIN_BOUND_DEG)/2);
	Servos_Off();
	while(1)
		nop();
}

void Sonar_Fallback() {
	sonarEchoCountStop();
	lcd_display(LCD_LINE7, " Sonar ");
	Fallback();	//TODO: remove this call when barometer will be used
}

void Rc_Fallback() {
	rcCountStop();
	lcd_display(LCD_LINE7, " RC ");
	Fallback();
}
