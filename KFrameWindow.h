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

#ifndef KFRAMEWINDOW_H
#define KFRAMEWINDOW_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KWindow.h"
#include "KScrollBar.h"
#include "KMenu.h"
#include "KTitleBar.h"

class KFrameWindow : public KWindow
{
public :
    KFrameWindow() : KWindow() {}
    virtual ~KFrameWindow() {}

    virtual bool CalcFrameRect( PRECTL prcl, bool fClient ) const
    {
        return WinCalcFrameRect( GetHWND(), prcl, fClient );
    }

    virtual bool CreateStdWindow( KWindow* pkwndP, ULONG flStyle,
                                  PULONG pflCreateFlags,
                                  const std::string& strTitle, 
                                  ULONG flClientStyle,
                                  HMODULE hmodResources, ULONG ulId,
                                  KWindow& kwndClient );

    virtual void SetHWND( HWND hwnd );

    const KWindow& GetClient() const { return _kwndClient; }
    const KScrollBar& GetHorzScroll() const { return _kwndHorzScroll; }
    const KMenu& GetMenu() const { return _kwndMenu; }
    const KMenu& GetMinMax() const { return _kwndMinMax; }
    const KMenu& GetSysMenu() const { return _kwndSysMenu; }
    const KTitleBar& GetTitleBar() const { return _kwndTitleBar; }
    const KScrollBar& GetVertScroll() const { return _kwndVertScroll; }

    virtual bool Activate() const
    {
        return SetWindowPos( 0, 0, 0, 0, 0, SWP_ACTIVATE );
    }

    virtual bool Deactivate() const
    {
        return SetWindowPos( 0, 0, 0, 0, 0, SWP_DEACTIVATE );
    }

private :
    KWindow    _kwndClient;
    KScrollBar _kwndHorzScroll;
    KMenu      _kwndMenu;
    KMenu      _kwndMinMax;
    KMenu      _kwndSysMenu;
    KTitleBar  _kwndTitleBar;
    KScrollBar _kwndVertScroll;
};
#endif
