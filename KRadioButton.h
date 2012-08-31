#ifndef KRADIO_BUTTON_H
#define KRADIO_BUTTON_H

#include "KButton.h"

class KRadioButton : public KButton
{
public :
    KRadioButton() : KButton() {}
    virtual ~KRadioButton() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flWindowStyle, ULONG flButtonStyle,
                               LONG x, LONG y, LONG cx, LONG cy,
                               const KWindow* pkwndO, const KWindow* pkwndS,
                               ULONG id, PVOID pCtlData = 0,
                               PVOID pPresParams = 0 );
};
#endif

