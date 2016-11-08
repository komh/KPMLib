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

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KButton.h"

using namespace std;

bool KButton::CreateWindow( const KWindow* pkwndP, const string& strName,
                            ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( WC_BUTTON );

    if( !LOUSHORT( flStyle ))
        flStyle |= BS_PUSHBUTTON;

    return KWindow::CreateWindow( pkwndP, strName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

