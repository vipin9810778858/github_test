
/* $Id: safeview_osd_adaptation.h 15 2016-01-19 16:01:34Z agarcia $ */
/* Copyright 2003 Secuenzia Pixels. All rights reserved.
 *
 * safeview_osd_adaptation.h
 *
 * This file defines common types  used by the different APIs provided
 * by SafeView.
 * SafeView software is based on this API.
 * Manufacturer  should  implement  the  API  in  order  to  integrate
 * SafeView software in the receiver.
 *
 * History:
 *      28/01/03        1.0     Miguel Angel González Iglesias
 * - First release
 *      03/06/03        2.0     Miguel Angel González Iglesias
 * - No relevant changes.
 *      01/07/04        2.2     Miguel Angel González Iglesias
 * - No relevant changes.
 *      26/12/06        2.3     Rafael Barriuso Maicas
 * - Added multiple image formats support (function
 *   'safeview_draw_image').
 * - Added color and text style enums.
 * - Prefixed 'set_native_palette' and 'set_safeview_palette' with
 *   'safeview_'.
 * - Added text styles and 'item' argument to 'safeview_draw_text'
 * - Added 'safeview_init_osd_adaptation'.
 * - Added 'safeview_draw_game'.
 * - Added declaration of exported images and gadgets.
 * - Renamed 'safeview_clear_all' to 'safeview_clear_screen'.
 * - Added 'safeview_can_open'.
 * - Added 'safeview_can_draw'.
 * - Added 'safeview_refresh_osd' and 'safeview_refresh_screen'.
 * - Added 'safeview_draw_message' and 'safeview_clear_messages'.
 * - Added 'safeview_save_displayed_message' and
 *   'safeview_restore_displayed_message'.
 * - Added 'safeview_preload_image' and 'safeview_unload_image'
 *   declaration.
 * - Added 'SAFEVIEW_STB_FORMAT' image format support.
 * - Added 'safeview_return_to_stb_menu',
 *   'safeview_return_to_tv_screen' and 'safeview_exit_from_stb_menu'
 *   for CAS-STB menu integration.
 *      16/10/08
 * - Modified 'safeview_draw_image' to support image stretching.
 * - Modified 'safeview_draw_text' to return the number of character
 *   actually drawn.
 * - Moved 'safeview_osd_keys_get_management' and
 *   'safeview_osd_keys_release_management' from key_adaptation.
 * - Changed 'safeview_draw_game' to 'safeview_draw_image_palette'.
 *      25/05/09
 * - Added 'safeview_get_stb_language'.
 *
 * This software is  subject to updates, revisions,  and extensions by
 * Secuenzia. Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and Secuenzia.
 */

#ifndef _SAFEVIEW_OSD_ADAPTATION_H_
#define _SAFEVIEW_OSD_ADAPTATION_H_

#include "safeview_common_types.h"
#include "safeview_loyalty_api.h"

/* #if !SAFEVIEW_OSD_MANAGER_SUPPORT */

#define SAFEVIEW_IMAGE_FORMAT_NOT_SUPPOTED                      (-8)
#define SAFEVIEW_UNKNOWN_IMAGE_LENGTH                           (-1)
#define SAFEVIEW_UNKNOWN_IMAGE_DIMENSIONS                       (-1)

// Colors
typedef enum
{
    SAFEVIEW_NO_COLOR = -1,
    SAFEVIEW_BLACK_COLOR,
    SAFEVIEW_WHITE_COLOR,
    SAFEVIEW_ORANGE_COLOR,
    SAFEVIEW_BLUE_COLOR,
    SAFEVIEW_PINK_COLOR,        //Changed, 20130529
    SAFEVIEW_BROWN_COLOR,       //Changed, 20130529
    SAFEVIEW_DESC_COLOR,
    SAFEVIEW_GREEN_COLOR,
    SAFEVIEW_GREY_COLOR,
    SAFEVIEW_YELLOW_COLOR,
    SAFEVIEW_RED_COLOR,
    SAFEVIEW_GREYGREEN_COLOR
} SafeViewColor;

// Text color styles
typedef enum
{
    SAFEVIEW_TEXT_WHITE_STYLE = 0,
    SAFEVIEW_TEXT_BLACK_STYLE,
    SAFEVIEW_TEXT_BLUE_STYLE,
    SAFEVIEW_TEXT_PINK_STYLE,   //Changed, 20130529
    SAFEVIEW_TEXT_BROWN_STYLE,  //Changed, 20130529
    SAFEVIEW_TEXT_GREEN_STYLE,
    SAFEVIEW_TEXT_YELLOW_STYLE,
    SAFEVIEW_TEXT_RED_STYLE,
    SAFEVIEW_TEXT_GREY_STYLE,   //New, 20130529
    SAFEVIEW_TEXT_ORANGE_STYLE, //New, 20130529
    SAFEVIEW_TEXT_TRANSPARENT_STYLE     //New, 20130529
} SafeViewTextStyle;

