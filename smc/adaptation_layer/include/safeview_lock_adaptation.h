/* $Id: safeview_lock_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_lock_adaptation.h
 *
 * This file defines a standard API to access lock capabilities.
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

#ifndef _SAFEVIEW_LOCK_ADAPTATION_H_
#define _SAFEVIEW_LOCK_ADAPTATION_H_

#include "safeview_common_types.h"

typedef void *SafeViewLock;

/*************************************************************************************
    Function:   safeview_lock_create
    Params:     None.
    Return:     Returns the lock created.
    Desc:       Creates a new lock.
*************************************************************************************/
SafeViewLock safeview_lock_create (void);

/*************************************************************************************
    Function:   safeview_lock_remove
    Params:     Lock to remove.
    Return:     No return value.
    Desc:       Removes the lock.
*************************************************************************************/
void safeview_lock_remove (SafeViewLock lock);

/*************************************************************************************
    Function:   safeview_lock_lock
    Params:     Lock.
    Return:     No return vaue.
    Desc:       Locks.
*************************************************************************************/
void safeview_lock_lock (SafeViewLock lock);

/*************************************************************************************
    Function:   safeview_lock_unlock
    Params:     Lock.
    Return:     No return vaue.
    Desc:       Unlocks.
*************************************************************************************/
void safeview_lock_unlock (SafeViewLock lock);

#endif /* ifndef _SAFEVIEW_LOCK_ADAPTATION_H_ */
