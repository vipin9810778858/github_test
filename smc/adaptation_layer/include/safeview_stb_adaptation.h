/* $Id: safeview_stb_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2012 SafeView S.L. All rights reserved.
 *
 * safeview_stb_adaptation.h
 *
 * This file  defines types and  functions used by the  different APIs
 * provided by SafeView.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *      26/01/12        1.0     Rafael Barriuso
 * - First release (from safeview_utils_adaptation)
 *      26/01/12        2.0     Rafael Barriuso
 * - Added new functions: "safeview_stb_change_to_channel"
 * "safeview_stb_change_to_audio"
 *      06/09/12        2.1     Miguel Seisdedos
 * - Added new function: "safeview_stb_current_service_get"
 *
 * This software is  subject to updates, revisions,  and extensions by
 * SafeView. Use of this software  shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and SafeView.
 */

#ifndef _SAFEVIEW_STB_ADAPTATION_H_
#define _SAFEVIEW_STB_ADAPTATION_H_

#include "safeview_common_types.h"

/*************************************************************************************
    Function:   safeview_get_stb_id
    Params:     len: number of available bytes in 'stb_id' to store the STB ID.
                stb_id: buffer to store the STB identifier.
    Return:     None.
    Desc:       Returns an unique identifier of the box. please go through this doc SV_cardbasedSTB_Production_Procedure.pdf
*************************************************************************************/
void safeview_get_stb_id (int len, unsigned char *stb_id);

/*************************************************************************************
    Function:   safeview_set_stb_pin
    Params:     pin: new PIN to be set.
    Return:     SAFEVIEW_OK if new pin is set, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets a new PIN in the receiver.
*************************************************************************************/
SafeViewResult safeview_set_stb_pin (char *pin);

/*************************************************************************************
    Function:   safeview_reinstall_stb_channels
    Params:     None.
    Return:     SAFEVIEW_OK if new pin is set, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Performs a re-installation of the services (NIT search, freq scanning, ...).
*************************************************************************************/
SafeViewResult safeview_reinstall_stb_channels (void);

/*************************************************************************************
    Function:   safeview_get_stb_persistent_data
    Params:     len: number of available bytes in 'buffer' to store the persistent data from the STB.
                buffer: buffer to store the persistent data from the STB.
    Return:     SAFEVIEW_OK if data could be retrieved, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Returns the persistent data previously stored with 'safeview_set_stb_persistent_data'.
*************************************************************************************/
SafeViewResult safeview_get_stb_persistent_data (int len,
                                                 unsigned char *buffer);

/*************************************************************************************
    Function:   safeview_set_stb_persistent_data
    Params:     len: buffer length
                buffer: data to store in persistent memory
    Return:     SAFEVIEW_OK if data could be stored, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Stores the given data in the persistent memory of the STB.
*************************************************************************************/
SafeViewResult safeview_set_stb_persistent_data (int len,
                                                 unsigned char *buffer);

/*************************************************************************************
    Function:   safeview_stb_change_to_channel
    Params:     tunerId: ID of the tuner in which the channel has to be changed
                onid: new original networt ID to tune
                tsid: new transport service ID to tune
                sid: new service ID to tune
    Return:     SAFEVIEW_OK if channel was changed, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Forces a zapping to the given channel
*************************************************************************************/
SafeViewResult safeview_stb_change_to_channel (SafeViewDemuxId tunerId,
                                               SafeViewOnid onid,
                                               SafeViewTsid tsid,
                                               SafeViewSid sid);

/*************************************************************************************
    Function:   safeview_stb_current_service_get
    Params:     tunerId: Tuner ID of the  tuner which the STB is using
                to tune the current service.
                onid: Original network ID of the current service.
                tsid: Transport service ID of the current service.
                sid: Service ID of the current service.
    Return:     SAFEVIEW_OK if valid data gotten, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Gets from STB the current service tuned and the tunerId which is
                tuning it.
*************************************************************************************/
SafeViewResult safeview_stb_current_service_get (SafeViewDemuxId * tunerId,
                                                 SafeViewOnid * onid,
                                                 SafeViewTsid * tsid,
                                                 SafeViewSid * sid);

/*************************************************************************************
    Function:   safeview_stb_change_to_audio
    Params:     tunerId: ID of the tuner in which the audio needs to be changed
                newAudioPid: PID of the audio to be tuned
    Return:     SAFEVIEW_OK if audio was properly changed, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Selects a new audio PID to show to the user.
*************************************************************************************/
SafeViewResult safeview_stb_change_to_audio (SafeViewDemuxId tunerId,
                                             SafeViewPID newAudioPid);

/*************************************************************************************
    Function:   safeview_stb_pin_check
    Params:     pin: PIN number to be checked as ASCII numeric characters.
                length: number of characters in the PIN number (usually SAFEVIEW_STB_PIN_LENGTH).
    Return:     SAFEVIEW_OK if the PIN number was successfully verified, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Compares the given PIN number with the STB PIN.
*************************************************************************************/
SafeViewResult safeview_stb_pin_check (unsigned char *pin, int length);

/*************************************************************************************
    Function:   safeview_stb_cur_svc_name_get
    Params:     bufferSize: Buffer size. Maximum number of bytes to be
                copied on buffer, including terminating null char.
                buffer: Buffer  where current  service name has  to be
                copied.
    Return:     SAFEVIEW_OK if everything OK, SAFEVIEW_GENERIC_ERROR otherwise.
    Desc:       Gets current service name.
*************************************************************************************/
SafeViewResult safeview_stb_cur_svc_name_get (unsigned short bufferSize,
                                              char *buffer);

/*************************************************************************************
    Function:   safeview_stb_to_standby
    Params:     void
    Return:     void
    Desc:       STB is put into standby mode.
*************************************************************************************/
SafeViewResult safeview_stb_to_standby (void);

#endif /* ifndef _SAFEVIEW_STB_ADAPTATION_H_ */
