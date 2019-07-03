/* $Id: safeview_loyalty_api.h 12 2015-09-30 15:39:33Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels.  All rights reserved.
 *
 * safeview_loyalty_api.h
 *
 * This file defines the API  that SafeView implements to offer access
 * to loyalty functionality.
 *
 * History:
 *     31/01/03    1.0 Miguel Angel González Iglesias
 *                 First release
 *     03/06/03    2.0 Miguel Angel González Iglesias
 *                 New messages format. See documentation for details.
 *                 New function to retrieve folder names.
 *                 set_emm now uses a callback to return the result.
 *                 New function to set an ecm.
 *                 Changes in wallet information. Now a wallet has a type, a value and an expiration date.
 *                 Wallet, registry and purchase lengths changed.
 *                 New functions to set messages read and removed.
 *                 Wallet hash callback now returns the phone number also.
 *     29/07/03    2.1 Miguel Angel González Iglesias
 *                 SendEMM is now supported by testcard.
 *                 New function to delay the management of EMMs for a while.
 *     29/09/03    2.2 Miguel Angel González Iglesias
 *                 The maximum alert data length has changed to 1024.
 *                 SafeViewAlertDataLength is now two bytes long then.
 *                 Points added callback Wallet parameter is WalletIndex instead of WalletId.
 *                 Added a key parameter when passing an ECM through application.
 *     20/11/07    2.3 Rafael Barriuso Maicas
 *                 Added SAFEVIEW_WALLET_TICKET to SafeViewWalletType.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_LOYALTY_API_H_
#define _SAFEVIEW_LOYALTY_API_H_

#include "safeview_common_types.h"
#include "safeview_list_api.h"
#include "safeview_config.h"

#define SAFEVIEW_MAX_ALERT_FROM_LENGTH                          128
#define SAFEVIEW_MAX_ALERT_SUBJECT_LENGTH                       128
#define SAFEVIEW_MAX_ALERT_DATA_LENGTH                          1024
#define SAFEVIEW_MAX_ALERT_ECM_LENGTH                           256
#define SAFEVIEW_MAX_WALLET_DESC_LENGTH                         256
//#define SAFEVIEW_MAX_PAYTV_NAME_LENGTH                          128
#define SAFEVIEW_MAX_PAYTV_NAME_LENGTH                          256
#define SAFEVIEW_MAX_PAYTV_DESC_LENGTH                          256
#define SAFEVIEW_MAX_PAYTV_COMMAND_LENGTH                       134
#define SAFEVIEW_MAX_REGISTRY_NAME_LENGTH                       24
#define SAFEVIEW_MAX_PURCHASE_NAME_LENGTH                       24
#define SAFEVIEW_MAX_PHONE_NUMBER_LENGTH                        9

#define SAFEVIEW_MAX_WALLET_NAME_LENGTH                         22
#define SAFEVIEW_MAX_FOLDER_NAME_LENGTH                         18
#define SAFEVIEW_MAX_WALLET_HASH_LENGTH                         30

typedef unsigned char SafeViewOperatorId;
typedef unsigned short SafeViewWalletId;
typedef unsigned char SafeViewWalletIndex;
typedef unsigned short SafeViewAlertId;
typedef unsigned char SafeViewAlertToLength;
typedef unsigned char SafeViewAlertFromLength;
typedef unsigned short SafeViewAlertDataLength;
typedef unsigned char SafeViewCampaignDescLength;
typedef unsigned char SafeViewRegistryIndex;
typedef unsigned short SafeViewWalletValue;

typedef enum
{
    SAFEVIEW_WALLET_UNDEFINED_TYPE = 0,
    SAFEVIEW_WALLET_COUPON = 1,
    SAFEVIEW_WALLET_CAMPAIGN = 2,
    SAFEVIEW_WALLET_TICKET = 3
} SafeViewWalletType;

typedef enum
{
    SAFEVIEW_NOT_KEY = 0,
    SAFEVIEW_RED_KEY = 1,
    SAFEVIEW_GREEN_KEY = 2,
    SAFEVIEW_YELLOW_KEY = 3,
    SAFEVIEW_BLUE_KEY = 4,
    SAFEVIEW_OK_KEY = 13
} SafeViewKey;

typedef enum
{
    SAFEVIEW_REGISTRY_WIN = 6,
    SAFEVIEW_REGISTRY_LOST = 7,
    SAFEVIEW_REGISTRY_PENDING = 8
} SafeViewRegistryResult;

typedef enum
{
    SAFEVIEW_USER_ALERT_PERSONAL = 0,
    SAFEVIEW_USER_ALERT_COMERCIAL = 1,
    SAFEVIEW_USER_ALERT_DISTRIBUTOR = 2,
    SAFEVIEW_USER_ALERT_GOLD = 3,
    SAFEVIEW_USER_ALERT_WALLET_DESC = 4,
//      SAFEVIEW_USER_ALERT_PAYTV                       = 5
    SAFEVIEW_USER_ALERT_PAYTV = 9,

#if SAFEVIEW_CUSTOM_ACCOUNT_INFO_PACK_ENABLED

    SAFEVIEW_USER_CUSTOM_NO_SIGNAL_MSG = 0x70,
    SAFEVIEW_USER_CUSTOM_NO_RIGHTS_MSG = 0x71,
    SAFEVIEW_USER_ACCOUNT_INFO = 0x72,
    SAFEVIEW_USER_PRODUCTS_INFO = 0x73,

#endif //#if SAFEVIEW_CUSTOM_ACCOUNT_INFO_PACK_ENABLED

    SAFEVIEW_USER_FP_0X87 = 0x87,       //Old fingerprinting
    SAFEVIEW_USER_PRAYERTIME = 0x88,
    SAFEVIEW_USER_STBCOMMAND = 0x89,

#if SAFEVIEW_ADVANCED_MSGS_SUPPORT

    SAFEVIEW_USER_TICKER = 0x8A,
    SAFEVIEW_USER_POPUP = 0x8B,

#endif //#if SAFEVIEW_ADVANCED_MSGS_SUPPORT

    SAFEVIEW_USER_FP_0X8C = 0x8C,        //New fingerprinting
    SAFEVIEW_USER_OTHER = 0xE0  /* Means unspecified */

} SafeViewUserAlertType;

