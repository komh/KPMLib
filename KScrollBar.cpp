#define INCL_WIN
#include <os2.h>

#include "KScrollBar.h"

bool KScrollBar::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( WC_SCROLLBAR );

    return KWindow::CreateWindow( pkwndP, pcszName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

