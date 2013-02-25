#define INCL_WIN
#include <os2.h>

#include <string>

#include "KMenu.h"

bool KMenu::CreateWindow( const KWindow* pkwndP, const string& strName,
                          ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                          const KWindow* pkwndO, const KWindow* pkwndS,
                          ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( WC_MENU );

    return KWindow::CreateWindow( pkwndP, strName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

