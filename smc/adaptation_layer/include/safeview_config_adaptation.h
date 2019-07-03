/* $Id: safeview_config_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2011 SafeView. All rights reserved.
 *
 * safeview_config_adaptation.h
 *
 * This  file defines  configuration constants  for each  STB chipset.
 * Manufacturer should redefine the constants to match its case.
 *
 * History:
 *      23/02/11        1.0     Rafael Barriuso Maicas
 *			17/02/2017					Vipin Saxena(Creator)
 * - Moved adaptation configuration macros to this file.
 *      01/07/13        2.0     Miguel Seisdedos Vega
 * - Selection of suitable config file according chipset/manufacturer.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * SafeView. Use of this software  shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and SafeView.
 */

#ifndef _SAFEVIEW_CONFIG_ADAPTATION_H_
#define _SAFEVIEW_CONFIG_ADAPTATION_H_

/***************************************************************************
 * Processor endianness
 ***************************************************************************/
#define SAFEVIEW_LITTLE_ENDIAN                                  1
#define SAFEVIEW_BIG_ENDIAN                                     2

/***************************************************************************
 * Specific chipset parameters
 ***************************************************************************/
#ifndef SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION
#error SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION NOT defined!

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_CELESTIAL1201_JUSTEK
#include "safeview_config_celestial1201_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_SUNPLUS1002_JUSTEK
#include "safeview_config_sunplus1002_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_M2C_TECATEL
#include "safeview_config_m2c_tecatel.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5100_IRISMEDIA
#include "safeview_config_st5100_irismedia.h"   //No safeview_config_st5100_irismedia.h so far

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5107_IRISMEDIA
#include "safeview_config_st5107_irismedia.h"   //No safeview_config_st5107_irismedia.h so far

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5105_IRISMEDIA
#include "safeview_config_st5105_irismedia.h"   //No safeview_config_st5105_irismedia.h so far

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ALI3381C_JUSTEK
#include "safeview_config_ali3381c_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_CELESTIAL1800_JUSTEK
#include "safeview_config_celestial1800_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_SUNPLUS_ABV
#include "safeview_config_sunplus_abv.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ALI3208_NEWLAND
#include "safeview_config_ali3208_newland.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ALI3601_NEWLAND
#include "safeview_config_ali3601_newland.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_HI3716M_JUSTEK
#include "safeview_config_hisilicon3716_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ALI3202_JUSTEK
#include "safeview_config_ali3202_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5197_JUSTEK
#include "safeview_config_st5197_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ALI3601E_JUSTEK
#include "safeview_config_ali3601e_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5197_ONEEIGHT
#include "safeview_config_st5197_one-eight.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_GX3113B_JUSTEK
#include "safeview_config_gx3113b_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_GX3231_JUSTEK
#include "safeview_config_gx3231_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5197_NEWLAND
#include "safeview_config_st5197_newland.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_HI3716M_ANDROID_JUSTEK
#include "safeview_config_hisilicon3716android_justek.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_MSD5019_NEWLAND
#include "safeview_config_msd5019_newland.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_STXH205B_ONEEIGHT
#include "safeview_config_stxh205b_oneeight.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ST5251_ONEEIGHT
#include "safeview_config_st5251_one-eight.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_ALIM3281_SMT
#include "safeview_config_alim3281_smt.h"

#elif SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION == SAFEVIEW_CHIPSET_MANUFACTURER_CC6000_MONTAGE
#include "safeview_config_cc6000_montage.h"

#else /* !SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION */
#error Unsupported chipset/manufacturer. Check SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION macro.

#endif /* !SAFEVIEW_CHIPSET_MANUFACTURER_SELECTION */

/***************************************************************************
 * Debugging
 ***************************************************************************/
#if SAFEVIEW_NO_TRACES
#define SAFEVIEW_DEBUG(x)
#define SAFEVIEW_ERROR(x)
#define SAFEVIEW_DEBUG2(x)
#define SAFEVIEW_DEBUGLINE

#else /* !SAFEVIEW_NO_TRACES */
#define SAFEVIEW_DEBUG(x)                                       if (TRACE_DEBUG) \
    { SAFEVIEW_NATIVE_TRACE_DEBUG_FN (x); }

#define SAFEVIEW_ERROR(x)                                       if (TRACE_ERROR) \
    { SAFEVIEW_NATIVE_TRACE_ERROR_FN ("ERROR in file %s, line %d\n", __FILE__, __LINE__); \
        SAFEVIEW_NATIVE_TRACE_ERROR_FN (x); }

#define SAFEVIEW_DEBUG2(x)                                      SAFEVIEW_NATIVE_TRACE_DEBUG_FN (x)

#define SAFEVIEW_DEBUGLINE()                                    SAFEVIEW_DEBUG2 (("%s:%d\n", __FILE__, __LINE__))

#endif /* !SAFEVIEW_NO_TRACES */

#endif /* ifndef _SAFEVIEW_CONFIG_ADAPTATION_H_ */
