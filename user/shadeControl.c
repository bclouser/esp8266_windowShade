
#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "gpio.h"
#include "shadeControl.h"


#define BUTTON_SHADE_DOWN_IO_NUM OUTPUT1_IO_NUM
#define BUTTON_SHADE_UP_IO_NUM   OUTPUT2_IO_NUM
#define BUTTON_SHADE_STOP_IO_NUM OUTPUT3_IO_NUM

static os_timer_t onButtonTimeout;
static const int buttonTimeoutMilliseconds = 3 * 1000; // 4 seconds
static const int stopButtonTimeoutMilliseconds = 800; // 500ms
static bool buttonDown = false;


void ICACHE_FLASH_ATTR initShadeControl(void){

	// Tell pin mux to make it a gpio
	PIN_FUNC_SELECT(OUTPUT1_IO_MUX, OUTPUT1_IO_FUNC);
	PIN_FUNC_SELECT(OUTPUT2_IO_MUX, OUTPUT2_IO_FUNC);
	PIN_FUNC_SELECT(OUTPUT3_IO_MUX, OUTPUT3_IO_FUNC);

	// These buttons are active low. Init them to be high
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT1_IO_NUM), 1);
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT2_IO_NUM), 1);
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT3_IO_NUM), 1);
}

static void ICACHE_FLASH_ATTR getOffAllButtons(void){
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT1_IO_NUM), 1);
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT2_IO_NUM), 1);
	GPIO_OUTPUT_SET(GPIO_ID_PIN(OUTPUT3_IO_NUM), 1);
	// Turn off timer
	os_timer_disarm(&onButtonTimeout);
	buttonDown = false;
}

static void ICACHE_FLASH_ATTR shadeTimeoutCallback(void){
	os_printf("Timeout. Getting off all switches now\r\n");
	getOffAllButtons();
}

void startShadeMovingUp(void){
	// Ensure we are completely off other buttons
	getOffAllButtons();

	os_printf("Pressing UP button \r\n");
	GPIO_OUTPUT_SET(GPIO_ID_PIN(BUTTON_SHADE_UP_IO_NUM), 0);
	os_timer_setfn(&onButtonTimeout, (os_timer_func_t *)shadeTimeoutCallback);
	os_timer_arm(&onButtonTimeout, buttonTimeoutMilliseconds, 0);
	buttonDown=true;
}

// Start shade moving without an explicit timeout
void startShadeMovingDown(void){
	// Ensure we are completely off other buttons
	getOffAllButtons();

	os_printf("Pressing DOWN button \r\n");
	GPIO_OUTPUT_SET(GPIO_ID_PIN(BUTTON_SHADE_DOWN_IO_NUM), 0);
	os_timer_setfn(&onButtonTimeout, (os_timer_func_t *)shadeTimeoutCallback);
	os_timer_arm(&onButtonTimeout, buttonTimeoutMilliseconds, 0);
	buttonDown=true;
}

void stopShade(void){
	// Ensure we are completely off other buttons
	getOffAllButtons();

	os_printf("Pressing STOP button \r\n");
	GPIO_OUTPUT_SET(GPIO_ID_PIN(BUTTON_SHADE_STOP_IO_NUM), 0);
	os_timer_setfn(&onButtonTimeout, (os_timer_func_t *)shadeTimeoutCallback);
	os_timer_arm(&onButtonTimeout, buttonTimeoutMilliseconds, 0);
	buttonDown=true;
}


