/* $Id: safeview_descrambler_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_descrambler_adaptation.h
 *
 * This   file  defines   a   standard  API   to  access   descrambler
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
 *      08/05/08        2.3     Rafael Barriuso Maicas
 * - Added 'safeview_init_descrambler_adaptation'.
 *      14/07/10        3.0     Rafael Barriuso Maicas
 * - Adapted source code for IPTV CAS.
 *      20/10/15        3.1     Alejandro García Rodríguez
 * - Adding support to different scrambler modes.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_DESCRAMBLER_ADAPTATION_H_
#define _SAFEVIEW_DESCRAMBLER_ADAPTATION_H_

#include "safeview_common_types.h"
#include "safeview_psi_adaptation.h"    /* SafeViewComponentType */

#define SAFEVIEW_NO_DESCRAMBLER                                 ( (SafeViewDescramblerHandler)(-1) )

/*
 * SV_AS_LEVEL_KCHIP: Level  where KCHIP is used  for decryption. This
 * is the only level in 2ladder mode.
 * SV_AS_LEVEL_NO_KCHIP: Level  which is NOT  where KCHIP is  used for
 * decryption. This level is only used in 3ladder mode.
 * Note:
 * -2ladder mode uses only SV_AS_LEVEL_KCHIP.
 * -3ladder mode uses SV_AS_LEVEL_KCHIP and SV_AS_LEVEL_NO_KCHIP.
 */
typedef enum _SafeViewAdvSecKeyLadderLevel
{
    SV_AS_LEVEL_KCHIP = 0,
    SV_AS_LEVEL_NO_KCHIP = 1
} SafeViewAdvSecKeyLadderLevel;

typedef enum _SafeViewAdvSecAlgorithm
{
    SV_AS_ALGORITHM_TDES = 0,
    SV_AS_ALGORITHM_AES = 1
} SafeViewAdvSecAlgorithm;

typedef enum _SafeViewAdvSecLadderMode
{
    SV_AS_LADDER_MODE_NONE = 1,
    SV_AS_LADDER_MODE_2 = 2,
    SV_AS_LADDER_MODE_3 = 3
} SafeViewAdvSecLadderMode;

typedef enum _SafeViewAdvSecEnable
{
    SV_AS_DISABLE = 0,
    SV_AS_ENABLE = 1
} SafeViewAdvSecEnable;

typedef enum _SafeViewScramblerMode
{
    SV_SCRAMBLER_MODE_CSA2 = 0,
    SV_SCRAMBLER_MODE_CSA3 = 1,
    SV_SCRAMBLER_MODE_AESECB = 2
} SafeViewScramblerMode;

/* typedef void *SafeViewDescramblerHandler; */
typedef unsigned int SafeViewDescramblerHandler;

/*************************************************************************************
    Function:   safeview_init_descrambler_adaptation
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes the descrambler adaptation layer.
*************************************************************************************/
SafeViewResult safeview_init_descrambler_adaptation (void);

/*************************************************************************************
    Function:   safeview_end_descrambler_adaptation
    Params:     None
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       This function releases all the resources allocated by the descrambler.
*************************************************************************************/
SafeViewResult safeview_end_descrambler_adaptation (void);

/*************************************************************************************
    Function:   safeview_descrambler_open
    Params:     demux_id: Demux ID the descrambler is attached to
                type: Component type.
                enable: Whether the Advance Security is being used or not
                scramblerMode: Type of the scrambler protocol
    Return:     The descrambler handler if OK, SAFEVIEW_NO_DESCRAMBLER if error.
    Desc:       Opens a descrambler.
*************************************************************************************/
SafeViewDescramblerHandler safeview_descrambler_open (SafeViewDemuxId
                                                      demux_id,
                                                      SafeViewComponentType
                                                      type,
                                                      SafeViewAdvSecEnable
                                                      enable,
                                                      SafeViewScramblerMode
                                                      scramblerMode);

/*************************************************************************************
    Function:   safeview_descrambler_session_key_set
    Params:     handler: Descrambler handler.
                sessionKeys: Session key information.
                sessionKeysSize: Size of session keys.
                ladderLevel: Ladder level in secure chip where sessionKeys has to be set.
                algorithm: Decryption algorithm to use in secure chip.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets session keys.
*************************************************************************************/
SafeViewResult
safeview_descrambler_session_key_set (SafeViewDescramblerHandler handler,
                                      void *sessionKeys,
                                      unsigned int sessionKeysSize,
                                      SafeViewAdvSecKeyLadderLevel
                                      ladderLevel,
                                      SafeViewAdvSecAlgorithm algorithm);

/*************************************************************************************
    Function:   safeview_descrambler_close
    Params:     handler: Descrambler identifier.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Closes a descrambler.
*************************************************************************************/
SafeViewResult safeview_descrambler_close (SafeViewDescramblerHandler
                                           handler);

/*************************************************************************************
    Function:   safeview_descrambler_set_pid
    Params:     handler: Descrambler identifier.
                pid: PID to set to the descrambler.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets the PID of a descrambler.
*************************************************************************************/
SafeViewResult safeview_descrambler_set_pid (SafeViewDescramblerHandler
                                             handler, SafeViewPID pid);

/*************************************************************************************
    Function:   safeview_descrambler_set_CWs
    Params:     handler: Descrambler identifier.
                odd_CW: Odd CW.
                even_CW: Even CW.
                CW_length: CW length.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets the CWs of a descrambler.
*************************************************************************************/
SafeViewResult safeview_descrambler_set_CWs (SafeViewDescramblerHandler
                                             handler, unsigned char *odd_CW,
                                             unsigned char *even_CW,
                                             unsigned char CW_length);

/*************************************************************************************
    Function:   safeview_descrambler_ladder_mode_set
    Params:     ladderMode: Ladder mode (2ladder/3ladder) to configure secure chip.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Sets the desired ladder mode (2ladder/3ladder) in secure chip.
*************************************************************************************/
SafeViewResult safeview_descrambler_ladder_mode_set (SafeViewAdvSecLadderMode
                                                     ladderMode);

#endif /* ifndef _SAFEVIEW_DESCRAMBLER_ADAPTATION_H_ */
