#ifndef K_PRESENTATION_SPACE_H
#define K_PRESENTATION_SPACE_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

class KWindowPS
{
public :
    friend HPS pkwps2hps( const KWindowPS* pkwps );

    KWindowPS() : _hps( 0 ) {};
    virtual ~KWindowPS() {};

    virtual bool BeginPaint( const KWindow* pkwnd, const KWindowPS* pkwps,
                             PRECTL prcl )
    {
        _hps = WinBeginPaint( pkwnd2hwnd( pkwnd ), pkwps2hps( pkwps ), prcl );

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
