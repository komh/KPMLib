#define INCL_WIN
#include <os2.h>

#include "KPMMainThread.h"

KPMMainThread::KPMMainThread()
{
    _tid = 1;

    _hab = WinInitialize( 0 );
    _hmq = WinCreateMsgQueue( _hab, 0);
}

KPMMainThread::~KPMMainThread()
{
    WinDestroyMsgQueue( _hmq );
    WinTerminate( _hab );
}

