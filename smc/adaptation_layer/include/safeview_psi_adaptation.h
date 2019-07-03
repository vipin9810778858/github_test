/* $Id: safeview_psi_adaptation.h 14 2015-12-09 16:40:11Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_psi_adaptation.h
 *
 * This file defines a standard API to access PSI capabilities.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *     28/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     13/07/03    2.0 Miguel Angel González Iglesias
 *                 Added some basic types.
 *                 Added functions for register and unregister a callback for generic descriptors.
 *     01/07/04    2.2 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     04/12/06    2.3 Rafael Barriuso Maicas
 *                 Added 'safeview_get_current_channel'.
 *                 Moved PID, SID, TSID, etc types to safeview_common_types.h.
 *                 Added 'safeview_current_channel_restart'.
 *                 Moved descriptor tags definition here from 'safeview_common.h' (core)
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_PSI_ADAPTATION_H_
#define _SAFEVIEW_PSI_ADAPTATION_H_

#include "safeview_common_types.h"

#define SAFEVIEW_NO_CHANNEL                                     0
#define SAFEVIEW_NO_DEMUX                                       ((SafeViewDemuxId)-1)

#define CA_TAG                                                  0x09
#define VBI_TELETEXT_DESCRIPTOR_TAG                             0x46
#define TELETEXT_DESCRIPTOR_TAG                                 0x56
#define SUBTITLING_DESCRIPTOR_TAG                               0x59
#define AC3_DESCRIPTOR_TAG                                      0x6A
#define SAFEVIEW_DESCRIPTOR_TAG                                 0x9A
#define SAFEVIEW_PRIO_COMP_DESCRIPTOR_TAG                       0x9B
#define SAFEVIEW_PIDS_DESCRIPTOR_TAG                            0x99
#define SAFEVIEW_MOSAIC_TAG                                     0x98

/* Number of retries for the psi_cache to get the tables. Note: the psi_adaptation will try to get them forever */
#define GETTABLES_NUMBER_OF_RETRIES                             100
/* Milliseconds between table_get retry */
#define GETTABLES_WAIT_MS                                       300

/* ISO 13818-1 stream types:
   0x00 ITU-T | ISO/IEC Reserved
   0x01 ISO/IEC 11172 Video
   0x02 ITU-T Rec. H.262 | ISO/IEC 13818-2 Video or ISO/IEC 11172-2 constrained parameter video stream
   0x03 ISO/IEC 11172 Audio
   0x04 ISO/IEC 13818-3 Audio
   0x05 ITU-T Rec. H.222.0 | ISO/IEC 13818-1 private_sections
   0x06 ITU-T Rec. H.222.0 | ISO/IEC 13818-1 PES packets containing private data
   0x07 ISO/IEC 13522 MHEG
   0x08 ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A DSM CC
   0x09 ITU-T Rec. H.222.1
   0x0A ISO/IEC 13818-6 type A
   0x0B ISO/IEC 13818-6 type B
   0x0C ISO/IEC 13818-6 type C
   0x0D ISO/IEC 13818-6 type D
   0x0E ISO/IEC 13818-1 auxiliary
   0x0F-0x7F ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved
   0x80-0xFF User Private
*/
typedef enum
{
    RESERVED = 0x00,
    VIDEO = 0x01,
    OTHER_VIDEO = 0x02,
    AUDIO = 0x03,
    OTHER_AUDIO = 0x04,
    PRIVATE_SECTIONS = 0x05,
    PES_PRIVATE_DATA_AC3 = 0x06,        /* Dolby AC3?? */
    MHEG = 0x07,
    DSMCC = 0x08,
    H_222_1 = 0x09,
    ISO13818_6_A = 0x0A,
    ISO13818_6_B = 0x0B,
    ISO13818_6_C = 0x0C,
    ISO13818_6_D = 0x0D,
    ISO13818_1_AUX = 0x0E,
    H_222_0_RESERVED = 0x0F,    // 0x0F to 0x7F
    H264_VIDEO = 0x1B,
    DCII_VIDEO = 0x80,          // User private: 0x80 to 0xFF
    AC3_AUDIO_STREAM = 0x81,
    DCII_SUBTITLES = 0x82,
    DCII_SUBTITLES_OTHER = 0x8B
} SafeViewComponentType;

/* Events can be related to mux, service, component or CAT/PMT CA descriptors */
typedef enum
{
    ANY_PSI_TYPE = 0,
    MUX_EVENT,
    SERVICE_EVENT,
    COMPONENT_EVENT,
    CAT_DESC_EVENT,
    PMT_DESC_EVENT,
    SAFEVIEW_PIDS_DESC_EVENT
} PSIEventType;

/* Event action types. A component on event means that the component has been tuned. */
/* A component off event means that the component has been deselected.               */
typedef enum
{
    ANY_ACTION = 0,
    ITEM_ON,
    ITEM_OFF,
    ITEM_UPDATE
} PSIEventAction;

