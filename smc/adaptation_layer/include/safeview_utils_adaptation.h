/* $Id: safeview_utils_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_utils_adaptation.h
 *
 * This file defines common types  used by the different APIs provided
 * by SafeView.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *     28/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     03/06/03    2.0 Miguel Angel González Iglesias
 *                 New function for retrieving the current date.
 *     01/07/04    2.2 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     28/12/06    2.3 Rafael Barriuso Maicas
 *                 Added function 'safeview_strcpy'.
 *                 Added function 'safeview_get_date_hour_string'.
 *                 Added function 'safeview_get_date_string'.
 *                 Added function 'safeview_start_timer'.
 *                 Added function 'safeview_stop_timer'.
 *                 Added function 'safeview_get_hour_string'.
 *                 Added endianness-related macros.
 *                 Added function 'safeview_get_hour_minute'.
 *                 Added definition of 'SAFEVIEW_DATE_OFFSET'.
 *                 Added functions 'safeview_start_time_measure', 'safeview_stop_time_measure(void)',
 *                 'safeview_get_time_measure', 'safeview_print_time_measure'.
 *                 Added function 'safeview_get_random_number'.
 *                 Added funcition 'safeview_get_date_dayname_string'.
 *     25/05/09    Moved string date functions to core ('safeview_get_hour_minute', 'safeview_get_date_hour_string',
 *                 'safeview_get_date_string', 'safeview_get_date_dayname_string', 'safeview_get_hour_string'.
 *     23/09/09    Added 'safeview_get_stb_id'.
 *     09/07/10    3.0 Rafael Barriuso Maicas
 *                 Adapted code for IPTV.
 *     26/01/12    Moved STB functionalities to a separate adaptation header.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_UTILS_ADAPTATION_H_
#define _SAFEVIEW_UTILS_ADAPTATION_H_

#include "safeview_common_types.h"
#include "safeview_config_adaptation.h"

/* Mon, 31 Dec 2001 23:00:00 GMT */
#define SAFEVIEW_DATE_OFFSET                                    1009839600

/* Macros for endianness management (SMC and air data are big endian) */

#ifndef SAFEVIEW_STB_CHIP_ENDIANNESS

#error No chipset endianness defined!

#endif //#ifndef SAFEVIEW_STB_CHIP_ENDIANNESS

#if SAFEVIEW_STB_CHIP_ENDIANNESS == SAFEVIEW_LITTLE_ENDIAN

#define safeview_get_unsigned_short(x)                          (unsigned short)safeview_get_u2_big_to_little((unsigned char*)x)
#define safeview_get_unsigned_long(x)                           (unsigned long)safeview_get_u4_big_to_little((unsigned char*)x)
#define safeview_set_unsigned_short(x,y)                        safeview_set_u2_little_to_big(x, y)
#define safeview_set_unsigned_long(x,y)                         safeview_set_u4_little_to_big(x, y)

#elif SAFEVIEW_STB_CHIP_ENDIANNESS == SAFEVIEW_BIG_ENDIAN

#define safeview_get_unsigned_short(x)                          (*(unsigned short*)x)
#define safeview_get_unsigned_long(x)                           (*(unsigned long*)x)
#define safeview_set_unsigned_short(x,y)                        *(unsigned short*)y = (unsigned short)x;
#define safeview_set_unsigned_long(x,y)                         *(unsigned long*)y = (unsigned long)x;

#else //#if SAFEVIEW_STB_CHIP_ENDIANNESS == SAFEVIEW_LITTLE_ENDIAN

#error Wrong endianness defined!

#endif //#if SAFEVIEW_STB_CHIP_ENDIANNESS == SAFEVIEW_LITTLE_ENDIAN

#define safeview_get_u2_big_to_little(x)        \
    ((((unsigned short)(*(x))) << 8) |          \
     ((unsigned short)(*(x+1))))

#define safeview_get_u4_big_to_little(x)        \
    ((((unsigned long)(*(x)))<<24) +            \
     (((unsigned long)(*(x+1)))<<16) +          \
     (((unsigned long)(*(x+2)))<<8)+            \
     ((unsigned long)(*(x+3))))

#define safeview_set_u4_little_to_big(x,y)                      \
    *(unsigned char*)(y)     = *((unsigned char*)&(x)+3);       \
    *((unsigned char*)(y)+1) = *((unsigned char*)&(x)+2);       \
    *((unsigned char*)(y)+2) = *((unsigned char*)&(x)+1);       \
    *((unsigned char*)(y)+3) = *(unsigned char*)&(x)

#define safeview_set_u2_little_to_big(x,y)                      \
    *(unsigned char*)(y)     = *((unsigned char*)&(x)+1);       \
    *((unsigned char*)(y)+1) = *(unsigned char*)&(x)

typedef struct
{
    int tm_sec;                 /* seconds after the minute, 0 to 60
                                   (0 - 60 allows for the occasional leap second) */
    int tm_min;                 /* minutes after the hour, 0 to 59 */
    int tm_hour;                /* hours since midnight, 0 to 23 */
    int tm_mday;                /* day of the month, 1 to 31 */
    int tm_mon;                 /* months since January, 0 to 11 */
    int tm_year;                /* years since 1900 */
    int tm_wday;                /* days since Sunday, 0 to 6 */
    int tm_yday;                /* days since January 1, 0 to 365 */
    int tm_isdst;               /* Daylight Savings Time flag */
} SafeViewTmDate;

