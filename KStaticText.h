#ifndef KSTATIC_TEXT_H
#define KSTATIC_TEXT_H

#include "KWindow.h"

class KStaticText : public KWindow
{
public :
    KStaticText() : KWindow() {};
    virtual ~KStaticText() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
};
#endif
