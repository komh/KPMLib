/*
    KPMLib, C++ encapsulation class library for OS/2 PM
    Copyright (C) 2012-2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*/

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
    {
        return WinFillRect( _hps, prcl, lColor );
    }

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