// Text alignment
typedef enum
{
    SAFEVIEW_LEFT_ALIGNMENT = 0,
    SAFEVIEW_CENTER_ALIGNMENT,
    SAFEVIEW_RIGHT_ALIGNMENT
} SafeViewTextAlignment;

// Text font size
typedef enum
{
    SAFEVIEW_FONT_SIZE_NORMAL = 0,
    SAFEVIEW_FONT_SIZE_SMALL,
    SAFEVIEW_FONT_SIZE_BIG,
    SAFEVIEW_FONT_SIZE_SMALLEST,        //New, 20130529
    SAFEVIEW_FONT_SIZE_BIGGEST  //New, 20130529
} SafeViewFontSize;

#define SAFEVIEW_FONT_SIZE_LAST_USED                            (-1)

// Image format
typedef enum
{
    SAFEVIEW_AUTO_DETECT_FORMAT = 0,
    SAFEVIEW_BMP_FORMAT,
    SAFEVIEW_JPEG_FORMAT,
    SAFEVIEW_GIF_FORMAT,
    SAFEVIEW_PNG_FORMAT,
    SAFEVIEW_STB_FORMAT
} SafeViewImageFormat;

typedef enum
{
    SAFEVIEW_GAME_DRAW,
    SAFEVIEW_APP_DRAW,
    SAFEVIEW_POINTS_DRAW,
    SAFEVIEW_KEY_DRAW,
    SAFEVIEW_MSG_DRAW,
    SAFEVIEW_MINIGUIDE_DRAW
} SafeViewOSDDrawType;

/*************************************************************************************
    Function:   SafeViewDrawPasswdCb
    Params:     password:       ASCII password (PIN number) entered by the user.
    Return:     0 if the password was correct. Other value otherwise.
    Desc:       PIN verification callback.
*************************************************************************************/
typedef int (*SafeViewDrawPasswdCb) (const char *password);

/*************************************************************************************
    Function:   SafeViewDrawOkCb
    Params:     res:    SAFEVIEW_OK if the user pressed OK, SAFEVIEW_GENERIC_ERROR otherwise.
    Return:     None
    Desc:       Ok / cancel dialog callback.
*************************************************************************************/
typedef void (*SafeViewDrawOkCb) (int res);

/*************************************************************************************
    Function:   safeview_init_osd_adaptation
    Params:     No params.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Initializes OSD.
*************************************************************************************/
SafeViewResult safeview_init_osd_adaptation (void);

/*************************************************************************************
    Function:   safeview_osd_keys_get_management
    Params:     x, y, width, height: region of the OSD to take control of.
                stopTV: SAFEVIEW_TRUE if the TV video decoding has to be stopped
                Parameter x management: Most significant byte of parameter x must not be cosidered for the position value,
                and its bits have the following meaning:
                -------------------------------------------------------------------------
                | bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0 |
                -------------------------------------------------------------------------

*******************************************************************************************************************
Start OSD Popup case :
						- bit 0 : if it is high, it means OSD popup is non blocking else OSD popup is blocking
						- bit 2 : if it is high, it means OSD popup is suppressible else OSD popup is non suppressible
End OSD Popup case

********************************************************************************************************************

                - bit 0:        Indicates if the keys are required in blocking (0) or non-blocking (1) mode.
                                When required in blocking mode, the STB should answer SAFEVIEW_OK. Then, it
                                must not respond to the key and just pass the key codes to Safeview.
                                When required in non-blocking mode, the STB can answer SAFEVIEW_GENERIC_ERROR in
                                the case it is currently accesing OSD, so it will not allow Safeview to paint.
                                This last rule has an exception that is the case of a fingerprint operation
                                signalled by bit 1, as explained below.
                - bit 1:        Indicates if the keys are required for a fingerprint operation (1) or not (0).
                                In the case of a fingerprint operation the STB should answer always SAFEVIEW_OK,
                                regardless of bit 0 indicating blocking or non-blocking mode, because fingerprint
                                must be painted all times regardless of the STB status.
    Return:     SAFEVIEW_OK if success, SAFEVIEW_GENERIC_ERROR if not allowed to take the
                control of the OSD and keys at that moment.
    Desc:       Takes the control of the keys and OSD, if allowed.
*************************************************************************************/
SafeViewResult safeview_osd_keys_get_management (unsigned int x, int y, int width,
                                                 int height,
                                                 SafeViewBoolean stopTV,
                                                 SafeViewUserAlertType SV_alerttype );

