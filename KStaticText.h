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

#ifndef KSTATIC_TEXT_H
#define KSTATIC_TEXT_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KWindow.h"

class KStaticText : public KWindow
{
public :
    KStaticText() : KWindow() {};
    virtual ~KStaticText() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual HBITMAP QueryHandle() const
    {
        return LONGFROMMR( SendMsg( SM_QUERYHANDLE ));
    }

    virtual HBITMAP SetHandle( HBITMAP hbmHandle ) const
    {
        return LONGFROMMR( SendMsg( SM_SETHANDLE, MPFROMLONG( hbmHandle )));
    }

    virtual bool SetHandleP( HBITMAP hbmHandle ) const
    {
        return PostMsg( SM_SETHANDLE, MPFROMLONG( hbmHandle ));
    }
};
#endif
