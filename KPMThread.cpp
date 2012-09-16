#define INCL_WIN
#include <os2.h>

#include "KPMThread.h"

KPMThread::KPMThread()
{
    _hab = WinInitialize( 0 );
    _hmq = WinCreateMsgQueue( _hab, 0);
}

KPMThread::~KPMThread()
{
    WinDestroyMsgQueue( _hmq );
    WinTerminate( _hab );
}