/*************************************************************************************
    Function:   safeview_osd_keys_release_management
    Params:     None.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Releases the control of the keys and OSD.
*************************************************************************************/
SafeViewResult safeview_osd_keys_release_management (void);

/*************************************************************************************
    Function:   safeview_draw_rect
    Params:     xpos: X position.
                ypos: Y position.
                xsize: X size.
                ysize: Y size.
                color: Color.
    Return:     No return value.
    Desc:       Draws a solid rectangle.
*************************************************************************************/
void safeview_draw_rect (unsigned int xpos, unsigned int ypos,
                         unsigned int xsize, unsigned int ysize,
                         SafeViewColor color);

/*************************************************************************************
    Function:   safeview_draw_text
    Params:     item: Item related (NULL if none)
                xpos: X position.
                ypos: Y position.
                text: Text to draw.
                alignment: Text alignment.
                max_size: Max text size.
                max_lines: Max text lines.
                font_size: Font size to be used (default for last font size used).
                style: Text style.
    Return:     Returns the number of characters of the original text that
                the function managed to draw.
    Desc:       This function draws a text.
*************************************************************************************/
int safeview_draw_text (void *item, unsigned int xpos, unsigned int ypos,
                        const char *text, SafeViewTextAlignment alignment,
                        int max_size, int max_lines,
                        SafeViewFontSize font_size, SafeViewTextStyle style);

/*************************************************************************************
    Function:   safeview_preload_image
    Params:     format: format of the image to read.
                data_len: length of the image data or SAFEVIEW_UNKNOWN_IMAGE_LENGTH if unknown.
                data: Image data.
    Return:     A pointer to the preloaded data.
    Desc:       This function loads a compressed image and stores it in RAM in a
                STB-dependent (probably uncompressed) format, so it can then be drawn
                using 'safeview_draw_image' using format SAFEVIEW_STB_FORMAT.
*************************************************************************************/
void *safeview_preload_image (SafeViewImageFormat format, int data_len,
                              unsigned char *data);

/*************************************************************************************
    Function:   safeview_unload_image
    Params:     preloaded_data: preloaded data to be freed.
    Return:     None.
    Desc:       This function frees the memory allocated by a previous call to
                'safeview_preload_image'.
*************************************************************************************/
void safeview_unload_image (void *preloaded_data);

/*************************************************************************************
    Function:   safeview_draw_image
    Params:     xpos: X position.
                ypos: Y position.
                xsize: X size. If <= 0, try to use the original image width.
                ysize: Y size. If <= 0, try to use the original image height.
                format: Image data format.
                data_len: Image data length or SAFEVIEW_UNKNOWN_IMAGE_LENGTH if unknown.
                data: Image data.
    Return:     SAFEVIEW_OK if OK,
                SAFEVIEW_IMAGE_FORMAT_NOT_SUPPOTED if the requested format is no supported,
                SAFEVIEW_GENERIC_ERROR on other kind of error.
    Desc:       This function draws an image on the screen. If the width or height are
                different from the original image width and height, resizes the image.
*************************************************************************************/
SafeViewResult safeview_draw_image (unsigned int xpos, unsigned int ypos,
                                    unsigned int xsize, unsigned int ysize,
                                    SafeViewImageFormat format, int data_len,
                                    unsigned char *data);

/*************************************************************************************
    Function:   safeview_draw_image_palette
    Params:     xpos: X position.
                ypos: Y position.
                xsize: X size.
                ysize: Y size.
                format: Image data format.
                data_len: Image data length or SAFEVIEW_UNKNOWN_IMAGE_LENGTH if unknown.
                data: Data array.
                palette: palette to draw with
    Return:     SAFEVIEW_OK if OK,
                SAFEVIEW_IMAGE_FORMAT_NOT_SUPPOTED if the requested format is no supported,
                SAFEVIEW_GENERIC_ERROR on other kind of error.
    Desc:       This function draws an image using the supplied palette.
*************************************************************************************/
SafeViewResult safeview_draw_image_palette (unsigned short xpos,
                                            unsigned short ypos,
                                            unsigned short xsize,
                                            unsigned short ysize,
                                            SafeViewImageFormat format,
                                            int data_len, unsigned char *data,
                                            unsigned char *palette);

/*************************************************************************************
    Function:   safeview_set_safeview_palette
    Params:     No params.
    Return:     No return value.
    Desc:       This function sets SafeView palette.
*************************************************************************************/
void safeview_set_safeview_palette (void);

