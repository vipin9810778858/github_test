/* $Id: safeview_ad_banner_api.h 11 2015-09-30 12:46:14Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_ad_api.h
 *
 * Definition of basic SafeView native API.
 *
 * History:
 *     18/06/12    1.0 Miguel Angel González Iglesias
 *                 First release
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_AD_BANNER_API_H_
#define _SAFEVIEW_AD_BANNER_API_H_

#include "safeview_common_types.h"

typedef enum
{
    SAFEVIEW_MINIGUIDE_AD_TYPE = 0,
    SAFEVIEW_EPG_AD_TYPE = 1
} SafeViewAdType;

/*************************************************************************************
    Function:   safeview_get_ad_banner_image
    Params:     type: Ad banner type.
                onid: Original network id ot the service tuned.
                tsid: Transport stream id ot the service tuned.
                sid:  Service id ot the service tuned.
    Return:     Pointer to the image stored. NULL if the image is not in the system yet.
    Desc:       This function searches in the image list to find a image to be displayed
                in one specific ad banner position. The image is in PNG format.
*************************************************************************************/
unsigned char *safeview_get_ad_banner_image (SafeViewAdType type,
                                             SafeViewOnid onid,
                                             SafeViewTsid tsid,
                                             SafeViewSid sid);

#endif /* ifndef _SAFEVIEW_BASIC_API_H_ */
