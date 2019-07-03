/* $Id: safeview_demux_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_demux_adaptation.h
 *
 * This  file   defines  a  standard   API  to  access   demux  driver
 * capabilities.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *      28/01/03        1.0     Miguel Angel González Iglesias
 * - First release
 *      13/07/03        2.0     Miguel Angel González Iglesias
 * - No relevant changes.
 *      01/07/04        2.2     Miguel Angel González Iglesias
 * - No relevant changes.
 *      04/01/07        2.3     Rafael Barriuso Maicas
 * - Added 'restart' argument to 'safeview_create_new_section_handler'.
 * - Added 'safeview_stop_all_section_handlers'.
 *      16/09/09        2.4     Rafael Barriuso Maicas
 * - Added 'safeview_remove_section_handler' to free demux resources.
 * - Removed 'safeview_stop_all_section_handlers'.
 *      14/07/10        3.0     Rafael Barriuso Maicas
 * - Adapted source code for IPTV CAS.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_DEMUX_ADAPTATION_H_
#define _SAFEVIEW_DEMUX_ADAPTATION_H_

#include "safeview_common_types.h"

#define SAFEVIEW_MAX_SECTION_FILTER_LENGTH                      8

typedef void *SafeViewDemuxHandlerId;   /* Generic demux handler identifier */
typedef void *SafeViewDemuxFilterId;    /* Generic demux filter identifier  */

/* Stream type to be demultiplexed */
typedef enum
{
    SAFEVIEW_SECTION_STREAM,
    SAFEVIEW_ECM_STREAM,
    SAFEVIEW_EMM_STREAM
} SafeViewDemuxStreamType;

/* The following struct defines the filter  to be applied in the demux
 * section handler */
typedef struct
{
    SafeViewDemuxFilterId id;   /* Filter identifier */
    unsigned char value[SAFEVIEW_MAX_SECTION_FILTER_LENGTH];    /* Filter value */
    unsigned char mask[SAFEVIEW_MAX_SECTION_FILTER_LENGTH];     /* Filter mask */
    unsigned char length;       /* Useful length of the filter value and mask */
} SafeViewDemuxFilter;

/*************************************************************************************
    Function:   SafeViewNewSectionCb (function type)
    Params:     handler: handler of the demux receiving the section.
                section: Section received.
                section_length: Length of the section received.
    Return:     No return value.
    Desc:       This is the callback function type that must be called by the
                manufacturer implementation for each section received.
*************************************************************************************/
typedef void (*SafeViewNewSectionCb) (SafeViewDemuxHandlerId handler,
                                      unsigned char *section,
                                      unsigned short section_length);

/*************************************************************************************
    Function:   safeview_init_demux_adaptation
    Params:     None.
    Return:     SAFEVIEW_OK OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes demux adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_demux_adaptation (void);

/*************************************************************************************
    Function:   safeview_end_demux_adaptation
    Params:     None.
    Return:     SAFEVIEW_OK OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Ends the demux adaptation layer and releases any resources allocated.
*************************************************************************************/
SafeViewResult safeview_end_demux_adaptation (void);

/*************************************************************************************
    Function:   safeview_create_new_section_handler
    Params:     demux_id: Demux hardware identifier. If more than one frontend, this
                should select the frontend demux to be used.
                num_filters: Number of filters to be allocated for this demux section
                handler.
                stream_type: SafeView stream type: Section, ECM or EMM.
                callback: Function to be called for each new section received.
                restart: Flag to indicate whether the demux should continue taking
                further sections or not.
    Return:     New demux handler identifier if OK, or 0 if error.
    Desc:       Creates a new demux handler with specific number of filters
                capabilities.
*************************************************************************************/
SafeViewDemuxHandlerId safeview_create_new_section_handler (SafeViewDemuxId
                                                            demux_id,
                                                            unsigned char
                                                            num_filters,
                                                            SafeViewDemuxStreamType
                                                            stream_type,
                                                            SafeViewNewSectionCb
                                                            callback,
                                                            SafeViewBoolean
                                                            restart);

/*************************************************************************************
    Function:   safeview_create_new_section_handler
    Params:     handler: demux handler to be removed
    Return:     SAFEVIEW_OK if successfully removed,
                SAFEVIEW_ERROR if it didn't exist or couldn't be removed.
    Desc:       Removes an existing section handler previously created with
                'safeview_create_new_section_handler'.
*************************************************************************************/
SafeViewResult safeview_remove_section_handler (SafeViewDemuxHandlerId
                                                handler);

/*************************************************************************************
    Function:   safeview_start_section_handler
    Params:     handler: Demux handler.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Starts retrieving sections.
*************************************************************************************/
SafeViewResult safeview_start_section_handler (SafeViewDemuxHandlerId
                                               handler);

/*************************************************************************************
    Function:   safeview_stop_section_handler
    Params:     handler: Demux handler.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Stops retrieving sections.
*************************************************************************************/
SafeViewResult safeview_stop_section_handler (SafeViewDemuxHandlerId handler);

/*************************************************************************************
    Function:   safeview_set_section_handler_pid
    Params:     handler: Demux handler.
                pid: PID to be set.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets a specific PID to the handler.
*************************************************************************************/
SafeViewResult safeview_set_section_handler_pid (SafeViewDemuxHandlerId
                                                 handler, SafeViewPID pid);

/*************************************************************************************
    Function:   safeview_set_section_handler_filter
    Params:     handler: Demux handler.
                filter: Filter to add to the demux handler.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets a specific filter to the handler.
*************************************************************************************/
SafeViewResult safeview_set_section_handler_filter (SafeViewDemuxHandlerId
                                                    handler,
                                                    SafeViewDemuxFilter *
                                                    filter);

/*************************************************************************************
    Function:   safeview_update_section_handler_filter
    Params:     handler: Demux handler.
                filter: Filter to be changed.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Updates a specific filter.
*************************************************************************************/
SafeViewResult safeview_update_section_handler_filter (SafeViewDemuxHandlerId
                                                       handler,
                                                       SafeViewDemuxFilter *
                                                       filter);

#endif /* ifndef _SAFEVIEW_DEMUX_ADAPTATION_H_ */
