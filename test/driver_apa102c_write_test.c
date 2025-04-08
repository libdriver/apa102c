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
 * @file      driver_apa102c_write_test.c
 * @brief     driver apa102c write test source file
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

#include "driver_apa102c_write_test.h"
#include <stdlib.h>

static apa102c_handle_t gs_handle;        /**< apa102c handle */
static uint8_t gs_buffer[1024];           /**< inner temp buffer */
static uint32_t gs_rgb[21];               /**< inner rgb buffer */

/**
 * @brief     write test
 * @param[in] cnt number of leds
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t apa102c_write_test(uint32_t cnt, uint32_t times)
{
    uint8_t res;
    uint32_t num;
    uint32_t i, j;
    apa102c_info_t info;
    const uint32_t color[7] = {0xFF0000U, 0xFF7F00U, 0xFFFF00U, 0x00FF00U, 0x00FFFFU, 0x0000FFU, 0x8F00FFU};
    
    /* link interface function */
    DRIVER_APA102C_LINK_INIT(&gs_handle, apa102c_handle_t);
    DRIVER_APA102C_LINK_SPI_INIT(&gs_handle, apa102c_interface_spi_init);
    DRIVER_APA102C_LINK_SPI_DEINIT(&gs_handle, apa102c_interface_spi_deinit);
    DRIVER_APA102C_LINK_SPI_WRITE_COMMAND(&gs_handle, apa102c_interface_spi_write_cmd);
    DRIVER_APA102C_LINK_DELAY_MS(&gs_handle, apa102c_interface_delay_ms);
    DRIVER_APA102C_LINK_DEBUG_PRINT(&gs_handle, apa102c_interface_debug_print);;
    
    /* get information */
    res = apa102c_info(&info);
    if (res != 0)
    {
        apa102c_interface_debug_print("apa102c: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        apa102c_interface_debug_print("apa102c: chip is %s.\n", info.chip_name);
        apa102c_interface_debug_print("apa102c: manufacturer is %s.\n", info.manufacturer_name);
        apa102c_interface_debug_print("apa102c: interface is %s.\n", info.interface);
        apa102c_interface_debug_print("apa102c: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        apa102c_interface_debug_print("apa102c: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        apa102c_interface_debug_print("apa102c: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        apa102c_interface_debug_print("apa102c: max current is %0.2fmA.\n", info.max_current_ma);
        apa102c_interface_debug_print("apa102c: max temperature is %0.1fC.\n", info.temperature_max);
        apa102c_interface_debug_print("apa102c: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* check cnt */
    if (cnt == 0)
    {
        apa102c_interface_debug_print("apa102c: cnt can't be 0.\n");
        
        return 1;
    }
    if (cnt > 21)
    {
        apa102c_interface_debug_print("apa102c: cnt is over 21 and use 21.\n");
    }
    
    /* start write test */
    apa102c_interface_debug_print("apa102c: start write test.\n");
    
    /* apa102c initialization */
    res = apa102c_init(&gs_handle);
    if (res != 0)
    {
        apa102c_interface_debug_print("apa102c: init failed.\n");
       
        return 1;
    }
    
    /* set number */
    num = cnt > 21 ? 21 : cnt;
    
    for (i = 0; i < times; i++)
    {
        for (j = 0; j < num; j++)
        {
            gs_rgb[j] = APA102C_COLOR(color[i % 7] >> 16, color[i % 7] >> 8, color[i % 7] >> 0, 16);
        }
        res = apa102c_write(&gs_handle, (uint32_t *)gs_rgb, num, gs_buffer, 1024);
        if (res != 0)
        {
            apa102c_interface_debug_print("apa102c: write failed.\n");
            (void)apa102c_deinit(&gs_handle);
           
            return 1;
        }
        
        /* delay 1000 ms */
        apa102c_interface_delay_ms(1000);
        
        /* output */
        apa102c_interface_debug_print("apa102c: %d/%d times.\n", i + 1, times);
    }
    
    /* close all leds */
    res = apa102c_write_off(&gs_handle, num, gs_buffer, 1024);
    if (res != 0)
    {
        apa102c_interface_debug_print("apa102c: write failed.\n");
        (void)apa102c_deinit(&gs_handle);
       
        return 1;
    }
    
    /* finish write test */
    apa102c_interface_debug_print("apa102c: finish write test.\n");
    
    /* close the chip */
    (void)apa102c_deinit(&gs_handle);
    
    return 0;
}
