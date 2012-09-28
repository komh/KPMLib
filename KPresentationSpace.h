#ifndef K_PRESENTATION_SPACE_H
#define K_PRESENTATION_SPACE_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

class KPresentationSpace
{
public :
    friend HPS pkps2hps( const KPresentationSpace* pkps );

    KPresentationSpace() : _hps( 0 ) {};
    virtual ~KPresentationSpace() {};

    virtual bool BeginPaint( const KWindow* pkwnd,
                             const KPresentationSpace* pkps,
                             PRECTL prcl )
    {
        _hps = WinBeginPaint( pkwnd2hwnd( pkwnd ), pkps2hps( pkps ), prcl );

        return _hps;
    }

    virtual LONG DrawText( LONG cchText, PCCH lpchText, PRECTL prcl,
                           LONG clrFore, LONG clrBack, ULONG flCmd )
    {
        return WinDrawText( _hps, cchText, lpchText, prcl, clrFore, clrBack,
                            flCmd );
    }

    virtual bool EndPaint() { return WinEndPaint( _hps ); }

    virtual bool FillRect( PRECTL prcl, LONG lColor )
    { return WinFillRect( _hps, prcl, lColor ); }

    virtual bool GetPS( const KWindow* pkwnd )
    {
        _hps = WinGetPS( pkwnd2hwnd( pkwnd ));

        return _hps;
    }

    virtual bool ReleasePS() { return WinReleasePS( _hps ); }

    const HPS& GetHPS() const { return _hps; }

protected :
    HPS _hps;
};
#endif
