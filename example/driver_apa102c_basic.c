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
 * @file      driver_apa102c_basic.c
 * @brief     driver apa102c basic source file
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

#include "driver_apa102c_basic.h"

static apa102c_handle_t gs_handle;        /**< apa102c handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t apa102c_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_APA102C_LINK_INIT(&gs_handle, apa102c_handle_t);
    DRIVER_APA102C_LINK_SPI_INIT(&gs_handle, apa102c_interface_spi_init);
    DRIVER_APA102C_LINK_SPI_DEINIT(&gs_handle, apa102c_interface_spi_deinit);
    DRIVER_APA102C_LINK_SPI_WRITE_COMMAND(&gs_handle, apa102c_interface_spi_write_cmd);
    DRIVER_APA102C_LINK_DELAY_MS(&gs_handle, apa102c_interface_delay_ms);
    DRIVER_APA102C_LINK_DEBUG_PRINT(&gs_handle, apa102c_interface_debug_print);
    
    /* apa102c initialization */
    res = apa102c_init(&gs_handle);
    if (res != 0)
    {
        apa102c_interface_debug_print("apa102c: init failed.\n");
       
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write 
 * @param[in] *color pointer to a color buffer
 * @param[in] len color length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t apa102c_basic_write(uint32_t *color, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    if (apa102c_write(&gs_handle, color, len, temp, temp_len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example write off
 * @param[in] len color length
 * @param[in] *temp pointer to a temp buffer
 * @param[in] temp_len temp buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t apa102c_basic_write_off(uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    if (apa102c_write_off(&gs_handle, len, temp, temp_len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t apa102c_basic_deinit(void)
{
    if (apa102c_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
