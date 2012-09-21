#define INCL_DOS
#define INCL_WIN
#include <os2.h>

#include <cstdlib>

#include "KPMSubThread.h"

bool KPMSubThread::BeginThread( void* arg, int cbStackSize )
{
    void* apArg[] = { this, arg };

    _tid = _beginthread( ThreadStart, 0, cbStackSize, apArg );

    if( _tid == -1 )
        return false;

    return true;
}

bool KPMSubThread::WaitThread( bool fWait )
{
    TID tid = _tid;

    if( DosWaitThread( &tid, fWait ? DCWW_WAIT : DCWW_NOWAIT ))
        return false;

    return true;
}

void KPMSubThread::ThreadStart( void* arg )
{
    void** ppArg = reinterpret_cast< void** >( arg );
    KPMSubThread* thread = reinterpret_cast< KPMSubThread* >( ppArg[ 0 ]);
    arg = ppArg[ 1 ];

    thread->PMThreadStart( arg );
}

void KPMSubThread::PMThreadStart( void* arg )
{
    _hab = WinInitialize( 0 );
    _hmq = WinCreateMsgQueue( _hab, 0 );

    ThreadMain( arg );

    WinDestroyMsgQueue( _hmq );
    WinTerminate( _hab );
}

