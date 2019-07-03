/* $Id: safeview_debug_api.h 14 2015-12-09 16:40:11Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_debug_api.h
 *
 * This file defines functions to  get debugging information about the
 * state of the software.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *      06/04/09        1.0     Rafael Barriuso Maicas
 * - First release
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_DEBUG_API_H_
#define _SAFEVIEW_DEBUG_API_H_

#include "safeview_config.h"
#include "safeview_common_types.h"

//TODO: documentar todo

#if SAFEVIEW_DEBUG_INFO

int safeview_debug_get_unused_descramblers (void);      /* core */
int safeview_debug_get_rights_status (void);    /* core */
int safeview_debug_get_smc_status (void);       /* core */
void *safeview_debug_get_components (void);     /* core */
void *safeview_debug_get_emm_channels (void);   /* core */
int safeview_debug_get_current_ecm_pid (void);  /* core */
int safeview_debug_get_current_emm_pid (void);  /* core */
void *safeview_debug_get_personal_msgs (void);  /* core */
SafeViewDate safeview_debug_last_open_date (void);      /* core */

#if SAFEVIEW_ADAPTATION_DEBUG_INFO

unsigned char *safeview_debug_get_last_cws (void);      /* descrambler adaptation */
int safeview_debug_get_open_descrablers (void); /* descrambler adaptation */
int safeview_debug_sprintf_demux_info (char *strBuff, int maxLen);      /* demux adaptation */
int safeview_debug_get_service_status (void);   /* PSI adaptation */
unsigned long safeview_debug_get_status_flags (void);   /* PSI adaptation */
void safeview_debug_get_current_channel (SafeViewDemuxId * demux, int *freq, SafeViewSid * ch); /* PSI adaptation */
int safeview_debug_get_decoder_status (void);   /* decoder adaptation */
int safeview_debug_get_allocated_memory (void); /* memory adaptation */

#endif /* SAFEVIEW_ADAPTATION_DEBUG_INFO */

int safeview_debug_screen_paint (void); /* core */
int safeview_debug_screen_paint2 (void);        /* core */

#if SAFEVIEW_DEBUG_TRACE_SCREEN

SafeViewResult safeview_debug_trace_init (void);
void safeview_debug_trace_write (const char *format, ...);
int safeview_debug_screen_trace_paint (void);

#endif /* SAFEVIEW_DEBUG_TRACE_SCREEN */

#endif /* SAFEVIEW_DEBUG_INFO */

#endif /* ifndef _SAFEVIEW_DEBUG_API_H_ */
