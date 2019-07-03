/* $Id: safeview_osd_api.h 14 2015-12-09 16:40:11Z agarcia $ */
/* Copyright 2010 SafeView S.L.  All rights reserved.
 *
 * safeview_osd_api.h
 *
 * This API allows SafeView to send OSD requests to the upper software
 * application.
 *
 * History:
 *      10/06/2010      1.0     Rafael Barriuso Maicas
 * - First release for IPTV CAS.
 *      17/10/2013      2.0     Safeview
 * - Changes in the parameters.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * SafeView S.L. Use of this software shall be permitted only pursuant
 * to the  terms and conditions  of the license agreement  between the
 * licensee and SafeView S.L.
 */

#ifndef _SAFEVIEW_OSD_API_H_
#define _SAFEVIEW_OSD_API_H_

#include "safeview_common_types.h"

// Text alignment
typedef enum
{
    SAFEVIEW_LEFT_ALIGNMENT = 0,
    SAFEVIEW_CENTER_ALIGNMENT,
    SAFEVIEW_RIGHT_ALIGNMENT
} SafeViewOSDTextAlignment;

// Text font size
typedef enum
{
    SAFEVIEW_FONT_SIZE_NORMAL = 0,
    SAFEVIEW_FONT_SIZE_SMALL,
    SAFEVIEW_FONT_SIZE_BIG,
    SAFEVIEW_FONT_SIZE_SMALLEST,
    SAFEVIEW_FONT_SIZE_BIGGEST
} SafeViewOSDFontSize;

/* OSD blocking mode */
typedef enum
{
    SAFEVIEW_OSD_NON_BLOCKING,
    SAFEVIEW_OSD_BLOCKING
} SafeViewOSDBlockingMode;

/* OSD display mode */
typedef enum
{
    SAFEVIEW_OSD_ALWAYS_ONTOP,
    SAFEVIEW_OSD_CAN_BE_HIDDEN
} SafeViewOSDDisplayMode;

/* OSD display mode */
typedef enum
{
    SAFEVIEW_OSD_STATIC,
    SAFEVIEW_OSD_NORMAL_SPEED,
    SAFEVIEW_OSD_SLOW_SPEED,
    SAFEVIEW_OSD_FAST_SPEED
} SafeViewOSDSpeedMode;

/* OSD event types */
typedef enum
{
    SAFEVIEW_OSD_BASIC_POPUP,   // CAS wants to display a basic popup (similar to old safeview_draw_message)
    SAFEVIEW_OSD_POPUP,         // CAS wants to display a popup
    SAFEVIEW_OSD_COVERT_FP,     // CAS wants to display a covert fp
    SAFEVIEW_OSD_CLEAR,         // CAS wants to clear the screen (except the always on top messages)
    SAFEVIEW_OSD_FORCE_CLEAR    // CAS wants to clear the screen (including the always on top messages)
} SafeViewOSDEventType;

typedef enum
{
    SAFEVIEW_BASIC_POPUP_PLAIN, // Equivalent to old safeview_draw_message. No callback needed. Should be kept indefinitely on screen.
    SAFEVIEW_BASIC_POPUP_OK,    // Basic OK popup. Should disappear as soon as the user presses a key. A callback can be registered to know if user pressed OK. Callback can be NULL if result not needed.
    SAFEVIEW_BASIC_POPUP_PIN    // Basic PIN popup. Should disappear as soon as the user enters a PIN. A callback is registered to send the PIN to Safeview lib.
} SafeViewOSDBasicPopupType;

/* Basic popup information */
typedef struct
{
    SafeViewOSDBasicPopupType type;
    const char *text;           //Text to be painted
    void *param;                //SafeViewOSDOkCb or SafeViewOSDPinCb by now
} SafeViewOSDBasicPopupDataType;

/* Popup information */
typedef struct
{
    unsigned int bg_xpos;       // Background x position
    unsigned int bg_ypos;       // Background y position
    unsigned int bg_xsize;      // Background x size (0 means autofit text)
    unsigned int bg_ysize;      // Background y size (0 means autofit text)
    unsigned int bg_color;      // Background color in RGBA fomat
    const char *text;           // Text to be painted over the background
    SafeViewOSDTextAlignment alignment; // Text alignment
    SafeViewOSDFontSize font_size;      // Text font size
    unsigned int text_color;    // Text color in RGBA format
    SafeViewOSDBlockingMode blocking;   // Indicates if the message must block the STB or not
    SafeViewOSDDisplayMode mode;        // Indicates if the message must be always visible or can be hidden with an action (zapping, epg open, etc.)
    SafeViewOSDSpeedMode speed; // Speed in the text movement for ticker popups, can be static for static popups.
    unsigned short duration;    // Duration of the popup in seconds
} SafeViewOSDPopupDataType;

/*************************************************************************************
    Function:   SafeViewOSDCb (function type)
    Params:     type: type of received OSD event.
                param: data of the event (depends on the type of event; can be NULL
                for certain event types).
    Return:     SAFEVIEW_OK if the event was properly managed, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Callback type for OSD events reception.
*************************************************************************************/
typedef SafeViewResult (*SafeViewOSDCb) (SafeViewOSDEventType type,
                                         void *param);

/*************************************************************************************
    Function:   SafeViewOSDOkCb (function type)
    Params:     res: SAFEVIEW_OK if the user pressed OK, SAFEVIEW_GENERIC_ERROR
                otherwise.
    Return:     void.
    Desc:       OK dialog callback.
*************************************************************************************/
typedef void (*SafeViewOSDOkCb) (SafeViewResult res);

/*************************************************************************************
    Function:   SafeViewOSDPinCb (function type)
    Params:     password. ASCII password (PIN number) entered by the user.
    Return:     void.
    Desc:       PIN verification callback.
*************************************************************************************/
typedef void (*SafeViewOSDPinCb) (const char *password);

/*************************************************************************************
    Function:   safeview_register_osd_cb
    Params:     cb: Callback function to be registered.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       This function allows registering a callback to receive OSD events
                generated by the CAS.
*************************************************************************************/
SafeViewResult safeview_register_osd_cb (SafeViewOSDCb cb);

/*************************************************************************************
    Function:   safeview_unregister_osd_cb
    Params:     cb: Callback function to be unregistered.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       This function allows unregistering a callback to receive OSD events.
*************************************************************************************/
SafeViewResult safeview_unregister_osd_cb (SafeViewOSDCb cb);

#endif /* ifndef _SAFEVIEW_OSD_API_H_ */