typedef struct _SafeViewPPVEvent
{
    struct _SafeViewPPVEvent *next;
    struct _SafeViewPPVEvent *prev;
    SafeViewDate start_time;
    SafeViewDate end_time;
    unsigned char name[SAFEVIEW_MAX_PAYTV_NAME_LENGTH];
} SafeViewPPVEvent;

typedef struct
{
    SafeViewAlertId mail_id;
    SafeViewOperatorId operator_id;
    SafeViewBoolean read;
    SafeViewUserAlertType type;
    union
    {
        struct
        {
            SafeViewDate date;
            SafeViewDate expiration_date;
            unsigned char from[SAFEVIEW_MAX_ALERT_FROM_LENGTH];
            unsigned char subject[SAFEVIEW_MAX_ALERT_SUBJECT_LENGTH];
            unsigned char data[SAFEVIEW_MAX_ALERT_DATA_LENGTH];
            unsigned char ecm_length;
            unsigned char ecm[SAFEVIEW_MAX_ALERT_ECM_LENGTH];
        } message_info;
        struct
        {
            SafeViewWalletId wallet_id;
            unsigned char description[SAFEVIEW_MAX_WALLET_DESC_LENGTH];
        } wallet_info;
/*
  struct
  {
  SafeViewDate            start_time;
  SafeViewDate            end_time;
  SafeViewPoints  price;
  unsigned char   name[SAFEVIEW_MAX_PAYTV_NAME_LENGTH];
  unsigned char   description[SAFEVIEW_MAX_PAYTV_DESC_LENGTH];
  unsigned char   command_length;
  unsigned char   command[SAFEVIEW_MAX_PAYTV_COMMAND_LENGTH];
  } paytv_info;
*/
        struct
        {
            //SafeViewDate  start_time;
            //SafeViewDate  end_time;
            SafeViewDate date;  //Not used at the moment
            SafeViewDate expiration_date;
            unsigned short logo_id;
            unsigned long product_id;
            unsigned short subject_id;
            unsigned long price;
            unsigned char name[SAFEVIEW_MAX_PAYTV_NAME_LENGTH];
            unsigned char description[SAFEVIEW_MAX_PAYTV_DESC_LENGTH];
            SafeViewList *event_list;
#if SAFEVIEW_IPPV_SUPPORT
            unsigned char command_length;
            unsigned char command[SAFEVIEW_MAX_PAYTV_COMMAND_LENGTH];
#endif
        } paytv_info;
    } d;
} SafeViewUserAlert;

