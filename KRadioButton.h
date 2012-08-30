#ifndef KRADIO_BUTTON_H
#define KRADIO_BUTTON_H

#include "KButton.h"

class KRadioButton : public KButton
{
public :
    KRadioButton() : KButton() {}
    virtual ~KRadioButton() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 )
    {
        return KButton::CreateWindow( pkwndP, pcszName,
                                      flStyle | BS_RADIOBUTTON,
                                      x, y, cx, cy,
                                      pkwndO, pkwndS, id,
                                      pCtlData, pPresParams );
    }
};
#endif

