//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (win64) Build 3865809 Sun May  7 15:05:29 MDT 2023
//Date        : Sat Sep 14 20:03:47 2024
//Host        : DESKTOP-RRPQJKB running 64-bit major release  (build 9200)
//Command     : generate_target SPI_Bootloader_wrapper.bd
//Design      : SPI_Bootloader_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module SPI_Bootloader_wrapper
   (clk_100MHz,
    gpio_rtl_0_tri_io,
    gpio_rtl_1_tri_o,
    spi_rtl_0_io0_io,
    spi_rtl_0_io1_io,
    spi_rtl_0_sck_io,
    spi_rtl_0_ss_io,
    uart_rtl_0_ctsn,
    uart_rtl_0_rtsn,
    uart_rtl_0_rxd,
    uart_rtl_0_txd);
  input clk_100MHz;
  inout [0:0]gpio_rtl_0_tri_io;
  output [1:0]gpio_rtl_1_tri_o;
  inout spi_rtl_0_io0_io;
  inout spi_rtl_0_io1_io;
  inout spi_rtl_0_sck_io;
  inout [0:0]spi_rtl_0_ss_io;
  input uart_rtl_0_ctsn;
  output uart_rtl_0_rtsn;
  input uart_rtl_0_rxd;
  output uart_rtl_0_txd;

  wire clk_100MHz;
  wire [0:0]gpio_rtl_0_tri_i_0;
  wire [0:0]gpio_rtl_0_tri_io_0;
  wire [0:0]gpio_rtl_0_tri_o_0;
  wire [0:0]gpio_rtl_0_tri_t_0;
  wire [1:0]gpio_rtl_1_tri_o;
  wire reset_rtl_0;
  wire spi_rtl_0_io0_i;
  wire spi_rtl_0_io0_io;
  wire spi_rtl_0_io0_o;
  wire spi_rtl_0_io0_t;
  wire spi_rtl_0_io1_i;
  wire spi_rtl_0_io1_io;
  wire spi_rtl_0_io1_o;
  wire spi_rtl_0_io1_t;
  wire spi_rtl_0_sck_i;
  wire spi_rtl_0_sck_io;
  wire spi_rtl_0_sck_o;
  wire spi_rtl_0_sck_t;
  wire [0:0]spi_rtl_0_ss_i_0;
  wire [0:0]spi_rtl_0_ss_io_0;
  wire [0:0]spi_rtl_0_ss_o_0;
  wire spi_rtl_0_ss_t;
  wire uart_rtl_0_baudoutn;
  wire uart_rtl_0_ctsn;
  wire uart_rtl_0_dcdn;
  wire uart_rtl_0_ddis;
  wire uart_rtl_0_dsrn;
  wire uart_rtl_0_dtrn;
  wire uart_rtl_0_out1n;
  wire uart_rtl_0_out2n;
  wire uart_rtl_0_ri;
  wire uart_rtl_0_rtsn;
  wire uart_rtl_0_rxd;
  wire uart_rtl_0_rxrdyn;
  wire uart_rtl_0_txd;
  wire uart_rtl_0_txrdyn;

  SPI_Bootloader SPI_Bootloader_i
       (.clk_100MHz(clk_100MHz),
        .gpio_rtl_0_tri_i(gpio_rtl_0_tri_i_0),
        .gpio_rtl_0_tri_o(gpio_rtl_0_tri_o_0),
        .gpio_rtl_0_tri_t(gpio_rtl_0_tri_t_0),
        .gpio_rtl_1_tri_o(gpio_rtl_1_tri_o),
        .reset_rtl_0('b0),
        .spi_rtl_0_io0_i(spi_rtl_0_io0_i),
        .spi_rtl_0_io0_o(spi_rtl_0_io0_o),
        .spi_rtl_0_io0_t(spi_rtl_0_io0_t),
        .spi_rtl_0_io1_i(spi_rtl_0_io1_i),
        .spi_rtl_0_io1_o(spi_rtl_0_io1_o),
        .spi_rtl_0_io1_t(spi_rtl_0_io1_t),
        .spi_rtl_0_sck_i(spi_rtl_0_sck_i),
        .spi_rtl_0_sck_o(spi_rtl_0_sck_o),
        .spi_rtl_0_sck_t(spi_rtl_0_sck_t),
        .spi_rtl_0_ss_i(spi_rtl_0_ss_i_0),
        .spi_rtl_0_ss_o(spi_rtl_0_ss_o_0),
        .spi_rtl_0_ss_t(spi_rtl_0_ss_t),
        .uart_rtl_0_baudoutn(),
        .uart_rtl_0_ctsn(uart_rtl_0_ctsn),
        .uart_rtl_0_dcdn(),
        .uart_rtl_0_ddis(),
        .uart_rtl_0_dsrn(),
        .uart_rtl_0_dtrn(),
        .uart_rtl_0_out1n(),
        .uart_rtl_0_out2n(),
        .uart_rtl_0_ri(),
        .uart_rtl_0_rtsn(uart_rtl_0_rtsn),
        .uart_rtl_0_rxd(uart_rtl_0_rxd),
        .uart_rtl_0_rxrdyn(),
        .uart_rtl_0_txd(uart_rtl_0_txd),
        .uart_rtl_0_txrdyn());
  IOBUF gpio_rtl_0_tri_iobuf_0
       (.I(gpio_rtl_0_tri_o_0),
        .IO(gpio_rtl_0_tri_io[0]),
        .O(gpio_rtl_0_tri_i_0),
        .T(gpio_rtl_0_tri_t_0));
  IOBUF spi_rtl_0_io0_iobuf
       (.I(spi_rtl_0_io0_o),
        .IO(spi_rtl_0_io0_io),
        .O(spi_rtl_0_io0_i),
        .T(spi_rtl_0_io0_t));
  IOBUF spi_rtl_0_io1_iobuf
       (.I(spi_rtl_0_io1_o),
        .IO(spi_rtl_0_io1_io),
        .O(spi_rtl_0_io1_i),
        .T(spi_rtl_0_io1_t));
  IOBUF spi_rtl_0_sck_iobuf
       (.I(spi_rtl_0_sck_o),
        .IO(spi_rtl_0_sck_io),
        .O(spi_rtl_0_sck_i),
        .T(spi_rtl_0_sck_t));
  IOBUF spi_rtl_0_ss_iobuf_0
       (.I(spi_rtl_0_ss_o_0),
        .IO(spi_rtl_0_ss_io[0]),
        .O(spi_rtl_0_ss_i_0),
        .T(spi_rtl_0_ss_t));
endmodule
