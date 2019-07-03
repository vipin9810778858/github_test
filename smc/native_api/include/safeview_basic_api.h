/* $Id: safeview_basic_api.h 14 2015-12-09 16:40:11Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_basic_api.h
 *
 * Definition of basic SafeView native API.
 *
 * History:
 *     31/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     03/06/03    2.0 Miguel Angel González Iglesias
 *                 safeview_start can be blocking or non-blocking.
 *                 New function to manage a unique event.
 *     01/07/04    2.2 Miguel Angel González Iglesias
 *                 No relevant changes.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_BASIC_API_H_
#define _SAFEVIEW_BASIC_API_H_

#include "safeview_common_types.h"

/*************************************************************************************
    Function:   safeview_init
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes safeview.
*************************************************************************************/
SafeViewResult safeview_init (void);

/*************************************************************************************
    Function:   safeview_release
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Releases safeview.
*************************************************************************************/
SafeViewResult safeview_release (void);

/*************************************************************************************
    Function:   safeview_start
    Params:     blocking_mode: SAFEVIEW_BLOCKING_MODE if this function
                should   block   and   start   managing   events,   or
                SAFEVIEW_NON_BLOCKING_MODE if the  function should not
                block.   In the  first  case, the  function should  be
                called in a different thread.  In the second case, the
                caller  should  call  later  safeview_manage_event  to
                manage each new event arrived.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Starts Safeview system.
*************************************************************************************/
SafeViewResult safeview_start (SafeViewBlockingType blocking);

/*************************************************************************************
    Function:   safeview_stop
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Stops Safeview system.
*************************************************************************************/
SafeViewResult safeview_stop (void);

/*************************************************************************************
    Function:   safeview_manage_event
    Params:     None
    Return:     SAFEVIEW_NO_EVENT_MANAGED if no event has been managed.
                SAFEVIEW_EVENT_MANAGED if an event has been managed.
                SAFEVIEW_GENERIC_ERROR if error.
    Desc:       This function looks for an event to manage.
*************************************************************************************/
int safeview_manage_event (void);

/* #if !SAFEVIEW_OSD_MANAGER_SUPPORT */

/*************************************************************************************
    Function:   safeview_application_open
    Params:     None
    Return:     None
    Desc:       This function opens the SafeView CAS application from the STB menu.
*************************************************************************************/
void safeview_application_open (void);

/*************************************************************************************
    Function:   safeview_application_open_screen
    Params:     screen_num: screen ID
    Return:     None
    Desc:       This function opens the SafeView CAS application in the given screen
                number.
*************************************************************************************/
void safeview_application_open_screen (int screen_num);

/* #endif //#if !SAFEVIEW_OSD_MANAGER_SUPPORT */

/*************************************************************************************
    Function:   safeview_supported_atr
    Params:     atr: ATR string.
    Return:     1 if safeview ATR, 0 if not.
    Desc:       Tests if an ATR is a SafeView ATR.
*************************************************************************************/
SafeViewBoolean safeview_supported_atr (unsigned char *atr);

/*************************************************************************************
    Function:   safeview_get_custom_data
    Params:     None
    Return:     Byte array with cutom data
    Desc:       This function returns the customized SafeView data or NULL if none.
                The byte array is statically alloc'd.
*************************************************************************************/
unsigned char *safeview_get_custom_data (void);

#endif /* ifndef _SAFEVIEW_BASIC_API_H_ */