/*************************************************************************************
    Function:   safeview_set_native_palette
    Params:     No params.
    Return:     No return value.
    Desc:       This function sets native palette.
*************************************************************************************/
void safeview_set_native_palette (void);

/*************************************************************************************
    Function:   safeview_can_use_screen
    Params:     None.
    Return:     Returns true if OK, false if not.
    Desc:       This function returns if the OSD can be used by SafeView or not.
*************************************************************************************/
SafeViewBoolean safeview_can_use_screen (void);

/*************************************************************************************
    Function:   safeview_can_draw
    Params:     draw_type: Element wanted to draw.
    Return:     Returns true if OK, false if not.
    Desc:       This function indicates if the caller can draw the element it wants.
*************************************************************************************/
SafeViewBoolean safeview_can_draw (SafeViewOSDDrawType draw_type);

/*************************************************************************************
    Function:   safeview_set_screen_in_use
    Params:     used: Boolean indicating if the screen is in use.
    Return:     No return value.
    Desc:       This function notifies lower layers that SafeView is using the OSD.
*************************************************************************************/
void safeview_set_screen_in_use (SafeViewBoolean used);

/*************************************************************************************
    Function:   safeview_clear_screen
    Params:     None.
    Return:     None.
    Desc:       Clear all the screen
*************************************************************************************/
void safeview_clear_screen (void);

/*************************************************************************************
    Function:   safeview_clear_area
    Params:     x: x coord.
                y: Y coord.
                width: width
                height: height
    Return:     None.
    Desc:       Clears the given area of the OSD.
*************************************************************************************/
void safeview_clear_area (int x, int y, int width, int height);

/*************************************************************************************
    Function:   safeview_refresh_osd
    Params:     x: x coord.
                y: Y coord.
                w: width
                h: height
    Return:     None.
    Desc:       Updates the given area of the OSD, i.e. it actually draws the area of
                the OSD.
*************************************************************************************/
void safeview_refresh_osd (int x, int y, int w, int h);

/*************************************************************************************
    Function:   safeview_refresh_screen
    Params:     None.
    Return:     None.
    Desc:       Updates the entire OSD.
*************************************************************************************/
void safeview_refresh_screen (void);

/*************************************************************************************
    Function:   safeview_draw_message
    Params:     text: text to be shown
    Return:     None.
    Desc:       Pops up a text message to the user. The pop-up should follow the STB
                application look and feel.
*************************************************************************************/
void safeview_draw_message (const char *text);

/*************************************************************************************
    Function:   safeview_draw_password_message
    Params:     text: text to be shown
                cb: password checking callback
    Return:     None.
    Desc:       Pops up a text message to the user, allowing him to enter a PIN number.
                The message is shown until "cb" callback returns 0.
                The pop-up should follow the STB application look and feel.
*************************************************************************************/
void safeview_draw_password_message (const char *text,
                                     SafeViewDrawPasswdCb cb);

/*************************************************************************************
    Function:   safeview_draw_ok_message
    Params:     text: text to be shown
                cb: function which will be called when the user presses one of the buttons
    Return:     None.
    Desc:       Pops up a dialog consisting of a text message and OK / Cancel buttons.
                When the user presses any option, the callback is called delivering the user’s choice.
*************************************************************************************/
void safeview_draw_ok_message (const char *text, SafeViewDrawOkCb cb);

/*************************************************************************************
    Function:   safeview_clear_messages
    Params:     None.
    Return:     None.
    Desc:       Hides any pop-up message shown in the screen using 'safeview_draw_message'.
*************************************************************************************/
void safeview_clear_messages (void);

/*************************************************************************************
    Function:   safeview_disable_messages
    Params:     None.
    Return:     None.
    Desc:       Disables SafeView pop-up messages, so it won't be shown even if
                'safeview_draw_message' is called.
*************************************************************************************/
void safeview_disable_messages (void);

/*************************************************************************************
    Function:   safeview_enable_messages
    Params:     None.
    Return:     None.
    Desc:       Enables SafeView pop-up messages.
*************************************************************************************/
void safeview_enable_messages (void);

/*************************************************************************************
    Function:   safeview_return_to_stb_menu
    Params:     None.
    Return:     None.
    Desc:       Opens the STB menu. This function may be called when the SafeView
                application is closed.
*************************************************************************************/
void safeview_return_to_stb_menu (void);

/*************************************************************************************
    Function:   safeview_return_to_tv_screen
    Params:     None.
    Return:     None.
    Desc:       Returns to TV mode. This function may be called when the SafeView
                application is closed.
*************************************************************************************/
void safeview_return_to_tv_screen (void);

