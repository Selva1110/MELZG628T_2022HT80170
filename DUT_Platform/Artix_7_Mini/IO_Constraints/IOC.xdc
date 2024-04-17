# Clock and Reset IO Constraints
set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports reset]
set_property PACKAGE_PIN D13 [get_ports clk]
set_property PACKAGE_PIN R15 [get_ports reset]

# Peripheral IO Constraints

# GPIO
set_property PACKAGE_PIN R7 [get_ports {gpio_rtl_0_tri_io[1]}]
set_property PACKAGE_PIN P6 [get_ports {gpio_rtl_0_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_0_tri_io[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_0_tri_io[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_0_tri_io[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_0_tri_io[0]}]
set_property PULLDOWN true [get_ports {gpio_rtl_0_tri_io[0]}]

##SPI
set_property PACKAGE_PIN P8 [get_ports {spi_rtl_0_ss_io[0]}]
set_property PACKAGE_PIN T5 [get_ports spi_rtl_0_io1_io]
set_property PACKAGE_PIN R8 [get_ports spi_rtl_0_io0_io]
set_property PACKAGE_PIN T8 [get_ports spi_rtl_0_sck_io]                
set_property IOSTANDARD LVCMOS33 [get_ports {spi_rtl_0_ss_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_0_io0_io]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_0_io1_io]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_0_sck_io]

##UART
set_property PACKAGE_PIN T10 [get_ports uart_rtl_0_txd]
set_property PACKAGE_PIN T9 [get_ports uart_rtl_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rtl_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rtl_0_txd]

##PWM
set_property PACKAGE_PIN T7 [get_ports pwm0_0]
set_property IOSTANDARD LVCMOS33 [get_ports pwm0_0]

##[get_ports {spi_rtl_0_ss_io[0]}]      FPGA_GPIO_2
##[get_ports spi_rtl_0_io0_io]          FPGA_GPIO_5
##[get_ports spi_rtl_0_io1_io]          FPGA_GPIO_4
##[get_ports spi_rtl_0_sck_io]          FPGA_GPIO_3
##uart_rtl_0_txd                        FPGA_GPIO_1
##uart_rtl_0_rxd                        FPGA_GPIO_0





set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets clk_1]
