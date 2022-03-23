/*
 *  drv_pwm.h
 *
 *  Created on: 2016. 7.12.
 *      Author: Baram, PBHP
 */

#ifndef DRV_PWM_H
#define DRV_PWM_H


#ifdef __cplusplus
 extern "C" {
#endif


#ifndef DEF_H
#define DEF_H

#include <stdint.h>
#include <stdbool.h>

#ifndef BOOL
#define BOOL uint8_t
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/*
#ifndef bool
#define bool uint8_t
#endif

#ifndef true
#define true  1
#endif

#ifndef false
#define false 0
#endif

*/

typedef void (*voidFuncPtr)(void);


#include "../def_err.h"




#define _DEF_CAN1               0
#define _DEF_CAN2               1
#define _DEF_CAN_BAUD_125K      0
#define _DEF_CAN_BAUD_250K      1
#define _DEF_CAN_BAUD_500K      2
#define _DEF_CAN_BAUD_1000K     3
#define _DEF_CAN_STD            0
#define _DEF_CAN_EXT            1





#endif

#include "../../bsp/opencr/bsp.h"






extern TIM_HandleTypeDef    hTIM1;
extern TIM_HandleTypeDef    hTIM2;
extern TIM_HandleTypeDef    hTIM3;
extern TIM_HandleTypeDef    hTIM9;
extern TIM_HandleTypeDef    hTIM11;
extern TIM_HandleTypeDef    hTIM12;


int drv_pwm_init();

void drv_pwm_set_freq(uint32_t ulPin, uint32_t freq_data);
uint32_t drv_pwm_get_freq(uint32_t ulPin);
uint32_t drv_pwm_get_period(uint32_t ulPin);

void drv_pwm_setup(uint32_t ulPin);
void drv_pwm_release(uint32_t ulPin);

void drv_pwm_set_duty(uint32_t ulPin, uint32_t res, uint32_t ulDuty );
uint32_t drv_pwm_get_pulse(uint32_t ulPin);
uint8_t drv_pwm_get_init(uint32_t ulPin);





#ifdef __cplusplus
}
#endif


#endif
