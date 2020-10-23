#include "stdafx.h"

#include "LibDfs.h"
#include "Mediator.h"

namespace LibDfs {

struct pimple
{
    std::shared_ptr<Mediator>   mediator;
    int vers[10];  //test app used

    pimple()
        : mediator( std::shared_ptr<Mediator>( new Mediator() ) )
    {
        memset( vers, 0x00, 10 );
    }
    ~pimple()
    {
        mediator.reset();
    }
};

LibDfsFacade::LibDfsFacade()
    : _pim( nullptr )
{
    _pim = new pimple;
}

LibDfsFacade::~LibDfsFacade()
{
    Stop();

    if ( _pim )
    {
        delete _pim;
        _pim = nullptr;
    }
}

void LibDfsFacade::SetInfo( DfsInfo &info )
{
    if ( _pim )
        _pim->mediator->SetInfo( info );
}

void LibDfsFacade::SetCallBack( LibDfsCallBackHandler *p )
{
    if ( _pim )
        _pim->mediator->SetCallBack( p );
}

void LibDfsFacade::Start()
{
    if ( _pim )
    {
        _pim->mediator->SetPause( common::threadLock::resume );
        _pim->mediator->SetState( start );
        _pim->mediator->Start();
    }
}

void LibDfsFacade::Pause()
{
    if ( _pim )
    {
        _pim->mediator->SetPause( common::threadLock::pause );
        _pim->mediator->SetState( pause );
    }
}

void LibDfsFacade::Resume()
{
    if ( _pim )
    {
        _pim->mediator->SetPause( common::threadLock::resume );
        _pim->mediator->SetState( resume );
    }
}

void LibDfsFacade::Stop()
{
    if ( _pim )
        _pim->mediator->SetPause( common::threadLock::stop );
}

void LibDfsFacade::ResetRegServiceCode( const char *serviceCode /*include null char*/ )
{
    if ( _pim && serviceCode != nullptr )
        _pim->mediator->ResetRegServiceCode( serviceCode );
}

int LibDfsFacade::GetRegServiceCode( const char *serviceCode /*include null char*/ )
{
    if ( _pim && serviceCode != nullptr )
        return _pim->mediator->GetRegServiceCode( serviceCode );

    return 0;
}

int ( &LibDfsFacade::GetRegServiceCodeAll( const char *serviceCode /*include null char*/ ) )[10]
{
    auto verList = _pim->mediator->GetRegServiceCodeAll( serviceCode );
    int index = 0;
    for ( auto ver : verList )
    {
        _pim->vers[index] = ver;
        ++index;
    }

    return _pim->vers;
}

patchInfo LibDfsFacade::GetPatchInfo()
{
    if ( _pim )
        return _pim->mediator->GetPatchInfo();

    return patchInfo();
}

lastVersionInfo LibDfsFacade::GetLastVersionInfo()
{
    if ( _pim )
        return _pim->mediator->GetLastVersionInfo();

    return lastVersionInfo();
}

lastVersionInfo LibDfsFacade::GetLastVersionInfoAllNew()
{
    if ( _pim )
        return _pim->mediator->GetLastVersionInfoAllNew();

    return lastVersionInfo();
}

ToPatchInfo LibDfsFacade::GetExistPatchInfo()
{
    if ( _pim )
        return _pim->mediator->GetExistPatchInfo();

    return ToPatchInfo();
}

errorListInfo LibDfsFacade::GetErrorList()
{
    if ( _pim )
        return _pim->mediator->GetErrorList();

    return errorListInfo();
}

serviceInfo LibDfsFacade::GetServiceInfo()
{
    if ( _pim )
        return _pim->mediator->GetServiceInfo();

    return serviceInfo();
}

void LibDfsFacade::SetDownloadSpeedLimit( const int limit )
{
    if ( _pim )
        return _pim->mediator->SetDownloadSpeedLimit( limit );
}

void LibDfsFacade::SetFileProcPriority( const FileProcessPriority priority )
{
    if ( _pim )
        _pim->mediator->SetFileProcPriority( priority );
}

}