/* Callbacks */

/*************************************************************************************
    Callback:   NumWalletsEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_get_num_wallets function.
                wallets:     Number of wallets.
                result:      Operation result.
    Desc:       Returns the wallets number due to an safeview_get_num_wallets query.
*************************************************************************************/
typedef void (*NumWalletsEventHandler) (void *caller_data,
                                        unsigned char wallets,
                                        SafeViewResult result);

/*************************************************************************************
    Callback:   WalletPointsEventHandler
    Params:     wallet:       Wallet index in which new points have been added.
                text:         Text to be displayed when new points are added to a wallet.
                added_points: Points added to the wallet (Not used in this release).
    Desc:       Called when new points are added to a wallet.
*************************************************************************************/
typedef void (*WalletPointsEventHandler) (SafeViewWalletIndex wallet,
                                          unsigned char *text,
                                          SafeViewPoints added_points);

/*************************************************************************************
    Callback:   WalletLostEventHandler
    Params:     wallet:       Wallet index in which points have been lost.
                text:         Text to be displayed when points are lost in a wallet.
                added_points: Points lost in the wallet (Not used in this release).
    Desc:       Called when lost points are lost in a wallet.
*************************************************************************************/
typedef void (*WalletLostEventHandler) (SafeViewWalletIndex wallet,
                                        unsigned char *text,
                                        SafeViewPoints lost_points);

/*************************************************************************************
    Callback:   WalletInfoEventHandler
    Params:     caller_data:  Data passed by the caller when calling safeview_get_wallet_info_by_index or by_id function.
                operator_id:  Operator identifier.
                wallet_id:    Wallet identifier.
                wallet_name:  Wallet name.
                points:       Wallet points.
                type:         Wallet type.
                hash:         If can generate a hash code or not.
                value:        Wallet value.
                date:         Wallet expiration.
                result:       Operation result.
    Desc:       Returns the wallet info due to an safeview_get_wallet_info_by_index or by_id query.
*************************************************************************************/
typedef void (*WalletInfoEventHandler) (void *caller_data,
                                        SafeViewWalletIndex wallet,
                                        SafeViewOperatorId operator_id,
                                        SafeViewWalletId wallet_id,
                                        unsigned char *wallet_name,
                                        SafeViewPoints points,
                                        SafeViewWalletType type,
                                        SafeViewBoolean hash,
                                        SafeViewWalletValue value,
                                        SafeViewDate date,
                                        SafeViewResult result);

/*************************************************************************************
    Callback:   UserAlertEventHandler
    Params:     message: New message received.
    Desc:       Called when a new message arrives.
*************************************************************************************/
typedef void (*UserAlertEventHandler) (SafeViewUserAlert * message);

/*************************************************************************************
    Callback:   KeyProcessedEventHandler
    Params:     key_processed: Key processed by SafeView.
    Desc:       Called when a remote control key has been processed by SafeView.
*************************************************************************************/
typedef void (*KeyProcessedEventHandler) (SafeViewKey key_processed);

/*************************************************************************************
    Callback:   NumRegistriesEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_get_num_registries function.
                registries:  Number of registries.
                result:      Operation result.
    Desc:       Returns the registries number due to an safeview_get_num_registries query.
*************************************************************************************/
typedef void (*NumRegistriesEventHandler) (void *caller_data,
                                           unsigned char registries,
                                           SafeViewResult result);