/*************************************************************************************
    Function:   SafeViewTimerCb
    Params:     data: data registered.
    Return:     No return value.
    Desc:       Callback called when the timer is reached.
*************************************************************************************/
typedef void (*SafeViewTimerCb) (void *data);

/*************************************************************************************
    Function:   safeview_sleep
    Params:     msecs: Milliseconds to wait.
    Return:     No return value.
    Desc:       Sleeps msecs milliseconds.
*************************************************************************************/
void safeview_sleep (unsigned int msecs);

/*************************************************************************************
    Function:   safeview_get_date
    Params:     No params.
    Return:     Current UTC date.
    Desc:       Returns the current UTC date. Similar to ANSI C time().
*************************************************************************************/
SafeViewDate safeview_get_date (void);

/*************************************************************************************
   Function:    safeview_localtime
   Params:      time: time in safeview_get_date() format
                resultingTmDate: pointer to an allocated SafeViewTmDate where the
                result will be stored.
   Return:      SAFEVIEW_OK if ok, SAFEVIEW_GENERIC_ERROR if the conversion
                couldn't be made.
   Desc:        Converts a SafeViewDate to a SafeViewTmDate containing the local
                time. Similar to ANSI C localtime().
*************************************************************************************/
SafeViewResult safeview_localtime (SafeViewDate time,
                                   SafeViewTmDate * resultingTmDate);

/*************************************************************************************
    Function:   safeview_memcpy
    Params:     dest: Destination buffer.
                orig: Origin buffer.
                len: Bytes to copy.
    Return:     No return value.
    Desc:       Copies a string.
*************************************************************************************/
void safeview_memcpy (void *dest, const void *src, unsigned int len);

/*************************************************************************************
    Function:   safeview_memset
    Params:     dest: Destination buffer.
                c: Character.
                len: Bytes to set.
    Return:     No return value.
    Desc:       Sets a string to a value.
*************************************************************************************/
void *safeview_memset (void *dest, int c, unsigned int len);

/*************************************************************************************
    Function:   safeview_memcmp
    Params:     buf1: First buffer.
                buf2: Second buffer.
                len: Bytes to compare.
    Return:     No return value.
    Desc:       Compares a string.
*************************************************************************************/
int safeview_memcmp (const void *buf1, const void *buf2, unsigned int len);

/*************************************************************************************
    Function:   safeview_strcpy
    Params:     dest: Destination string.
                src: Source string.
    Return:     Returns dest.
    Desc:       Copies a string to another.
*************************************************************************************/
char *safeview_strcpy (char *dest, const char *src);

/*************************************************************************************
    Function:   safeview_start_timer
    Params:     timer_id: id of the timer (between 0 and SAFEVIEW_MAX_NUM_TIMERS)
                cb: Callback to call when the timer is reached.
                time: Milliseconds to wait for the timer.
                data: Generic data that is passed in the callback.
    Return:     SAFEVIEW_OK if success, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Starts a timer that should call the cb function when reached.
                The callback is only called once per call to this function
                (one-shot timers).
                The implementation must allow calling this function from the
                callback function of the timer itself.
*************************************************************************************/
SafeViewResult safeview_start_timer (unsigned int timer_id,
                                     SafeViewTimerCb cb, int time,
                                     void *data);

/*************************************************************************************
    Function:   safeview_stop_timer
    Params:     timer_id: id of the timer to stop
                cb: Callback to call when the timer is reached.
                time: Time to wait for the timer.
                data: Generic data that is passed in the callback.
    Return:     SAFEVIEW_OK if success, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Stops the timer. Once this function is called, the callback function
                must not be called.
*************************************************************************************/
SafeViewResult safeview_stop_timer (unsigned int timer_id, SafeViewTimerCb cb,
                                    int time, void *data);

/*************************************************************************************
    Function:   safeview_get_random_number
    Params:     result: 8 byte unsigned char array to store the result
    Return:     None.
    Desc:       Generates a (pseudo-)random number of 8 bytes
*************************************************************************************/
void safeview_get_random_number (unsigned char *result);

/*************************************************************************************
    Function:   safeview_utils_local_time_offset_get
    Params:     None.
    Return:     int with the local time offset in seconds. Positive if UTC+X (East
                from Greenwich). Negative if UTC-X (West from Greenwich).
    Desc:       Gets the current local time offset from the STB.
*************************************************************************************/
int safeview_utils_local_time_offset_get (void);

/*************************************************************************************
    Function:   safeview_utils_task_register
    Params:     threadName: char* with the thread name.
                priority: unsigned int with the priority. The lower priority value,
                the less priority the thread should have.
                pTaskFunction: Function to call when starting the new thread.
                pParam: void* parameter to pass when calling pTaskFunction.
                stackSize: unsigned int with the stack size the thread should have.
    Return:     SAFEVIEW_OK if OK.
                SAFEVIEW_GENERIC_ERROR in case of error.
    Desc:       Registers a function to be called from a brand new thread.
*************************************************************************************/
SafeViewResult safeview_utils_task_register (char *threadName,
                                             unsigned int priority,
                                             void (*pTaskFunction) (void
                                                                    *pParam),
                                             void *pParam,
                                             unsigned int stackSize);

#endif /* ifndef _SAFEVIEW_UTILS_ADAPTATION_H_ */
