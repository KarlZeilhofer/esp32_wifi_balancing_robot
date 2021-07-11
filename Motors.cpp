/*
 * Motors.cpp
 *
 *  Created on: 25.09.2017
 *      Author: anonymous
 */

#include <Arduino.h>
#include "defines.h"
#include "globals.h"
#include <stdint.h>

// Set target speed of Stepper Motor1
// unit is in 16th fullsteps per second (200 steps/revolution * 16microsteps/fullstep = 3200 Microsteps/s for 1 revolution/s)
// tspeed could be positive or negative (reverse)
void setMotorSpeedM1(int32_t tspeed)
{
    target_speed_M1 = tspeed;
}

// Set speed of Stepper Motor2
// tspeed could be positive or negative (reverse)
void setMotorSpeedM2(int32_t tspeed)
{
    target_speed_M2 = tspeed;
}