/*************************************************************************************
    Callback:   RegistryInfoEventHandler
    Params:     caller_data:     Data passed by the caller when calling safeview_get_registry_info function.
                registry_index:  Registry index.
                registry_name:   Registry name.
                registry_date:   Registry date.
                registry_result: Registry result (win, lost or pending).
                registry_points: Registry points won or lost.
                result:          Operation result.
    Desc:       Returns the registry info due to an safeview_get_registry_info query.
*************************************************************************************/
typedef void (*RegistryInfoEventHandler) (void *caller_data,
                                          SafeViewRegistryIndex
                                          registry_index,
                                          unsigned char *registry_name,
                                          SafeViewDate registry_date,
                                          SafeViewRegistryResult
                                          registry_result,
                                          SafeViewPoints registry_points,
                                          SafeViewResult result);

/*************************************************************************************
    Callback:   WalletHashEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_get_wallet_hash function.
                operator_id: Operator id.
                wallet_id:   Wallet id.
                hash_length: Hash length.
                hash:        Hash string.
                phone_number: Phone number to call to.
                result:      Operation result.
    Desc:       Returns the wallet hash due to an safeview_get_wallet_hash query.
*************************************************************************************/
typedef void (*WalletHashEventHandler) (void *caller_data,
                                        SafeViewOperatorId operator_id,
                                        SafeViewWalletId wallet_id,
                                        unsigned char hash_length,
                                        unsigned char *hash,
                                        unsigned char *phone_number,
                                        SafeViewResult result);

/*************************************************************************************
    Callback:   FolderNameEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_get_folder_name function.
                folder_id:   Folder which name is requested.
                folder_name: Folder name.
                result:      Operation result.
    Desc:       Returns the folder name due to an safeview_get_folder_name query.
*************************************************************************************/
typedef void (*FolderNameEventHandler) (void *caller_data,
                                        unsigned char folder,
                                        unsigned char *folder_name,
                                        SafeViewResult result);

/*************************************************************************************
    Callback:   EMMEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_send_emm function.
                result:      Operation result.
    Desc:       Returns the folder name due to an safeview_send_emm query.
*************************************************************************************/
typedef void (*EMMEventHandler) (void *caller_data, SafeViewResult result);

/*************************************************************************************
    Callback:   ECMEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_send_ecm function.
                result:      Operation result.
    Desc:       Returns the folder name due to an safeview_send_ecm query.
*************************************************************************************/
typedef void (*ECMEventHandler) (void *caller_data, SafeViewResult result);

/*************************************************************************************
    Callback:   MessageReadEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_message_read function.
                result:      Operation result.
    Desc:       Returns the folder name due to an safeview_message_read query.
*************************************************************************************/
typedef void (*MessageReadEventHandler) (void *caller_data,
                                         SafeViewResult result);

/*************************************************************************************
    Callback:   MessageRemovedEventHandler
    Params:     caller_data: Data passed by the caller when calling safeview_message_removed function.
                result:      Operation result.
    Desc:       Returns the folder name due to an safeview_message_removed query.
*************************************************************************************/
typedef void (*MessageRemovedEventHandler) (void *caller_data,
                                            SafeViewResult result);

typedef struct
{
    WalletPointsEventHandler walletPointsCb;
    WalletLostEventHandler walletLostCb;
    UserAlertEventHandler userAlertCb;
    KeyProcessedEventHandler keyProcessedCb;
} SafeViewWalletCallbacks;

/*************************************************************************************
    Function:   safeview_register_wallet_callbacks
    Params:     caller_data: This data will be returned when the callback is called.
                cbSt: Callback structure.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Registers callbacks to be called when wallets event ocurr.
*************************************************************************************/
SafeViewResult safeview_register_wallet_callbacks (SafeViewWalletCallbacks *
                                                   cbSt);

