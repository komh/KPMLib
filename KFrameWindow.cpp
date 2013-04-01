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

#include <cstdlib>

#include "KWindow.h"
#include "KFrameWindow.h"

bool KFrameWindow::CreateStdWindow( KWindow* pkwndP, ULONG flStyle,
                                    PULONG pflCreateFlags,
                                    const string& strTitle, ULONG flClientStyle,
                                    HMODULE hmodResources, ULONG ulId,
                                    KWindow& kwndClient )
{
    FRAMECDATA fcd;

    fcd.cb            = sizeof( fcd );
    fcd.flCreateFlags = *pflCreateFlags;
    fcd.hmodResources = hmodResources;
    fcd.idResources   = ulId;

    SetClassName( WC_FRAME );
    CreateWindow( pkwndP, strTitle, flStyle, 0, 0, 0, 0, 0,
                  KWND_TOP, ulId, &fcd, 0 );

    kwndClient.CreateWindow( this, "",
                             flClientStyle,
                             0, 0, 0, 0, this, KWND_TOP, FID_CLIENT,
                             0, 0 );

    // to assign a client handle
    SetHWND( GetHWND());

    if( *pflCreateFlags & FCF_SHELLPOSITION )
    {
        SWP swp;
        QueryTaskSizePos( &swp );
        SetWindowPos( KWND_TOP, swp.x, swp.y, swp.cx, swp.cy,
                      SWP_MOVE | SWP_SIZE );
    }

    return true;
}

void KFrameWindow::SetHWND( HWND hwnd )
{
    KWindow::SetHWND( hwnd );

    WindowFromID( FID_CLIENT, _kwndClient );
    WindowFromID( FID_HORZSCROLL, _kwndHorzScroll );
    WindowFromID( FID_MENU, _kwndMenu );
    WindowFromID( FID_MINMAX, _kwndMinMax );
    WindowFromID( FID_SYSMENU, _kwndSysMenu );
    WindowFromID( FID_TITLEBAR, _kwndTitleBar );
    WindowFromID( FID_VERTSCROLL, _kwndVertScroll );
}

