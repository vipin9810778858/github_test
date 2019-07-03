/* $Id: safeview_common_types.h 14 2015-12-09 16:40:11Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_common_types.h
 *
 * This file defines common types  used by the different APIs provided
 * by SafeView.
 *
 * History:
 *     28/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     03/06/03    2.0 Miguel Angel González Iglesias
 *                 Added SafeViewCAId and SafeViewEMMVersion types.
 *                 Added type for blocking type.
 *                 Added type for event managing.
 *                 Added type for ECM length.
 *     29/07/03    2.1 Miguel Angel González Iglesias
 *                 SafeViewPoints is an unsigned short instead of short.
 *     01/07/04    2.2 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     18/01/07    2.3 Rafael Barriuso Maicas
 *                 Added PID, SID, TSID, etc types.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_COMMON_TYPES_H_
#define _SAFEVIEW_COMMON_TYPES_H_

/* Common return constants */
#define SAFEVIEW_OK                                             0
#define SAFEVIEW_GENERIC_ERROR                                  (-1)
#define SAFEVIEW_NO_SMARTCARD_INSERTED                          (-2)
#define SAFEVIEW_NO_SUCH_WALLET                                 (-3)
#define SAFEVIEW_NO_SUCH_REGISTRY                               (-4)
#define SAFEVIEW_NO_SUCH_PURCHASE                               (-5)
#define SAFEVIEW_NO_VALID_PIN                                   (-6)
#define SAFEVIEW_NO_MEMORY_AVAILABLE                            (-7)
#define SAFEVIEW_NO_EVENT_MANAGED                               0       /* Returned by safeview_manage_event */
#define SAFEVIEW_EVENT_MANAGED                                  1

typedef enum
{
    SAFEVIEW_FALSE = 0,
    SAFEVIEW_TRUE = 1
} SafeViewBoolean;

/* Blocking type mode for the mainloop */
typedef enum
{
    SAFEVIEW_BLOCKING_MODE = 0,
    SAFEVIEW_NON_BLOCKING_MODE = 1
} SafeViewBlockingType;

/* Common return type */
typedef int SafeViewResult;



/* Common types */
typedef unsigned char SafeViewDemuxId;
typedef unsigned short SafeViewOnid;
typedef unsigned short SafeViewTsid;
typedef unsigned long SafeViewSid;
typedef unsigned long SafeViewComponentTrack;
typedef unsigned short SafeViewPID;

typedef unsigned short SafeViewPoints;
typedef unsigned char SafeViewPurchaseLength;
typedef unsigned char SafeViewEcmLength;
typedef unsigned char SafeViewEmmLength;
typedef unsigned long SafeViewDate;


typedef int SafeViewSlotId;


typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;
typedef unsigned long long int u8;
typedef char s1;
typedef short s2;
typedef int s4;
typedef long long int s8;

/* Check,  at compilation  time,  if  sizes for  this  machine are  as
 * expected */
typedef char myAssertA[(sizeof (u1) == 1) ? 2 : -1];    //Error if sizeof(u1) != 1
typedef char myAssertB[(sizeof (u2) == 2) ? 2 : -1];    //Error if sizeof(u2) != 2
typedef char myAssertC[(sizeof (u4) == 4) ? 2 : -1];    //Error if sizeof(u4) != 4
typedef char myAssertD[(sizeof (u8) == 8) ? 2 : -1];    //Error if sizeof(u8) != 8
typedef char myAssertE[(sizeof (s1) == 1) ? 2 : -1];    //Error if sizeof(s1) != 1
typedef char myAssertF[(sizeof (s2) == 2) ? 2 : -1];    //Error if sizeof(s2) != 2
typedef char myAssertG[(sizeof (s4) == 4) ? 2 : -1];    //Error if sizeof(s4) != 4
typedef char myAssertH[(sizeof (s8) == 8) ? 2 : -1];    //Error if sizeof(s8) != 8
typedef char myAssertI[(sizeof (unsigned long) == 4) ? 2 : -1]; //Error if sizeof(unsigned long) != 4
typedef char myAssertJ[(sizeof (unsigned long int) == 4) ? 2 : -1];     //Error if sizeof(unsigned long int) != 4
typedef char myAssertK[(sizeof (long) == 4) ? 2 : -1];  //Error if sizeof(long) != 4
typedef char myAssertL[(sizeof (long int) == 4) ? 2 : -1];      //Error if sizeof(long int) != 4
typedef char myAssertM[(sizeof (SafeViewBoolean) == 4) ? 2 : -1];       //Error if sizeof(enumeration) != 4

#endif /* ifndef _SAFEVIEW_COMMON_TYPES_H_ */
