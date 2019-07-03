/* $Id: safeview_cas_api.h 11 2015-09-30 12:46:14Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_cas_api.h
 *
 * This file defines the API  that SafeView implements to offer access
 * to CAS functionality.
 *
 * History:
 *     28/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     25/06/03    2.0 Miguel Angel González Iglesias
 *                 New functions and callbacks to change and validate the smartcard PIN.
 *     01/07/04    2.2 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     25/09/08    2.3 Rafael Barriuso Maicas
 *                 Renamed 'is_current_channel_safeview_scrambled' to 'safeview_is_current_channel_scrambled'.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_CAS_API_H_
#define _SAFEVIEW_CAS_API_H_

#include "safeview_config.h"
#include "safeview_common_types.h"

#define SAFEVIEW_MAX_NUM_PURCHASE_OPTIONS                       4

typedef unsigned char SafeViewPurchaseIndex;

typedef enum
{
    SAFEVIEW_HAS_NO_RIGHTS,
    SAFEVIEW_HAS_RIGHTS,
    SAFEVIEW_HAS_NO_PAIRED_RIGHTS,

#if SAFEVIEW_PARENTAL_RATING_SUPPORT

    SAFEVIEW_HAS_NO_PARENTAL_RIGHTS,

#if SAFEVIEW_FORBIDDEN_CONTENT_SUPPORT

    SAFEVIEW_FORBIDDEN_CONTENT_RIGHTS,

#endif                          //#if SAFEVIEW_FORBIDDEN_CONTENT_SUPPORT

#endif                          //#if SAFEVIEW_PARENTAL_RATING_SUPPORT

    SAFEVIEW_UNKNOWN_RIGHTS
} SafeViewHasRightsType;

typedef enum
{
    SAFEVIEW_PURCHASE_OK,
    SAFEVIEW_PURCHASE_ERROR
} SafeViewPurchaseResult;

typedef enum
{
    SAFEVIEW_PURCHASE_EXISTING_RIGHT,
    SAFEVIEW_PURCHASE_NOT_ENOUGH_MEMORY,
    SAFEVIEW_PURCHASE_NOT_ENOUGH_CREDIT,
    SAFEVIEW_PURCHASE_CONDITIONS_NOT_SATISFIED,
    SAFEVIEW_PURCHASE_NO_VALID_PIN,
    SAFEVIEW_PURCHASE_NO_SMARTCARD_INSERTED,
    SAFEVIEW_PURCHASE_UNKNOWN_ERROR
} SafeViewPurchaseError;

typedef enum
{
    SAFEVIEW_INQUIRY_ACCESS_RIGHTS_NOT_GRANTED,
    SAFEVIEW_INQUIRY_ACCESS_RIGHTS_GRANTED,
    SAFEVIEW_INQUIRY_NOT_ENOUGH_CREDIT,
    SAFEVIEW_INQUIRY_CONDITIONS_NOT_SATISFIED,
    SAFEVIEW_INQUIRY_NO_SMARTCARD_INSERTED,
    SAFEVIEW_INQUIRY_NO_MEMORY_AVAILABLE,
    SAFEVIEW_INQUIRY_UNKNOWN_ERROR
} SafeViewInquiryResult;

typedef struct
{
    unsigned char num_options;
    SafeViewInquiryResult indexInfo[SAFEVIEW_MAX_NUM_PURCHASE_OPTIONS];
} SafeViewInquiryInfo;

/* Callbacks */

/*************************************************************************************
    Callback:   RightsChangedEventHandler
    Params:     rights:      Rights of the current program.
    Desc:       Called when the rights of the current program changes.
*************************************************************************************/
#if SAFEVIEW_MULTISERVICE_SUPPORT

typedef void (*RightsChangedEventHandler) (SafeViewDemuxId demux_id,
                                           SafeViewHasRightsType rights);

#else //#if SAFEVIEW_MULTISERVICE_SUPPORT

typedef void (*RightsChangedEventHandler) (SafeViewHasRightsType rights);

#endif //#if SAFEVIEW_MULTISERVICE_SUPPORT

/*************************************************************************************
    Callback:   InquiryEventHandler
    Params:     caller_data: Data passed by the caller when calling
                safeview_inquiry_event function.
                eventInfo:   Event information.
    Desc:       Returns the event information due to an safeview_inquiry_event query.
*************************************************************************************/
typedef void (*InquiryEventHandler) (void *caller_data,
                                     SafeViewInquiryInfo * eventInfo);

/*************************************************************************************
    Callback:   PurchaseEventHandler
    Params:     caller_data: Data passed by the caller when calling
                safeview_purchase_ppv function.
                status:      Purchase result.
                reason:      In case of error, error reason.
    Desc:       Returns the result of an safeview_purchase_event query.
*************************************************************************************/
typedef void (*PurchaseEventHandler) (void *caller_data,
                                      SafeViewPurchaseResult status,
                                      SafeViewPurchaseError reason);

