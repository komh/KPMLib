#ifndef KCHECK_BOX_H
#define kCHECK_BOX_H

#include "KButton.h"

class KCheckBox : public KButton
{
public :
    KCheckBox() : KButton() {}
    virtual ~KCheckBox() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flWindowStyle, ULONG flButtonStyle,
                               LONG x, LONG y, LONG cx, LONG cy,
                               const KWindow* pkwndO, const KWindow* pkwndS,
                               ULONG id, PVOID pCtlData = 0,
                               PVOID pPresParams = 0 );
};
#endif
