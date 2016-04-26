/*
 * Kalman.c
 *
 *  Created on: 16/feb/2016
 *      Author: pc asus
 */

#include "Kalman.h"

KALMAN *pitchKalman;
KALMAN *rollKalman;
KALMAN *yawKalman;

KALMAN kalman1;
KALMAN kalman2;
KALMAN kalman3;

const float Q_angle = 0.0122; // Process noise variance for the accelerometer
const float  Q_bias = 0.0027; // Process noise variance for the gyro bias
const float  R_measure = 0.01; // Measurement noise variance - this is actually the variance of the measurement noise

void init_Kalman(void)
{
	// Init PitchKalman

        kalman1.angle = 0; // Reset the angle
        kalman1.bias = 0; // Reset bias

        kalman1.P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
        kalman1.P[0][1] = 0;
        kalman1.P[1][0] = 0;
        kalman1.P[1][1] = 0;

	pitchKalman=&kalman1;

	// Init RollKalman

        kalman2.angle = 0; // Reset the angle
        kalman2.bias = 0; // Reset bias

        kalman2.P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
        kalman2.P[0][1] = 0;
        kalman2.P[1][0] = 0;
        kalman2.P[1][1] = 0;

	rollKalman=&kalman2;

	// Init YawKalman   NOTA: VEDERE LA MATRICE BENE (!)

	    kalman3.angle = 0; // Reset the angle
        kalman3.bias = 0; // Reset bias

		kalman3.P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
        kalman3.P[0][1] = 0;
        kalman3.P[1][0] = 0;
        kalman3.P[1][1] = 0;

	yawKalman=&kalman3;

		return;
}



float getAngle(float newAngle, float newRate, float dt, KALMAN* Kalman)
{
        // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
        // Modified by Kristian Lauszus
        // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it

        // Discrete Kalman filter time update equations - Time Update ("Predict")
        // Update xhat - Project the state ahead
        /* Step 1 */
        Kalman->rate = newRate - Kalman->bias;
        Kalman->angle += dt * Kalman->rate;

        // Update estimation error covariance - Project the error covariance ahead
        /* Step 2 */
        Kalman->P[0][0] += dt * (dt*Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Q_angle);
        Kalman->P[0][1] -= dt * Kalman->P[1][1];
        Kalman->P[1][0] -= dt * Kalman->P[1][1];
        Kalman->P[1][1] += Q_bias * dt;

        // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
        // Calculate Kalman gain - Compute the Kalman gain
        /* Step 4 */
        Kalman->S = Kalman->P[0][0] + R_measure;
        /* Step 5 */
        Kalman->K[0] = Kalman->P[0][0] / Kalman->S;
        Kalman->K[1] = Kalman->P[1][0] / Kalman->S;

        // Calculate angle and bias - Update estimate with measurement zk (newAngle)
        /* Step 3 */
        Kalman->y = newAngle - Kalman->angle;
        /* Step 6 */
        Kalman->angle += Kalman->K[0] * Kalman->y;
        Kalman->bias += Kalman->K[1] * Kalman->y;

        // Calculate estimation error covariance - Update the error covariance
        /* Step 7 */
        Kalman->P[0][0] -= Kalman->K[0] * Kalman->P[0][0];
        Kalman->P[0][1] -= Kalman->K[0] * Kalman->P[0][1];
        Kalman->P[1][0] -= Kalman->K[1] * Kalman->P[0][0];
        Kalman->P[1][1] -= Kalman->K[1] * Kalman->P[0][1];

    return Kalman->angle;
}


//Used to set angle, this should be set as the starting angle
void setAngle(float newAngle, KALMAN* Kalman)
{
	Kalman->angle = newAngle;

}


// Return the unbiased rate
float getRate(KALMAN Kalman)
{
	return Kalman.rate;
}
