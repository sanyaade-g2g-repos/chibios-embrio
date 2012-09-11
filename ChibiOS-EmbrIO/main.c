/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

#include "ch.h"
#include "hal.h"
#include "board.h"
#include "test.h"
#include "chprintf.h"
#include "embrio.h"
#include "Embryo.h"



/* test embrio program
extern unsigned char _binary_test01_eaf_start;
extern unsigned char _binary_test01_eaf_end;
extern unsigned char _binary_test01_eaf_size;
*/

/*
extern unsigned char _binary_hello1_eaf_start;
extern unsigned char _binary_hello1_eaf_end;
extern unsigned char _binary_hello1_eaf_size;

extern unsigned char _binary_hello2_eaf_start;
extern unsigned char _binary_hello2_eaf_end;
extern unsigned char _binary_hello2_eaf_size;
*/

// VM0 code
extern unsigned char _binary_vm0_eaf_start;
extern unsigned char _binary_vm0_eaf_end;
extern unsigned char _binary_vm0_eaf_size;

// VM1 code
extern unsigned char _binary_vm1_eaf_start;
extern unsigned char _binary_vm1_eaf_end;
extern unsigned char _binary_vm1_eaf_size;


/*
// TEST
extern unsigned char _binary_blob_bin_start;
extern unsigned char _binary_blob_bin_end;
extern unsigned char _binary_blob_bin_size;
*/

/*
 * Green LED blinker thread, times are in milliseconds.
 */
/*
static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palClearPad(GPIOC, GPIOC_LED_STATUS1);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, GPIOC_LED_STATUS1);
    chThdSleepMilliseconds(500);
  }
  return (msg_t)1;
}
*/

/*===========================================================================*/
/* GPT                                                                       */
/*===========================================================================*/

/*
 * GPT1
 */

static void gpt1cb(GPTDriver *gptp) {
	(void)gptp;

	EmbrioVM *vm_tmp;
	Embryo_Function ef;

	vm_tmp = vm_man->vm_first;

	while(vm_tmp != NULL){

		ef = embryo_program_function_find(vm_tmp->ep, "@eventGPT1");

		if(ef != EMBRYO_FUNCTION_NONE){
			// chprintf((BaseChannel*)&SD3,"%d.",i);
			chMsgSend(vm_tmp->tp,(msg_t)ef);
		}else{
			// chprintf((BaseChannel*)&SD3,"%dk",i);
		}
		vm_tmp = vm_tmp->vm_next;
		// i++;
	}
}

static const GPTConfig gpt1cfg = {
  1000,     /* 1kHz timer clock.*/
  gpt1cb    /* Timer callback.*/
};

/*
 * GPT2
 */

static void gpt2cb(GPTDriver *gptp) {
	(void)gptp;

	EmbrioVM *vm_tmp;
	Embryo_Function ef;

	vm_tmp = vm_man->vm_first;

	while(vm_tmp != NULL){


		ef = embryo_program_function_find(vm_tmp->ep, "@eventGPT2");

		if(ef != EMBRYO_FUNCTION_NONE){
			chMsgSend(vm_tmp->tp,(msg_t)ef);
			// chprintf((BaseChannel*)&SD3,":");
		}else{
			// chprintf((BaseChannel*)&SD3,"y");
		}

		vm_tmp = vm_tmp->vm_next;
	}
}

static const GPTConfig gpt2cfg = {
  1000,     /* 1kHz timer clock.*/
  gpt2cb    /* Timer callback.*/
};

/*
 * GPT3
 */

static void gpt3cb(GPTDriver *gptp) {
	(void)gptp;

	EmbrioVM *vm_tmp;
	Embryo_Function ef;

	vm_tmp = vm_man->vm_first;

	while(vm_tmp != NULL){


		ef = embryo_program_function_find(vm_tmp->ep, "@eventGPT3");

		if(ef != EMBRYO_FUNCTION_NONE){
			chMsgSend(vm_tmp->tp,(msg_t)ef);
			// chprintf((BaseChannel*)&SD3,";");
		}else{
			// chprintf((BaseChannel*)&SD3,"z");
		}

		vm_tmp = vm_tmp->vm_next;
	}
}

