#ifndef KTITLE_BAR_H
#define KTITLE_BAR_H

#include "KWindow.h"

class KTitleBar : public KWindow
{
public :
    KTitleBar() : KWindow() {};
    virtual ~KTitleBar() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
};
#endif