/* As an example, a zapping must generate the following events in the shown order:*/
/*    - Component off (One event for each component used in the service)          */
/*    - Service off                                                               */
/*    - MUX off (if the mux of the new service is different from the current one) */
/*    - MUX on  (if the mux of the new service is different from the current one) */
/*    - Service on                                                                */
/*    - Component on (One event for each component used in the service)           */
/* Additionally, a new PMT or CAT CA descriptor on event must be generated each   */
/* time a new CA descriptor is found in the corresponding table                   */

/*************************************************************************************
    Function:   PSICb (function type)
    Params:     eventType: MUX, Service or Component event.
                demux_id: Demux Id.
                onid: Original network id.
                tsid: Transport stream id.
                sid: Service id. 0 if is a MUX event
                component_pid: Component pid. 0 if it is a SERVICE or MUX event.
                component_type: Component type. 0 if it is a SERVICE or MUX event.
                component_track: Component track. 0 if it is a SERVICE or MUX event.
                action: If is an ON event or an OFF event.
    Return:     No return value.
    Desc:       Callback called for each PSI event.
*************************************************************************************/
typedef void (*PSICb) (PSIEventType eventType,
                       SafeViewDemuxId demux_id,
                       SafeViewOnid onid,
                       SafeViewTsid tsid,
                       SafeViewSid sid,
                       SafeViewPID component_pid,
                       SafeViewComponentType component_type,
                       SafeViewComponentTrack component_track,
                       PSIEventAction action);

/*************************************************************************************
    Function:   NewDescCb (function type)
    Params:     eventType: PMT or CAT descriptor.
                demux_id: Demux Id.
                onid: Original network id.
                tsid: Transport stream id.
                sid: Service id. 0 if is a MUX event
                component_pid: Component pid. 0 if it is a SERVICE or MUX event.
                descriptor: Descriptor received (Including tag and length).
    Return:     No return value.
    Desc:       Callback called for each CA descriptor event.
*************************************************************************************/
typedef void (*NewDescCb) (PSIEventType eventType,
                           SafeViewDemuxId demux_id,
                           SafeViewOnid onid,
                           SafeViewTsid tsid,
                           SafeViewSid sid,
                           SafeViewPID component_pid,
                           unsigned char *descriptor);

/*************************************************************************************
    Function:   safeview_init_psi_adaptation
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes the PSI adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_psi_adaptation (void);

/*************************************************************************************
    Function:   safeview_start_psi_adaptation
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Starts the PSI adaptation layer.
*************************************************************************************/
SafeViewResult safeview_start_psi_adaptation (void);

/*************************************************************************************
    Function:   safeview_registerPSICb
    Params:     demux_id: Demux Id.
                psi_callback: Function to be called for each new PSI event.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers PSI callback.
*************************************************************************************/
SafeViewResult safeview_registerPSICb (SafeViewDemuxId demux_id,
                                       PSICb psi_callback);

/*************************************************************************************
    Function:   safeview_unregisterPSICb
    Params:     demux_id: Demux Id.
                psi_callback: Function to be called for each new PSI event.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Unregisters a PSI callback.
*************************************************************************************/
SafeViewResult safeview_unregisterPSICb (SafeViewDemuxId demux_id,
                                         PSICb psi_callback);

/*************************************************************************************
    Function:   safeview_registerDescCb
    Params:     tag: Tag to look for.
                demux_id: Demux Id.
                eventType: PMT or CAT descriptor.
                onid: Original network id.
                tsid: Transport stream id.
                sid: Service id. 0 if CAT descriptor.
                component_pid: Component PID. 0 if Service  or CAT descriptor.
                safeview_ca_desc_manager: Function to be called for each new CA descriptor event.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers CADesc callback.
*************************************************************************************/
SafeViewResult safeview_registerDescCb (unsigned char tag,
                                        SafeViewDemuxId demux_id,
                                        PSIEventType eventType,
                                        SafeViewOnid onid,
                                        SafeViewTsid tsid,
                                        SafeViewSid sid,
                                        SafeViewPID component_pid,
                                        NewDescCb safeview_desc_manager);

/*************************************************************************************
    Function:   safeview_unregisterDescCb
    Params:     tag: Tag to llok for.
                demux_id: Demux Id.
                eventType: PMT or CAT descriptor.
                onid: Original network id.
                tsid: Transport stream id.
                sid: Service id. 0 if CAT descriptor.
                component_pid: Component PID. 0 if Service  or CAT descriptor.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Unregisters CADesc callback.
*************************************************************************************/
SafeViewResult safeview_unregisterDescCb (unsigned char tag,
                                          SafeViewDemuxId demux_id,
                                          PSIEventType eventType,
                                          SafeViewOnid onid,
                                          SafeViewTsid tsid,
                                          SafeViewSid sid,
                                          SafeViewPID component_pid);

/*************************************************************************************
    Function:   safeview_get_current_channel
    Params:     demux: Pointer to where store the current demux id.
                freq: Pointer to where store the currently tuned frequency.
                ch: Pointer to where store the currently tuned SID.
    Return:     None.
    Desc:       This function returns the channel number currently tuned in the demux.
*************************************************************************************/
void safeview_get_current_channel (SafeViewDemuxId * demux, int *freq,
                                   SafeViewSid * ch);

#endif /* ifndef _SAFEVIEW_PSI_ADAPTATION_H_ */
