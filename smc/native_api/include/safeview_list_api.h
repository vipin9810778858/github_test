/* $Id: safeview_list_api.h 6 2015-03-20 18:09:11Z Safeview $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_list_api.h
 *
 * Generic list manager.
 *
 * History:
 *      30/01/03        1.0     Miguel Angel González Iglesias
 *      First release
 *      23/06/03        2.0     Miguel Angel González Iglesias
 *      New function to move one item to first.
 *      New function to remove last item.
 *      New function to add an item to the beginning of the list.
 *      01/07/04        2.2     Miguel Angel González Iglesias
 *      No relevant changes.
 *      28/12/06        2.3     Rafael Barriuso Maicas
 *      Added function safeview_list_add_item_in_pos to header.
 *      08/06/2015      3.0     Alejandro García Rodríguez
 *      Merging    adaptation_layer/i/safeview_list_adaptation.h   and
 *      core/i/safeview_list.h   to   native_api/i/safeview_list_api.h
 *      because module is implemented and can be offered to the client
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_LIST_API_H_
#define _SAFEVIEW_LIST_API_H_

#include "safeview_common_types.h"
#include "safeview_lock_adaptation.h"

typedef struct _SafeViewListItem
{
    struct _SafeViewListItem *next;
    struct _SafeViewListItem *prev;
    void *event_data;
} SafeViewListItem;

typedef struct
{
    SafeViewListItem *head;
    SafeViewListItem *tail;
    SafeViewLock lock;
    unsigned short items;
} SafeViewList;

/*************************************************************************************
    Function:   safeview_list_create
    Params:     No params.
    Return:     Returns the new list created, or NULL if error.
    Desc:       Creates a new generic list.
*************************************************************************************/
SafeViewList *safeview_list_create (void);

/*************************************************************************************
    Function:   safeview_list_create_without_lock
    Params:     No params.
    Return:     Returns the new list created, or 0 if error.
    Desc:       Creates  a new  generic  list,  without an  associated
                lock.
*************************************************************************************/
SafeViewList *safeview_list_create_without_lock (void);

/*************************************************************************************
    Function:   safeview_list_remove
    Params:     list: List to remove.
    Return:     Returns the new list created, or NULL if error.
    Desc:       Creates a new generic list.
*************************************************************************************/
void safeview_list_remove (SafeViewList * list);

/*************************************************************************************
    Function:   safeview_list_add_item
    Params:     list: Generic list.
                item: Generic list item.
    Return:     No return value.
    Desc:       Inserts a new item at the end of the list.
*************************************************************************************/
void safeview_list_add_item (SafeViewList * list, SafeViewListItem * item);

/*************************************************************************************
    Function:   safeview_list_add_first_item
    Params:     list: Generic list.
                item: Generic list item.
    Return:     No return value.
    Desc:       Inserts a new item at the beginning of the list.
*************************************************************************************/
void safeview_list_add_first_item (SafeViewList * list,
                                   SafeViewListItem * item);

/*************************************************************************************
    Function:   safeview_list_add_item_in_pos
    Params:     list: Generic list.
                item: Generic item.
    Return:     No return value.
    Desc:       Inserts a new item in a specific position of the list.
*************************************************************************************/
void safeview_list_add_item_in_pos (SafeViewList * list,
                                    SafeViewListItem * item_pos,
                                    SafeViewListItem * item);

/*************************************************************************************
    Function:   safeview_list_remove_first_item
    Params:     list: Generic list.
    Return:     The first item in the list.
    Desc:       Returns the first event in the list. This item is also
                deleted from the list.
*************************************************************************************/
SafeViewListItem *safeview_list_remove_first_item (SafeViewList * list);

/*************************************************************************************
    Function:   safeview_list_remove_last_item
    Params:     list: Generic list.
    Return:     No return value.
    Desc:       Returns the last event in  the list. This item is also
                deleted from the list.
*************************************************************************************/
SafeViewListItem *safeview_list_remove_last_item (SafeViewList * list);

/*************************************************************************************
    Function:   safeview_list_lock
    Params:     list: Generic list.
    Return:     No return value.
    Desc:       Locks the list.
*************************************************************************************/
void safeview_list_lock (SafeViewList * list);

/*************************************************************************************
    Function:   safeview_list_unlock
    Params:     queue: Generic list.
    Return:     No return value.
    Desc:       Unlocks the list.
*************************************************************************************/
void safeview_list_unlock (SafeViewList * list);

/*************************************************************************************
    Function:   safeview_list_remove_item
    Params:     list: Generic list.
                item: Generic list item.
    Return:     No return value.
    Desc:       Removes the item from the queue.
*************************************************************************************/
void safeview_list_remove_item (SafeViewList * list, SafeViewListItem * item);

/*************************************************************************************
    Function:   safeview_list_remove_and_get_next_item
    Params:     list: Generic list.
                item: Generic list item.
    Return:     Next item in the list.
    Desc:       Removes the item from the  queue, and gets a reference
                of the next one.
*************************************************************************************/
SafeViewListItem *safeview_list_remove_and_get_next_item (SafeViewList * list,
                                                          SafeViewListItem *
                                                          item);

/*************************************************************************************
    Function:   safeview_list_move_to_first
    Params:     list: Generic list.
                item: Generic list item.
    Return:     No return value.
    Desc:       Removes the item from the queue.
*************************************************************************************/
void safeview_list_move_to_first (SafeViewList * list,
                                  SafeViewListItem * item);

/*************************************************************************************
    Function:   safeview_list_empty_and_remove
    Params:     list: Generic list.
    Return:     No return value.
    Desc:       Empties and  removes a  generic list. Note  that items
                should not have allocated pointers (except, obviously,
                next  and prev)  or they  should have  been previously
                freed.
*************************************************************************************/
void safeview_list_empty_and_remove (SafeViewList * list);

/*************************************************************************************
    Function:   safeview_list_empty
    Params:     list: Generic list.
    Return:     No return value.
    Desc:       Empties  a generic  list. Note  that items  should not
                have allocated  pointers (except, obviously,  next and
                prev) or they should have been previously freed.
*************************************************************************************/
void safeview_list_empty (SafeViewList * list);

#endif /* ifndef _SAFEVIEW_LIST_API_H_ */
