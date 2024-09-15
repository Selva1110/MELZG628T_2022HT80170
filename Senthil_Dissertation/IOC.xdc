
set_property IOSTANDARD LVCMOS33 [get_ports {spi_rtl_0_ss_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_0_io0_io]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_0_io1_io]
set_property IOSTANDARD LVCMOS33 [get_ports spi_rtl_0_sck_io]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rtl_0_ctsn]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rtl_0_rtsn]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rtl_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_rtl_0_txd]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_1_tri_o[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_1_tri_o[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_rtl_0_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports clk_100MHz]
set_property PACKAGE_PIN D13 [get_ports clk_100MHz]
set_property PACKAGE_PIN T9 [get_ports {gpio_rtl_0_tri_io[0]}]
set_property PACKAGE_PIN P6 [get_ports {gpio_rtl_1_tri_o[1]}]
set_property PACKAGE_PIN R7 [get_ports {gpio_rtl_1_tri_o[0]}]
set_property PACKAGE_PIN R12 [get_ports uart_rtl_0_ctsn]
set_property PACKAGE_PIN P11 [get_ports uart_rtl_0_rtsn]
set_property PACKAGE_PIN P10 [get_ports uart_rtl_0_rxd]
set_property PACKAGE_PIN T12 [get_ports uart_rtl_0_txd]

set_property PACKAGE_PIN T5 [get_ports spi_rtl_0_io1_io]
set_property PACKAGE_PIN T8 [get_ports spi_rtl_0_io0_io]
set_property PACKAGE_PIN P8 [get_ports {spi_rtl_0_ss_io[0]}]
set_property PACKAGE_PIN T10 [get_ports spi_rtl_0_sck_io]
set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets clk]


##set_property PACKAGE_PIN P8 [get_ports {spi_rtl_0_ss_io[0]}]        ##GPIO_2
##set_property PACKAGE_PIN T5 [get_ports spi_rtl_0_io1_io]            ##GPIO_4  DO
##set_property PACKAGE_PIN T8 [get_ports spi_rtl_0_io0_io]            ##GPIO_3  DI
##set_property PACKAGE_PIN T10 [get_ports spi_rtl_0_sck_io]           ##GPIO_1

