#define INCL_WIN
#include <os2.h>

#include <string>

#include "KListBox.h"

bool KListBox::CreateWindow( const KWindow* pkwndP, const string& strName,
                             ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                             const KWindow* pkwndO, const KWindow* pkwndS,
                             ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( WC_LISTBOX );

    return KWindow::CreateWindow( pkwndP, strName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

