#ifndef KMENU_H
#define KMENU_H

#include "KWindow.h"

class KMenu : public KWindow
{
public :
    KMenu() : KWindow() {};
    virtual ~KMenu() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
};
#endif
