/* $Id: safeview_key_adaptation.h 13 2015-10-06 11:41:34Z agarcia $ */
/* Copyright 2007 Secuenzia Pixels. All rights reserved.
 *
 * safeview_key_adaptation.h
 *
 * This file defines a standard API to manage the remote control keys.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *     05/01/07    1.0 Rafael Barriuso Maicas
 *                 First release
 *     10/06/09    1.1 Rafael Barriuso Maicas
 *                 Moved key codes here.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_KEY_ADAPTATION_H_
#define _SAFEVIEW_KEY_ADAPTATION_H_

#include "safeview_common_types.h"

/* #if !SAFEVIEW_OSD_MANAGER_SUPPORT */

/* SafeView key codes */
#define SAFEVIEW_NATIVE_BACK_KEY                                0x0008  //IRD_KEY_BACK
#define SAFEVIEW_NATIVE_OK_KEY                                  0x000A  //IRD_KEY_OK
#define SAFEVIEW_NATIVE_EXIT_KEY                                0x001B  //IRD_KEY_EXIT
#define SAFEVIEW_NATIVE_VOLUME_UP_KEY                           0x001C
#define SAFEVIEW_NATIVE_VOLUME_DOWN_KEY                         0x001D
#define SAFEVIEW_NATIVE_MUTE_KEY                                0x001E
#define SAFEVIEW_NATIVE_LEFT_ARROW_KEY                          0x0025  //IRD_KEY_ARROW_LEFT
#define SAFEVIEW_NATIVE_UP_ARROW_KEY                            0x0026  //IRD_KEY_ARROW_UP
#define SAFEVIEW_NATIVE_RIGHT_ARROW_KEY                         0x0027  //IRD_KEY_ARROW_RIGHT
#define SAFEVIEW_NATIVE_DOWN_ARROW_KEY                          0x0028  //IRD_KEY_ARROW_DOWN
#define SAFEVIEW_NATIVE_0_KEY                                   0x0030  //IRD_KEY_0
#define SAFEVIEW_NATIVE_1_KEY                                   0x0031  //IRD_KEY_1
#define SAFEVIEW_NATIVE_2_KEY                                   0x0032  //IRD_KEY_2
#define SAFEVIEW_NATIVE_3_KEY                                   0x0033  //IRD_KEY_3
#define SAFEVIEW_NATIVE_4_KEY                                   0x0034  //IRD_KEY_4
#define SAFEVIEW_NATIVE_5_KEY                                   0x0035  //IRD_KEY_5
#define SAFEVIEW_NATIVE_6_KEY                                   0x0036  //IRD_KEY_6
#define SAFEVIEW_NATIVE_7_KEY                                   0x0037  //IRD_KEY_7
#define SAFEVIEW_NATIVE_8_KEY                                   0x0038  //IRD_KEY_8
#define SAFEVIEW_NATIVE_9_KEY                                   0x0039  //IRD_KEY_9
#define SAFEVIEW_NATIVE_MOSAIC_KEY                              0x00B4  //EMG_MSG_KEYCODE_MOSAIC
#define SAFEVIEW_NATIVE_RED_KEY                                 0x0193  //IRD_KEY_RED
#define SAFEVIEW_NATIVE_GREEN_KEY                               0x0194  //IRD_KEY_GREEN
#define SAFEVIEW_NATIVE_YELLOW_KEY                              0x0195  //IRD_KEY_YELLOW
#define SAFEVIEW_NATIVE_BLUE_KEY                                0x0196  //IRD_KEY_BLUE
#define SAFEVIEW_NATIVE_TEXT_KEY                                0x01CB  //IRD_KEY_TELETEXT
#define SAFEVIEW_NATIVE_POWER_KEY                               0x0F00  //IRD_KEY_POWER
#define SAFEVIEW_NATIVE_FOLDER_CLUB                             0x0F10  //IRD_KEY_APP
#define SAFEVIEW_NATIVE_INFO_KEY                                0x0F12  //IRD_KEY_INFO
#define SAFEVIEW_NATIVE_LIST_KEY                                0x0F13  //IRD_KEY_LIST
#define SAFEVIEW_NATIVE_MENU_KEY                                0x0F14  //IRD_KEY_MENU
#define SAFEVIEW_NATIVE_TVRADIO_KEY                             0x0F20  //IRD_KEY_TV_RADIO
#define SAFEVIEW_NATIVE_SUBTITLE_KEY                            0x0F21  //IRD_KEY_SUBTITLE
#define SAFEVIEW_NATIVE_AUDIO_KEY                               0x0F22  //IRD_KEY_AUDIO
#define SAFEVIEW_NATIVE_ZOOM_KEY                                0x0F23  //IRD_KEY_ZOOM
#define SAFEVIEW_NATIVE_PROG_UP_KEY                             0x0F24
#define SAFEVIEW_NATIVE_PROG_DOWN_KEY                           0x0F25
#define SAFEVIEW_NATIVE_INBOX_KEY                               0x0F26

/** Key code type */
typedef unsigned int SafeViewKeyCode;

/*************************************************************************************
    Function:   SafeViewKeyManagerCb
    Params:     key: Code of the pressed key.
    Return:     1 if the key was processed, 0 if not.
    Desc:       Key pressed callback type.
*************************************************************************************/
typedef int (*SafeViewKeyManagerCb) (SafeViewKeyCode key);

/*************************************************************************************
    Function:   safeview_key_adaptation_init
    Params:     None.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes the key adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_key_adaptation (void);

/*************************************************************************************
    Function:   safeview_register_key_manager
    Params:     cb: Callback to be called for each key pressed.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers to receive key events notifications.
*************************************************************************************/
SafeViewResult safeview_register_key_manager (SafeViewKeyManagerCb cb);

/*************************************************************************************
    Function:   safeview_unregister_key_manager
    Params:     cb: Callback to unregister.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Unregisters the key manager callback.
*************************************************************************************/
SafeViewResult safeview_unregister_key_manager (SafeViewKeyManagerCb cb);

/* #endif /\* !SAFEVIEW_OSD_MANAGER_SUPPORT *\/ */

#endif /* ifndef _SAFEVIEW_KEY_ADAPTATION_H_ */
