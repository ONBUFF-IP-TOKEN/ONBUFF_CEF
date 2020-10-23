/**
*@author    Copyright (c) 2016
*@brief     dfs client library
*@date      2017.05.08
*/
#ifndef LIBDFS_H_
#define LIBDFS_H_

#include "LibDfsCallBackHandler.h"

namespace LibDfs {

/**
@brief dfs main class
*/
class LIBDFS_API LibDfsFacade
{
public:
    LibDfsFacade();
    virtual ~LibDfsFacade();

    /**
    *@brief set base patch info before Start() called
    */
    void SetInfo( DfsInfo &info );

    /**
    *@brief LibDfsCallBackHandler register
    */
    void SetCallBack( LibDfsCallBackHandler *p );

    /**
    *@brief start patch
    */
    void Start();

    /**
    *@brief pause patch
    */
    void Pause();

    /**
    *@brief resume patch
    */
    void Resume();

    /**
    *@brief end patch
    */
    void Stop();

    /**
    *@brief reset 0 version (not used)
    *@param serviceCode of be reset app
    */
    void ResetRegServiceCode( const char *serviceCode /*include null char*/ );

    /**
    *@brief get local version
    *@param serviceCode
    *@return current local version info
    */
    int GetRegServiceCode( const char *serviceCode /*include null char*/ );
    int  ( &GetRegServiceCodeAll( const char *serviceCode /*include null char*/ ) )[10];

    /**
    *@brief base patch info : valid value after SetInfo called
    */
    patchInfo GetPatchInfo();

    /**
    *@brief last patch info : valid value after SetInfo called
    */
    lastVersionInfo GetLastVersionInfo();
    lastVersionInfo GetLastVersionInfoAllNew();

    /**
    *@brief get patchable info : SetInfo called and valid data received
    *@return pathch info
    */
    ToPatchInfo GetExistPatchInfo();

    /**
    *@brief get error list info
    *@return error list log
    */
    errorListInfo GetErrorList();

    /**
    @brief service info Á¤º¸
    */
    serviceInfo GetServiceInfo();

    /**
    *@brief download speed limit
    *@param limit ( 1kbyte ~ 100MByte, unlimit : 0, unit : 1kbyte )
    */
    void SetDownloadSpeedLimit( const int limit );

    /**
    *@brief file process priority
    *@param priority : FileProcessPriority enum
    */
    void SetFileProcPriority( const FileProcessPriority priority = FILE_PROC_PRIORITY_1 );

private:
    struct pimple *_pim;

};

} /*namespace LibDfs*/

#endif /*LIBDFS_H_*/