static const GPTConfig gpt3cfg = {
  1000,     /* 1kHz timer clock.*/
  gpt3cb    /* Timer callback.*/
};


/*===========================================================================*/
/* EXTI                                                                      */
/*===========================================================================*/

static void ext0cb(EXTDriver *extp, expchannel_t channel) {

	(void)extp;
	(void)channel;

	// chprintf((BaseChannel*)&SD3,":");
	EmbrioVM *vm_tmp;
	Embryo_Function ef;

	vm_tmp = vm_man->vm_first;

	while(vm_tmp != NULL){


		ef = embryo_program_function_find(vm_tmp->ep, "@eventEXTI2");

		if(ef != EMBRYO_FUNCTION_NONE){
			chMsgSend(vm_tmp->tp,(msg_t)ef);
			// chprintf((BaseChannel*)&SD3,";");
		}else{
			// chprintf((BaseChannel*)&SD3,"z");
		}

		vm_tmp = vm_tmp->vm_next;
	}
}

static void ext1cb(EXTDriver  *extp, expchannel_t channel) {

	(void)extp;
	(void)channel;

	// chprintf((BaseChannel*)&SD3,".");

	// chprintf((BaseChannel*)&SD3,":");
	EmbrioVM *vm_tmp;
	Embryo_Function ef;

	vm_tmp = vm_man->vm_first;

	while(vm_tmp != NULL){


		ef = embryo_program_function_find(vm_tmp->ep, "@eventEXTI1");

		if(ef != EMBRYO_FUNCTION_NONE){
			chMsgSend(vm_tmp->tp,(msg_t)ef);
			// chprintf((BaseChannel*)&SD3,";");
		}else{
			// chprintf((BaseChannel*)&SD3,"z");
		}

		vm_tmp = vm_tmp->vm_next;
	}
}

static const EXTConfig ext1cfg = {
	{
		{EXT_CH_MODE_RISING_EDGE, ext0cb},	/* EXT line  0 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  1 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  2 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  3 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  4 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  5 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  6 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  7 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  8 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line  9 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 10 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 11 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 12 */
		{EXT_CH_MODE_RISING_EDGE, ext1cb},	/* EXT line 13 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 14 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 15 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 16 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 17 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 18 */
		{EXT_CH_MODE_DISABLED, NULL},		/* EXT line 19 */
	},
	EXT_MODE_EXTI(EXT_MODE_GPIOA,			/*  0 */
		0,									/*  1 */
		0,									/*  2 */
		0,									/*  3 */
		0,									/*  4 */
		0,									/*  5 */
		0,									/*  6 */
		0,									/*  7 */
		0,									/*  8 */
		0,									/*  9 */
		0,									/* 10 */
		0,									/* 11 */
		0,									/* 12 */
		EXT_MODE_GPIOC,						/* 13  */
		0,									/* 14 */
		0)									/* 15 */
};

/*********************************************************************************
 *
 * SPI & ADC
 *
 *********************************************************************************/

static void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n);

// static void spicb(SPIDriver *spip);

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   2

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      4

/*
 * ADC samples buffer.
 */
static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 4 samples of 2 channels, SW triggered.
 * Channels:    IN11   (48 cycles sample time)
 *              Sensor (192 cycles sample time)
 */
static const ADCConversionGroup adcgrpcfg = {
		FALSE,
		ADC_GRP1_NUM_CHANNELS,
		adccb,
		NULL,
		/* HW dependent part.*/
		0,
		ADC_CR2_SWSTART,
		ADC_SMPR1_SMP_AN11(ADC_SAMPLE_55P5) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_55P5),
		0,
		ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
		0,
		ADC_SQR3_SQ2_N(ADC_CHANNEL_IN11) | ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)
};

/*
 * ADC end conversion callback.
 * The PWM channels are reprogrammed using the latest ADC samples.
 * The latest samples are transmitted into a single SPI transaction.
 */
