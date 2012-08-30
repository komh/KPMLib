#ifndef KCHECK_BOX_H
#define kCHECK_BOX_H

#include "KButton.h"

class KCheckBox : public KButton
{
public :
    KCheckBox() : KButton() {}
    virtual ~KCheckBox() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 )
    {
        return KButton::CreateWindow( pkwndP, pcszName,
                                      flStyle | BS_CHECKBOX,
                                      x, y, cx, cy,
                                      pkwndO, pkwndS, id,
                                      pCtlData, pPresParams );
    }
};
#endif
