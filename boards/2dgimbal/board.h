/*
 * Copyright (c) 2026 Efold & Moyl (still-sight / 2dgimbal)
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * 2dgimbal main board pin map (from hardware/2dgimbal schematic v1.2):
 *   YAW  (upper): motor U11 <- U4(DRV8313) <- IN1_1/2/3 = PWM0 P4/P3/P2
 *                 encoder J2 (upper JST-GH) = I2C3 (SDA3=PB12, SCL3=PB13)
 *   PITCH(lower): motor U1  <- U5(DRV8313) <- IN2_1/2/3 = PWM0 P7/P6/P5
 *                 encoder J1 (lower JST-GH) = I2C2 (SDA2=PB09, SCL2=PB08)
 *   DRV8313 EN1/2/3 hard-wired enabled; nRESET/nSLEEP/nFAULT on GPIO.
 *   MCU native USB0 (D+/D-) on con-cpu1 debug port -> CherryUSB CDC link.
 *   UART0 (PA01 RXD / PA00 TXD) <-> CH340N (backup console).
 */
#ifndef _2DGIMBAL_BOARD_H
#define _2DGIMBAL_BOARD_H

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_clock_drv.h"

/* ---------------- clock ---------------- */
#define BOARD_CPU_FREQ (480000000UL)
#define BOARD_NAME "2dgimbal"
#define BOARD_SHOW_CLOCK (0U)
#define BOARD_SHOW_BANNER (0U)

/* ---------------- PWM (both motors on PWM0, 20 kHz) ---------------- */
#define BOARD_PWM                     HPM_PWM0
#define BOARD_PWM_CLK_NAME            clock_mot0
/* yaw: phase1/2/3 = PWM0.P4/P3/P2 ; pitch: phase1/2/3 = PWM0.P7/P6/P5 */
#define BOARD_YAW_PWM_CH   { 4U, 3U, 2U }
#define BOARD_YAW_PWM_CMP  { 0U, 2U, 4U }
#define BOARD_PITCH_PWM_CH  { 7U, 6U, 5U }
#define BOARD_PITCH_PWM_CMP { 6U, 8U, 10U }
#define BOARD_PWM_FIRST_CH  (2U)
#define BOARD_PWM_LAST_CH   (7U)

/* ---------------- encoders (AS5600 on sub boards) ---------------- */
/* yaw = J2 upper connector = I2C3 ; pitch = J1 lower connector = I2C2 */
#define BOARD_I2C_YAW                 HPM_I2C3
#define BOARD_I2C_YAW_CLK_NAME        clock_i2c3
#define BOARD_I2C_PITCH               HPM_I2C2
#define BOARD_I2C_PITCH_CLK_NAME      clock_i2c2
#define AS5600_I2C_ADDRESS            (0x36U)

/* ---------------- DRV8313 control GPIOs ---------------- */
#define BOARD_DRV_GPIO_CTRL           HPM_GPIO0
/* yaw = U4 (upper), pitch = U5 (lower); active level: rst/slp HIGH = run */
#define BOARD_YAW_SLP_PORT            GPIO_DI_GPIOA
#define BOARD_YAW_SLP_PIN             (9U)   /* PA09 */
#define BOARD_PITCH_SLP_PORT          GPIO_DI_GPIOA
#define BOARD_PITCH_SLP_PIN           (10U)  /* PA10 */
#define BOARD_YAW_RST_PORT            GPIO_DI_GPIOB
#define BOARD_YAW_RST_PIN             (14U)  /* PB14 */
#define BOARD_PITCH_RST_PORT          GPIO_DI_GPIOB
#define BOARD_PITCH_RST_PIN           (15U)  /* PB15 */
#define BOARD_YAW_FAULT_PORT          GPIO_DI_GPIOB
#define BOARD_YAW_FAULT_PIN           (10U)  /* PB10, nFAULT open-drain out */
#define BOARD_PITCH_FAULT_PORT        GPIO_DI_GPIOB
#define BOARD_PITCH_FAULT_PIN         (11U)  /* PB11 */

/* ---------------- USB CDC link (con-cpu1) ---------------- */
#define BOARD_USB                     HPM_USB0
#define BOARD_USB_CLK_NAME            clock_usb0

/* ---------------- UART0 console (CH340N, backup link) ---------------- */
#define BOARD_APP_UART_BASE           HPM_UART0
#define BOARD_APP_UART_IRQ            IRQn_UART0
#define BOARD_APP_UART_BAUDRATE       (115200UL)
#define BOARD_APP_UART_CLK_NAME       clock_uart0

/* ---------------- tick timer ---------------- */
#define BOARD_CALLBACK_TIMER          (HPM_GPTMR3)
#define BOARD_CALLBACK_TIMER_CH       (1U)
#define BOARD_CALLBACK_TIMER_IRQ      IRQn_GPTMR3
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr3)

/* ---------------- on-board QSPI NOR (eeprom emulation) ---------------- */
#define BOARD_APP_XPI_NOR_XPI_BASE    (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR (0xfcf90002U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0 (0x00000006U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1 (0x00001000U)

#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif

void board_init(void);
void board_init_clock(void);
void board_init_usb_dp_dm_pins(void);
void board_delay_us(uint32_t us);
void board_delay_ms(uint32_t ms);
void board_timer_create(uint32_t ms, board_timer_cb cb);

#endif /* _2DGIMBAL_BOARD_H */
