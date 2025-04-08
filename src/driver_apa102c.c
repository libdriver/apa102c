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
 * @file      driver_apa102c.c
 * @brief     driver apa102c source file
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

#include "driver_apa102c.h"

/**
 * @brief chip register definition
 */
#define CHIP_NAME                 "Shiji Lighting APA102C"        /**< chip name */
#define MANUFACTURER_NAME         "Shiji Lighting"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        5.0f                            /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                            /**< chip max supply voltage */
#define MAX_CURRENT               200.0f                          /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                          /**< chip min operating temperature */
#define TEMPERATURE_MAX           70.0f                           /**< chip max operating temperature */
#define DRIVER_VERSION            1000                            /**< driver version */

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
uint8_t apa102c_init(apa102c_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->spi_init == NULL)                                        /* check spi_init */
    {
        handle->debug_print("apa102c: spi_init is null.\n");             /* spi_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_deinit == NULL)                                      /* check spi_deinit */
    {
        handle->debug_print("apa102c: spi_deinit is null.\n");           /* spi_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->spi_write_cmd == NULL)                                   /* check spi_write_cmd */
    {
        handle->debug_print("apa102c: spi_write_cmd is null.\n");        /* spi_write_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("apa102c: delay_ms is null.\n");             /* delay_ms is null */
       
        return 3;                                                        /* return error */
    }
    
    if (handle->spi_init() != 0)                                         /* spi init */
    {
        handle->debug_print("apa102c: spi init failed.\n");              /* spi init failed */
       
        return 1;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t apa102c_write(apa102c_handle_t *handle, uint32_t *color, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    uint32_t i;
    uint16_t byte_size;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (color == NULL)                                                      /* check color */
    {
        handle->debug_print("apa102c: color is null.\n");                   /* color is null */
       
        return 4;                                                           /* return error */
    }
    if (temp == NULL)                                                       /* check temp */
    {
        handle->debug_print("apa102c: temp is null.\n");                    /* temp is null */
       
        return 5;                                                           /* return error */
    }
    
    byte_size = len * 4 + 8;                                                /* get byte size */
    if (byte_size > temp_len)                                               /* check byte size */
    {
        handle->debug_print("apa102c: temp buffer is too small.\n");        /* temp buffer is too small */
       
        return 6;                                                           /* return error */
    }
    temp[0] = 0x00;                                                         /* start frame */
    temp[1] = 0x00;                                                         /* start frame */
    temp[2] = 0x00;                                                         /* start frame */
    temp[3] = 0x00;                                                         /* start frame */
    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        temp[4 + i * 4 + 0] = (color[i] >> 24) & 0xFF;                      /* set brightness */
        temp[4 + i * 4 + 1] = (color[i] >> 16) & 0xFF;                      /* set blue */
        temp[4 + i * 4 + 2] = (color[i] >> 8) & 0xFF;                       /* set green */
        temp[4 + i * 4 + 3] = (color[i] >> 0) & 0xFF;                       /* set red */
    }
    temp[4 + len * 4 + 0] = 0xFF;                                           /* end frame */
    temp[4 + len * 4 + 1] = 0xFF;                                           /* end frame */
    temp[4 + len * 4 + 2] = 0xFF;                                           /* end frame */
    temp[4 + len * 4 + 3] = 0xFF;                                           /* end frame */
    
    if (handle->spi_write_cmd(temp, (uint16_t)byte_size) != 0)              /* write command */
    {
        handle->debug_print("apa102c: write command failed.\n");            /* write command failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t apa102c_write_off(apa102c_handle_t *handle, uint32_t len, uint8_t *temp, uint32_t temp_len)
{
    uint32_t i;
    uint16_t byte_size;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (temp == NULL)                                                       /* check temp */
    {
        handle->debug_print("apa102c: temp is null.\n");                    /* temp is null */
       
        return 4;                                                           /* return error */
    }
    
    byte_size = len * 4 + 8;                                                /* get byte size */
    if (byte_size > temp_len)                                               /* check byte size */
    {
        handle->debug_print("apa102c: temp buffer is too small.\n");        /* temp buffer is too small */
       
        return 5;                                                           /* return error */
    }
    temp[0] = 0x00;                                                         /* start frame */
    temp[1] = 0x00;                                                         /* start frame */
    temp[2] = 0x00;                                                         /* start frame */
    temp[3] = 0x00;                                                         /* start frame */
    for (i = 0; i < len; i++)                                               /* set the color frame */
    {
        temp[4 + i * 4 + 0] = 0xE0;                                         /* set brightness */
        temp[4 + i * 4 + 1] = 0x00;                                         /* set blue */
        temp[4 + i * 4 + 2] = 0x00;                                         /* set green */
        temp[4 + i * 4 + 3] = 0x00;                                         /* set red */
    }
    temp[4 + len * 4 + 0] = 0xFF;                                           /* end frame */
    temp[4 + len * 4 + 1] = 0xFF;                                           /* end frame */
    temp[4 + len * 4 + 2] = 0xFF;                                           /* end frame */
    temp[4 + len * 4 + 3] = 0xFF;                                           /* end frame */
    
    if (handle->spi_write_cmd(temp, (uint16_t)byte_size) != 0)              /* write command */
    {
        handle->debug_print("apa102c: write command failed.\n");            /* write command failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t apa102c_deinit(apa102c_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = handle->spi_deinit();                                      /* spi deinit */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("apa102c: spi deinit failed.\n");        /* spi deinit failed */
       
        return 1;                                                    /* return error */
    }
    handle->inited = 0;                                              /* flag closed */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t apa102c_set_reg(apa102c_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    return handle->spi_write_cmd(buf, len);        /* write to reg */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an apa102c info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t apa102c_info(apa102c_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(apa102c_info_t));                        /* initialize apa102c info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
