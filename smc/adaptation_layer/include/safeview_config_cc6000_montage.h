/* $Id: safeview_config_alim3281_smt.h 21 2015-07-17 14:23:07Z Safeview $ */
/* Copyright 2015 SafeView. All rights reserved.
 *
 * safeview_config_Mstar7c02HD_microzen.h
 *
 * This file defines  configuration constants for chipset/manufacturer
 * ALi M3281 Sandmartin.
 *
 * Manufacturer should redefine the constants to match its case.
 *
 * History:
 *     21/06/2016       1.1     Vipin Saxena(Creator)
 *     27/06/13         1.0     Miguel Seisdedos Vega
 * - Moved from safeview_config_adaptation.h
 *
 * This software is  subject to updates, revisions,  and extensions by
 * SafeView. Use of this software  shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and SafeView.
 *
 */

#ifndef _SAFEVIEW_CONFIG_CC6000_MONTAGE_H_
#define _SAFEVIEW_CONFIG_CC6000_MONTAGE_H_

/***************************************************************************
 * Processor endianness
 ***************************************************************************/
#define SAFEVIEW_STB_CHIP_ENDIANNESS                            SAFEVIEW_LITTLE_ENDIAN

/***************************************************************************
 * Maximum number of open descramblers supported by the STB
 ***************************************************************************/
#define SAFEVIEW_MAX_NUM_DESCRAMBLERS                           16

/***************************************************************************
 * Number of demuxes the STB has
 ***************************************************************************/
#define SAFEVIEW_NUM_DEMUXES                                    128

/***************************************************************************
 * STB PIN number length (number of digits)
 ***************************************************************************/
#define SAFEVIEW_STB_PIN_LENGTH                                 6

/***************************************************************************
 * Define the error and debug tracing functions
 ***************************************************************************/
extern int  mtos_printk(const char *p_format, ...);
#define SAFEVIEW_NATIVE_TRACE_DEBUG_FN                          mtos_printk
#define SAFEVIEW_NATIVE_TRACE_ERROR_FN                          mtos_printk

/***************************************************************************
 * Internal adaptation layer debug information on / off
 ***************************************************************************/
#define SAFEVIEW_NO_TRACES                                      0
#define SAFEVIEW_ADAPTATION_DEBUG_INFO                          0

/***************************************************************************
 * Tests and workarounds definition area
 *__________________________________________________________________________
 * Register all supported tests and workarounds
 * IMPORTANT:  any macro  defined  here must  have  its default  value
 * defined in safeview_default_macro_values.h
 ***************************************************************************/

#define SAFEVIEW_FP_OVER_MENUS_JUSTEK_WAY								1

/* Uses safeview_osd_text_size_get */
#define SAFEVIEW_USE_TEXT_SIZE_GET                              1

/* EZXML_NOMMAP  is a  defined/not  defined  compilation constant,  no
 * matter its value if defined */
#define EZXML_NOMMAP                                            1

/* 0: PNG images; 4,8,16: 4,8,16-bit BMP images */
#define SAFEVIEW_BMP_SWAT_LOGOS                                 0

#endif /* ifndef _SAFEVIEW_CONFIG_MSTAR_MSD7C02_MICROZEN_H_ */
