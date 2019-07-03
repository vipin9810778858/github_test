/* $Id: safeview_smartcard_adaptation.h 13 2015-10-06 11:41:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_smartcard_adaptation.h
 *
 * This file defines a standard  API to access smartcard reader driver
 * capabilities.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *      30/01/03        1.0     Miguel Angel González Iglesias
 * - First release
 *      03/06/03        2.0     Miguel Angel González Iglesias
 * - safeview_smc_command returns the T0 status also.
 *      01/07/04        2.2     Miguel Angel González Iglesias
 * - Added a new smartcard error status.
 *      05/01/07        2.3     Rafael Barriuso Maicas
 * - Replaced 'safeview_smartcard_adaptation_init' with
 *   'safeview_init_smartcard_adaptation'.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_SMARTCARD_ADAPTATION_H_
#define _SAFEVIEW_SMARTCARD_ADAPTATION_H_

#include "safeview_common_types.h"k

/* SafeView smartcard configuration values */
#define SAFEVIEW_SMARTCARD_BAUDRATE                             9600
#define SAFEVIEW_SMARTCARD_PTS                                  0

/* Possible return values */
#define SAFEVIEW_SMC_NO_ANSWER_ERROR                            (-2)
#define SAFEVIEW_SMC_WRITE_ERROR                                (-3)
#define SAFEVIEW_SMC_PROTOCOL_ERROR                             (-4)

#define SAFEVIEW_GENERIC_CLA                                    0x00
#define SAFEVIEW_SPECIFIC_CLA                                   0x80
#define SAFEVIEW_MAX_SMC_ANSWER_LENGTH                          192

/* Protocol type */
typedef enum
{
    SAFEVIEW_SMC_T0_PROTOCOL = 0,
    SAFEVIEW_SMC_T1_PROTOCOL
} SMCProtocol;

/* Smartcard event types */
typedef enum
{
    SAFEVIEW_SMC_INSERTED_EVENT = 0,
    SAFEVIEW_SMC_NOT_INSERTED_EVENT,
    SAFEVIEW_SMC_ERROR_EVENT
} SMCEventType;

/*************************************************************************************
    Function:   SMCStatusCallback
    Params:     slot: Slot id.
                status: Smartcard status.
    Return:     No return value.
    Desc:       Smartcard status callback type.
*************************************************************************************/
typedef void (*SMCStatusCallback) (SafeViewSlotId slot, SMCEventType event);

/*************************************************************************************
    Function:   safeview_init_smartcard_adaptation
    Params:     None.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initialices the smartcard adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_smartcard_adaptation (void);

/*************************************************************************************
    Function:   safeview_smartcard_reset
    Params:     slot: Slot id.
                atr: Allocated buffer where the ATR is returned.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Resets the smartcard.
*************************************************************************************/
SafeViewResult safeview_smartcard_reset (SafeViewSlotId slot,
                                         unsigned char *atr);

/*************************************************************************************
    Function:   safeview_smartcard_set_baudrate
    Params:     slot: Slot id.
                baudrate: Baudrate to set in the slot.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets the baudrate to be used in the slot.
*************************************************************************************/
SafeViewResult safeview_smartcard_set_baudrate (SafeViewSlotId slot,
                                                unsigned int baudrate);

/*************************************************************************************
    Function:   safeview_smartcard_set_protocol
    Params:     slot: Slot id.
                protocol: Protocol to set.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets the protocol to be used in the slot.
*************************************************************************************/
SafeViewResult safeview_smartcard_set_protocol (SafeViewSlotId slot,
                                                SMCProtocol protocol);

/*************************************************************************************
    Function:   safeview_smc_command
    Params:     slot: Slot id.
                CLA: CLA byte.
                INS: INS byte.
                P1: P1 byte.
                P2: P2 byte.
                data_length: Data length.
                data: Command data.
                answer: Allocated buffer to store the answer.
                answer_length: In parameter specifies the answer length expected.
                Out one specifies the answer length.
                result: Two T0 bytes returned by the smartcard.
    Return:     SAFEVIEW_OK if OK, or
                SAFEVIEW_SMC_NO_ANSWER_ERROR,
                SAFEVIEW_SMC_WRITE_ERROR,
                SAFEVIEW_SMC_PROTOCOL_ERROR,
                SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sends a command to the smartcard.
*************************************************************************************/
SafeViewResult safeview_smc_command (SafeViewSlotId slot,
                                     unsigned char CLA,
                                     unsigned char INS,
                                     unsigned char P1,
                                     unsigned char P2,
                                     unsigned char data_length,
                                     unsigned char *data,
                                     unsigned char *answer,
                                     unsigned char *answer_length,
                                     unsigned char *result);

/*************************************************************************************
    Function:   safeview_is_smartcard_inserted
    Params:     slot: Slot id.
    Return:     SAFEVIEW_TRUE if inserted, SAFEVIEW_FALSE if not inserted.
    Desc:       Returns if the smartcard is or not inserted.
*************************************************************************************/
SafeViewBoolean safeview_is_smartcard_inserted (SafeViewSlotId slot);

/*************************************************************************************
    Function:   safeview_register_smc_status
    Params:     slot: Slot id.
                cb: Callback to be called for each new status.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers to receive smartcard status changes notifications..
*************************************************************************************/
SafeViewResult safeview_register_smc_status (SafeViewSlotId slot,
                                             SMCStatusCallback cb);

/*************************************************************************************
    Function:   safeview_unregister_smc_status
    Params:     slot: Slot id.
                cb: Callback to unregister.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Unregisters to receive smartcard status changes notifications..
*************************************************************************************/
SafeViewResult safeview_unregister_smc_status (SafeViewSlotId slot,
                                               SMCStatusCallback cb);

#endif /* ifndef _SAFEVIEW_SMC_ADAPTATION_H_ */
