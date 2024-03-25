/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
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

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xuartlite.h"
#include "xspi.h"
#include "xintc.h"

#define GPIO_EXAMPLE_DEVICE_ID  XPAR_AXI_GPIO_0_DEVICE_ID
#define UART_DEVICE_ID			XPAR_UARTLITE_0_DEVICE_ID
#define INTC_DEVICE_ID		  	XPAR_INTC_0_DEVICE_ID
#define SPI_DEVICE_ID			XPAR_SPI_0_DEVICE_ID
#define LED_MAX_BLINK			0x10	/* Number of times the LED Blinks */
#define LED_DELAY				10		/*LED Blink Delay*/
#define Output_Pin 				1  		/*LED button*/
#define TEST_BUFFER_SIZE        30		/*Buffer Max Size*/



XGpio Gpio;								/* The driver instance for GPIO Device. */
XUartLite UartLite;						/*The driver instance for UART Device. */
XIntc InterruptController;				/*The driver instance for InterruptController Device. */
XSpi  SpiInstance;	 					/* The instance of the SPI device */
int Status;

/*
 * The following buffers are used in this example to send and receive data
 * with the UartLite.
 */
u8 SendBuffer[] = {0x55,0xAA, 0x55};
u8 ReceiveBuffer[TEST_BUFFER_SIZE];

/*
 * The following counters are used to determine when the entire buffer has
 * been sent and received.
 */
static volatile int TotalReceivedCount;
static volatile int TotalSentCount;/*
 * The following variables are shared between non-interrupt processing and
 * interrupt processing such that they must be global.
 */
volatile int TransferInProgress;

volatile static int InterruptProcessed = FALSE;
static int GpioOutput_app(void)
{
	u32 Data;
	volatile int Delay;
	u32 LedLoop;

	/*
	 * Set the direction for the pin to be output and
	 * Enable the Output enable for the LED Pin.
	 */
	XGpio_SetDataDirection(&Gpio, Output_Pin, 0);

	/* Set the GPIO output to be low. */
	XGpio_DiscreteWrite(&Gpio, Output_Pin, 0x0);


	for (LedLoop = 0; LedLoop < LED_MAX_BLINK; LedLoop ++) {


		/* Wait a small amount of time so the LED is visible. */
		for (Delay = 0; Delay < LED_DELAY; Delay++);


		/* Set the GPIO Output to High. */
		XGpio_DiscreteWrite(&Gpio, Output_Pin, 0x1);

		/*
		 * Read the state of the data and verify. If the data
		 * read back is not the same as the data written then
		 * return FAILURE.
		 */
		Data = XGpio_DiscreteRead(&Gpio, Output_Pin);
		if (Data != 1 ) {
			return XST_FAILURE;
		}

		/* Wait a small amount of time so the LED is visible. */
		for (Delay = 0; Delay < LED_DELAY; Delay++);



		/* Clear the GPIO Output. */
		XGpio_DiscreteWrite(&Gpio, Output_Pin, 0x0);

		/*
		 * Read the state of the data and verify. If the data
		 * read back is not the same as the data written then
		 * return FAILURE.
		 */
		Data = XGpio_DiscreteRead(&Gpio, Output_Pin);
		if (Data != 0) {
			return XST_FAILURE;
		}
	}
	return XST_SUCCESS;
}


static int UartLiteIntr_app(void)
{
	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(&UartLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
		 * Send the buffer using the UartLite.
	*/

	XUartLite_Send(&UartLite, SendBuffer, sizeof(SendBuffer));


	/*
		 * Start receiving data before sending it since there is a loopback.
	*/
	XUartLite_Recv(&UartLite, ReceiveBuffer, TEST_BUFFER_SIZE);


	/*
	 * Connect the UartLite to the interrupt subsystem such that interrupts can
	 * occur. This function is application specific.
	 */

	while ((TotalReceivedCount == 1)) {
	}



	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function does a minimal test on the Spi device and driver as a
* design example. The purpose of this function is to illustrate how to use
* the XSpi component using the interrupt mode.
*
* This function sends data and expects to receive the same data.
*
*
* @param	IntcInstancePtr is a pointer to the instance of the INTC
* 		component.
* @param	SpiInstancePtr is a pointer to the instance of Spi component.
* @param	SpiDeviceId is the Device ID of the Spi Device and is the
*		XPAR_<SPI_instance>_DEVICE_ID value from xparameters.h.
* @param	SpiIntrId is the interrupt Id and is typically
*		XPAR_<INTC_instance>_<SPI_instance>_VEC_ID value from
*		xparameters.h .
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note
*
* This function contains an infinite loop such that if interrupts are not
* working it may never return.
*
******************************************************************************/
int SpiOutput_app(XSpi *SpiInstancePtr,
			u16 SpiDeviceId)
{
	int Status;
	u32 Count;
	u8 Test;
	XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XSpi_SelfTest(SpiInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Run loopback test only in case of standard SPI mode.
	 */
	if (SpiInstancePtr->SpiMode != XSP_STANDARD_MODE) {
		return XST_SUCCESS;
	}


	/*
	 * Set the Spi device as a master and in loopback mode.
	 */
	Status = XSpi_SetOptions(SpiInstancePtr, XSP_MASTER_OPTION |
 					XSP_LOOPBACK_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Start the SPI driver so that interrupts and the device are enabled.
	 */
	XSpi_Start(SpiInstancePtr);

	/*
	 * Transmit the data.
	 */
	TransferInProgress = TRUE;
	XSpi_Transfer(SpiInstancePtr, SendBuffer, ReceiveBuffer, sizeof(SendBuffer));

	/*
	 * Wait for the transmission to be complete.
	 */
	while (TransferInProgress);

	return XST_SUCCESS;
}

int main()
{
	init_platform();


	Status = XGpio_Initialize(&Gpio, GPIO_EXAMPLE_DEVICE_ID);
		if (Status != XST_SUCCESS) {
			printf("Gpio Initialization Failed\r\n");
			return XST_FAILURE;
		}
	Status = XSpi_Initialize(&SpiInstance, SPI_DEVICE_ID);
	if (Status != XST_SUCCESS) {
				printf("SPI Initialization Failed\r\n");
				return XST_FAILURE;
		}
    Status = XUartLite_Initialize(&UartLite, UART_DEVICE_ID);
    	if (Status != XST_SUCCESS) {
    		printf("UART Init Failed\r\n");
    		return XST_FAILURE;
    	}
	Status = XIntc_Initialize(&InterruptController, INTC_DEVICE_ID);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
    printf("Hello World\n\r");
    while(1)
    {
    	Status = GpioOutput_app();
		if (Status != XST_SUCCESS) {
			printf("GPIO Polled Mode Example Test Failed \r\n");
		}
		/*
			 * Run the UartLite Interrupt example, specify the Device ID that is
			 * generated in xparameters.h.
			 */
		Status = UartLiteIntr_app();
		if (Status != XST_SUCCESS) {
			xil_printf("Uartlite interrupt Example Failed\r\n");
			//return XST_FAILURE;
		}
    }
    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}
