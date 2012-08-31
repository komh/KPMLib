#define INCL_WIN
#include <os2.h>

#include "KPushButton.h"

bool KPushButton::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                                ULONG flWindowStyle, ULONG flButtonStyle,
                                LONG x, LONG y, LONG cx, LONG cy,
                                const KWindow* pkwndO, const KWindow* pkwndS,
                                ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    ULONG flPrimaryStyle = flButtonStyle & BS_PRIMARYSTYLES;

    if( flPrimaryStyle != BS_PUSHBUTTON )
        flPrimaryStyle = BS_3STATE;

    flButtonStyle |= ( flButtonStyle & ~BS_PRIMARYSTYLES ) | flPrimaryStyle;

    return KButton::CreateWindow( pkwndP, pcszName,
                                  flWindowStyle, flButtonStyle,
                                  x, y, cx, cy, pkwndO, pkwndS, id,
                                  pCtlData, pPresParams );
}

