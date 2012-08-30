#ifndef KSCROLL_BAR_H
#define KSCROLL_BAR_H

#include "KWindow.h"

class KScrollBar : public KWindow
{
public :
    KScrollBar() : KWindow() {};
    virtual ~KScrollBar() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
};
#endif
