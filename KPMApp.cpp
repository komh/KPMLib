#define INCL_WIN
#include <os2.h>

#include "KPMApp.h"

KPMApp::KPMApp()
{
    _hab = WinInitialize( 0 );
    _hmq = WinCreateMsgQueue( _hab, 0);
}

KPMApp::~KPMApp()
{
    WinDestroyMsgQueue( _hmq );
    WinTerminate( _hab );
}

void KPMApp::Run()
{
    QMSG qm;

    while( WinGetMsg( _hab, &qm, 0, 0, 0 ))
        WinDispatchMsg( _hab, &qm );
}

