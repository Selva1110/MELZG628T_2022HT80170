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
#include "xintc.h"		/* Interrupt controller device driver */
#include "xspi.h"		/* SPI device driver */
#include "spi_flash_drv.h"

/************************** Variable Definitions *****************************/

/*
 * The instances to support the device drivers are global such that they
 * are initialized to zero each time the program runs. They could be local
 * but should at least be static so they are zeroed.
 */
static XIntc InterruptController;
static XSpi Spi;
int wait_timeout =0;
/*
 * The following variables are shared between non-interrupt processing and
 * interrupt processing such that they must be global.
 */
volatile static int TransferInProgress;

/*
 * The following variable tracks any errors that occur during interrupt
 * processing.
 */
static int ErrorCount;

/*
 * Buffers used during read and write transactions.
 */
static u8 ReadBuffer[PAGE_SIZE + READ_WRITE_EXTRA_BYTES + 4];
static u8 WriteBuffer[PAGE_SIZE + READ_WRITE_EXTRA_BYTES];
u8 lb_data = 0x5A;
/*
 * Byte offset value written to Flash. This needs to be redefined for writing
 * different patterns of data to the Flash device.
 */
static u8 TestByte = 0x20;
#if 0
int spi_lb_test(void)
{
	int Status;
	int rx_data;
		XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */

		/*
		 * Initialize the SPI driver so that it's ready to use,
		 * specify the device ID that is generated in xparameters.h.
		 */
		ConfigPtr = XSpi_LookupConfig(SPI_DEVICE_ID);
		if (ConfigPtr == NULL) {
			return XST_DEVICE_NOT_FOUND;
		}

		Status = XSpi_CfgInitialize(&Spi, ConfigPtr,
					  ConfigPtr->BaseAddress);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Connect the SPI driver to the interrupt subsystem such that
		 * interrupts can occur. This function is application specific.
		 */
		Status = SetupInterruptSystem(&Spi);
		if(Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Setup the handler for the SPI that will be called from the interrupt
		 * context when an SPI status occurs, specify a pointer to the SPI
		 * driver instance as the callback reference so the handler is able to
		 * access the instance data.
		 */
		XSpi_SetStatusHandler(&Spi, &Spi, (XSpi_StatusHandler)SpiHandler);

		/*
		 * Set the SPI device as a master and in manual slave select mode such
		 * that the slave select signal does not toggle for every byte of a
		 * transfer, this must be done before the slave select is set.
		 */
		Status = XSpi_SetOptions(&Spi, XSP_MASTER_OPTION | XSP_LOOPBACK_OPTION |
					 XSP_MANUAL_SSELECT_OPTION);
		if(Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		TransferInProgress =TRUE;
		/*
		 * Start the SPI driver so that interrupts and the device are enabled.
		 */
		XSpi_Start(&Spi);

		XSpi_Transfer(&Spi, &lb_data, &rx_data, sizeof(lb_data));
		while(TransferInProgress);
		if(lb_data != rx_data) {
			print_log("SPI Loopback test Failed\r\n");
			return XST_FAILURE;
		}
		print_log("Successfully ran SPI Loopback test\r\n");
		return XST_SUCCESS;
}

#endif

#if 0
int spi_flash_test(void)
{
	int Status;
	u32 Index;
	u32 Address;
	XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */

	/*
	 * Initialize the SPI driver so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h.
	 */
	ConfigPtr = XSpi_LookupConfig(SPI_DEVICE_ID);
	if (ConfigPtr == NULL) {
		return XST_DEVICE_NOT_FOUND;
	}

	Status = XSpi_CfgInitialize(&Spi, ConfigPtr,
				  ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the SPI driver to the interrupt subsystem such that
	 * interrupts can occur. This function is application specific.
	 *
	Status = SetupInterruptSystem(&Spi);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handler for the SPI that will be called from the interrupt
	 * context when an SPI status occurs, specify a pointer to the SPI
	 * driver instance as the callback reference so the handler is able to
	 * access the instance data.
	 *
	XSpi_SetStatusHandler(&Spi, &Spi, (XSpi_StatusHandler)SpiHandler);

	/*
	 * Set the SPI device as a master and in manual slave select mode such
	 * that the slave select signal does not toggle for every byte of a
	 * transfer, this must be done before the slave select is set.
	 */
	Status = XSpi_SetOptions(&Spi, XSP_MASTER_OPTION );
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Select the quad flash device on the SPI bus, so that it can be
	 * read and written using the SPI bus.
	 */
	Status = XSpi_SetSlaveSelect(&Spi, SPI_SELECT);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the SPI driver so that interrupts and the device are enabled.
	 */
	XSpi_Start(&Spi);

	/*
	 * Specify the address in the Quad Serial Flash for the Erase/Write/Read
	 * operations.
	 */
	Address = FLASH_TEST_ADDRESS;

	/*
	 * Perform the Write Enable operation.
	 */
	Status = SpiFlashWriteEnable(&Spi);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform the Sector Erase operation.
	 */
	Status = SpiFlashSectorErase(&Spi, Address);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the Quad Enable (QE) bit in the flash device, so that Quad
	 * operations can be performed on the flash.

	Status = SpiFlashQuadEnable(&Spi);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform the Write Enable operation.
	 */
	Status = SpiFlashWriteEnable(&Spi);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Write the data to the Page using Page Program command.
	 */
	Status = SpiFlashWrite(&Spi, Address, PAGE_SIZE, COMMAND_PAGE_PROGRAM);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Clear the read Buffer.
	 */
	for(Index = 0; Index < PAGE_SIZE + READ_WRITE_EXTRA_BYTES; Index++) {
		ReadBuffer[Index] = 0x0;
	}

	/*
	 * Read the data from the Page using Random Read command.
	 */
	Status = SpiFlashRead(&Spi, Address, PAGE_SIZE, COMMAND_RANDOM_READ);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Compare the data read against the data written.
	 */
	for(Index = 0; Index < PAGE_SIZE; Index++) {
		if(ReadBuffer[Index + READ_WRITE_EXTRA_BYTES] !=
					(u8)(Index + TestByte)) {
			return XST_FAILURE;
		}
	}

	/*
	 * Clear the Read Buffer.
	 */
	for(Index = 0; Index < PAGE_SIZE + READ_WRITE_EXTRA_BYTES +
	    DUAL_READ_DUMMY_BYTES; Index++) {
		ReadBuffer[Index] = 0x0;
	}

	/*
	 * Read the data from the Page using Dual Output Fast Read command.
	 */
	Status = SpiFlashRead(&Spi, Address, PAGE_SIZE, COMMAND_DUAL_READ);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Compare the data read against the data written.
	 */
	for(Index = 0; Index < PAGE_SIZE; Index++) {
		if(ReadBuffer[Index + READ_WRITE_EXTRA_BYTES +
				DUAL_READ_DUMMY_BYTES] !=
					(u8)(Index + TestByte)) {
			return XST_FAILURE;
		}
	}

	/*
	 * Enable High Performance Mode so that data can be read from the flash
	 * using DIO and QIO read commands.
	 */
	Status = SpiFlashEnableHPM(&Spi);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Clear the read Buffer.
	 */
	for(Index = 0; Index < PAGE_SIZE + READ_WRITE_EXTRA_BYTES +
	    DUAL_IO_READ_DUMMY_BYTES; Index++) {
		ReadBuffer[Index] = 0x0;
	}

	/*
	 * Read the data from the Page using Dual IO Fast Read command.
	 */
	Status = SpiFlashRead(&Spi, Address, PAGE_SIZE, COMMAND_DUAL_IO_READ);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Compare the data read against the data written.
	 */
	for(Index = 0; Index < PAGE_SIZE; Index++) {
		if(ReadBuffer[Index + READ_WRITE_EXTRA_BYTES +
				DUAL_IO_READ_DUMMY_BYTES] !=
					(u8)(Index + TestByte)) {
			return XST_FAILURE;
		}
	}

	/*
	 * Clear the read Buffer.
	 */
	for(Index = 0; Index < PAGE_SIZE + READ_WRITE_EXTRA_BYTES +
	    QUAD_IO_READ_DUMMY_BYTES; Index++) {
		ReadBuffer[Index] = 0x0;
	}

	print_log("Successfully ran SPI winbond Dual Mode flash \r\n");
	return XST_SUCCESS;
}
#endif
int spi_flash_test(void)
{

	int Status;
		u32 Index;
		u32 Address;
		XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */

		/*
		 * Initialize the SPI driver so that it's ready to use,
		 * specify the device ID that is generated in xparameters.h.
		 */
		ConfigPtr = XSpi_LookupConfig(SPI_DEVICE_ID);
		if (ConfigPtr == NULL) {
			return XST_DEVICE_NOT_FOUND;
		}

		Status = XSpi_CfgInitialize(&Spi, ConfigPtr,
					  ConfigPtr->BaseAddress);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Set the SPI device as a master and in manual slave select mode such
		 * that the slave select signal does not toggle for every byte of a
		 * transfer, this must be done before the slave select is set.
		 */
		Status = XSpi_SetOptions(&Spi, XSP_MASTER_OPTION );
		if(Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Select the quad flash device on the SPI bus, so that it can be
		 * read and written using the SPI bus.
		 */
		Status = XSpi_SetSlaveSelect(&Spi, SPI_SELECT);
		if(Status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		/*
		 * Start the SPI driver so that interrupts and the device are enabled.
		 */
		XSpi_Start(&Spi);

		/*
		 * Specify the address in the Quad Serial Flash for the Erase/Write/Read
		 * operations.
		 */
		Address = FLASH_TEST_ADDRESS;

		WriteBuffer[BYTE1] = COMMAND_WRITE_ENABLE;

		Status = XSpi_Transfer(&Spi, WriteBuffer, NULL,
						WRITE_ENABLE_BYTES);

		/*WriteBuffer[BYTE1] = COMMAND_SECTOR_ERASE;
		WriteBuffer[BYTE2] = (u8) (Address >> 16);
		WriteBuffer[BYTE3] = (u8) (Address >> 8);
		WriteBuffer[BYTE4] = (u8) (Address);

		Status = XSpi_Transfer(&Spi, WriteBuffer , NULL,
				SECTOR_ERASE_BYTES);

		while(TransferInProgress)
		{
			if(wait_timeout == 0x200)
			{
				TransferInProgress = FALSE;
				break;
			}
			else
				wait_timeout++;
		}

		Status = XSpi_Transfer(&Spi, WriteBuffer, NULL,
								WRITE_ENABLE_BYTES);*/

		WriteBuffer[BYTE1] = COMMAND_PAGE_PROGRAM;

		/*
		 * Fill in the TEST data that is to be written into the Winbond Serial
		 * Flash device.
		 */
		for(Index = 1; Index < PAGE_SIZE + READ_WRITE_EXTRA_BYTES; Index++) {
			WriteBuffer[Index] = (u8)((Index - 4) + TestByte);
		}

		Status = XSpi_Transfer(&Spi, WriteBuffer, NULL,
						(PAGE_SIZE + READ_WRITE_EXTRA_BYTES));

		for(Index = 0; Index < PAGE_SIZE + READ_WRITE_EXTRA_BYTES; Index++) {
				ReadBuffer[Index] = 0x0;
			}

		/*
		 * Prepare the WriteBuffer.
		 */
		WriteBuffer[BYTE1] = COMMAND_RANDOM_READ;

		Status = XSpi_Transfer( &Spi, WriteBuffer, ReadBuffer,
						(PAGE_SIZE + 2 + READ_WRITE_EXTRA_BYTES));
		Status = XST_SUCCESS;
		for(Index = 0; Index < PAGE_SIZE; Index++) {
				if(ReadBuffer[Index + READ_WRITE_EXTRA_BYTES +
						DUAL_READ_DUMMY_BYTES] !=
							(u8)(Index + TestByte)) {
					Status = XST_FAILURE;
				}
		}
		return Status;
}
int main()
{
	int Status = XST_SUCCESS;
	Status = init_platform();
	if(Status != XST_SUCCESS) {
			print_log(" Platform Init Failed \r\n");
		}
	Status = spi_flash_test();
	if(Status != XST_SUCCESS) {
		print_log(" SPI Loopback Test Failed \r\n");
	}

    print_log("Hello World\n\r");
    while(1)
    {
    	print_log("Platform is Alive \r\n");
    }
    print_log("Successfully ran Test Platform application");
    cleanup_platform();
    return 0;
}



