#ifndef KSCROLL_BAR_H
#define KSCROLL_BAR_H

#include "KWindow.h"

class KScrollBar : public KWindow
{
public :
    KScrollBar() : KWindow() {};
    virtual ~KScrollBar() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual LONG QueryPos() { return LONGFROMMR( SendMsg( SBM_QUERYPOS )); }
    virtual void QueryRange( LONG& lFirst, LONG& lLast )
    {
        MRESULT mr = SendMsg( SBM_QUERYRANGE );

        lFirst = SHORT1FROMMR( mr );
        lLast  = SHORT2FROMMR( mr );
    }

    virtual bool SetPos( LONG lSlider )
    { return SendMsg( SBM_SETPOS, MPFROMLONG( lSlider )); }

    virtual bool SetScrollBar( LONG lSlider, LONG lFirst, LONG lLast )
    {
        return SendMsg( SBM_SETSCROLLBAR, MPFROMLONG( lSlider ),
                        MPFROM2SHORT( lFirst, lLast ));
    }

    virtual bool SetThumbSize( LONG lVisible, LONG lTotal )
    { return SendMsg( SBM_SETTHUMBSIZE, MPFROM2SHORT( lVisible, lTotal )); }
};
#endif