/*************************************************************************************
    Callback:   NumPurchasesEventHandler
    Params:     caller_data: Data passed by the caller when calling
                safeview_get_num_purchases function.
                purchases:   Number of stored purchases.
                result:      Operation result.
    Desc:       Returns the purchases number due to an safeview_get_num_purchases query.
*************************************************************************************/
typedef void (*NumPurchasesEventHandler) (void *caller_data,
                                          unsigned char purchases,
                                          SafeViewResult result);

/*************************************************************************************
    Callback:   PurchaseInfoEventHandler
    Params:     caller_data:      Data passed by the caller when calling
                safeview_get_purchase_info function.
                purchase_index:   Number of stored purchases.
                purchase_name:    Purchased event name.
                purchase_date:    Purchased event date.
                purchase_points:  Purchased event price.
                result:           Operation result.
    Desc:       Returns the purchase information due to an
                safeview_get_purchase_info query.
*************************************************************************************/
typedef void (*PurchaseInfoEventHandler) (void *caller_data,
                                          SafeViewPurchaseIndex
                                          purchase_index,
                                          unsigned char *purchase_name,
                                          SafeViewDate purchase_date,
                                          SafeViewPoints purchase_points,
                                          SafeViewResult result);

/*************************************************************************************
    Callback:   CheckPINEventHandler
    Params:     caller_data: Data passed by the caller when calling
                safeview_get_folder_name function.
                result:      Operation result.
    Desc:       Returns if the PIN is valid.
*************************************************************************************/
typedef void (*CheckPINEventHandler) (void *caller_data,
                                      SafeViewResult result);

/*************************************************************************************
    Callback:   ChangePINEventHandler
    Params:     caller_data: Data passed by the caller when calling
                safeview_get_folder_name function.
                result:      Operation result.
    Desc:       Sets a new PIN.
*************************************************************************************/
typedef void (*ChangePINEventHandler) (void *caller_data,
                                       SafeViewResult result);

typedef struct
{
    RightsChangedEventHandler rightsChangedCb;
} SafeViewCallbacks;

/*************************************************************************************
    Function:   safeview_register_cas_callbacks
    Params:     cbSt: Callbacks structure.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers callbacks related to CAS.
*************************************************************************************/
SafeViewResult safeview_register_cas_callbacks (SafeViewCallbacks * cbSt);

/*************************************************************************************
    Function:   safeview_is_current_channel_scrambled
    Params:     demux_id: Demux Id.
    Return:     SAFEVIEW_TRUE if the channel is scrambled, SAFEVIEW_FALSE if not.
    Desc:       Returns if the channel is scrambled (and scrambled with SafeView
                system) or not.
*************************************************************************************/
SafeViewBoolean safeview_is_current_channel_scrambled (SafeViewDemuxId
                                                       demux_id);

/*************************************************************************************
    Function:   safeview_inquiry_event
    Params:     data: data used to inquiry for the event.
                data_length: data length.
                caller_data: This data will be returned when the callback is called.
                cb: Callback to notify the result of the inquiry.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Inquiries for buying an event using the corresponding data.
*************************************************************************************/
SafeViewResult safeview_inquiry_event (unsigned char *data,
                                       SafeViewPurchaseLength data_length,
                                       void *caller_data,
                                       InquiryEventHandler cb);

/*************************************************************************************
    Function:   safeview_purchase_event
    Params:     data: Data used to purchase the event.
                data_length: Data length.
                buy_option: Option selected to buy the event. (Available options are
                returned by inquiry function).
                caller_data: This data will be returned when the callback is called.
                cb: Callback to notify the result of the purchase.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Purchases an event using the corresponding data.
*************************************************************************************/
SafeViewResult safeview_purchase_event (unsigned char *data,
                                        SafeViewPurchaseLength data_length,
                                        unsigned char buy_option,
                                        void *caller_data,
                                        PurchaseEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_num_purchases
    Params:     caller_data: This data will be returned when the callback is called.
                cb: Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the number of purchases through a callback.
*************************************************************************************/
SafeViewResult safeview_get_num_purchases (void *caller_data,
                                           NumPurchasesEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_purchase_info
    Params:     purchase_index: Purchase index.
                caller_data: This data will be returned when the callback is called.
                cb: Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the purchase info.
*************************************************************************************/
SafeViewResult safeview_get_purchase_info (SafeViewPurchaseIndex
                                           purchase_index, void *caller_data,
                                           PurchaseInfoEventHandler cb);

/*************************************************************************************
    Function:   safeview_check_pin
    Params:     pin:         PIN to check.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Checks if the PIN is valid.
*************************************************************************************/
SafeViewResult safeview_check_pin (unsigned char *pin,
                                   void *caller_data,
                                   CheckPINEventHandler cb);

/*************************************************************************************
    Function:   safeview_change_pin
    Params:     pin:         PIN to set.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Sets a new PIN.
*************************************************************************************/
SafeViewResult safeview_change_pin (unsigned char *pin,
                                    void *caller_data,
                                    ChangePINEventHandler cb);

#endif /* ifndef _SAFEVIEW_CAS_API_H_ */
