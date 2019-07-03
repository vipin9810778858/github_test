/* $Id: safeview_file_adaptation.h 13 2015-10-06 11:41:34Z agarcia $ */
/* Copyright 2011 SafeView S.L. All rights reserved.
 *
 * safeview_file_adaptation.h
 *
 * This file declares the file system adaptation layer.
 *
 * History:
 *      05/07/11        1.0     Rafael Barriuso Maicas
 * - First release
 *
 * This software is  subject to updates, revisions,  and extensions by
 * SafeView.  Use of this software shall be permitted only pursuant to
 * the  terms and  conditions  of the  license  agreement between  the
 * licensee and SafeView.
 */

#ifndef _SAFEVIEW_FILE_ADAPTATION_H_
#define _SAFEVIEW_FILE_ADAPTATION_H_

#include "safeview_common_types.h"
#include "safeview_list_api.h"

#define SAFEVIEW_NO_FILE                                        ((SafeViewFile*)NULL)

typedef void *SafeViewFile;

typedef struct _SafeViewDirEntry
{
    struct _SafeViewDirEntry *next;
    struct _SafeViewDirEntry *prev;
    char *fileName;
    SafeViewBoolean isDirectory;
    SafeViewBoolean isFile;
} SafeViewDirEntry;

/*************************************************************************************
    Function:   safeview_file_fopen
    Params:     filename: path to the file to be opened
                mode: a combination of "r", "w", "b", "+", similar to the stdio modes.
    Return:     Handler of the file opened or SAFEVIEW_NO_FILE if open failed.
    Desc:       Opens a file in the STB file system.
*************************************************************************************/
SafeViewFile safeview_file_fopen (const char *filename, const char *mode);
SafeViewFile safeview_file_fopen64 (const char *filename, const char *mode);

/*************************************************************************************
    Function:   safeview_file_fread
    Params:     file: handler of the file to be read.
                size: number of bytes to be read.
                destination: already allocated buffer where to put the read data.
    Return:     Number of bytes actually read, -1 if error.
    Desc:       Reads data from an open file.
*************************************************************************************/
int safeview_file_fread (SafeViewFile file, unsigned long size,
                         unsigned char *destination);

/*************************************************************************************
    Function:   safeview_file_fwrite
    Params:     file: handler of the file to be written.
                size: number of bytes to be written.
                source: buffer containing the data to be written.
    Return:     Number of bytes actually written, -1 if error.
    Desc:       Writes data to an open file.
*************************************************************************************/
int safeview_file_fwrite (SafeViewFile file, unsigned long size,
                          const unsigned char *source);

/*************************************************************************************
    Function:   safeview_file_fflush
    Params:     file: handler of the file to be flushed.
    Return:     SAFEVIEW_OK on success, SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Tries to flush the given file.
*************************************************************************************/
SafeViewResult safeview_file_fflush (SafeViewFile file);

/*************************************************************************************
    Function:   safeview_file_fseek
    Params:     file: handler of the file to be seeked.
                offset: number of bytes from the beginning of the file to set the
                current position of the read/write cursor.
    Return:     SAFEVIEW_OK on success, SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Moves the position indicator to a new one by adding an offset from the
                beginning of the file.
                If offset is greater than the size of the file, it should grow the file.
*************************************************************************************/
SafeViewResult safeview_file_fseek (SafeViewFile file, unsigned long offset);
SafeViewResult safeview_file_fseek64 (SafeViewFile file,
                                      long long int offset);

/*************************************************************************************
    Function:   safeview_file_fclose
    Params:     file: handler to the file to be closed.
    Return:     SAFEVIEW_OK on success, SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Closes a file handler.
*************************************************************************************/
SafeViewResult safeview_file_fclose (SafeViewFile file);

/*************************************************************************************
    Function:   safeview_file_fmove
    Params:     oldName: path to the current file
                newName: path to the new file
    Return:     SAFEVIEW_OK on success, SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Renames a file. The file must be closed.
*************************************************************************************/
SafeViewResult safeview_file_fmove (const char *oldName, const char *newName);

/*************************************************************************************
    Function:   safeview_file_fremove
    Params:     fileName: path to file to be deleted
    Return:     SAFEVIEW_OK on success, SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Deletes a file. The file must be closed.
*************************************************************************************/
SafeViewResult safeview_file_fremove (const char *fileName);

/*************************************************************************************
    Function:   safeview_file_mkdir
    Params:     path: path to the directory to be created.
    Return:     SAFEVIEW_OK if the directory is successfully created or it already existed,
                SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Creates a new directory.
*************************************************************************************/
SafeViewResult safeview_file_mkdir (const char *path);

/*************************************************************************************
    Function:   safeview_file_rmdir
    Params:     path: path to the directory to be deleted.
    Return:     SAFEVIEW_OK if the directory was successfully removed,
                SAFEVIEW_GENERIC_ERROR on error.
    Desc:       Removes an empty directory.
*************************************************************************************/
SafeViewResult safeview_file_rmdir (const char *path);

/*************************************************************************************
    Function:   safeview_file_flength
    Params:     path: path to the requested file.
    Return:     The size of the file in bytes on success, -1 on error.
    Desc:       Gets the length in bytes of the given file.
*************************************************************************************/
long safeview_file_flength (const char *path);

/*************************************************************************************
    Function:   safeview_directory_list
    Params:     dirPath: path to the directory to be examined.
    Return:     A list of "SafeViewDirEntry" elements.
    Desc:       Lists the elements contained in the given directory.
                The result must be freed using "safeview_directory_free".
*************************************************************************************/
SafeViewList *safeview_directory_list (const char *dirPath);

/*************************************************************************************
    Function:   safeview_directory_free
    Params:     dirList: list of files to be freed.
    Return:     None.
    Desc:       Frees the list of elements allocated in "safeview_directory_list"
*************************************************************************************/
void safeview_directory_free (SafeViewList * dirList);

/*************************************************************************************
    Function:   safeview_file_free_disk_space_get
    Params:     Pointer to the mounting directory name.
    Return:     Free disk space in bytes. -1 if error.
    Desc:       Returns the free disk space in bytes.
*************************************************************************************/
long long int safeview_file_free_disk_space_get (char *mountDir);

#endif /* ifndef _SAFEVIEW_FILE_ADAPTATION_H_ */
