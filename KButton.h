#ifndef KBUTTON_H
#define KBUTTON_H

#include "KWindow.h"

class KButton : public KWindow
{
public :
    KButton();
    virtual ~KButton();


    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
};
#endif
