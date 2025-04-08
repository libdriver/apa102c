/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_apa102c.h
 * @brief     driver apa102c header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-04-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/04/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_APA102C_H
#define DRIVER_APA102C_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup apa102c_driver apa102c driver function
 * @brief    apa102c driver modules
 * @{
 */

/**
 * @addtogroup apa102c_base_driver
 * @{
 */

/**
 * @brief apa102c handle structure definition
 */
typedef struct apa102c_handle_s
{
    uint8_t (*spi_init)(void);                                   /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                 /**< point to a spi_deinit function address */
    uint8_t (*spi_write_cmd)(uint8_t *buf, uint16_t len);        /**< point to a spi_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                               /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);             /**< point to a debug_print function address */
    uint8_t inited;                                              /**< inited flag */
} apa102c_handle_t;

/**
 * @brief apa102c information structure definition
 */
typedef struct apa102c_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} apa102c_info_t;

/**
 * @}
 */

/**
 * @defgroup apa102c_link_driver apa102c link driver function
 * @brief    apa102c link driver modules
 * @ingroup  apa102c_driver
 * @{
 */

/**
 * @brief     initialize apa102c_handle_t structure
 * @param[in] HANDLE pointer to an apa102c handle structure
 * @param[in] STRUCTURE apa102c_handle_t
 * @note      none
 */
#define DRIVER_APA102C_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to an apa102c handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_APA102C_LINK_SPI_INIT(HANDLE, FUC)                (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to an apa102c handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_APA102C_LINK_SPI_DEINIT(HANDLE, FUC)              (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write_cmd function
 * @param[in] HANDLE pointer to an apa102c handle structure
 * @param[in] FUC pointer to a spi_write_cmd function address
 * @note      none
 */
#define DRIVER_APA102C_LINK_SPI_WRITE_COMMAND(HANDLE, FUC)       (HANDLE)->spi_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an apa102c handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_APA102C_LINK_DELAY_MS(HANDLE, FUC)                (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an apa102c handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_APA102C_LINK_DEBUG_PRINT(HANDLE, FUC)             (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup apa102c_base_driver apa102c base driver function
 * @brief    apa102c base driver modules
 * @ingroup  apa102c_driver
 * @{
 */

/**
 * @brief     make color
 * @param[in] RED red color
 * @param[in] GREEN green color
 * @param[in] BLUE blue color
 * @param[in] BRIGHTNESS brightness
 * @note      0<= RED <= 255
 *            0<= GREEN <= 255
 *            0<= BLUE <= 255
 *            0<= BRIGHTNESS <= 31
 */
#define APA102C_COLOR(RED, GREEN, BLUE, BRIGHTNESS)    ((uint32_t)(0xE | ((BRIGHTNESS) & 0x1F)) << 24) | \
                                                       ((uint32_t)((BLUE) & 0xFF) << 16) | \
                                                       ((uint32_t)((GREEN) & 0xFF) << 8) | \
                                                       ((uint32_t)((RED) & 0xFF) << 0)

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an apa102c info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t apa102c_info(apa102c_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an apa102c handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t apa102c_init(apa102c_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an apa102c handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apa102c_deinit(apa102c_handle_t *handle);

/**
 * @brief     write color frame
 * @param[in] *handle pointer to an apa102c handle structure
 * @param[in] *color pointer to a color buffer
 * @param[in] len color length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 color is null
 *            - 5 temp is null
 *            - 6 temp buffer is too small
 * @note      none
 */
uint8_t apa102c_write(apa102c_handle_t *handle, uint32_t *color, uint32_t len, uint8_t *temp, uint32_t temp_len);

/**
 * @brief     write off frame
 * @param[in] *handle pointer to an apa102c handle structure
 * @param[in] len color length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 temp is null
 *            - 5 temp buffer is too small
 * @note      none
 */
uint8_t apa102c_write_off(apa102c_handle_t *handle, uint32_t len, uint8_t *temp, uint32_t temp_len);

/**
 * @}
 */

/**
 * @defgroup apa102c_extern_driver apa102c extern driver function
 * @brief    apa102c extern driver modules
 * @ingroup  apa102c_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to an apa102c handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t apa102c_set_reg(apa102c_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