void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

	(void) buffer; (void) n;
	/* Note, only in the ADC_COMPLETE state because the ADC driver fires an
     intermediate callback when the buffer is half full.*/
	if (adcp->state == ADC_COMPLETE) {
		adcsample_t avg_ch1, avg_ch2;

		/* Calculates the average values from the ADC samples.*/
		avg_ch1 = (samples[0] + samples[2] + samples[4] + samples[6]) / 4;
		avg_ch2 = (samples[1] + samples[3] + samples[5] + samples[7]) / 4;

		chprintf((BaseChannel*)&SD3,"%d %d\r\n",avg_ch1,avg_ch2);

/*		chSysLockFromIsr();


		// SPI slave selection and transmission start.
		spiSelectI(&SPID2);
		spiStartSendI(&SPID2, ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH, samples);

		chSysUnlockFromIsr();*/
	}
}


#ifdef _TEST_



/*
 * SPI1 configuration structure.
 * Speed 5.25MHz, CPHA=1, CPOL=1, 8bits frames, MSb transmitted first.
 * The slave select line is the pin GPIOE_CS_SPI on the port GPIOE.
 */
static const SPIConfig spi1cfg = {
		NULL,
		/* HW dependent part.*/
		GPIOE,
		GPIOE_CS_SPI,
		SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_CPOL | SPI_CR1_CPHA
};

/*
 * SPI2 configuration structure.
 * Speed 21MHz, CPHA=0, CPOL=0, 16bits frames, MSb transmitted first.
 * The slave select line is the pin 12 on the port GPIOA.
 */
static const SPIConfig spi2cfg = {
		spicb,
		/* HW dependent part.*/
		GPIOB,
		12,
		SPI_CR1_DFF
};



/*
 * SPI end transfer callback.
 */
static void spicb(SPIDriver *spip) {

	/* On transfer end just releases the slave select line.*/
	chSysLockFromIsr();
	spiUnselectI(spip);
	chSysUnlockFromIsr();
}



/*
 * Application entry point.
 */
int main(void) {

	/*
	 * Activates the serial driver 2 using the driver default configuration.
	 * PA2(TX) and PA3(RX) are routed to USART2.
	 */
	sdStart(&SD2, NULL);
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));


	/*
	 * Initializes the SPI driver 2. The SPI2 signals are routed as follow:
	 * PB12 - NSS.
	 * PB13 - SCK.
	 * PB14 - MISO.
	 * PB15 - MOSI.
	 */
	spiStart(&SPID2, &spi2cfg);
	palSetPad(GPIOB, 12);
	palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL |
			PAL_STM32_OSPEED_HIGHEST);           /* NSS.     */
	palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5) |
			PAL_STM32_OSPEED_HIGHEST);           /* SCK.     */
	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5));              /* MISO.    */
	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5) |
			PAL_STM32_OSPEED_HIGHEST);           /* MOSI.    */

	/*
	 * Initializes the ADC driver 1 and enable the thermal sensor.
	 * The pin PC0 on the port GPIOC is programmed as analog input.
	 */
	adcStart(&ADCD1, NULL);
	adcSTM32EnableTSVREFE();
	palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG);


	/*
	 * Initializes the SPI driver 1 in order to access the MEMS. The signals
	 * are initialized in the board file.
	 * Several LIS302DL registers are then initialized.
	 */
	spiStart(&SPID1, &spi1cfg);
	lis302dlWriteRegister(&SPID1, LIS302DL_CTRL_REG1, 0x43);
	lis302dlWriteRegister(&SPID1, LIS302DL_CTRL_REG2, 0x00);
	lis302dlWriteRegister(&SPID1, LIS302DL_CTRL_REG3, 0x00);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state, when the button is
	 * pressed the test procedure is launched with output on the serial
	 * driver 2.
	 */
	while (TRUE) {
		int8_t x, y, z;

		x = (int8_t)lis302dlReadRegister(&SPID1, LIS302DL_OUTX);
		y = (int8_t)lis302dlReadRegister(&SPID1, LIS302DL_OUTY);
		z = (int8_t)lis302dlReadRegister(&SPID1, LIS302DL_OUTZ);
		chprintf((BaseChannel *)&SD2, "%d, %d, %d\r\n", x, y, z);
		chThdSleepMilliseconds(500);
	}
}

