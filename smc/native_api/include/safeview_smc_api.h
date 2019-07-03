/* $Id: safeview_smc_api.h 14 2015-12-09 16:40:11Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_smc_api.h
 *
 * This file defines the API  that SafeView implements to offer access
 * to smartcard.
 *
 * History:
 *     28/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     13/07/03    2.0 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     03/11/03    2.2 Miguel Angel González Iglesias
 *                 Owner and length are given a maximum length.
 *     12/05/08    2.3 Rafael Barriuso Maicas
 *                 Added 'SAFEVIEW_SMC_NOT_INITIALIZED' status.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_SMC_API_H_
#define _SAFEVIEW_SMC_API_H_

#include "safeview_config.h"

#include "safeview_common_types.h"

#define SAFEVIEW_MAX_OWNER_LENGTH                               36
#ifndef TESTCARD
#define SAFEVIEW_MAX_ALIAS_LENGTH                               16
#endif /* #ifndef TESTCARD */

#define SAFEVIEW_MAX_NUM_FOLDERS                                3

typedef unsigned short SafeViewSMCHwVersion;
typedef unsigned short SafeViewSMCSwVersion;
typedef unsigned long SafeViewSMCAddr;


typedef enum
{
    SAFEVIEW_SMC_NOT_INSERTED = 0,
    SAFEVIEW_SMC_SAFEVIEW_OK,
    SAFEVIEW_SMC_NOT_SAFEVIEW,
    SAFEVIEW_SMC_BAD_INSERTED,
    SAFEVIEW_SMC_NOT_INITIALIZED
} SafeViewSMCStatus;


#if SAFEVIEW_OSD_MANAGER_SUPPORT && SAFEVIEW_PARENTAL_RATING_SUPPORT

typedef enum
{
    SAFEVIEW_RATING_BLOCK_ALL = 0,
    SAFEVIEW_RATING_UNDER_7 = 1,
    SAFEVIEW_RATING_UNDER_13 = 2,
    SAFEVIEW_RATING_UNDER_18 = 3,
    SAFEVIEW_RATING_BLOCK_ADULT = 4,
    SAFEVIEW_RATING_DISABLED = 5,
    SAFEVIEW_RATING_LAST = 6
#if SAFEVIEW_FORBIDDEN_CONTENT_SUPPORT
    , SAFEVIEW_RATING_FORBIDDEN_CONTENT = 0xF
#endif //#if SAFEVIEW_FORBIDDEN_CONTENT_SUPPORT
} SafeViewParentalRate;

#endif //#if SAFEVIEW_OSD_MANAGER_SUPPORT && SAFEVIEW_PARENTAL_RATING_SUPPORT

/* Callbacks */
/*************************************************************************************
    Callback:   SMCStatusHandler
    Params:     slot:   Slot in which the event has been produced.
                status: New smartcard status.
    Desc:       Called when there is a change in the smartcard status.
*************************************************************************************/
typedef void (*SMCStatusHandler) (SafeViewSlotId slot,
                                  SafeViewSMCStatus status);

/*************************************************************************************
    Callback:   SMCInfoHandler
    Params:     caller_data: Data passed by the caller when calling safeview_get_smc_info function.
                slot:        Slot in which the event has been produced.
                hw_version:  Smartcard HW version.
                sw_version:  Smartcard HW version.
                address:     Smartcard address.
                owner:       Smartcard owner.
#ifndef TESTCARD
                alias:       Smartcard owner alias.
#endif
                result:      Operation result.
    Desc:       Returns the smartcard info due to an safeview_get_smc_info query.
*************************************************************************************/
typedef void (*SMCInfoHandler) (void *caller_data,
                                SafeViewSlotId slot,
                                SafeViewSMCHwVersion hw_version,
                                SafeViewSMCSwVersion sw_version,
                                SafeViewSMCAddr address, unsigned char *owner,
#ifndef TESTCARD
                                unsigned char *alias,
#endif                          /* #ifdef TESTCARD */
                                SafeViewResult result);

typedef struct
{
    SMCStatusHandler smcStatusCb;
} SafeViewSMCStatusCallbacks;

/*************************************************************************************
    Function:   safeview_register_smc_callbacks
    Params:     cbSt: Callbacks structure.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers callbacks related to smartcard.
*************************************************************************************/
SafeViewResult safeview_register_smc_callbacks (SafeViewSMCStatusCallbacks *
                                                cbSt);

/*************************************************************************************
    Function:   safeview_get_smc_status
    Params:     slot: Slot id.
    Return:     Status of the smartcard.
    Desc:       Returns the status of the smartcard in the slot.
*************************************************************************************/
SafeViewSMCStatus safeview_get_smc_status (SafeViewSlotId slot);



/*************************************************************************************
    Function:   safeview_get_smc_info
    Params:     slot: Slot id.
                caller_data: This data will be returned when the callback is called.
                cb: Callback to be calles with the smartcard info.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the information stored in an safeview smartcard.
*************************************************************************************/
SafeViewResult safeview_get_smc_info (SafeViewSlotId slot,
                                      void *caller_data, SMCInfoHandler cb);

#if SAFEVIEW_OSD_MANAGER_SUPPORT

/*************************************************************************************
    Function:   safeview_parental_level_set
    Params:     SafeViewParentalRate: New parental rate to set.
    Return:     SAFEVIEW_OK if OK.
                SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets a new parental rate for Safeview system.
*************************************************************************************/
SafeViewResult safeview_parental_level_set (SafeViewParentalRate rate);

/*************************************************************************************
    Function:   safeview_parental_level_get
    Params:     SafeViewParentalRate*: Pointer to return the current parental rate
                in Safeview system. Pointer passed shall be not NULL.
    Return:     SAFEVIEW_OK if OK.
                SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Gets the current parental rate for Safeview system.
*************************************************************************************/
SafeViewResult safeview_parental_level_get (SafeViewParentalRate * rate);

#endif //#if SAFEVIEW_OSD_MANAGER_SUPPORT

#endif /* ifndef _SAFEVIEW_SMC_API_H_ */
