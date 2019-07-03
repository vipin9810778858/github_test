/* $Id: safeview_rc_adaptation.h 11 2015-09-30 12:46:14Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_rc_adaptation.h
 *
 * This file defines the functions used to access the return channel.
 *
 * History:
 *     01/06/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     03/06/03    2.0 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     30/10/03    2.2 Miguel Angel González Iglesias
 *                 New connect result constants.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_RC_ADAPTATION_H_
#define _SAFEVIEW_RC_ADAPTATION_H_

#include "safeview_common_types.h"
#include "safeview_loyalty_api.h"

typedef enum
{
    SAFEVIEW_RC_MODEM_USED,
    SAFEVIEW_RC_NO_TONE,
    SAFEVIEW_RC_NO_ANSWER,
    SAFEVIEW_RC_BUSY,
    SAFEVIEW_RC_IP_NO_ANSWER,
    SAFEVIEW_RC_GENERIC_ERROR,
    SAFEVIEW_RC_CONNECT_OK
} SafeViewConnectResult;

/*************************************************************************************
    Function:   SafeViewRCConnectCb (function type)
    Params:     operator_id: Operator requesting the connection.
                result: Connection result.
    Return:     No return value.
    Desc:       This is the callback function type that must be called by the manufacturer
                implementation to return the connection attempt result.
*************************************************************************************/
typedef void (*SafeViewRCConnectCb) (SafeViewOperatorId operator_id,
                                     SafeViewConnectResult result);

/*************************************************************************************
    Function:   SafeViewRCDisconnectCb (function type)
    Params:     operator_id: Operator requesting the connection.
    Return:     No return value.
    Desc:       This is the callback function type that must be called by the manufacturer
                implementation when the connection is down.
*************************************************************************************/
typedef void (*SafeViewRCDisconnectCb) (SafeViewOperatorId operator_id);

/*************************************************************************************
    Function:   SafeViewRCDataCb (function type)
    Params:     operator_id: Operator requesting the connection.
                data_length: Data length.
                data: Data received.
    Return:     No return value.
    Desc:       This is the callback function type that must be called by the manufacturer
                implementation when new data arrives in a conmnection.
*************************************************************************************/
typedef void (*SafeViewRCDataCb) (SafeViewOperatorId operator_id,
                                  unsigned char data_length,
                                  unsigned char *data);

/*************************************************************************************
    Function:   safeview_init_rc_adaptation
    Params:     None.
    Return:     SAFEVIEW_OK OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes rc adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_rc_adaptation (void);

/*************************************************************************************
    Function:   safeview_connect_to_server
    Params:     operator_id: Operator Id.
                phone_number: Phone number to call.
                safeview_rc_connect_cb: Connection callback.
                safeview_rc_disconnect_cb: Disconnection callback.
                safeview_rc_data_cb: Data callback.
    Return:     SAFEVIEW_OK OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Connects to the server
*************************************************************************************/
SafeViewResult safeview_connect_to_server (SafeViewOperatorId operator_id,
                                           unsigned char *phone_number,
                                           SafeViewRCConnectCb
                                           safeview_rc_connect_cb,
                                           SafeViewRCDisconnectCb
                                           safeview_rc_disconnect_cb,
                                           SafeViewRCDataCb
                                           safeview_rc_data_cb);

/*************************************************************************************
    Function:   safeview_disconnect_from_server
    Params:     operator_id: Operator Id.
    Return:     SAFEVIEW_OK OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Disconnects from server.
*************************************************************************************/
SafeViewResult safeview_disconnect_from_server (SafeViewOperatorId
                                                operator_id);

/*************************************************************************************
    Function:   safeview_send_data_to_server
    Params:     operator_id: Operator Id.
                data_length: Data length.
                data: data to send
    Return:     SAFEVIEW_OK OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sends data to server.
*************************************************************************************/
SafeViewResult safeview_send_data_to_server (SafeViewOperatorId operator_id,
                                             unsigned char data_length,
                                             unsigned char *data);

#endif /* ifndef _SAFEVIEW_RC_ADAPTATION_H_ */
