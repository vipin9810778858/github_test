/* $Id: safeview_memory_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_memory_adaptation.h
 *
 * This file defines a standard API to access memory capabilities.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *     03/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     13/07/03    2.0 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     01/07/04    2.2 Miguel Angel González Iglesias
 *                 No relevant changes.
 *     14/07/10    3.0 Rafael Barriuso Maicas
 *                 Adapted source code for IPTV CAS.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_MEMORY_ADAPTATION_H_
#define _SAFEVIEW_MEMORY_ADAPTATION_H_

#include "safeview_common_types.h"

/*************************************************************************************
    Function:   safeview_malloc
    Params:     size: Memory size asked for.
    Return:     The pointer to the allocated memory, 0 if no memoy available.
    Desc:       Allocates memory.
*************************************************************************************/
void *safeview_malloc (unsigned int size);

/*************************************************************************************
    Function:   safeview_free
    Params:     data: Data to free.
    Return:     No return vaue.
    Desc:       Frees a previous allocated memory.
*************************************************************************************/
void safeview_free (void *data);

#endif /* ifndef _SAFEVIEW_MEMORY_ADAPTATION_H_ */
