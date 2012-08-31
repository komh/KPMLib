#ifndef K3STATE_H
#define K3STATE_H

#include "KButton.h"

class K3State : public KButton
{
public :
    K3State() : KButton() {}
    virtual ~K3State() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flWindowStyle, ULONG flButtonStyle,
                               LONG x, LONG y, LONG cx, LONG cy,
                               const KWindow* pkwndO, const KWindow* pkwndS,
                               ULONG id, PVOID pCtlData = 0,
                               PVOID pPresParams = 0 );
};
#endif

