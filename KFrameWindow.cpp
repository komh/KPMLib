#define INCL_WIN
#include <os2.h>

#include <stdlib.h>
#include <string.h>

#include "KWindow.h"
#include "KFrameWindow.h"

KFrameWindow::KFrameWindow() : KWindow()
{
}

KFrameWindow::~KFrameWindow()
{
}

bool KFrameWindow::CreateStdWindow( KWindow* pkwndP, ULONG flStyle,
                                    PULONG pflCreateFlags,
                                    PCSZ pcszTitle, ULONG flClientStyle,
                                    HMODULE hmodResources, ULONG ulId,
                                    KWindow& kwndClient )
{
    FRAMECDATA fcd;

    fcd.cb            = sizeof( fcd );
    fcd.flCreateFlags = *pflCreateFlags;
    fcd.hmodResources = hmodResources;
    fcd.idResources   = ulId;

    SetClassName( WC_FRAME );
    CreateWindow( pkwndP, pcszTitle, flStyle, 0, 0, 0, 0, 0,
                  KWND_TOP, ulId, &fcd, 0 );

    _hab = WinQueryAnchorBlock( _hwnd );

    kwndClient.CreateWindow( this, PMLITERAL(""),
                             flClientStyle,
                             0, 0, 0, 0, this, KWND_TOP, FID_CLIENT,
                             0, 0 );

    WindowFromID( FID_CLIENT, _kwndClient );

    if( *pflCreateFlags & FCF_SHELLPOSITION )
    {
        SWP swp;
        WinQueryTaskSizePos( _hab, 0, &swp );
        WinSetWindowPos( _hwnd, HWND_TOP, swp.x, swp.y, swp.cx, swp.cy,
                         SWP_MOVE | SWP_SIZE );
    }

    return true;
}

