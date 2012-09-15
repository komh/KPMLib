#define INCL_WIN
#include <os2.h>

#include "KEntryField.h"

bool KEntryField::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                                ULONG flStyle, LONG x, LONG y,
                                LONG cx, LONG cy,
                                const KWindow* pkwndO, const KWindow* pkwndS,
                                ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( WC_ENTRYFIELD );

    return KWindow::CreateWindow( pkwndP, pcszName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

