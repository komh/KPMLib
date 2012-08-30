#define INCL_WIN
#include <os2.h>

#include "KStaticText.h"

bool KStaticText::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                                ULONG flStyle, LONG x, LONG y,
                                LONG cx, LONG cy, const KWindow* pkwndO,
                                const KWindow* pkwndS, ULONG id,
                                PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( PMLITERAL( WC_STATIC ));

    return KWindow::CreateWindow( pkwndP, pcszName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

