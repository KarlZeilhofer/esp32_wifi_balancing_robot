/*
 * Timers.c
 *
 *  Created on: 24.09.2017
 *      Author: anonymous
 */

#include "globals.h"
#include "defines.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_types.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "esp32-hal-timer.h"
#include <stdint.h>

extern "C" {

portMUX_TYPE muxer1 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE muxer2 = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR timer1ISR() {
    static bool stepSet = false; // ist STEP pin momentan HIGH?
    static uint32_t timer_period = ZERO_SPEED_PERIOD;

    portENTER_CRITICAL_ISR(&muxer1);

    int32_t act_speed = act_speed_M1;
    int32_t target_speed = target_speed_M1;

    // change DIR pin only on falling edge of STEP pin, to comply with setup and hold timings
    if(stepSet){
        digitalWrite(PIN_MOTOR1_STEP, LOW);
        stepSet = false;

        if(act_speed > 0){
            digitalWrite(PIN_MOTOR1_DIR, HIGH);
        }else{
            digitalWrite(PIN_MOTOR1_DIR, LOW);
        }
    }else{
        // Update timer period
        if(act_speed == 0 && target_speed!=0){
            // TODO: setup DIR pin first!
            timer_period = TIMER_CLOCK/MIN_STEP_CLOCK;
            if(target_speed > 0){
                act_speed = MIN_STEP_CLOCK;
            }else{
                act_speed = -MIN_STEP_CLOCK;
            }
        // TODO: handle speed direction change!
        }else{
            int32_t abs_act_speed = abs(act_speed);
            int32_t delta_speed = (MAX_ACCEL + abs_act_speed/2)/abs_act_speed; // constant accelleration, division with rounding

            if(target_speed > act_speed){ // accellerating
                act_speed = act_speed + delta_speed;
            }else if(target_speed < act_speed){ // decellerating
                act_speed = act_speed - delta_speed;
            }
            abs_act_speed = abs(act_speed);
            timer_period = (TIMER_CLOCK+abs_act_speed/2)/abs_act_speed;
        }


        digitalWrite(PIN_MOTOR1_STEP, HIGH); // step on rising edge
        stepSet = true;
    }

    if (act_speed != 0) {
        // toggle step signal. state is increased in stepper controller each rising edge.
        // pulse width has to be at least 1us.

        if (act_speed > 0)
            steps1--;
        else
            steps1++;
    }
    act_speed_M1 = act_speed;

    portEXIT_CRITICAL_ISR(&muxer1);

    timerAlarmWrite(timer1, timer_period, true);
}
void IRAM_ATTR timer2ISR() {
    static bool set = false;
    portENTER_CRITICAL_ISR(&muxer2);

    if (act_dir_M2 != 0) {
        // toggle step signal. state is increased in stepper controller each rising edge.
        // pulse width has to be at least 1us.
        if(set){
            set = false;
            digitalWrite(PIN_MOTOR2_STEP, LOW);
        }else{
            set = true;
            digitalWrite(PIN_MOTOR2_STEP, HIGH);
        }

        if (act_dir_M2 > 0)
            steps2--;
        else
            steps2++;
    }
    portEXIT_CRITICAL_ISR(&muxer2);
}
} // end extern C

void initTimers() {

    timer1 = timerBegin(0, CPU_CLOCK/TIMER_CLOCK, true);
    timerAttachInterrupt(timer1, &timer1ISR, true);
    timerAlarmWrite(timer1, ZERO_SPEED_PERIOD, true);

    timer2 = timerBegin(1, CPU_CLOCK/TIMER_CLOCK, true);
    timerAttachInterrupt(timer2, &timer2ISR, true);
    timerAlarmWrite(timer2, ZERO_SPEED_PERIOD, true);

    timerAlarmEnable(timer1);
    timerAlarmEnable(timer2);
}
