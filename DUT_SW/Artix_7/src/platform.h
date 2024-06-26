/******************************************************************************
*
* Copyright (C) 2008 - 2014 Xilinx, Inc.  All rights reserved.
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

#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#include "platform_config.h"
#include "xtmrctr.h"
#include "xintc.h"
#include "xgpio.h"
#include "xuartlite.h"


#define GPIO_DEVICE_ID  		XPAR_AXI_GPIO_0_DEVICE_ID
#define INTC_DEVICE_ID		  	XPAR_INTC_0_DEVICE_ID
#define TIMER_DEVICE_ID			XPAR_AXI_TIMER_0_DEVICE_ID
#define UART_DEVICE_ID			XPAR_UARTLITE_0_DEVICE_ID
//#define print_log(x)


#define TMRCTR_INTERRUPT_ID		XPAR_INTC_0_TMRCTR_0_VEC_ID


#define Output_Pin 				1  		/*LED button*/





int init_Tmr();
int init_gpio();
int init_platform();
void cleanup_platform();


static void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber);
#endif
