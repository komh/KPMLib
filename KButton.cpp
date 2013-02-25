#define INCL_WIN
#include <os2.h>

#include <string>

#include "KButton.h"

bool KButton::CreateWindow( const KWindow* pkwndP, const string& strName,
                            ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( WC_BUTTON );

    if( !LOUSHORT( flStyle ))
        flStyle |= BS_PUSHBUTTON;

    return KWindow::CreateWindow( pkwndP, strName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

