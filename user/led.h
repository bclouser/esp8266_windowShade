#ifndef _LED_H_
#define _LED_H_

#include "ets_sys.h"
#include "gpio.h"
#include "pwm.h"


/*Definition of GPIO PIN params, for GPIO initialization*/
#define LED_0_OUT_IO_MUX     PERIPHS_IO_MUX_GPIO2_U
#define LED_0_OUT_IO_NUM     2
#define LED_0_OUT_IO_FUNC    FUNC_GPIO2

#define LED_1_OUT_IO_MUX     PERIPHS_IO_MUX_MTDO_U
#define LED_1_OUT_IO_NUM     15
#define LED_1_OUT_IO_FUNC    FUNC_GPIO15

#define LED_2_OUT_IO_MUX     PERIPHS_IO_MUX_MTCK_U
#define LED_2_OUT_IO_NUM     13
#define LED_2_OUT_IO_FUNC    FUNC_GPIO13

#define LED_3_OUT_IO_MUX     PERIPHS_IO_MUX_MTDI_U
#define LED_3_OUT_IO_NUM     12
#define LED_3_OUT_IO_FUNC    FUNC_GPIO12

typedef enum {
	e_ledNum1 = 0,
	e_ledNum2,
	e_ledNum3,
	e_ledNum4,
	e_numLeds
} LedNumEnum;

void initLeds();
void turnLedsOff();
bool setLed(LedNumEnum ledNum, bool on);
void  blinkLed(LedNumEnum led, int delay);

#endif