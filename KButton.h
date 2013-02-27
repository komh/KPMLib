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

#ifndef KBUTTON_H
#define KBUTTON_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KWindow.h"

// kLIBC 0.6.5 does not have BM_AUTOSIZE
#ifndef BM_AUTOSIZE
#define BM_AUTOSIZE 0x128
#endif

class KButton : public KWindow
{
public :
    KButton() : KWindow() {};
    virtual ~KButton() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    enum CheckState { kUncheck = 0, kCheck, kIndeterminate };

    virtual bool AutoSize() { return SendMsg( BM_AUTOSIZE ); }
    virtual bool AutoSizeP() { return PostMsg( BM_AUTOSIZE ); }
    virtual void Click( bool fUp ) { SendMsg( BM_CLICK, MPFROMLONG( fUp )); }

    virtual bool ClickP( bool fUp )
    {
        return PostMsg( BM_CLICK, MPFROMLONG( fUp ));
    }

    virtual USHORT QueryCheck()
    {
        return SHORT1FROMMR( SendMsg( BM_QUERYCHECK ));
    }

    virtual SHORT QueryCheckIndex()
    {
        return SHORT1FROMMR( SendMsg( BM_QUERYCHECKINDEX ));
    }

    virtual bool QueryHilite() { return SendMsg( BM_QUERYHILITE ); }

    virtual USHORT SetCheck( USHORT usCheck )
    {
        return SHORT1FROMMR( SendMsg( BM_SETCHECK, MPFROMSHORT( usCheck )));
    }

    virtual bool SetDefault( bool fDefault )
    {
        return SendMsg( BM_SETDEFAULT, MPFROMLONG( fDefault ));
    }

    virtual bool SetDefaultP( bool fDefault )
    {
        return PostMsg( BM_SETDEFAULT, MPFROMLONG( fDefault ));
    }

    virtual bool SetHilite( bool fHilite )
    {
        return SendMsg( BM_SETHILITE, MPFROMLONG( fHilite ));
    }

    virtual bool SetHiliteP( bool fHilite )
    {
        return PostMsg( BM_SETHILITE, MPFROMLONG( fHilite ));
    }
};
#endif