/*************************************************************************************
    Function:   safeview_exit_from_stb_menu
    Params:     None.
    Return:     None.
    Desc:       Closes the STB menu. This function is called to assure there's no
                interferences in the OSD when the SafeView application
                opens.
*************************************************************************************/
void safeview_exit_from_stb_menu (void);

/*************************************************************************************
    Function:   safeview_open_stb_epg
    Params:     None.
    Return:     None.
    Desc:       Opens the STB electronic program guide screen.
*************************************************************************************/
void safeview_open_stb_epg (void);

/*************************************************************************************
    Function:   safeview_get_stb_language
    Params:     None.
    Return:     An ASCII string representing a ISO 639-1 language code. For example:
                "en" for English, "es" for Spanish, "fr" for French, "de" for German.
    Desc:       Gets the currently selected language of the STB GUI.
*************************************************************************************/
const char *safeview_get_stb_language (void);

/*************************************************************************************
    Function:   safeview_get_screen_size
    Params:     pwidth: pointer to an unsigned int where to store the current screen width.
                May be 0 if the current screen size couldn't be determined.
                pheight: pointer to an unsigned int where to store the current screen height.
                May be 0 if the current screen size couldn't be determined.
    Return:     None.
    Desc:       Gets the current OSD dimensions expressed in pixels.
*************************************************************************************/
void safeview_get_screen_size (unsigned int *pwidth, unsigned int *pheight);

/* #if SAFEVIEW_PRAYERTIME_SUPPORT */

//TODO: document
SafeViewResult safeview_prayertime_get_logo (int logoId,
                                             unsigned char **ppData,
                                             int *pDataLen);
/* #endif /\* SAFEVIEW_PRAYERTIME_SUPPORT / */

/*************************************************************************************
    Function:   safeview_osd_text_size_get
    Params:     text:           Text string to calculate its size on screen.
                fontSize:       Font size of text to be used for calculations.
                maxWidth:       Maximum width (pixels) to be used for calculations.
                                If not enough, more than 1 line shall be used.
                numLines:       Pointer where the number of lines needed shall be returned.
                realWidth:      Pointer where real width (pixels) shall be returned. It
                                shall be lower or equal than maxWidth.
                totalHeight:    Pointer where total height (pixels) required shall
                                be returned. It's expected to increase as numLines
                                increases.
    Return:     SAFEVIEW_OK if OK, SAFEVIEW_GENERIC_ERROR if error.
    Desc:       Gets the number of lines, the real width (pixels) and the total height
                (pixels) that safeview_draw_text will need to draw a text string on
                screen according a font size and a maximum width. It's expected this
                function to use similar calculations to those done in safeview_draw_text
                to split the text string in several lines. Examples:

                -Given a text string, a font size and a maximum width (pixels), if text
                fits into 1 line, safeview_osd_text_size_get shall return numLines 1,
                realWidth (pixels, usually lower than maxWidth) and totalHeight
                (pixels).

                -Given a text string, a font size and a maximum width (pixels), if text
                fits into 4 lines, safeview_osd_text_size_get shall return numLines 4,
                realWidth (pixels) the width value of the wider line and totalHeight
                (pixels).
*************************************************************************************/
SafeViewResult safeview_osd_text_size_get (const char *text,
                                           SafeViewFontSize fontSize,
                                           unsigned int maxWidth,
                                           unsigned char *numLines,
                                           unsigned int *realWidth,
                                           unsigned int *totalHeight);

/* #if SV_MIDDLEWAREPAGE_SCALEDVIDEO */

/*************************************************************************************
    Function:   safeview_scale_video_window
    Params:     xpos: Position X of the scaled window
                ypos: Position Y of the scaled window
                xsize: Size X of the scaled window
                ysize: Size Y of the scaled window
    Return:     No return value.
    Desc:       Scales the video window.
*************************************************************************************/
void safeview_scale_video_window (int xpos, int ypos, int xsize, int ysize);

/*************************************************************************************
    Function:   safeview_scaled_info_mode
    Params:     No params
    Return:     No return value.
    Desc:       Scales the  video window and  shows at the left  a bar
                with the program name and the current/next event names
                and dates.
*************************************************************************************/
void safeview_scaled_info_mode (char *banner);

/* #endif /\* SV_MIDDLEWAREPAGE_SCALEDVIDEO *\/ */

/* #endif /\* !SAFEVIEW_OSD_MANAGER_SUPPORT *\/ */

#endif /* ifndef _SAFEVIEW_OSD_ADAPTATION_H_ */
