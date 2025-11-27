/*
  Native File Dialog

  User API

  http://www.frogtoss.com/labs
 */


#ifndef _NFD_H
#define _NFD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* denotes UTF-8 char */
typedef char nfdchar_t;

/* opaque data structure -- see NFD_PathSet_* */
typedef struct {
    nfdchar_t *buf;
    size_t *indices; /* byte offsets into buf */
    size_t count;    /* number of indices into buf */
} nfdpathset_t;

typedef enum {
    NFD_ERROR,       /* programmatic error */
    NFD_OKAY,        /* user pressed okay, or successful return */
    NFD_CANCEL,      /* user pressed cancel */
    NFD_RUNS_ASYNC   /* works asynchronous, callback will cleanup things */
} nfdresult_t;

/**
 * callback will be called with the result (ERROR, OKAY or CANCEL) and an allocated output out or NULL.
 * The allocated output must be freed by the callback function.
 */
typedef void (*nfd_async_callback) (nfdresult_t result, const char *out, void *user_data);


#ifdef _WINDOWS
typedef void *nfd_parent_window_data_ptr_t;
#endif
#ifdef __linux
#include <gtk/gtk.h>
typedef GtkWindow *nfd_parent_window_data_ptr_t;
#endif

/* nfd_<targetplatform>.c */


void NFD_SetTexts(const nfdchar_t *cancel,
                  const nfdchar_t *doOpen,
                  const nfdchar_t *doSave,
                  const nfdchar_t *doSelect);

/* single file open dialog */    
nfdresult_t NFD_OpenDialog( const nfdchar_t *filterList,
                            const nfdchar_t *defaultPath,
                            nfdchar_t **outPath
                           );

nfdresult_t NFD_OpenDialogWithParent(const nfdchar_t *dialogtitle,
                                     const nfdchar_t *filterlist,
                                     const nfdchar_t *defaultPath,
                                     nfdchar_t **outPath,
                                     nfd_parent_window_data_ptr_t parent,
                                     nfd_async_callback cb,
                                     void *user_data
                                     );

/* multiple file open dialog */    
nfdresult_t NFD_OpenDialogMultiple( const nfdchar_t *filterList,
                                    const nfdchar_t *defaultPath,
                                    nfdpathset_t *outPaths );

nfdresult_t NFD_OpenDialogMultipleWithParent( const nfdchar_t *dialogtitle,
                                              const nfdchar_t *filterList,
                                              const nfdchar_t *defaultPath,
                                              nfdpathset_t *outPaths,
                                              nfd_parent_window_data_ptr_t parent,
                                              nfd_async_callback cb,
                                             void *user_data
                                             );

/* save dialog */
nfdresult_t NFD_SaveDialog( const nfdchar_t *filterList,
                            const nfdchar_t *defaultPath,
                            nfdchar_t **outPath );

nfdresult_t NFD_SaveDialogWithParent(const nfdchar_t *dialogtitle,
                                     const nfdchar_t *filterlist,
                                     const nfdchar_t *defaultPath,
                                     nfdchar_t **outPath,
                                     nfd_parent_window_data_ptr_t parent,
                                     nfd_async_callback cb,
                                     void *user_data
                                     );

/* select folder dialog */
nfdresult_t NFD_PickFolder( const nfdchar_t *defaultPath,
                            nfdchar_t **outPath);

nfdresult_t NFD_PickFolderWithParent(const nfdchar_t *dialogtitle,
                                     const nfdchar_t *defaultPath,
                                     nfdchar_t **outPath,
                                     nfd_parent_window_data_ptr_t parent,
                                     nfd_async_callback cb,
                                     void *user_data
                                     );



/* nfd_common.c */

/* get last error -- set when nfdresult_t returns NFD_ERROR */
const char *NFD_GetError( void );
/* get the number of entries stored in pathSet */
size_t      NFD_PathSet_GetCount( const nfdpathset_t *pathSet );
/* Get the UTF-8 path at offset index */
nfdchar_t  *NFD_PathSet_GetPath( const nfdpathset_t *pathSet, size_t index );
/* Free the pathSet */    
void        NFD_PathSet_Free( nfdpathset_t *pathSet );


#ifdef __cplusplus
}
#endif

#endif
