#define INCL_WIN
#include <os2.h>

#include <string>

#include <cstdlib>

#include "KWindow.h"
#include "KFrameWindow.h"

bool KFrameWindow::CreateStdWindow( KWindow* pkwndP, ULONG flStyle,
                                    PULONG pflCreateFlags,
                                    const string& strTitle, ULONG flClientStyle,
                                    HMODULE hmodResources, ULONG ulId,
                                    KWindow& kwndClient )
{
    FRAMECDATA fcd;

    fcd.cb            = sizeof( fcd );
    fcd.flCreateFlags = *pflCreateFlags;
    fcd.hmodResources = hmodResources;
    fcd.idResources   = ulId;

    SetClassName( WC_FRAME );
    CreateWindow( pkwndP, strTitle, flStyle, 0, 0, 0, 0, 0,
                  KWND_TOP, ulId, &fcd, 0 );

    kwndClient.CreateWindow( this, "",
                             flClientStyle,
                             0, 0, 0, 0, this, KWND_TOP, FID_CLIENT,
                             0, 0 );

    WindowFromID( FID_CLIENT, _kwndClient );
    WindowFromID( FID_HORZSCROLL, _kwndHorzScroll );
    WindowFromID( FID_MENU, _kwndMenu );
    WindowFromID( FID_MINMAX, _kwndMinMax );
    WindowFromID( FID_SYSMENU, _kwndSysMenu );
    WindowFromID( FID_TITLEBAR, _kwndTitleBar );
    WindowFromID( FID_VERTSCROLL, _kwndVertScroll );

    if( *pflCreateFlags & FCF_SHELLPOSITION )
    {
        SWP swp;
        QueryTaskSizePos( &swp );
        SetWindowPos( KWND_TOP, swp.x, swp.y, swp.cx, swp.cy,
                      SWP_MOVE | SWP_SIZE );
    }

    return true;
}

