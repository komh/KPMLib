#define INCL_WIN
#include <os2.h>

#include "KButton.h"

bool KButton::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                            ULONG flWindowStyle, ULONG flButtonStyle,
                            LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( PMLITERAL( WC_BUTTON ));

    if( ! flButtonStyle )
        flButtonStyle = BS_PUSHBUTTON;

    flWindowStyle |= flButtonStyle;
    return KWindow::CreateWindow( pkwndP, pcszName, flWindowStyle,
                                  x, y, cx, cy, pkwndO, pkwndS, id,
                                  pCtlData, pPresParams );
}

