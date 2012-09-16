#define INCL_WIN
#include <os2.h>

#include "KPMApp.h"

int KPMApp::Run()
{
    QMSG qm;

    while( WinGetMsg( _hab, &qm, 0, 0, 0 ))
        WinDispatchMsg( _hab, &qm );

    return 0;
}

