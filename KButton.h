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

    enum CheckState { kUncheck = 0, kCheck, kIndeterminate };

    virtual bool AutoSize();
    virtual void Click( bool fUp );
    virtual CheckState QueryCheck();
    virtual int QueryCheckIndex();
    virtual bool QueryHilite();
    virtual CheckState SetCheck( CheckState bcsNew );
    virtual bool SetDefault( bool fDefault );
    virtual bool SetHilite( bool fHilite );
};
#endif
