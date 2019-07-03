/* $Id: safeview_decoder_adaptation.h 13 2015-10-06 11:41:34Z agarcia $ */
/* Copyright 2006 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_decoder_adaptation.c
 *
 * This file implements the standard API to access decoder status
 *
 * History:
 *      21/11/06        1.0     Rafael Barriuso Maicas
 * - First release
 *      14/07/10        3.0     Rafael Barriuso Maicas
 * - Adapted source code for IPTV CAS.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia.  Use of  this software shall be  permitted only pursuant
 * to the  terms and conditions  of the license agreement  between the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_DECODER_ADAPTATION_H_
#define _SAFEVIEW_DECODER_ADAPTATION_H_

#include "safeview_common_types.h"

/* Supported decoder status */
typedef enum
{
    SAFEVIEW_UNKNOWN_DECODING_STATE,
    SAFEVIEW_DECODING_VIDEO,
    SAFEVIEW_NOT_DECODING_VIDEO
} SafeViewDecodingStatus;

/*************************************************************************************
    Function:   SafeViewDecodingStatus (function type)
    Params:     state: New status of the video decoder
    Return:     No return value.
    Desc:       This callback must be called by the manufacturer each time the
                decoding status changes, that is, when the receiver begins or stops
                displaying video (and audio) on the screen
*************************************************************************************/
typedef void (*DecoderStatusCallback) (SafeViewDecodingStatus state);

/*************************************************************************************
    Function:   safeview_init_decoder_adaptation
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes the decoder adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_decoder_adaptation (void);

/*************************************************************************************
    Function:   safeview_end_decoder_adaptation
    Params:     None
    Return:     None
    Desc:       This function frees all resources allocated by the decoder layer.
*************************************************************************************/
void safeview_end_decoder_adaptation (void);

/*************************************************************************************
    Function:   safeview_start_decoder_monitor
    Params:     None
    Return:     None
    Desc:       Starts the decoder monitor and calls the registered callbacks when
                the status of the decoder changes.
*************************************************************************************/
void safeview_start_decoder_monitor (void);

/*************************************************************************************
    Function:   safeview_stop_decoder_monitor
    Params:     None
    Return:     None
    Desc:       Stops the decoder monitor so no callbacks are called.
*************************************************************************************/
void safeview_stop_decoder_monitor (void);

/*************************************************************************************
    Function:   safeview_register_decoder_status
    Params:     cb: Callback to be called for each new status.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers a callback to receive notifications when the decoder status changes.
*************************************************************************************/
SafeViewResult safeview_register_decoder_status (DecoderStatusCallback cb);

/*************************************************************************************
    Function:   safeview_unregister_decoder_status
    Params:     cb: Callback to unregister.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Unregisters a decoder status callback.
*************************************************************************************/
SafeViewResult safeview_unregister_decoder_status (DecoderStatusCallback cb);

#endif /* ifndef _SAFEVIEW_DECODER_ADAPTATION_H_ */
