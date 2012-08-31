#ifndef KPUSH_BUTTON_H
#define KPUSH_BUTTON_H

#include "KButton.h"

class KPushButton : public KButton
{
public :
    KPushButton() : KButton() {}
    virtual ~KPushButton() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flWindowStyle, ULONG flButtonStyle,
                               LONG x, LONG y, LONG cx, LONG cy,
                               const KWindow* pkwndO, const KWindow* pkwndS,
                               ULONG id, PVOID pCtlData = 0,
                               PVOID pPresParams = 0 );
};
#endif

