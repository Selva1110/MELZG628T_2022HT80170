# Clock and Reset IO Constraints
set_property PACKAGE_PIN AA30 [get_ports clk]
set_property PACKAGE_PIN W30 [get_ports reset]
set_property IOSTANDARD LVCMOS18 [get_ports clk]
set_property IOSTANDARD LVCMOS18 [get_ports reset]

# Peripheral IO Constraints

# GPIO
set_property IOSTANDARD LVCMOS18 [get_ports {gpio_rtl_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS18 [get_ports {gpio_rtl_0_tri_io[0]}]
set_property PACKAGE_PIN AA5 [get_ports {gpio_rtl_0_tri_io[1]}]
set_property PACKAGE_PIN AC27 [get_ports {gpio_rtl_0_tri_io[0]}]


##SPI
set_property IOSTANDARD LVCMOS18 [get_ports {spi_rtl_0_ss_io[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports spi_rtl_0_io0_io]
set_property IOSTANDARD LVCMOS18 [get_ports spi_rtl_0_io1_io]
set_property IOSTANDARD LVCMOS18 [get_ports spi_rtl_0_sck_io]
set_property PACKAGE_PIN G32 [get_ports {spi_rtl_0_ss_io[0]}]
set_property PACKAGE_PIN T24 [get_ports spi_rtl_0_io0_io]
set_property PACKAGE_PIN R26 [get_ports spi_rtl_0_io1_io]
set_property PACKAGE_PIN H29 [get_ports spi_rtl_0_sck_io]

##UART
set_property IOSTANDARD LVCMOS18 [get_ports uart_rtl_0_rxd]
set_property IOSTANDARD LVCMOS18 [get_ports uart_rtl_0_txd]
set_property PACKAGE_PIN J28 [get_ports uart_rtl_0_rxd]
set_property PACKAGE_PIN K26 [get_ports uart_rtl_0_txd]

##PWM
set_property IOSTANDARD LVCMOS18 [get_ports pwm0_0]
set_property PACKAGE_PIN K28 [get_ports pwm0_0]

##Debug
set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets clk_1]


####        RTL Signal                          FMC-Num     BRK-BRD     FPGA BRD
####	[get_ports {spi_rtl_0_ss_io[0]}]       ##PF2 247       G24	    FPGA G32
####	[get_ports spi_rtl_0_io0_io]           ##PF2 257       G25	    FPGA T24
####	[get_ports spi_rtl_0_io1_io]           ##PF2 258       H25	    FPGA R26
####	[get_ports spi_rtl_0_sck_io]           ##PF2 268       H26	    FPGA H29
####	[get_ports uart_rtl_0_rxd]			   ##PF2 288       H28	    FPGA J28
####	[get_ports uart_rtl_0_txd]			   ##PF2 298       H29	    FPGA K26
####	[get_ports pwm0_0]					   ##PF2 287       G28	    FPGA K28
####	[get_ports {gpio_rtl_0_tri_io[1]}]	   ##PF2 234       D23	    FPGA AC27
####	[get_ports {gpio_rtl_0_tri_io[0]}]	   ##PF2 244       D24	    FPGA AA5 	//Doubt
