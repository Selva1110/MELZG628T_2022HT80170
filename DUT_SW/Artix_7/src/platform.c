/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "platform.h"
#include "platform_config.h"

/*
 * The following constants are used to set the reset value of the timer counter,
 * making this number larger reduces the amount of time this example consumes
 * because it is the value the timer counter is loaded with when it is started
 */
#define RESET_VALUE_CNTR_0	 0xFFFE795F   //0xFFFFFF9B		//0xFFFE795F //0x186A0 for 1KHz     /// 0x5F5E100 for 1 Sec Timer
#define RESET_VALUE_CNTR_1	 0xFFFFFFFF
#define TIMER_CNTR_0	 		0
#define TIMER_CNTR_1	 		1


volatile static XGpio Gpio;								/* The driver instance for GPIO Device. */
volatile static XIntc InterruptController;					/*The driver instance for InterruptController Device. */
volatile static XTmrCtr TimerCounterInst;   				/* The instance of the Timer Counter */
volatile static XUartLite UartLite;						/*The driver instance for UART Device. */

int Status;

void
enable_caches()
{
#ifdef __PPC__
    Xil_ICacheEnableRegion(CACHEABLE_REGION_MASK);
    Xil_DCacheEnableRegion(CACHEABLE_REGION_MASK);
#elif __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_ICACHE
    Xil_ICacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_DCACHE
    Xil_DCacheEnable();
#endif
#endif
}

void
disable_caches()
{
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
    Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
    Xil_ICacheDisable();
#endif
#endif
}


volatile int Timer_Expiry_Count;
/*****************************************************************************/
/**
* This function setups the interrupt system such that interrupts can occur
* for the timer counter. This function is application specific since the actual
* system may or may not have an interrupt controller.  The timer counter could
* be directly connected to a processor without an interrupt controller.  The
* user should modify this function to fit the application.
*
* @param	IntcInstancePtr is a pointer to the Interrupt Controller
*		driver Instance.
* @param	TmrCtrInstancePtr is a pointer to the XTmrCtr driver Instance.
* @param	DeviceId is the XPAR_<TmrCtr_instance>_DEVICE_ID value from
*		xparameters.h.
* @param	IntrId is XPAR_<INTC_instance>_<TmrCtr_instance>_VEC_ID
*		value from xparameters.h.
*
* @return
*		- XST_SUCCESS if the Test is successful
*		- XST_FAILURE if the Test is not successful
*
* @note		This function contains an infinite loop such that if interrupts
*		are not working it may never return.
*
******************************************************************************/
int SetupIntrSystem(XIntc *IntcInstancePtr,
				 XTmrCtr *TmrCtrInstancePtr,
				 u16 DeviceId,
				 u16 IntrId)
{
	 int Status;


	/*
	 * Initialize the interrupt controller driver so that
	 * it's ready to use, specify the device ID that is generated in
	 * xparameters.h
	 */
	Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the
	 * specific interrupt processing for the device
	 */
	Status = XIntc_Connect(IntcInstancePtr, IntrId,
				(XInterruptHandler)XTmrCtr_InterruptHandler,
				(void *)TmrCtrInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specific real mode so that
	 * the timer counter can cause interrupts thru the interrupt controller.
	 */
	Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Enable the interrupt for the timer counter
	 */
	XIntc_Enable(IntcInstancePtr, IntrId);


	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
					(Xil_ExceptionHandler)
					XIntc_InterruptHandler,
					IntcInstancePtr);

	/*
	 * Enable non-critical exceptions.
	 */
	Xil_ExceptionEnable();


	return XST_SUCCESS;
}
void TMR_task1()
{
	u32 Data;
	if(Timer_Expiry_Count % 1000 == 0){
		Data = XGpio_DiscreteRead(&Gpio, Output_Pin);
		Data = (~Data) & Output_Pin;
		XGpio_DiscreteWrite(&Gpio, Output_Pin, Data);
	}
}



