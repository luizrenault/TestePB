/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **                STMicroelectronics STM32F4xx Standard Peripherals Library
 **
 **  Distribution: The file is distributed "as is", without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. This file may only be built (assembled or compiled and linked)
 **  using the Atollic TrueSTUDIO(R) product. The use of this file together
 **  with other tools than Atollic TrueSTUDIO(R) is not permitted.
 **
 *****************************************************************************
 */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "grSim_Commands.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */


bool decodifica_pacote(uint8_t *buffer, size_t size, grSim_Robot_Command *robotcommand){
	pb_istream_t istream = pb_istream_from_buffer(buffer, size);
	bool status=pb_decode(&istream, grSim_Robot_Command_fields, robotcommand);
	return status;
}

uint8_t this_robot_id=0;

void set_speeds(float vel_x, float vel_y, float vel_theta){

}

int main(void){
	grSim_Robot_Command robotcommand;
	uint8_t buffer[128]={8, 0, 21, 0, 0, 0, 0, 29, 0, 0, 0, 0, 37, 0, 0, 128, 63, 45, 0, 0, 0, 64, 53, 0, 0, 64, 64, 56, 0, 64, 0 , 0};
	int i = 0;

	grSim_Robot_Command gr=grSim_Robot_Command_init_zero;

	if(decodifica_pacote(buffer, 31, &gr)  && gr.id==this_robot_id){
		set_speeds(gr.velnormal, gr.veltangent, gr.velangular);
	}




	/* Initialize LEDs */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	/* Turn on LEDs */
	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);

	/* Infinite loop */
	while (1)
	{
		i++;
	}
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	/* TODO, implement your code here */
	return -1;
}
