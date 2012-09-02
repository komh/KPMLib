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

    virtual SHORT QueryPos() { return SHORT1FROMMR( SendMsg( SBM_QUERYPOS )); }
    virtual void QueryRange( SHORT& sFirst, SHORT& sLast )
    {
        MRESULT mr = SendMsg( SBM_QUERYRANGE );

        sFirst = SHORT1FROMMR( mr );
        sLast  = SHORT2FROMMR( mr );
    }

    virtual bool SetPos( SHORT sSlider )
    { return SendMsg( SBM_SETPOS, MPFROMSHORT( sSlider )); }

    virtual bool SetScrollBar( SHORT sSlider, SHORT sFirst, SHORT sLast )
    {
        return SendMsg( SBM_SETSCROLLBAR, MPFROMSHORT( sSlider ),
                        MPFROM2SHORT( sFirst, sLast ));
    }

    virtual bool SetThumbSize( SHORT sVisible, SHORT sTotal )
    { return SendMsg( SBM_SETTHUMBSIZE, MPFROM2SHORT( sVisible, sTotal )); }
};
#endif
