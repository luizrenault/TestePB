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

bool robot_commands_encode_callback(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
{
	int i;
	grSim_Robot_Command robotcommand={};

	for(i=1; i<6;i++){
		robotcommand.id=i;
		robotcommand.veltangent=0.0f;
		robotcommand.velnormal=0.0f;
		robotcommand.velangular=0.0f;
		robotcommand.kickspeedx=0.0f;
		robotcommand.kickspeedz=0.0f;
		robotcommand.spinner=false;
		robotcommand.wheelsspeed=false;
		robotcommand.has_wheel1=false;
		robotcommand.has_wheel2=false;
		robotcommand.has_wheel3=false;
		robotcommand.has_wheel4=false;

        /* This encodes the header for the field, based on the constant info
         * from pb_field_t. */
		if (!pb_encode_tag_for_field(stream, field))
			return false;

		/* This encodes the data for the field, based on our FileInfo structure. */
        if (!pb_encode_submessage(stream, grSim_Robot_Command_fields, &robotcommand))
            return false;

	}
    return true;
}


bool robot_commands_decode_callback(pb_istream_t *stream, const pb_field_t *field, void **arg)
{
	grSim_Robot_Command robotcommand={};

	if (!pb_decode(stream, grSim_Robot_Command_fields, &robotcommand))
        return false;

    return true;
}

int main(void){
	uint8_t buffer[128];
	size_t message_length;
	bool status;
	grSim_Commands message=grSim_Commands_init_zero;
	pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
	message.isteamyellow=true;
	message.timestamp=10.0f;
	message.robot_commands.funcs.encode=&robot_commands_encode_callback;
    status = pb_encode(&stream, grSim_Commands_fields, &message);
    message_length = stream.bytes_written;


	pb_istream_t istream = pb_istream_from_buffer(buffer, sizeof(buffer));
	message.robot_commands.funcs.decode=&robot_commands_decode_callback;
    status=pb_decode(&istream, grSim_Commands_fields, &message);

	int i = 0;

  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.  
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /* TODO - Add your application code here */

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
