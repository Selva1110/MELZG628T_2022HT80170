/************************** Constant Definitions *****************************/
#define SPI_0_BASEADDR 0x44A00000U
#define SPI_0_HIGHADDR 0x44A01FFFU


#define SPI_Reg_Write(BaseAddress, RegOffset, RegisterValue)	\
	(volatile int *)((BaseAddress##_BASEADDR) + (XSP_##RegOffset##_OFFSET) = RegisterValue;

#define SPI_Reg_Read(BaseAddress, RegOffset)	\
	(int)(*(volatile int *)((BaseAddress##_BASEADDR) + (XSP_##RegOffset##_OFFSET))

#define SPI_Clear_Bit(BaseAddress, RegOffset, BitMask, BitValue)	\
	(volatile int *)((BaseAddress##_BASEADDR) + (XSP_##RegOffset##_OFFSET) = (int)(*(volatile int *)((BaseAddress##_BASEADDR) + (XSP_##RegOffset##_OFFSET)) & (~(XSP_##BitMask##_MASK));

#define SPI_Set_Bit(BaseAddress, RegOffset, BitMask, BitValue)	\
	(volatile int *)((BaseAddress##_BASEADDR) + (XSP_##RegOffset##_OFFSET) = (int)(*(volatile int *)((BaseAddress##_BASEADDR) + (XSP_##RegOffset##_OFFSET)) | ((XSP_##BitMask##_MASK));




/**
 * XSPI register offsets
 */
/** @name Register Map
 *
 * Register offsets for the XSpi device.
 * @{
 */
#define XSP_DGIER_OFFSET	0x1C	/**< Global Intr Enable Reg */
#define XSP_IISR_OFFSET		0x20	/**< Interrupt status Reg */
#define XSP_IIER_OFFSET		0x28	/**< Interrupt Enable Reg */
#define XSP_SRR_OFFSET	 	0x40	/**< Software Reset register */
#define XSP_CR_OFFSET		0x60	/**< Control register */
#define XSP_SR_OFFSET		0x64	/**< Status Register */
#define XSP_DTR_OFFSET		0x68	/**< Data transmit */
#define XSP_DRR_OFFSET		0x6C	/**< Data receive */
#define XSP_SSR_OFFSET		0x70	/**< 32-bit slave select */
#define XSP_TFO_OFFSET		0x74	/**< Tx FIFO occupancy */
#define XSP_RFO_OFFSET		0x78	/**< Rx FIFO occupancy */

/* @} */


/**
 * @name Global Interrupt Enable Register (GIER) mask(s)
 * @{
 */
#define XSP_GINTR_ENABLE_MASK	0x80000000	/**< Global interrupt enable */

/* @} */


/** @name SPI Device Interrupt Status/Enable Registers
 *
 * <b> Interrupt Status Register (IPISR) </b>
 *
 * This register holds the interrupt status flags for the Spi device.
 *
 * <b> Interrupt Enable Register (IPIER) </b>
 *
 * This register is used to enable interrupt sources for the Spi device.
 * Writing a '1' to a bit in this register enables the corresponding Interrupt.
 * Writing a '0' to a bit in this register disables the corresponding Interrupt.
 *
 * ISR/IER registers have the same bit definitions and are only defined once.
 * @{
 */
#define XSP_INTR_MODE_FAULT_MASK	0x00000001 /**< Mode fault error */
#define XSP_INTR_SLAVE_MODE_FAULT_MASK	0x00000002 /**< Selected as slave while
						     *  disabled */
#define XSP_INTR_TX_EMPTY_MASK		0x00000004 /**< DTR/TxFIFO is empty */
#define XSP_INTR_TX_UNDERRUN_MASK	0x00000008 /**< DTR/TxFIFO underrun */
#define XSP_INTR_RX_FULL_MASK		0x00000010 /**< DRR/RxFIFO is full */
#define XSP_INTR_RX_OVERRUN_MASK	0x00000020 /**< DRR/RxFIFO overrun */
#define XSP_INTR_TX_HALF_EMPTY_MASK	0x00000040 /**< TxFIFO is half empty */
#define XSP_INTR_SLAVE_MODE_MASK	0x00000080 /**< Slave select mode */
#define XSP_INTR_RX_NOT_EMPTY_MASK	0x00000100 /**< RxFIFO not empty */

/**
 * The following bits are available only in axi_qspi Interrupt Status and
 * Interrupt Enable registers.
 */
#define XSP_INTR_CPOL_CPHA_ERR_MASK	0x00000200 /**< CPOL/CPHA error */
#define XSP_INTR_SLAVE_MODE_ERR_MASK	0x00000400 /**< Slave mode error */
#define XSP_INTR_MSB_ERR_MASK		0x00000800 /**< MSB Error */
#define XSP_INTR_LOOP_BACK_ERR_MASK	0x00001000 /**< Loop back error */
#define XSP_INTR_CMD_ERR_MASK		0x00002000 /**< 'Invalid cmd' error */

/**
 * Mask for all the interrupts in the IP Interrupt Registers.
 */
#define XSP_INTR_ALL		(XSP_INTR_MODE_FAULT_MASK | \
				 XSP_INTR_SLAVE_MODE_FAULT_MASK | \
				 XSP_INTR_TX_EMPTY_MASK | \
				 XSP_INTR_TX_UNDERRUN_MASK | \
				 XSP_INTR_RX_FULL_MASK | \
				 XSP_INTR_TX_HALF_EMPTY_MASK | \
				 XSP_INTR_RX_OVERRUN_MASK | \
				 XSP_INTR_SLAVE_MODE_MASK | \
				 XSP_INTR_RX_NOT_EMPTY_MASK | \
				 XSP_INTR_CMD_ERR_MASK | \
				 XSP_INTR_LOOP_BACK_ERR_MASK | \
				 XSP_INTR_MSB_ERR_MASK | \
				 XSP_INTR_SLAVE_MODE_ERR_MASK | \
				 XSP_INTR_CPOL_CPHA_ERR_MASK)

/**
 * The interrupts we want at startup. We add the TX_EMPTY interrupt in later
 * when we're getting ready to transfer data.  The others we don't care
 * about for now.
 */
#define XSP_INTR_DFT_MASK	(XSP_INTR_MODE_FAULT_MASK |	\
				 XSP_INTR_TX_UNDERRUN_MASK |	\
				 XSP_INTR_RX_OVERRUN_MASK |	\
				 XSP_INTR_SLAVE_MODE_FAULT_MASK | \
				 XSP_INTR_CMD_ERR_MASK)
/* @} */

/**
 * SPI Software Reset Register (SRR) mask.
 */
#define XSP_SRR_RESET_MASK		0x0000000A


/** @name SPI Control Register (CR) masks
 *
 * @{
 */
#define XSP_CR_LOOPBACK_MASK	   0x00000001 /**< Local loopback mode */
#define XSP_CR_ENABLE_MASK	   0x00000002 /**< System enable */
#define XSP_CR_MASTER_MODE_MASK	   0x00000004 /**< Enable master mode */
#define XSP_CR_CLK_POLARITY_MASK   0x00000008 /**< Clock polarity high
								or low */
#define XSP_CR_CLK_PHASE_MASK	   0x00000010 /**< Clock phase 0 or 1 */
#define XSP_CR_TXFIFO_RESET_MASK   0x00000020 /**< Reset transmit FIFO */
#define XSP_CR_RXFIFO_RESET_MASK   0x00000040 /**< Reset receive FIFO */
#define XSP_CR_MANUAL_SS_MASK	   0x00000080 /**< Manual slave select
								assert */
#define XSP_CR_TRANS_INHIBIT_MASK  0x00000100 /**< Master transaction
								inhibit */

/**
 * LSB/MSB first data format select. The default data format is MSB first.
 * The LSB first data format is not available in all versions of the Xilinx Spi
 * Device whereas the MSB first data format is supported by all the versions of
 * the Xilinx Spi Devices. Please check the HW specification to see if this
 * feature is supported or not.
 */
#define XSP_CR_LSB_MSB_FIRST_MASK	0x00000200

/* @} */

/** @name SPI Control Register (CR) masks for XIP Mode
 *
 * @{
 */
#define XSP_CR_XIP_CLK_PHASE_MASK	0x00000001 /**< Clock phase 0 or 1 */
#define XSP_CR_XIP_CLK_POLARITY_MASK	0x00000002 /**< Clock polarity
								high or low */

/* @} */




/** @name Status Register (SR) masks
 *
 * @{
 */
#define XSP_SR_RX_EMPTY_MASK	   0x00000001 /**< Receive Reg/FIFO is empty */
#define XSP_SR_RX_FULL_MASK	   0x00000002 /**< Receive Reg/FIFO is full */
#define XSP_SR_TX_EMPTY_MASK	   0x00000004 /**< Transmit Reg/FIFO is
								empty */
#define XSP_SR_TX_FULL_MASK	   0x00000008 /**< Transmit Reg/FIFO is full */
#define XSP_SR_MODE_FAULT_MASK	   0x00000010 /**< Mode fault error */
#define XSP_SR_SLAVE_MODE_MASK	   0x00000020 /**< Slave mode select */

/*
 * The following bits are available only in axi_qspi Status register.
 */
#define XSP_SR_CPOL_CPHA_ERR_MASK  0x00000040 /**< CPOL/CPHA error */
#define XSP_SR_SLAVE_MODE_ERR_MASK 0x00000080 /**< Slave mode error */
#define XSP_SR_MSB_ERR_MASK	   0x00000100 /**< MSB Error */
#define XSP_SR_LOOP_BACK_ERR_MASK  0x00000200 /**< Loop back error */
#define XSP_SR_CMD_ERR_MASK	   0x00000400 /**< 'Invalid cmd' error */

/* @} */

/** @name Status Register (SR) masks for XIP Mode
 *
 * @{
 */
#define XSP_SR_XIP_RX_EMPTY_MASK	0x00000001 /**< Receive Reg/FIFO
								is empty */
#define XSP_SR_XIP_RX_FULL_MASK		0x00000002 /**< Receive Reg/FIFO
								is full */
#define XSP_SR_XIP_MASTER_MODF_MASK	0x00000004 /**< Receive Reg/FIFO
								is full */
#define XSP_SR_XIP_CPHPL_ERROR_MASK	0x00000008 /**< Clock Phase,Clock
							 Polarity Error */
#define XSP_SR_XIP_AXI_ERROR_MASK	0x00000010 /**< AXI Transaction
								Error */

/* @} */


/** @name SPI Transmit FIFO Occupancy (TFO) mask
 *
 * @{
 */
/* The binary value plus one yields the occupancy.*/
#define XSP_TFO_MASK		0x0000001F

/* @} */

/** @name SPI Receive FIFO Occupancy (RFO) mask
 *
 * @{
 */
/* The binary value plus one yields the occupancy.*/
#define XSP_RFO_MASK		0x0000001F

/* @} */

/** @name Data Width Definitions
 *
 * @{
 */
#define XSP_DATAWIDTH_BYTE	 8  /**< Tx/Rx Reg is Byte Wide */
#define XSP_DATAWIDTH_HALF_WORD	16  /**< Tx/Rx Reg is Half Word (16 bit)
						Wide */
#define XSP_DATAWIDTH_WORD	32  /**< Tx/Rx Reg is Word (32 bit)  Wide */

/* @} */

/** @name SPI Modes
 *
 * The following constants define the modes in which qxi_qspi operates.
 *
 * @{
 */
#define XSP_STANDARD_MODE	0
#define XSP_DUAL_MODE		1
#define XSP_QUAD_MODE		2

 /*@}*/
/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