#endif

/*
 * Application entry point.
 */
int main(void) {

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	/*
	 * Creates the blinker thread.
	 */
	// chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);


	embryo_init();
	embrioInit();

	/*
	 * Activates the serial driver 3 using the driver default configuration.
	 */
	sdStart(&SD3, NULL);


	// switch off the leds
	palClearPad(GPIOC, GREEN_LED);
	palClearPad(GPIOC, YELLOW_LED);

	if(vm_man == NULL){
		chprintf((BaseChannel*)&SD3,"\n\n\rVMM NO\r\n");
	}else{
		vm_man->vm_count = 0;
		vm_man->vm_first = NULL;
		vm_man->state = EMBRIOVMM_STOP;
		// chprintf((BaseChannel*)&SD3,"\n\n\rVMM OK\r\n");
	}

	vm[0] = (EmbrioVM*)chPoolAlloc(&EVM_mp);

	if(vm[0] == NULL){
		chprintf((BaseChannel*)&SD3,"VM 0 NO\r\n");
	}else{
		// insert VM in linked list of VMs
		embrioVMMinsert(vm_man, vm[0]);
		// chprintf((BaseChannel*)&SD3,"VM 0 OK\r\n");
		vm[0]->ep = embryo_program_load_local(&_binary_vm0_eaf_start, &_binary_vm0_eaf_end, &_binary_vm0_eaf_size, (BaseChannel*)&SD3, TRUE);

		if(vm[0]->ep == NULL){
			chprintf((BaseChannel*)&SD3,"VM 0 ep NO\r\n");
			vm[0]->state = EMBRIOVM_FAIL;
		}else{
			// chprintf((BaseChannel*)&SD3,"VM 0 ep OK\r\n");
			vm[0]->hook = NULL;
			vm[0]->tp = vmStart(vm[0], NORMALPRIO, "VM0");
		}
	}

	vm[1] = (EmbrioVM*)chPoolAlloc(&EVM_mp);

	if(vm[1] == NULL){
		chprintf((BaseChannel*)&SD3,"VM 1 NO\r\n");
	}else{
		// insert VM in linked list of VMs
		embrioVMMinsert(vm_man, vm[1]);
		// chprintf((BaseChannel*)&SD3,"VM 1 OK\r\n");
		vm[1]->ep = embryo_program_load_local(&_binary_vm1_eaf_start, &_binary_vm1_eaf_end, &_binary_vm1_eaf_size, (BaseChannel*)&SD3, TRUE);

		if(vm[1]->ep == NULL){
			chprintf((BaseChannel*)&SD3,"VM 1 ep NO\r\n");
			vm[1]->state = EMBRIOVM_FAIL;
		}else{
			// chprintf((BaseChannel*)&SD3,"VM 1 ep OK\r\n");
			vm[1]->hook = NULL;
			vm[1]->tp = vmStart(vm[1], NORMALPRIO, "VM1");
		}
	}

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state.
	 */

	// sdWrite(&SD3,"pippo\n",strlen("pippo\n"));

	chRegSetThreadName("VM Manager");

	gptStart(&GPTD1, &gpt1cfg);
	gptStart(&GPTD2, &gpt2cfg);
	gptStart(&GPTD3, &gpt3cfg);

	gptStartContinuous(&GPTD1, 20001);
	gptStartContinuous(&GPTD2, 12001);
	gptStartContinuous(&GPTD3, 23001);

	extStart(&EXTD1, &ext1cfg);

	 extChannelEnable(&EXTD1, 0);
	 extChannelEnable(&EXTD1, 13);

	 /*
	  * Initializes the ADC driver 1 and enable the thermal sensor.
	  * The pin PC0 on the port GPIOC is programmed as analog input.
	  */
	 adcStart(&ADCD1, NULL);
	 palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG);

	 while (TRUE) {
		if (palReadPad(GPIOC, GPIOC_SWITCH_TAMPER) == 0){
			// TestThread(&SD3);
			palTogglePad(GPIOC, GREEN_LED);
		}
		chThdSleepMilliseconds(500);
	}
}