/*************************************************************************************
    Function:   safeview_get_num_wallets
    Params:     caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the number of wallets through a callback.
*************************************************************************************/
SafeViewResult safeview_get_num_wallets (void *caller_data,
                                         NumWalletsEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_wallet_info_by_index
    Params:     wallet_index: wallet_index.
                caller_data:  This data will be returned when the callback is called.
                cb:           Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the wallet info through a callback.
*************************************************************************************/
SafeViewResult safeview_get_wallet_info_by_index (SafeViewWalletIndex
                                                  wallet_index,
                                                  void *caller_data,
                                                  WalletInfoEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_wallet_info_by_id
    Params:     operator_id: Operator ID.
                wallet_id:   wallet_id.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the wallet info through a callback.
*************************************************************************************/
SafeViewResult safeview_get_wallet_info_by_id (SafeViewOperatorId operator_id,
                                               SafeViewWalletId wallet_id,
                                               void *caller_data,
                                               WalletInfoEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_wallet_hash
    Params:     operator_id: Operator ID.
                wallet_id:   wallet_id.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the wallet hash through a callback.
*************************************************************************************/
SafeViewResult safeview_get_wallet_hash (SafeViewOperatorId operator_id,
                                         SafeViewWalletId wallet_id,
                                         void *caller_data,
                                         WalletHashEventHandler cb);

/*************************************************************************************
    Function:   safeview_key_pressed
    Params:     key: key pressed.
    Return:     No return value.
    Desc:       Notifies that a key has been pressed.
*************************************************************************************/
void safeview_key_pressed (SafeViewKey key);

/*************************************************************************************
    Function:   safeview_get_num_registries
    Params:     caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the number of registries through a callback.
*************************************************************************************/
SafeViewResult safeview_get_num_registries (void *caller_data,
                                            NumRegistriesEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_registry_info
    Params:     registry_index: Registry index.
                caller_data:    This data will be returned when the callback is called.
                cb:             Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the registry info.
*************************************************************************************/
SafeViewResult safeview_get_registry_info (SafeViewRegistryIndex
                                           registry_index, void *caller_data,
                                           RegistryInfoEventHandler cb);

/*************************************************************************************
    Function:   safeview_send_emm
    Params:     emm:        EMM to send to the smartcard.
                emm_length: EMM length
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Sends an EMM to the smartcard.
*************************************************************************************/
SafeViewResult safeview_send_emm (unsigned char *emm,
                                  SafeViewEmmLength emm_length,
                                  void *caller_data, EMMEventHandler cb);

/*************************************************************************************
    Function:   safeview_send_ecm
    Params:     ecm:        ECM to send to the smartcard.
                ecm_length: ECM length
                key:            Key pressed.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Sends an ECM to the smartcard.
*************************************************************************************/
SafeViewResult safeview_send_ecm (unsigned char *ecm,
                                  SafeViewEcmLength ecm_length,
                                  SafeViewKey key,
                                  void *caller_data, ECMEventHandler cb);

/*************************************************************************************
    Function:   safeview_get_folder_name
    Params:     folder:      Folder number.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Gets the folder name through a callback.
*************************************************************************************/
SafeViewResult safeview_get_folder_name (unsigned char folder,
                                         void *caller_data,
                                         FolderNameEventHandler cb);

/*************************************************************************************
    Function:   safeview_set_message_read
    Params:     operator_id: Operator_id the message belongs to.
                alert_id:    Alert_id.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Notifies the smartcard that a message has been read.
*************************************************************************************/
SafeViewResult safeview_set_message_read (SafeViewOperatorId operator_id,
                                          SafeViewAlertId alert_id,
                                          void *caller_data,
                                          MessageReadEventHandler cb);

/*************************************************************************************
    Function:   safeview_set_message_removed
    Params:     operator_id: Operator_id the message belongs to.
                alert_id:    Alert_id.
                caller_data: This data will be returned when the callback is called.
                cb:          Callback to be called with the answer.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error,
                SAFEVIEW_NO_SMARTCARD_INSERTED if no SafeView smartcard inserted.
    Desc:       Notifies the smartcard that a message has been removed.
*************************************************************************************/
SafeViewResult safeview_set_message_removed (SafeViewOperatorId operator_id,
                                             SafeViewAlertId alert_id,
                                             void *caller_data,
                                             MessageRemovedEventHandler cb);

/*************************************************************************************
    Function:   safeview_delay_emm_management
    Params:     secs: Seconds to delay the emm management.
    Return:     No return value.
    Desc:       Delays the emm management for the seconds specified by parameter.
*************************************************************************************/
void safeview_delay_emm_management (unsigned long secs);

#endif /* ifndef _SAFEVIEW_LOYALTY_API_H_ */