void sleep_ms(int delayms)
{
	u32 temp = 0;
	while(delayms < (Timer_Expiry_Count-temp))
	{
		temp++;
	}
}
/*****************************************************************************/
/**
* This function is the handler which performs processing for the timer counter.
* It is called from an interrupt context such that the amount of processing
* performed should be minimized.  It is called when the timer counter expires
* if interrupts are enabled.
*
* This handler provides an example of how to handle timer counter interrupts
* but is application specific.
*
* @param	CallBackRef is a pointer to the callback function
* @param	TmrCtrNumber is the number of the timer to which this
*		handler is associated with.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber)
{

	XTmrCtr *InstancePtr = (XTmrCtr *)CallBackRef;
	/*
	 * Check if the timer counter has expired, checking is not necessary
	 * since that's the reason this function is executed, this just shows
	 * how the callback reference can be used as a pointer to the instance
	 * of the timer counter that expired, increment a shared variable so
	 * the main thread of execution can see the timer expired
	 */
	if (XTmrCtr_IsExpired(InstancePtr, TmrCtrNumber)) {
		Timer_Expiry_Count++;
		TMR_task1();
		XTmrCtr_Reset(&TimerCounterInst, TIMER_CNTR_0);
	}
}


int init_Tmr()
{
	/*
		 * Connect the timer counter to the interrupt subsystem such that
		 * interrupts can occur.  This function is application specific.
		 * In the cascade mode only the interrupt from Timer Zero is valid.
		 */

		/*
		 * Initialize the timer counter so that it's ready to use,
		 * specify the device ID that is generated in xparameters.h
		 */
		Status = XTmrCtr_Initialize(&TimerCounterInst, TIMER_DEVICE_ID);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		Status = SetupIntrSystem(&InterruptController,
						&TimerCounterInst,
						TIMER_DEVICE_ID,
						TMRCTR_INTERRUPT_ID);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Setup the handler for the timer counter that will be called from the
		 * interrupt context when the timer expires, specify a pointer to the
		 * timer counter driver instance as the callback reference so
		 * the handler is able to access the instance data
		 */
		XTmrCtr_SetHandler(&TimerCounterInst, TimerCounterHandler,
							&TimerCounterInst);


		/*
		 * Set a reset value for the timer counter such that it will expire
		 * eariler than letting it roll over from 0, the reset value is loaded
		 * into the timer counter when it is started
		 */
		XTmrCtr_SetResetValue(&TimerCounterInst, TIMER_CNTR_0,
					RESET_VALUE_CNTR_0);
		/*XTmrCtr_SetResetValue(&TimerCounterInst, TIMER_CNTR_1,
					RESET_VALUE_CNTR_1);*/


		/*
		 * Enable the interrupt of the timer counter so interrupts will occur
		 * and use auto reload mode such that the timer counter will reload
		 * itself automatically and continue repeatedly, without this option
		 * it would expire once only and set the Cascade mode.
		 */
		XTmrCtr_SetOptions(&TimerCounterInst, TIMER_CNTR_0,
								XTC_INT_MODE_OPTION |
								XTC_AUTO_RELOAD_OPTION );

		/*
		 * Reset the timer counters such that it's incrementing by default
		 */
		 XTmrCtr_Reset(&TimerCounterInst, TIMER_CNTR_0);
		// XTmrCtr_Reset(&TimerCounterInst, TIMER_CNTR_1);

		/*
		 * Start the timer counter 0 such that it's incrementing by default,
		 * then wait for it to timeout a number of times.
		 */
		XTmrCtr_Start(&TimerCounterInst, TIMER_CNTR_0);
		return XST_SUCCESS;

}

#if 1
void print_log( const char8 *ctrl1, ...)
{
	va_list argp;

	va_start(argp, ctrl1);

	xil_vprintf(ctrl1, argp);

	va_end(argp);
}
#endif

int
init_gpio()
{
		Status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

	/*
		 * Set the direction for the pin to be output and
		 * Enable the Output enable for the LED Pin.
		 */
		XGpio_SetDataDirection(&Gpio, Output_Pin, 0);

		/* Set the GPIO output to be low. */
		XGpio_DiscreteWrite(&Gpio, Output_Pin, 0x1);
		return XST_SUCCESS;
}

int
init_platform()
{
    /*
     * If you want to run this example outside of SDK,
     * uncomment one of the following two lines and also #include "ps7_init.h"
     * or #include "ps7_init.h" at the top, depending on the target.
     * Make sure that the ps7/psu_init.c and ps7/psu_init.h files are included
     * along with this example source files for compilation.
     */
    /* ps7_init();*/
    /* psu_init();*/
    enable_caches();
	Status = init_gpio();
   // init_uart();
	//Status = init_Tmr();
	return Status;
}

#if 1
void
cleanup_platform()
{
    disable_caches();
}
#endif
